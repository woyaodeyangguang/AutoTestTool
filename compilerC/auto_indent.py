import sys

def indent(input_file, output_file):
    f_in = open(input_file)
    if not f_in:
        print "ERROR: Can not open file {} for checking indent!".format(input_file)
        sys.exit(1)
    f_out = open(output_file, 'w')
    now_level = 0
    lines = f_in.readlines()
    n_lines = len(lines)
    i = 0
    while i < n_lines:
        line = lines[i]
        if line.lstrip().rstrip() == '':
            f_out.write(line)
            i += 1
            continue
        if line.lstrip().startswith('}'):
            now_level -= 1
        #print i, now_level, line
        line = '    '*now_level + line.lstrip()
        f_out.write(line)
        if line.lstrip().startswith('{') or line.rstrip().endswith('{'):
            now_level += 1
        i += 1
    f_in.close()
    f_out.close()

if  __name__ == "__main__":
	infile_name = sys.argv[1]
	outfile_name = infile_name+'.indent'
	indent(infile_name, outfile_name)