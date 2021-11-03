import sys
import re
asm_file = open(sys.argv[1])
ram_code_data_base = int(sys.argv[2],16)
ram_code_data_limit = int(sys.argv[3],16)
asm_lines = asm_file.readlines()


call_pattern = re.compile('(\w+):.+[,| ](\w+) <(\w+)>\n')
for line in asm_lines:
    call_match = call_pattern.search(line)
    if(call_match):
        line_pos = int(call_match.group(1),16)
        func_pos = int(call_match.group(2),16)
        if(line_pos>=ram_code_data_base and line_pos <ram_code_data_limit 
            and (func_pos<ram_code_data_base or func_pos> ram_code_data_limit)):
            print(line)
           
            
print("Finished.")