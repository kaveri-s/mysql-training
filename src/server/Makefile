# Makefile

PROG = server
OBJS = account.o bank.o lexer.o parser.o compiler.o thread.o connection.o server.o
CC	= g++
CFLAGS	= -g
LFLAGS = -lpthread

$(PROG):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG) $(LFLAGS)

# Backend Data Components
account.o:bank.h account.cpp
	$(CC) -c account.cpp

bank.o:bank.h bank.cpp
	$(CC) -c bank.cpp

# Compiler Components
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

# Processing Component
thread.o:data_structs.h thread.cpp
	$(CC) -c thread.cpp

# Connector Component
connection.o:data_structs.h connection.cpp
	$(CC) -c connection.cpp

# Driver
server.o:data_structs.h server.cpp
	$(CC) -c server.cpp

clean:
	rm -f core $(PROG) $(OBJS) lexer.c parser.c lexer.h parser.h