#
# Makefile for Chapter 03
#
# Type  make    to compile all the programs
# in the chapter 
#
all: fileinfo filesize ls1 ls2 ls2 

clean:
	rm -f fileinfo filesize ls1 ls2 ls3 317 chown1
chown1: chown1.c
	cc -o chown1 chown1.c

317: 3_17.c
	cc -o 317 3_17.c 

fileinfo: fileinfo.c 
	cc -o fileinfo fileinfo.c 

filesize: filesize.c 
	cc -o filesize filesize.c 

ls1: ls1.c 
	cc -o ls1 ls1.c 

ls2: ls2.c
	cc -o ls2 ls2.c

ls3: ls3.c 
	cc -o ls3 ls3.c

printdir: print_dir_info.c
	cc -o printdir print_dir_info.c