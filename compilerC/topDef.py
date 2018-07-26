import sys,os

def findBlocks(lines):
    if len(lines) == 0:
        return {}
    stack = []
    dic = {}
    i = 0
    dic[0] = len(lines) - 1
    while i < len(lines):
        line = lines[i]
        #print line
        #comment lines
        if line.lstrip().startswith("//"):
            i+=1
            continue
        if line.rstrip().find("//")>=0 and line.rstrip().find('{')>line.rstrip().find("//"):
            i+=1
            continue
        if line.rstrip().find("//")>=0 and line.rstrip().find('}')>line.rstrip().find("//"):
            i+=1
            continue   
        #when it is list assignment
        if line.rstrip().find('}')>0 and line.rstrip().find('{')>0:
            i+=1
            continue
        if line.lstrip().startswith('{') or line.rstrip().endswith('{'):
            stack.append(i)
        if line.lstrip().startswith('}') or line.rstrip().endswith('}'):
            if len(stack)<1:
                print "{ and } do not match"   
            #print stack[-1]
            dic[stack[-1]] = i        
            del stack[-1]
        i+=1
    return dic


def rearrangeLines(lines, beg, dic, index, totalindex, indexout_beg):
    new_lines = []
    identifier_defs = []
    normal_stmts = []
    normalindex = []
    i = beg
    head_line = ""
    indexout = indexout_beg
    iden_index = 0
    next = 0
    if  lines[i].lstrip().startswith('char*'):
        identifier_defs.append(lines[i])
        #when it is list assignment
    elif lines[i].rstrip().find('}')>0 and lines[i].rstrip().find('{')>0:    
        normal_stmts.append(lines[i])
        normalindex.append(i)
        next += 1
    elif lines[i].lstrip().startswith('{')  or lines[i].rstrip().endswith('{'):
        head_line = lines[i]
        iden_index += 1
    else:
        normalindex.append(i)
        next += 1
        normal_stmts.append(lines[i])
    if (beg == 0):
        totalindex += ""#str(indexout) + ' 0\n'
    else:
        totalindex += str(indexout) + ' ' + str(index[i-1][1]) + '\n'
    i += 1
    indexout += 1
    while i <= dic[beg]:
        line = lines[i]
        if line.lstrip().startswith('char*'):
            identifier_defs.append(line)
            totalindex += str(indexout) + ' ' + str(index[i-1][1]) + '\n'
            iden_index += 1
            indexout += 1
            i += 1
        elif line.rstrip().find('}')>0 and line.rstrip().find('{')>0:  
            i += 1
        elif line.lstrip().startswith('{')  or line.rstrip().endswith('{'):
            flag = 1
            #indexout += dic[i] + 1 - i
            i = dic[i] + 1
        else:
            i += 1
                        
    i = beg + 1       
    #print beg
    while i <= dic[beg]:
        line = lines[i]
        if line.lstrip().startswith('char*'):
            #identifier_defs.append(line)
            #totalindex += str(indexout) + ' ' + str(index[beg + iden_index])
            #iden_index += 1
            i += 1
        elif line.rstrip().find('}')>0 and line.rstrip().find('{')>0:  
            #totalindex += str(indexout) + ' ' + str(index[i])        
            normal_stmts.append(lines[i])
            #normalindex.append(i)
            totalindex += str(indexout) + ' ' + str(index[i-1][1]) + '\n'
            next = next + 1
            indexout += 1
            i += 1
        elif line.lstrip().startswith('{')  or line.rstrip().endswith('{'):
            [new_block, totalindex]= rearrangeLines(lines, i, dic, index, totalindex, indexout)
            indexout += dic[i] + 1 - i
            i = dic[i] + 1
            normal_stmts += new_block
        else:
            normalindex.append(i)
            #print "lines"
            #print index[2]+" "+index[2][0]
            #print index[5]
            #print str(i)+": "+line
            totalindex += str(indexout) + ' ' + str(index[i-1][1]) + '\n'
            #print "NOR"+str(i)+' '+str(indexout) + ' ' + str(index[i-1][1]) 
            next = next + 1
            indexout = indexout + 1
            normal_stmts.append(line)
            i += 1
    #print head_line
    indexout = indexout_beg
    if not head_line == "":
        new_lines.append(head_line)
        indexout += 1
    for line in identifier_defs:
        new_lines.append(line)
        indexout += 1
    next = 0
    for line in normal_stmts:
        #print line	
        #print 'Index' + str(next) + ' ' +str(len(normalindex))
        #print str(normalindex[next])+' ' +str(len(index))
        #print line
        #totalindex += str(beg + iden_index) + ' ' + str(index[normalindex[next]]) 
        new_lines.append(line)
        iden_index += 1
        next += 1
    return [new_lines, totalindex]


def topDefInBlock(infile_name, outfile_name):
    f_in = open(infile_name)
    if not f_in:
        print "ERROR: Can not open file {} for declaring identifiers at block beginning!".format(input_file)
        sys.exit(1)
    f_out = open(outfile_name, 'w')
    lines = f_in.readlines()
    #Read the index assigned by preprocess.py
    findex = open("index_preprocess", 'r')
    indices = findex.readlines()
    totalindex = ""
    index = []
    for line in indices:
        li = line.split()
        index.append(li)
        
    #Find the basic blocks
    dic = findBlocks(lines)
    #Rearrange lines
    [new_lines, totalindex] = rearrangeLines(lines, 0, dic, index, totalindex, 0)
    findexout = open("index_final", 'w')
    findexout.writelines(totalindex)
    findexout.close()
    
    f_out.writelines(new_lines)
    f_in.close()
    f_out.close()


def test_file(file_name_path):
    if not file_name_path.endswith('.top'):
        print "Invalid file type {}".format('.'+file_name_path.split('.')[-1])
    file_dir = os.path.abspath(os.path.join(file_name_path, os.pardir))
    file_name = os.path.split(file_name_path)[-1]
    output_file = os.path.join(file_dir, file_name.split('.')[0] + '.c')
    topDefInBlock(file_name_path, output_file)
    print 'File {} converted!'.format(file_name)

if __name__ == "__main__":
    test_file(sys.argv[1])