#include "client.h"
#include "myerror.h"

using namespace std;

enum entry
{
    START,
    COMMAND,
    HELP
}

void prompt(enum entry)
{
    switch (entry)
    {
    case 'START':
        cout << "Welcome to our Lorem bank. Type HELP to view list of commands. Happy banking!!";
        break;
    case 'COMMAND':
        cout << "Lorem:$ ";
        break;
    case 'HELP':
        cout << "List of commands"
    }
}

int init_buff(Buffer *buff)
{
    buff = (Buffer *)malloc(sizeof(Buffer));
    if (buff == NULL)
        return 1;

    buff->data = (char *)malloc(BUFF_SIZE);
    if (buff->data == NULL)
        return 1;

    buff->length = 0;

    return 0;
}

//Send user command to server
int send_command(int sock, Buffer *buff, int err)
{
    if (read_command(sock, buff))
        err = READ_ERR;

    if (send(sock, buff->data, buff->length, 0) == -1)
        err = SEND_ERR;
}

//Read command typed by user
int read_command(int sock, Buffer *buff)
{
    int len;
    while ((len = read(fd, buff->data, BUFF_SIZE - 1)) > 0)
    {
        buff->data[ret] = '\0';
        buff->length = len;
        if (len == BUFF_SIZE - 1)
            buff->more = 1;
        return 
    }
}

int main(int argc, char const *argv[])
{
    int sock, err;
    struct sockaddr_in addr;
    Buffer *buff;

    quit = false;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    if (init_buff(buff))
    {
        printf("\nBuffer Allocation Error\n");
        return -1;
    }

    while (!quit)
    {
        if (send_command(sock, buff, err))
        {
            switch (err)
            {
            case READ_ERR:
                printf("Unable to read from command line");
            }
            return -1;
        }

        if (receive_result(sock, buff, err))
        {
            switch (err)
            {
            }
            return -1;
        }
    }

    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);
    return 0;
}