main: main.c
	cc -g -O0 -DDEBUG -o main.o main.c 
clean:
	-rm todo