import SCons.Tool
import SCons.Builder
import xml.etree.ElementTree
import os
import shutil
import copy
from project_generator.project import ProjectTemplate
from project_generator.project import Project
from project_generator.settings import ProjectSettings

def uvision5_misc_flags(ic):
    if ic == 'le501x':
        return {
                        'c_flags':['--diag_suppress=1,61,66,68,188,1295,1296'],
                        'asm_flags':['--diag_suppress=1'],
                        'ld_flags':['--datacompressor=off','--diag_suppress=L6314,L6329']
                }
    else:
        return {
                        'c_flags':['-Wno-pointer-bool-conversion'],
                        'asm_flags':[''],
                        'ld_flags':['--datacompressor=off','--diag_suppress=L6314,L6329']
                }

def progen(target,source,env):
    project_data = {'common': {}}
    project_data['common'] = ProjectTemplate.get_project_template()
    project_data['common']['target'] = env['CPU']
    name = os.path.basename(target[0].path)
    project_data['common']['name'] = name
    project_dir_path = os.path.join(env['IC'],env['IDE'])
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

    if 'LIBS' in env:
        for lib in env['LIBS']:
            if type(lib) != str:
                project_data['common']['sources']['libs'] += [os.path.relpath(lib.srcnode().abspath)]
    project_data['common']['macros'] = env['CPPDEFINES']
    project_data['common']['linker_file'] = os.path.relpath(env['LINKSCRIPT'].srcnode().abspath)
    root_relpath = os.path.relpath(env['SDK_ROOT'].abspath,os.path.join(os.path.join(env['IC'],env['IDE'])))
    uvision5_cfg = {'misc': uvision5_misc_flags(env['IC']),
                    'template': env['SDK_ROOT'].abspath+'/tools/uvision.uvproj'}
    project_data['tool_specific'] = {
        'uvision5': uvision5_cfg,
        'uvision5_armc6': uvision5_cfg,
        'iar':{'misc':{
                    'c_flags':['--diag_suppress=Pa082,Pe188,Pa089,Pe068,Pa039,Pa131,Pe111','--warnings_are_errors'],
                    'ld_flags':['--diag_suppress=Lt009','--warnings_are_errors','--config_search {}'.format(os.path.join(root_relpath,'soc/arm_cm/'+env['IC']+'/compiler/'+env['IDE']))]

            },
            'template': env['SDK_ROOT'].abspath+'/tools/iar.ewp',}
    }
    if env['IC'] == 'lm3050':
        project_data['common']['target'] = 'cortex-m4-fpu'
        project_data['common']['sources']['soc'] += [os.path.relpath(os.path.join(env['SDK_ROOT'].abspath,'soc/arm_cm',str(env['IC']),'__info_array.c'),os.getcwd())]
        if env['IDE'] == 'uvision5':
            project_data['tool_specific']['uvision5']['misc']['ld_flags'].append(os.path.join(root_relpath,'soc/arm_cm',str(env['IC']),'compiler/armcc/rom_sym.txt'))
        elif env['IDE'] == 'iar':
            project_data['common']['target'] = 'arch-max' 
            project_data['tool_specific']['iar']['template'] = ''
    elif env['IC'] == 'le501x':
        if env['IDE'] == 'iar':
            project_data['common']['target'] = 'nucleo-f091rc' 
            project_data['tool_specific']['iar']['template'] = ''
    
    project_settings = ProjectSettings()
    project_settings.update({'export_dir':[project_dir_path]})
    project = Project(name,[project_data],project_settings)
    if env['IC'] != 'le501x' and env['IDE'] == 'uvision5':
        project.generate('uvision5_armc6')
    else:
        project.generate(env['IDE'])
    if env.get('STACK_HEX') is None:
        stack_path = ''
    else:
        stack_path = os.path.relpath(env['STACK_HEX'].srcnode().abspath,env['SDK_ROOT'].abspath)

    if env['IDE'] == 'uvision5':
        file = os.path.join(project_dir_path,"{}.uvprojx".format(name))
        et = xml.etree.ElementTree.parse(file)
        if env['IC'] == 'le501x':
            uAC6 = et.getroot().find('Targets').find('Target').find('uAC6')
            uAC6.text = "0"
            user_action1 = et.getroot().find('Targets').find('Target').find('TargetOption').find('TargetCommonOption').find('AfterMake').find('UserProg1Name')
            info_sbl_xml = os.path.join(env['SDK_ROOT'].abspath,'tools/le501x/hex_target.xml')
            info_sbl_et = xml.etree.ElementTree.parse(info_sbl_xml)
            et.getroot().find('Targets').append(info_sbl_et.getroot())
            if not env.get('STACK_HEX') is None:
                stack_hex_et = copy.deepcopy(info_sbl_et)
                outdir = stack_hex_et.getroot().find('TargetOption').find('TargetCommonOption').find('OutputDirectory')
                listdir = stack_hex_et.getroot().find('TargetOption').find('TargetCommonOption').find('ListingPath')
                listdir.text = outdir.text = os.path.relpath(os.path.dirname(env['STACK_HEX'].srcnode().abspath),os.path.join(env['IC'],env['IDE'])) + '\\'
                stack_file_name = os.path.basename(env['STACK_HEX'].srcnode().abspath)
                target_name = stack_hex_et.getroot().find('TargetName')
                output_name = stack_hex_et.getroot().find('TargetOption').find('TargetCommonOption').find('OutputName')
                target_name.text = output_name.text = stack_file_name
                et.getroot().find('Targets').append(stack_hex_et.getroot())
            user_action1.text = "{} @L {} {} {}".format(root_relpath +'\\tools\\'+env['IC']+'\\after_build.bat',root_relpath,env['APP_IMAGE_BASE'],stack_path)
            shutil.copy(env['SDK_ROOT'].abspath+'/tools/prog/LinkedSemi/LE501X.jlinkscript',os.path.join(os.path.join(env['IC'],env['IDE']),"JLinkSettings.jlinkscript"))

            note_replace_text = et.getroot().find('Targets').find('Target').find('TargetOption').find('TargetCommonOption').find('Device')
            note_replace_text.text = 'LE501X'
            note_replace_text = et.getroot().find('Targets').find('Target').find('TargetOption').find('TargetCommonOption').find('Vendor')
            note_replace_text.text = 'Linkedsemi'
            note_replace_text = et.getroot().find('Targets').find('Target').find('TargetOption').find('TargetCommonOption').find('PackID')
            note_replace_text.text = 'Linkedsemi.DFP.1.0.0'
            note_replace_text = et.getroot().find('Targets').find('Target').find('TargetOption').find('TargetCommonOption').find('PackURL')
            note_replace_text.text = 'https://www.linkedsemi.com/'
            note_replace_text = et.getroot().find('Targets').find('Target').find('TargetOption').find('TargetCommonOption').find('Cpu')
            note_replace_text.text = 'IROM(0x18000000,0x00080000) IRAM(0x20000000,0x00001000) CPUTYPE("Cortex-M0") CLOCK(12000000) ESEL ELITTLE'
            note_replace_text = et.getroot().find('Targets').find('Target').find('TargetOption').find('TargetCommonOption').find('RegisterFile')
            note_replace_text.text = '$$Device:LE501X$Device\ARM\ARMCM0\Include\ARMCM0.h'
            note_replace_text = et.getroot().find('Targets').find('Target').find('TargetOption').find('TargetCommonOption').find('SFDFile')
            note_replace_text.text = '$$Device:LE501X$SVD\ARMCM0.svd'

        elif env['IC'] == 'lm3050':
            # before_make = et.getroot().find('Targets').find('Target').find('TargetOption').find('TargetCommonOption').find('BeforeMake').find('UserProg1Name')
            # before_make.text = root_relpath +'\\tools\\'+env['IC']+'\\before_make.bat ' + root_relpath
            
            note_replace_text = et.getroot().find('Targets').find('Target').find('TargetOption').find('TargetCommonOption').find('Device')
            note_replace_text.text = 'LM3050'
            note_replace_text = et.getroot().find('Targets').find('Target').find('TargetOption').find('TargetCommonOption').find('Vendor')
            note_replace_text.text = 'Linkedsemi'
            note_replace_text = et.getroot().find('Targets').find('Target').find('TargetOption').find('TargetCommonOption').find('PackID')
            note_replace_text.text = 'Linkedsemi.DFP.1.0.0'
            note_replace_text = et.getroot().find('Targets').find('Target').find('TargetOption').find('TargetCommonOption').find('PackURL')
            note_replace_text.text = 'https://www.linkedsemi.com/'
            note_replace_text = et.getroot().find('Targets').find('Target').find('TargetOption').find('TargetCommonOption').find('Cpu')
            note_replace_text.text = 'IROM(0x00800000,0x00100000) IRAM(0x20001000,0x00001000) CPUTYPE("Cortex-M4") FPU2 CLOCK(12000000) ESEL ELITTLE'
            note_replace_text = et.getroot().find('Targets').find('Target').find('TargetOption').find('TargetCommonOption').find('RegisterFile')
            note_replace_text.text = '$$Device:LM3050$Device\ARM\ARMCM4\Include\ARMCM4_FP.h'
            note_replace_text = et.getroot().find('Targets').find('Target').find('TargetOption').find('TargetCommonOption').find('SFDFile')
            note_replace_text.text = '$$Device:LM3050$SVD\ARMCM4.svd'
    elif env['IDE'] == 'iar':
        file = os.path.join(project_dir_path,"{}.ewp".format(name))
        et = xml.etree.ElementTree.parse(file)
        for setting in et.getroot().find('configuration').findall('settings'):
            if setting.find('name').text == 'BUILDACTION':
                if env['IC'] == 'le501x':
                    setting.find('data').find('postbuild').text = "{} {} {} {} $PROJ_DIR$ {}".format('$PROJ_DIR$\\'+root_relpath +'\\tools\\'+env['IC']+'\\postbuild_iar.bat',name,'$PROJ_DIR$\\'+root_relpath,env['APP_IMAGE_BASE'],stack_path)
                if env['IC'] == 'lm3050':
                    pass
                    # setting.find('data').find('prebuild').text = '{} {} {}'.format('$PROJ_DIR$\\'+root_relpath +'\\tools\\'+env['IC']+'\\prebuild_iar.bat','$PROJ_DIR$\\'+root_relpath,'$PROJ_DIR$')
            if setting.find('name').text == 'ILINK':
                for opt in setting.find('data').findall('option'):
                    if opt.find('name').text == 'IlinkOutputFile':
                        opt.find('state').text = name + '.out'
            if setting.find('name').text == 'OBJCOPY':
                for opt in setting.find('data').findall('option'):
                    if opt.find('name').text == 'OOCOutputFormat':
                        opt.find('state').text = '1'
                    elif opt.find('name').text == 'OCOutputOverride':
                        opt.find('state').text = '1'    
                    elif opt.find('name').text == 'OOCOutputFile':
                        opt.find('state').text = os.path.basename(target[0].path) + '.hex'
            if env['IC'] == 'lm3050':
                if setting.find('name').text == 'General':
                    for opt in setting.find('data').findall('option'):
                        if opt.find('name').text == 'OGChipSelectEditMenu' or opt.find('name').text == 'GFPUDeviceSlave':
                            opt.find('state').text = 'LM3050	Linkedsemi LM3050'
                        if opt.find('name').text == 'GRuntimeLibSelect':
                            opt.find('state').text = '1'    #Library:Normal
                        if opt.find('name').text == 'GRuntimeLibSelectSlave':
                            opt.find('state').text = '1'          
            elif env['IC'] == 'le501x':
                if setting.find('name').text == 'General':
                    for opt in setting.find('data').findall('option'):
                        if opt.find('name').text == 'OGChipSelectEditMenu' or opt.find('name').text == 'GFPUDeviceSlave':
                            opt.find('state').text = 'LE501X	Linkedsemi LE501X'
                        if opt.find('name').text == 'GRuntimeLibSelect':
                            opt.find('state').text = '1'    #Library:Normal
                        if opt.find('name').text == 'GRuntimeLibSelectSlave':
                            opt.find('state').text = '1'
            if setting.find('name').text == 'ICCARM':
                for opt in setting.find('data').findall('option'):
                    if opt.find('name').text == 'IccAllowVLA':
                        opt.find('state').text = '1'                    
                    if opt.find('name').text == 'IccLang':
                        opt.find('state').text = '0'

    et.write(file,xml_declaration=True,short_empty_elements=False)

def generate(env):
    env['BUILDERS']['Program'] = SCons.Builder.Builder(action = progen)
    SCons.Tool.createProgBuilder(env)

def exists(env):
    return True