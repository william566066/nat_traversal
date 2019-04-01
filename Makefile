CC = gcc
CFLAGS  = -g -Wall

all:  nat_traversal nat_server nat_hole

# clang warn about unused argument, it requires -pthread when compiling but not when linking
nat_traversal:  main.o nat_traversal.o nat_type.o 
	$(CC) $(CFLAGS) -o nat_traversal main.o nat_traversal.o nat_type.o -pthread

nat_server: nat_server.c
	$(CC) $(CFLAGS) -o nat_server -c nat_server.c

nat_hole: nat_server.c
	$(CC) $(CFLAGS) -o nat_hole -c nat_hole.c

main.o:  main.c
	$(CC) $(CFLAGS) -c main.c

nat_traversal.o:  nat_traversal.c 
	$(CC) $(CFLAGS) -c nat_traversal.c

nat_type.o:  nat_type.c
	$(CC) $(CFLAGS) -c nat_type.c

clean: 
	$(RM) nat_traversal nat_server *.o *~
