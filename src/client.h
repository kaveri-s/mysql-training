#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <error.h>
#define PORT 8080
#define BUFF_SIZE 256

bool quit;

enum Entry
{
    START,
    COMMAND,
    HELP
};

