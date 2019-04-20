SRC = main.c Kruskal.c Heap.c DisjSet.c

run:main.exe
	.\main.exe
main.exe:$(SRC)
	gcc -o main.exe $(SRC) -fexec-charset=GBK -std=c11

.PHONY:cleano cleane

cleano:
	-rm *.o
cleane:
	-rm *.exe