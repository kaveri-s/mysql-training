# Makefile

PROG = server
OBJS = account.o bank.o lexer.o parser.o compiler.o thread.o connection.o server.o
FILES = account.cpp connection.cpp server.cpp bank.cpp compiler.cpp thread.cpp
CC	= g++
CFLAGS	= -g
LFLAGS = -lpthread

$(PROG):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG) $(LFLAGS)

account.o:bank.h account.cpp
	$(CC) -c account.cpp

bank.o:bank.h bank.cpp
	$(CC) -c bank.cpp

lexer.c:lexer.l
	flex lexer.l

parser.c:parser.y lexer.c
	bison parser.y

lexer.o:parse_struct.h parser.c parser.h
	$(CC) -c lexer.c

parser.o:parse_struct.h lexer.c parser.c lexer.h parser.h
	$(CC) -c parser.c

compiler.o:data_structs.h compiler.cpp
	$(CC) -c compiler.cpp

thread.o:data_structs.h thread.cpp
	$(CC) -c thread.cpp

connection.o:data_structs.h connection.cpp
	$(CC) -c connection.cpp

server.o:data_structs.h server.cpp
	$(CC) -c server.cpp

clean:
	rm -f core $(PROG) $(OBJS) lexer.c parser.c lexer.h parser.h