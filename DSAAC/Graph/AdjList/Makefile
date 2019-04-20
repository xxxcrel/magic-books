SRC = main.c Queue.c LGraph.c
run:main.exe
	.\main
main.exe:$(OBJS)
	gcc -o main.exe $(SRC) -fexec-charset=GBK -std=c11

.PHONY:cleano cleane
cleano:
	-rm *.o
cleane:
	-rm *.exe