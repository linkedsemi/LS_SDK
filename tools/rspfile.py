import sys
import re
from SCons.Subst import quote_spaces
WINPATHSEP_RE = re.compile(r"\\([^\"'\\]|$)")
def tempfile_arg_esc_func(arg):
    arg = quote_spaces(arg)
    if sys.platform != "win32":
        return arg
    # GCC requires double Windows slashes, let's use UNIX separator
    return WINPATHSEP_RE.sub(r"/\1", arg)

def link_by_rspfile(env):
    env["TEMPFILEARGESCFUNC"] = tempfile_arg_esc_func
    env['LINKCOM'] = "${TEMPFILE('%s')}" % env['LINKCOM']
