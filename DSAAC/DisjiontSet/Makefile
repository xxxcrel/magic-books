SRC = main.c disjset.c

run:main.exe
	.\main
main.exe:$(SRC)
	gcc -o main.exe $(SRC) -fexec-charset=GBK -std=c11

.PHONY:cleano cleane
cleano:
	-rm *.0
cleane:
	-rm *.exe