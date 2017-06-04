import sys
for line in open(sys.argv[1], 'r'):
    print line

# close file when file is recycle
# 讀取檔案最好的方式，就是不要去 read 它
