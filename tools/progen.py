import SCons.Tool
import SCons.Builder
import xml.etree.ElementTree
import os
import shutil
from project_generator.project import ProjectTemplate
from project_generator.project import Project
from project_generator.settings import ProjectSettings

def progen(target,source,env):
    project_data = {'common': {}}
    project_data['common'] = ProjectTemplate.get_project_template()
    project_data['common']['target'] = env['CPU']
    name = os.path.basename(target[0].path)
    project_data['common']['name'] = name
    if env['IDE'] == 'uvision5':
        project_data['common']['build_dir'] = 'UVBuild'
    project_data['common']['includes'] = list(map(lambda x: os.path.relpath(x.abspath),env.Dir(env['CPPPATH'])))
    project_data['common']['sources'] = {}
    sources = list(map(lambda x:(os.path.relpath(x.srcnode().path,env['SDK_ROOT'].abspath).split(os.sep)[0],os.path.relpath(x.srcnode().path)),source))
    for src in sources:
        if project_data['common']['sources'].get(src[0]) is None:
            project_data['common']['sources'][src[0]] = []
        project_data['common']['sources'][src[0]] += [src[1]]
    project_data['common']['sources']['libs'] = []

    if 'LIBS' in  env:
        for lib in env['LIBS']:
            project_data['common']['sources']['libs'] += [os.path.relpath(lib.srcnode().abspath)]
    project_data['common']['macros'] = env['CPPDEFINES']
    project_data['common']['linker_file'] = os.path.relpath(env['LINKSCRIPT'].srcnode().abspath)
    project_data['tool_specific'] = {
        'uvision5':{'misc':{
                        'ld_flags':['--datacompressor=off','--diag_suppress=L6314,L6329']
                    },
                    'template': env['SDK_ROOT'].abspath+'/tools/'+env['IC']+'/uvision.uvproj',
        }
    }
    project_settings = ProjectSettings()
    project_settings.update({
        'export_dir':[os.path.join(env['IC'],env['IDE'])]
    })
    project = Project(name,[project_data],project_settings)

    project.generate(env['IDE'])
    if env['IDE'] == 'uvision5' and env['IC'] == 'le501x':
        file = os.path.join(os.path.join(env['IC'],env['IDE']),"{}.uvprojx".format(name))
        et = xml.etree.ElementTree.parse(file)
        user_action1 = et.getroot().find('Targets').find('Target').find('TargetOption').find('TargetCommonOption').find('AfterMake').find('UserProg1Name')
        root_relpath = os.path.relpath(env['SDK_ROOT'].abspath,os.path.join(os.path.join(env['IC'],env['IDE'])))
        if env.get('STACK_HEX') is None:
            stack_path = ''
        else:
            stack_path = os.path.relpath(env['STACK_HEX'].srcnode().abspath,env['SDK_ROOT'].abspath)
        user_action1.text = "{} @L {} {} {}".format(root_relpath +'\\tools\\'+env['IC']+'\\after_build.bat',root_relpath,env['APP_IMAGE_BASE'],stack_path)
        et.write(file,xml_declaration=True,short_empty_elements=False)
        shutil.copy(env['SDK_ROOT'].abspath+'/tools/prog/LinkedSemi/LE501X.jlinkscript',os.path.join(os.path.join(env['IC'],env['IDE']),"JLinkSettings.jlinkscript"))

def generate(env):
    env['BUILDERS']['Program'] = SCons.Builder.Builder(action = progen)
    SCons.Tool.createProgBuilder(env)

def exists(env):
    return True