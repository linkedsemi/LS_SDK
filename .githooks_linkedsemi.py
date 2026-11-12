#!/usr/bin/env python3
# SPDX-License-Identifier: Apache-2.0
# This file runs under both `bash <name> ...` and `python3 <name> ...`:
# the line below hands the file over to python3 when a shell starts it.
''''exec python3 "$0" "$@" # '''
"""linkedsemi commit gate.

Install it by hand, once per clone. With no argument the script reports the
state and flips it (installed -> remove, not installed -> install):

    bash .githooks_linkedsemi.py              # toggle
    bash .githooks_linkedsemi.py --install
    bash .githooks_linkedsemi.py --remove
    bash .githooks_linkedsemi.py --check-range BASE..HEAD   # CI, no install

--check-range runs the same rules over every commit a range brings in, which
is what a merge request needs: the hooks only ever see one local commit.
The script writes four standalone hook files into the hooks directory of the
repository (the common git dir, so worktrees share them) and never runs by
itself: each installed hook is a full copy of this file with its hook name
pinned, so it keeps working when this file is not on disk. Every rule
lives here:

  1. only commits authored by @linkedsemi.com are checked
  2. no Chinese characters in new file names
  3. no added line mixing tabs and spaces in its indentation
  4. no added line ending with a tab or a space
  5. no added file or added last line without a trailing newline
  6. the commit message subject holds at least three English words
  7. renames with content changes, git revert, git merge (also --squash)
     and git rebase are allowed

Entry points and their hooks:

  pre-commit          git commit / git commit --amend   (skipped by --no-verify)
  commit-msg          git commit, --amend, cherry-pick  (skipped by --no-verify)
  prepare-commit-msg  git cherry-pick
  pre-applypatch      git am

  git merge (including --squash) and git rebase are not gated: they bring
  history over from elsewhere, not new work.

  git rebase is not gated: replaying commits that already sit on the branch
  is history maintenance, not new work, and rebasing onto a moving upstream
  would otherwise be blocked by every earlier commit.

The only escape hatch is the git built-in --no-verify. git cherry-pick and
git am have none of their own, so the official equivalent is
`git cherry-pick -n` or `git apply` followed by `git commit --no-verify`.

Only the python standard library is used.
"""

import os
import re
import subprocess
import sys

LINKEDSEMI_DOMAIN = "@linkedsemi.com"

MAX_REPORTED = 10
MIN_SUBJECT_WORDS = 3

WORD_PATTERN = re.compile(r"[A-Za-z][A-Za-z0-9_.'-]*")

HUNK_PATTERN = re.compile(r"^@@ -(\d+)(?:,(\d+))? \+(\d+)(?:,(\d+))? @@")

# CJK ideographs, CJK punctuation, fullwidth forms. A staged path may not
# contain any of these; file bodies are out of scope.
CJK_PATTERN = re.compile(
    "[\u2e80-\u2eff\u3000-\u303f\u3400-\u4dbf\u4e00-\u9fff"
    "\uf900-\ufaff\ufe30-\ufe4f\uff00-\uffef]")

# Marker present in $GIT_DIR when the operation must not be gated.
SKIP_MARKERS = (
    "MERGE_HEAD",     # merge conclusion
    "SQUASH_MSG",     # git merge --squash, then git commit
    "REVERT_HEAD",    # git revert -n followed by git commit
    "rebase-merge",   # git rebase -i ... edit, then git commit --amend
    "rebase-apply",   # git am / git rebase --apply
)


def fail(message):
    sys.stderr.write("error: %s\n" % message)
    return 1



def run_git(args, check=True):
    # Decode explicitly: under LC_ALL=C the locale encoding is ASCII and raw
    # UTF-8 paths would degrade to U+FFFD, silently disarming the CJK rule.
    result = subprocess.run(["git"] + args, capture_output=True, text=True,
                            encoding="utf-8", errors="replace")
    if check and result.returncode != 0:
        sys.stderr.write(result.stderr)
        sys.exit(1)
    return result



def git_dir():
    return run_git(["rev-parse", "--absolute-git-dir"]).stdout.strip()



def has_marker(name):
    return os.path.exists(os.path.join(git_dir(), name))



def is_skipped_operation():
    return any(has_marker(marker) for marker in SKIP_MARKERS)



def parse_author_script(path):
    """git am stores the patch author here before the commit exists."""
    try:
        with open(path, encoding="utf-8", errors="replace") as handle:
            content = handle.read()
    except OSError:
        return ""
    match = re.search(r"^GIT_AUTHOR_EMAIL='(.*)'$", content, re.MULTILINE)
    return match.group(1).strip().lower() if match else ""



def replayed_author_email():
    """Author of the commit that cherry-pick / am is replaying.

    `git var GIT_AUTHOR_IDENT` reports the committer in these cases, so the
    original author has to be read from the sequencer state instead."""
    if has_marker("rebase-apply"):
        recorded = parse_author_script(
            os.path.join(git_dir(), "rebase-apply", "author-script"))
        if recorded:
            return recorded
    if has_marker("CHERRY_PICK_HEAD") and not has_marker("rebase-merge"):
        recorded = run_git(
            ["show", "-s", "--format=%ae", "CHERRY_PICK_HEAD"]).stdout.strip()
        if recorded:
            return recorded.lower()
    return ""



def author_email():
    recorded = replayed_author_email()
    if recorded:
        return recorded
    ident = run_git(["var", "GIT_AUTHOR_IDENT"]).stdout.strip()
    # "Name <email> 1700000000 +0800"
    start = ident.find("<")
    end = ident.find(">", start)
    if start < 0 or end < 0:
        return ""
    return ident[start + 1:end]



def is_linkedsemi_author():
    return author_email().lower().endswith(LINKEDSEMI_DOMAIN)






def parse_name_status(output):
    """Parse `--name-status -z` output into [(status, new_path)]."""
    fields = output.split("\0")
    changes = []
    index = 0
    while index + 1 < len(fields):
        status = fields[index]
        if not status:
            break
        if status[0] in "RC" and index + 2 < len(fields):
            changes.append((status, fields[index + 2]))
            index += 3
        else:
            changes.append((status, fields[index + 1]))
            index += 2
    return changes



def staged_changes():
    """Return [(status, new_path)] for the index, with unquoted paths."""
    return parse_name_status(
        run_git(["diff", "--cached", "--name-status", "-z"]).stdout)




def staged_diff():
    """Unified diff of the index, with raw (unquoted) paths."""
    return run_git(["-c", "core.quotePath=false", "diff", "--cached",
                    "--no-color", "--no-ext-diff", "--src-prefix=a/",
                    "--dst-prefix=b/", "-U0"]).stdout



def emit(errors):
    """Print every collected violation, capped, and return the exit code."""
    for error in errors[:MAX_REPORTED]:
        sys.stderr.write("error: %s\n" % error)
    if len(errors) > MAX_REPORTED:
        sys.stderr.write("error: ... and %d more\n" % (len(errors) - MAX_REPORTED))
    return 1



def added_line_errors(diff=None):
    r"""Rules 3 to 5, one pass over the added lines of the index.

    The hunk header carries the line counts, so a hunk is consumed exactly and
    an added line whose content starts with "++ " is never mistaken for a
    "+++ " file header. The hunk stays open one line longer so that the
    "\ No newline at end of file" marker is still attributed to its file."""
    errors = []
    path = ""
    number = 0
    old_left = 0
    new_left = 0
    previous_added = False
    hunk_done = False
    in_hunk = False

    text = staged_diff() if diff is None else diff
    for line in text.split("\n"):
        if in_hunk:
            tag = line[:1]
            if tag == "\\":
                if previous_added and path:
                    errors.append("%s: file does not end with a newline" % path)
                previous_added = False
                if hunk_done:
                    in_hunk = False
                continue
            if tag in ("+", "-", " ") and not hunk_done:
                if tag == "+":
                    body = line[1:]
                    if body != body.rstrip(" \t"):
                        errors.append("%s:%d: trailing whitespace"
                                      % (path, number))
                    indent = body[:len(body) - len(body.lstrip(" \t"))]
                    # A tab indent followed by alignment spaces is normal in
                    # zephyr C: only spaces before a tab are a real mix.
                    if indent.startswith(" ") and "\t" in indent:
                        errors.append("%s:%d: mixed tabs and spaces in "
                                      "indentation" % (path, number))
                    previous_added = True
                    number += 1
                    new_left -= 1
                elif tag == "-":
                    previous_added = False
                    old_left -= 1
                else:
                    previous_added = False
                    old_left -= 1
                    number += 1
                    new_left -= 1
                if old_left <= 0 and new_left <= 0:
                    hunk_done = True
                continue
            in_hunk = False

        if line.startswith("diff --git "):
            path = ""
            number = 0
            previous_added = False
            continue
        if line.startswith("+++ "):
            header = line[4:]
            header = header[2:] if header.startswith("b/") else header
            path = "" if header == "/dev/null" else header
            continue
        match = HUNK_PATTERN.match(line)
        if match:
            number = int(match.group(3))
            old_left = int(match.group(2) or 1)
            new_left = int(match.group(4) or 1)
            previous_added = False
            hunk_done = False
            in_hunk = True

    return errors


def comments_are_stripped(lines):
    """git only drops '#' lines when it cleans up the message itself.

    With -m or -F the cleanup mode is whitespace, so a subject like
    "#42 fix the driver" is real content, not a comment."""
    markers = ("# Please enter the commit message", "# On branch ",
               "# ------------------------ >8")
    for line in lines:
        for marker in markers:
            if line.startswith(marker):
                return True
    return False



def message_subject(path):
    """First non-blank line of the message that git did not comment out."""
    try:
        with open(path, encoding="utf-8", errors="replace") as handle:
            lines = handle.read().split("\n")
    except OSError:
        return ""

    strip_comments = comments_are_stripped(lines)
    for line in lines:
        if line.startswith("------------------------ >8"):
            break
        if strip_comments and line.startswith("#"):
            continue
        if line.strip():
            return line.strip()
    return ""



def subject_errors(subject):
    """Rule 7: the subject needs enough english words."""
    words = WORD_PATTERN.findall(subject)
    if len(words) >= MIN_SUBJECT_WORDS:
        return []
    return ["the commit message needs at least %d english words, got %d: %s"
            % (MIN_SUBJECT_WORDS, len(words), subject or "<empty>")]


def check_message(path):
    """Rule 7 on a message file, for the commit-msg hook."""
    if is_skipped_operation():
        return 0

    errors = subject_errors(message_subject(path))
    if not errors:
        return 0
    return emit(errors)



def content_errors(changes, diff_text):
    """Rules 2 to 5 for one set of changes. Every violation is reported."""
    errors = []

    chinese = [path for status, path in changes
               if status[0] != "D" and CJK_PATTERN.search(path)]
    if chinese:
        errors.append("chinese characters are not allowed in file names: %s"
                      % ", ".join(chinese))

    errors.extend(added_line_errors(diff_text))


    return errors


def check_staged():
    """Rules 1 to 5 on the index. Every violation is reported in one run."""
    changes = staged_changes()
    if not changes:
        return 0

    errors = content_errors(changes, staged_diff())
    if not errors:
        return 0
    return emit(errors)


def commit_short(sha):
    return run_git(["rev-parse", "--short", sha]).stdout.strip()


def commit_author(sha):
    return run_git(["show", "-s", "--format=%ae", sha]).stdout.strip().lower()


def commit_subject(sha):
    return run_git(["show", "-s", "--format=%s", sha]).stdout.strip()


def commit_changes(sha):
    return parse_name_status(
        run_git(["diff-tree", "--no-commit-id", "--root", "-r", "--name-status",
                 "-z", sha]).stdout)


def commit_diff(sha):
    return run_git(["show", "--format=", "--patch", "--no-color",
                    "--no-ext-diff", "--src-prefix=a/", "--dst-prefix=b/",
                    "-U0", "--root", sha]).stdout


def range_commits(spec):
    """Every non-merge commit of BASE..HEAD, oldest first."""
    base = spec
    head = "HEAD"
    if ".." in spec:
        base, _, head = spec.partition("..")
        head = head or "HEAD"
    output = run_git(["rev-list", "--no-merges", "--reverse",
                      "%s..%s" % (base, head)]).stdout
    return [line for line in output.split("\n") if line]


def check_range(spec):
    """The same rules over every commit a merge request would bring in.

    Used by CI: the hooks only see a local commit, a merge request brings a
    whole range, and unreviewed commits can arrive from any clone."""
    if not spec:
        return fail("--check-range needs BASE..HEAD or CI_MERGE_REQUEST_DIFF_BASE_SHA")

    commits = range_commits(spec)
    errors = []
    checked = 0
    for sha in commits:
        if not commit_author(sha).endswith(LINKEDSEMI_DOMAIN):
            continue
        checked += 1
        short = commit_short(sha)
        found = content_errors(commit_changes(sha), commit_diff(sha))
        found.extend(subject_errors(commit_subject(sha)))
        errors.extend("%s: %s" % (short, item) for item in found)

    if errors:
        return emit(errors)

    sys.stdout.write("%d of %d commit(s) in %s checked, no violation\n"
                     % (checked, len(commits), spec))
    return 0


SHIM_MARKER = "linkedsemi commit gate"
# Written by earlier revisions; hooks still carry it and must stay recognisable
# so that --install replaces them and --remove deletes them.
OLD_MARKERS = ("LinkedSemi commit gate",)
SHIM_NAMES = ("pre-commit", "commit-msg", "prepare-commit-msg",
              "pre-applypatch")
# No longer installed, but older checkouts installed it: remove it so a rebase
# is not refused by a stale hook.
LEGACY_NAMES = ("pre-rebase",)

HOOK_NAME = ""

# The script name appears in the messages only; the installed hooks carry a
# full copy, so a rename here needs no other change.
SELF_NAME = ".githooks_linkedsemi.py"


def hooks_dir():
    """The directory git actually reads hooks from, absolute."""
    result = run_git(["rev-parse", "--path-format=absolute", "--git-path",
                      "hooks"], check=False)
    if result.returncode == 0 and result.stdout.strip():
        return result.stdout.strip()

    common = run_git(["rev-parse", "--git-common-dir"], check=False).stdout.strip()
    if not common:
        return ""
    if not os.path.isabs(common):
        common = os.path.join(
            run_git(["rev-parse", "--show-toplevel"], check=False).stdout.strip(),
            common)
    return os.path.join(os.path.normpath(common), "hooks")


def common_hooks_dir():
    common = run_git(["rev-parse", "--path-format=absolute",
                      "--git-common-dir"], check=False).stdout.strip()
    if not common:
        return ""
    return os.path.join(os.path.normpath(common), "hooks")


def is_our_hook(path):
    try:
        with open(path, encoding="utf-8", errors="replace") as handle:
            text = handle.read()
    except OSError:
        return False
    return any(marker in text for marker in (SHIM_MARKER,) + OLD_MARKERS)


def hook_source(hook):
    """A standalone hook file: this whole script with the hook name pinned.

    The installed hook never calls back into this script, so it keeps working
    when the file is missing: during a rebase onto an older branch, in a build
    tree that only checked out part of the history, or after the file moved."""
    with open(os.path.abspath(__file__), encoding="utf-8") as handle:
        source = handle.read()
    pinned = 'HOOK_NAME = "%s"' % hook
    if 'HOOK_NAME = ""' not in source:
        return ""
    source = source.replace('HOOK_NAME = ""', pinned, 1)
    header = ("# %s marker for %s, written by %s --install.\n"
              "# Do not edit: run 'bash %s --install' again.\n"
              % (SHIM_MARKER, hook, SELF_NAME, SELF_NAME))
    lines = source.split("\n")
    return "\n".join(lines[:2] + [header.rstrip("\n")] + lines[2:])


def install_verbose():
    target = hooks_dir()
    if not target:
        return fail("not inside a git working tree")

    if target.rstrip("/") != common_hooks_dir().rstrip("/"):
        return fail("core.hooksPath points at %s, so git would ignore the "
                    "hooks in %s. run 'git config --unset core.hooksPath' "
                    "first" % (target, common_hooks_dir()))

    try:
        os.makedirs(target, exist_ok=True)
    except OSError as error:
        return fail("cannot create %s: %s" % (target, error))

    for hook in LEGACY_NAMES:
        path = os.path.join(target, hook)
        if os.path.exists(path) and is_our_hook(path):
            try:
                os.unlink(path)
            except OSError as error:
                return fail("cannot remove %s: %s" % (path, error))
            sys.stdout.write("removed the obsolete %s\n" % path)

    installed = 0
    for hook in SHIM_NAMES:
        path = os.path.join(target, hook)
        if os.path.exists(path) and not is_our_hook(path):
            sys.stdout.write("keeping local %s\n" % path)
            continue
        try:
            with open(path, "w", encoding="utf-8", newline="\n") as handle:
                handle.write(hook_source(hook))
            os.chmod(path, 0o755)
        except OSError as error:
            return fail("cannot write %s: %s" % (path, error))
        sys.stdout.write("installed %s\n" % path)
        installed += 1

    sys.stdout.write("%d hook(s) installed in %s\n" % (installed, target))
    sys.stdout.write("remove them with: bash %s --remove\n" % SELF_NAME)
    return 0


def uninstall():
    target = hooks_dir()
    if not target or not os.path.isdir(target):
        sys.stdout.write("nothing to remove\n")
        return 0

    removed = 0
    for hook in SHIM_NAMES + LEGACY_NAMES:
        path = os.path.join(target, hook)
        if not os.path.exists(path) or not is_our_hook(path):
            continue
        try:
            os.unlink(path)
        except OSError as error:
            return fail("cannot remove %s: %s" % (path, error))
        sys.stdout.write("removed %s\n" % path)
        removed += 1

    if removed == 0:
        sys.stdout.write("nothing to remove in %s\n" % target)
        return 0

    sys.stdout.write("%d hook(s) removed from %s\n" % (removed, target))
    return 0


def usage():
    sys.stdout.write(
        "usage: bash %s             install, or remove when installed\n"
        "       bash %s --install   install the commit gate\n"
        "       bash %s --remove    remove the commit gate\n"
        "       bash %s --check-range BASE..HEAD   check commits, for CI\n"
        "default BASE for --check-range: CI_MERGE_REQUEST_DIFF_BASE_SHA\n"
        % (SELF_NAME, SELF_NAME, SELF_NAME, SELF_NAME))


def all_installed():
    target = hooks_dir()
    if not target:
        return False
    for hook in SHIM_NAMES:
        path = os.path.join(target, hook)
        if not os.path.exists(path) or not is_our_hook(path):
            return False
    return True


def toggle():
    """No option: report the state and flip it."""
    target = hooks_dir()
    if not target:
        return fail("not inside a git working tree")

    if all_installed():
        sys.stdout.write("the commit gate is installed, removing it\n")
        return uninstall()

    sys.stdout.write("the commit gate is not installed, installing it\n")
    return install_verbose()


def command(argv):
    option = argv[0] if argv else ""
    if option in ("--install", "-i"):
        return install_verbose()
    if option in ("--remove", "-r"):
        return uninstall()
    if option == "--check-range":
        spec = argv[1] if len(argv) > 1 else os.environ.get(
            "CI_MERGE_REQUEST_DIFF_BASE_SHA", "")
        if spec and ".." not in spec:
            spec = "%s..HEAD" % spec
        return check_range(spec)
    if option == "":
        return toggle()
    if option in ("--help", "-h"):
        usage()
        return 0
    sys.stderr.write("error: unknown option %s\n" % option)
    usage()
    return 2


def run_hook(hook, args):
    if not is_linkedsemi_author():
        return 0

    if hook == "pre-commit":
        if is_skipped_operation():
            return 0
        return check_staged()

    if hook == "prepare-commit-msg":
        # A rebase replays commits through the cherry-pick machinery, so
        # CHERRY_PICK_HEAD is set there too. Steps inside a rebase cannot be
        # vetoed here anyway (squash and fixup ignore the exit status), and
        # the replayed commits are already on the branch, so leave rebase
        # alone and gate only a standalone cherry-pick.
        if has_marker("rebase-merge") or has_marker("rebase-apply"):
            return 0
        if not has_marker("CHERRY_PICK_HEAD"):
            return 0
        if check_staged() != 0:
            return 1
        # cherry-pick runs no commit-msg hook, so rule 6 lives here too.
        return check_message(args[0] if args else "")

    if hook == "commit-msg":
        return check_message(args[0] if args else "")

    if hook == "pre-applypatch":
        return check_staged()

    return fail("internal error: unknown hook %s" % hook)


def main(argv):
    rest = argv[1:]
    if rest and rest[0] in ("--install", "-i", "--remove", "-r",
                            "--help", "-h", "--check-range"):
        return command(rest)
    if HOOK_NAME:
        return run_hook(HOOK_NAME, rest)
    if rest and rest[0] in SHIM_NAMES:
        return run_hook(rest[0], rest[1:])
    return command(rest)


if __name__ == "__main__":
    sys.exit(main(sys.argv))
