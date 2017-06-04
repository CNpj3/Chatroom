import sys # sys.argv is a list

file = open(sys.argv[1], 'r')
content = file.read()
print content

# file.write('test')
file.close()
