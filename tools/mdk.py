import mdk_xml_schema
import pyxb
import os
import SCons.Tool
import SCons.Builder
import subprocess
import shutil

def mdk_builder(target,source,env):
    prj_dir = os.path.join(env['PROJ_DIR'].srcnode().abspath,'mdk')
    proj_path = os.path.join(prj_dir,os.path.basename(target[0].path)+'.uvprojx')
    operation = env.get('OPERATION','proj_gen')
    if operation == 'build':
        proj_log = os.path.join(os.path.join(prj_dir,'UVBuild'),os.path.basename(target[0].path)+'.txt')
        proj_build = env['UV'] + ' -b "' + proj_path + '" -o "' + proj_log + '" -j0'
        complete = subprocess.run(proj_build,shell=True)
        subprocess.run('type "'+proj_log+'"',shell=True)
        return complete.returncode

    prj = mdk_xml_schema.Project()
    prj.ToolsetName = 'ARM'
    prj.Device = 'ARMCM0'
    prj.useUlib = 1
    if os.path.exists(prj_dir)==False:
        os.mkdir(prj_dir)
    jlink_script_src_dir = os.path.join(env.Dir('.').abspath,'tools\\prog\\LinkedSemi\\LE501X.jlinkscript')
    jlink_script_dst_dir = os.path.join(prj_dir, 'JLinkSettings.jlinkscript')

#    print(jlink_script_src_dir)
#    print(jlink_script_dst_dir)
    try:
        shutil.copy(jlink_script_src_dir, jlink_script_dst_dir)
    except IOError as e:
        print("Unable to copy jlink script file")
    except:
        print("Unexpected error:", sys.exc_info())
    
    inc_path_str = ""
    for node_path in env.Dir(env['CPPPATH']):
        inc_path_str = inc_path_str + os.path.relpath(node_path.abspath, prj_dir) + ";"
    prj.IncludePath = inc_path_str
    
    scat_file_str = os.path.relpath((env['LINKSCRIPT']).srcnode().abspath, prj_dir)
    prj.ScatterFile = scat_file_str
    
    prj.CDefines = " ".join(env['CPPDEFINES']).replace('-D','')
    prj.COptions = "--c99 -O2 " 
    prj.LinkOptions = " --datacompressor=off --diag_suppress=L6314,L6329 "
    beforecompile1 = mdk_xml_schema.UserAction('')
    beforecompile2 = mdk_xml_schema.UserAction('')
    beforebuild1 = mdk_xml_schema.UserAction('')
    beforebuild2 = mdk_xml_schema.UserAction('')
    if env.get('STACK_HEX_PATH') is None:
        afterbuild1 = mdk_xml_schema.UserAction(os.path.relpath(env.Dir("#").abspath, prj_dir) + '\\tools\\le501x\\after_build.bat @L ' + os.path.relpath(env.Dir("#").abspath, prj_dir))
    else:
        afterbuild1 = mdk_xml_schema.UserAction(os.path.relpath(env.Dir("#").abspath, prj_dir) + '\\tools\\le501x\\after_build.bat @L ' + os.path.relpath(env.Dir("#").abspath, prj_dir) + ' ' + env['STACK_HEX_PATH'])
    afterbuild2 = mdk_xml_schema.UserAction('')
    prj.User = pyxb.BIND(BeforeCompile1=beforecompile1,BeforeCompile2=beforecompile2,BeforeBuild1=beforebuild1,BeforeBuild2=beforebuild2,AfterBuild1=afterbuild1,AfterBuild2=afterbuild2)
    
    #c_list = []
    #asm_list = []
    obj_list = []
    lib_list = []
    all_file_list = []
    for build_src in source:
        src = build_src.srcnode().path
        filepath,extension = os.path.splitext(src)
        all_file_list.append(os.path.relpath(src,prj_dir))
        if extension != '.c' and extension != '.C' and extension != '.s' and extension != '.S':
            obj_list.append(os.path.relpath(src,prj_dir))
    if 'LIBS' in env:
        for lib in env['LIBS']:
            libpath,libext = os.path.splitext(lib.path)
            all_file_list.append(os.path.relpath(lib.path,prj_dir))
            if libext == '.o':
                obj_list.append(os.path.relpath(lib.path,prj_dir))
            else:
                lib_list.append(os.path.relpath(lib.path,prj_dir))

    group_name_list = []
    group_file_list = []
    group_build_file_list = []
    app_file_list = []
    for file_x in all_file_list:
        count = file_x.count("..\\")
        if count == 1:
            app_file_list.append(file_x)
        else:
            group_name = file_x.replace("..\\", "").split('\\')[0]
            group_name = group_name.split('.')[0]
            if group_name in group_name_list:
                index = group_name_list.index(group_name)
                group_file_list[index].append(file_x)
            else:
                group_name_list.append(group_name)
                temp_file_list = []
                temp_file_list.append(file_x)
                group_file_list.append(temp_file_list)
        
    group_list = []
    
    for group_name in group_name_list:
        index = group_name_list.index(group_name)
        group_build_file_list.append(new_file_list_build(group_file_list[index]))
        group_list.append(pyxb.BIND(group_name, pyxb.BIND(*group_build_file_list[index])))
        
    group_list.append(pyxb.BIND("app", pyxb.BIND(*new_file_list_build(app_file_list))))
    prj.Groups = pyxb.BIND(*group_list)
    
    filename = target[0].abspath + '.xml'
    with open(filename,'wb') as file_obj:
        file_obj.write(prj.toxml("utf-8"))

    #print(os.path.isfile(os.path.join(prj_dir,os.path.basename(target[0].path)+'.uvprojx')))
    if os.path.isfile(os.path.join(prj_dir,os.path.basename(target[0].path)+'.uvprojx'))==True:
        os.remove(os.path.join(prj_dir,os.path.basename(target[0].path)+'.uvprojx'))
    if os.path.isfile(os.path.join(prj_dir,os.path.basename(target[0].path)+'.uvoptx'))==True:
        os.remove(os.path.join(prj_dir,os.path.basename(target[0].path)+'.uvoptx'))    
    
    proj_gen = env['UV'] + ' ' + proj_path + ' -i ' + filename
    complete = subprocess.run(proj_gen,shell=True)
    return complete.returncode

def generate(env):
    env['BUILDERS']['Program'] = SCons.Builder.Builder(action = mdk_builder)
    env['UV'] = 'C:/Keil_v5/UV4/UV4.exe'
    SCons.Tool.createProgBuilder(env)
    
def exists(env):
    return True

def new_file_list_build(source_list):
    file_list = []
    file_type = 1
    for build_src in source_list:
        file_name,dot,extension = build_src.rpartition(".")
        #print(file_name,dot,extension)
        path, slash, file_name = file_name.rpartition("\\")
        if extension == 'c' or extension == 'C':
            file_type = 1
        elif extension == 's' or extension == 'S':
            file_type = 2
        else:
            file_type = 3
        file_list.append(pyxb.BIND(file_name+'.'+extension, file_type , build_src))
    return file_list
 