#encode=utf-8
"""
Preprocessing test code, including
1. Add type specify for (local) identifier definition;

"""
from auto_indent import indent
	
import sys, os
import re

incline_functions = [
    'click',
    'clickLink',
    'clickSwitchlabel',
    'expectToSee',
    'expectNotToSee',
    'expectToSeeLinktext',
    'expectNotToSeeLinktext',
    'feedTextBox',
    'selectDropBox',
    'login',
    'logout'
]

key_words = [
    'for',
    'if',
    'else',
    'function'
]

def check_identifier_def(line_no, stmt, identifier_list):
    """
    :param line_no: number of line
    :param stmt: statement to check
    :param identifier_list: identifier list in current zone
    :return: int 
        0: not identifier definition
        1: single identifier definition
        2: list identifier definition
    """
    if stmt.lstrip().startswith('//'):
        return 0
    pattern = re.compile(r'for(\ )*\((.*)\)')
    match = pattern.search(stmt.lstrip().rstrip())
    if match:
        return 0
    if not '=' in stmt:
        return 0
    if ('==' in stmt) or ('!=' in stmt):
        return 0
    quote_pos = stmt.find("\"")
    equal_pos = stmt.find("=")

    if (quote_pos>0 and equal_pos>0 and equal_pos>quote_pos):
        return 0
    '''
        stmt = stmt[:pos+1]
        print stmt
        quote_pos = stmt.find("\"")
        stmt = stmt[:pos+1]
        if
    '''
        
    now_identifier = stmt.split('=')[0].lstrip().rstrip()

    if now_identifier in incline_functions:
        print "ERROR[Line {}]: Use incline function name {} as identifier!".format(line_no, now_identifier)
        sys.exit(1)
    if now_identifier in key_words:
        print "ERROR[Line {}]: Use key word {} as identifier!".format(line_no, now_identifier)
        sys.exit(1)
    if now_identifier in identifier_list:
        return 0
    assign_right = stmt.split('=')[1].lstrip()
    if assign_right.startswith('{') or assign_right.startswith('[') or assign_right.startswith('('):
        return 2
    return 1

def decorate_for(line, global_list, list_name, iter_name, now_for_level, iterlist):
    pattern = re.compile(r'for(\ )*\((.*) in (.*)\)')
    match = pattern.match(line.lstrip())
    if match:
        (i, iter_name, list_name) = match.groups()
        if list_name not in global_list:
            global_list.append(list_name)
        #new_line = 'for(gugongIter'+str(itercount)+'=0; gugongIter<{}.length; gugongIter++)'.format(list_name)
        new_line = 'for({}=0; {}<{}.length; {}++)'.format(iter_name, iter_name, list_name, iter_name)
        if( iter_name not in iterlist):
            iterlist.append(iter_name)
        now_for_level = 0
        if line.rstrip().endswith('{'):
            new_line += '{'
            now_for_level += 1
        new_line += '\n'
        return new_line, list_name, iter_name, now_for_level
    else:
        print 'Not valid "for" statement!'+str(now_for_level)
        return line, list_name, iter_name, now_for_level

def preprocessing_file(input_file, output_file):
    f_in = open(input_file)
    if not f_in:
        print "ERROR: Can not open file {}!".format(input_file)
        sys.exit(1)
    global_vars = []
    out_lines = []
    f_out = open(output_file, 'w')
    index_file = "index_preprocess"
    index_out = open(index_file, 'w')
    i = 0
    identifier_list = []
    lines = f_in.readlines()
    n_lines = len(lines)
    now_for_level = -1
    iter_name = ""
    list_name = ""
    lineout = 0
    totalout = ""
    itercount = 0
    iterlist = []
    while i<n_lines:
        line = lines[i]
        if now_for_level >= 0:
            if '{' in line and ('}' not in line):
                now_for_level += 1
            if '}' in line and ('{' not in line):
                now_for_level -= 1
            # replace iter_name
            pattern = re.compile(r'([^\"\'a-zA-Z0-9_]+)'+iter_name+'([^\"\'a-zA-Z0-9_]+)')
            match = pattern.search(line)
            forline = ((line.lstrip().split('(')[0]).rstrip() == 'for')
            if match and not forline:                         
                #line = pattern.sub(r'\1{}[gugongIter]\2'.format(list_name), line)
                line = pattern.sub(r'\1{}[{}]\2'.format(list_name, iter_name), line)
        ## comments block
        if line.lstrip().startswith('/*'):
            out_lines.append(line)
            totalout += str(lineout+1) + ' ' + str(i) + '\n'
            while i+1<n_lines:
                i += 1
                line = lines[i]
                if line.rstrip().endswith('*/'):
                    break
                totalout += str(lineout+1) + ' ' + str(i) + '\n'
                lineout = lineout+1
                out_lines.append(line)
        ## new block: identifier valid zone
        #if line.lstrip().startswith('{') or line.rstrip().endswith('{'):
        if line.lstrip().startswith('void'):        
            identifier_list = []
        ## for loop head
        if line.lstrip().startswith('for'):
            line, list_name, iter_name, now_for_level = decorate_for(line, global_vars, list_name, iter_name, now_for_level, iterlist)
        if not line.rstrip().split('(')[0] == 'for':
            ## check whether variable definition
            identifier_def_flag = check_identifier_def(i, line, identifier_list)
            #whitespace is disturbing...            
            line.replace(" ","")            
            if identifier_def_flag == 1 :
                identifier_list.append((line.split('=')[0]).lstrip().rstrip())
                #print identifier_list[-1]+"."
                line1 = "char* {} ".format(line.split('=')[0])
                line1 = line1+";\n"
                out_lines.append(line1)
                totalout += str(lineout+1) + ' ' + str(i) + '\n'
                lineout += 1
                if (len(line.split(')'))<=1 and len(line.split(','))>1):
                    right = line.split(',')[1].lstrip()
                    while right!="":
                        identifier_list.append((right.split('=')[0]).lstrip().rstrip())
                        line1 = "char* {} ".format(right.split('=')[0])
                        line1 = line1+";\n"
                        out_lines.append(line1)
                        totalout += str(lineout+1) + ' ' + str(i) + '\n'
                        lineout = lineout + 1                        
                        if(len(right.split(','))<=1):
                            #print len(right.split(','))
                            break;
                        right = right.split(',')[1].lstrip()
                    print line
                    strinfo = re.compile(',')
                    line = strinfo.sub(';',line)
                newline = line
                out_lines.append(newline)
                totalout += str(lineout+1) + ' ' + str(i) + '\n'
                lineout = lineout+1
            elif identifier_def_flag == 2:
                now_var = line.split('=')[0].lstrip().rstrip()
                global_vars.append(now_var)
                identifier_list.append(now_var)
                line1 = "char* {}[] = {}".format(now_var, line.split('=')[1].split('}')[0])
                line1 = line1+"};\n"
                out_lines.append(line1)
                totalout += str(lineout+1) + ' ' + str(i) + '\n'
                lineout += 1
                pos = line.find('}')
                right = line[pos+1:]
                #print "line="+right
                #newline = line[:pos+1]
                #right = line.split(',')[1]
                if (right.startswith(',')): #(len(line.split(','))>1):
                    while(right!=""):
                        #newline += ";"
                        right = right[1:].lstrip()                   
                        now_var = right.split('=')[0].lstrip().rstrip()
                        #newline += now_var+"="
                        global_vars.append(now_var)
                        identifier_list.append(now_var)
                        line1 = "char* {}[] = {}".format(now_var, right.split('=')[1].split('}')[0])
                        line1 = line1+"};\n"
                        out_lines.append(line1)
                        totalout += str(lineout+1) + ' ' + str(i) + '\n'
                        lineout = lineout+1                        
                        #newline += right.split('=')[1].split('}')[0]+"}";
                        pos = right.find('}')
                        right = right[pos+1:]
                        if(len(right.split(','))<=1):
                            break;
                        #right = right.split(',')[1]
                #newline+=";\n"   
                #out_lines.append(newline)
            else:
                out_lines.append(line)
                totalout += str(lineout+1) + ' ' + str(i) + '\n'
                lineout = lineout+1
        else:
            out_lines.append(line)

            totalout += str(lineout+1) + ' ' + str(i) + '\n'
            lineout = lineout+1
        #print line
        i+=1
    f_in.close()
    #global_vars_declare = 'int i, gugongIter, null'
    global_vars_declare = 'int null'
    for gv in global_vars:
        global_vars_declare += ', {}.length'.format(gv)
    for name in iterlist:
        global_vars_declare += ', {}'.format(name)
    global_vars_declare += ';\n'
    out_lines.insert(0, global_vars_declare)
    f_out.writelines(out_lines)
    f_out.close()
    index_out.writelines(totalout)
    index_out.close()

def test_decorate_for():
    lines = [
        '  for(user_id in user_id_list)\n',
        'for(user_id in user_id_list)\n',
        '{',
        'Click("value", user_id);',
        '}'
    ]
    global_vars = []
    print decorate_for(lines[0], global_vars)
    print global_vars

def test_file(file_name_path):
    if not file_name_path.endswith('.t'):
        print "Invalid file type {}".format('.'+file_name_path.split('.')[-1])		
    file_dir = os.path.abspath(os.path.join(file_name_path, os.pardir))
    file_name = os.path.split(file_name_path)[-1]
    output_file = os.path.join(file_dir, file_name.split('.')[0] + '.it')
    output_file_indent = os.path.join(file_dir, file_name.split('.')[0]+'.top')
    preprocessing_file(file_name_path, output_file)
    indent(output_file, output_file_indent)
    print 'File {} converted!'.format(file_name)


def test_dir(source_code_dir):
    if not os.path.exists(source_code_dir):
        print 'No path {}'.format(source_code_dir)
        sys.exit(1)
    for file in os.listdir(source_code_dir):
        if file.endswith('.t'):
            test_file(file)

if __name__ == '__main__':
    file_name = sys.argv[1]
    test_file(file_name)
    # test_dir('E:\Palace\\test_specifications\samples_good\preprocessing')
    # test_decorate_for()
