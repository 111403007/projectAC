project: main.o project.o 
	cc main.o project.o -o project -lcrypt
main.o: main.c project.h
	cc -Wall -c main.c
project.o: project.c project.h 
	cc -Wall -c project.c

