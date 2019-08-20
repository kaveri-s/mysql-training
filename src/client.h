#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080
#define BUFF_SIZE 8192

bool quit;

struct Buffer {
    char *data;
    int length;
};