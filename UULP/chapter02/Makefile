#
# Makefile for Chapter 02
#
# Type  make    to compile all the programs
# in the chapter 
#

all: cp1 who1 who2 who3 more01 more02 wend who2_2 last cat head tail \
     od dd cat1 head1

clean:
	rm -f cp1 who1 who2 who3 who2_2 more01 more02 wend last cat head \
	tail od dd cat1 head1

head1: head1.c 
	cc -o head1 head1.c

cat1: cat1.c 
	cc -o cat1 cat1.c

head: head.c 
	cc -o head head.c 

tail: tail.c 
	cc -o tail tail.c 

od: od.c 
	cc -o od od.c 

dd: dd.c 
	cc -o dd dd.c
cat: cat.c 
	cc -o cat cat.c
last: last.c 
	cc -o last last.c

more01: more01.c 
	cc -o more01 more01.c 

more02: more02.c 
	cc -o more02 more02.c 

wend: wend.c 
	cc -o wend wend.c

cp1: cp1.c 
	cc -o cp1 cp1.c 

who1: who1.c 
	cc -o who1 who1.c 

who2: who2.c 
	cc -o who2 who2.c 

who3: who3.c utmplib.c
	cc -o who3 who3.c utmplib.c

who2.2.c: who2_2.c
	cc -o who2.2 who2_2.c 