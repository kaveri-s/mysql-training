#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>
#include <iostream>
#include <cstring>
#include <errno.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#define PORT 8080
#define BUFF_SIZE 1024

bool quit;

