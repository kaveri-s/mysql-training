# Makefile

PROG = client
OBJS = client.o
CC	= g++
CFLAGS	= -g
LFLAGS = -lreadline

$(PROG): $(OBJS)
	$(CC) $(LFLAGS) -o $(PROG) $(OBJS)

client.o:client.h client.cpp
	$(CC) $(CFLAGS) -c client.cpp

clean:
	rm -f core $(PROG) $(OBJS)