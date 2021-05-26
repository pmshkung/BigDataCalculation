.PHONY:: all main clean
main: main.o
	gcc main.o -o main
main.o: main.c
	gcc -c main.c -o main.o
clean:
	rm -rf *.o *.exe
