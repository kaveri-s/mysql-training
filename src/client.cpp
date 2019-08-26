#include "client.h"

using namespace std;

//Prints different prompts
void prompt(enum Entry ent)
{
    switch (ent)
    {
    case START:
        cout << "Welcome to Lorem bank. Type HELP to view list of commands. Happy banking!!" << endl;
        break;
    case COMMAND:
        cout << "Lorem >> " << endl;
        break;
    case HELP:
        cout << "List of commands" << endl;
        break;
    }

}

//Initiates connection
int init_conn(int *sock, struct sockaddr_in addr)
{

    if ((*sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perr();
        return 1;
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(PORT);

    if (connect(*sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perr();
        return 1;
    }

    return 0;
}

//Read command typed by user
char *read_command(int sock)
{
    char *buff;
    prompt(COMMAND);
    fflush(stdout);
    if ((buff = readline(NULL)) != NULL)
    {
        if (strlen(buff) > 0)
            add_history(buff);
        else
        {
            return NULL;
        }
    }

    return buff;
}

//Send user command to server
int send_command(int sock)
{
    char *buff;

    if ((buff = read_command(sock)) == NULL)
    {
        perr();
        return 1;
    }

    cout << buff;
    fflush(stdout);

    if (send(sock, buff, strlen(buff), 0) == -1)
    {
        perr();
        return 1;
    }

    free(buff);
    return 0;
}

int receive_result(int sock)
{
    char buffer[1024];
    int len = 0;

    if ((len = recv(sock, buffer, 1024, 0)) < 0)
    {
        perr();
    }

    buffer[len] = 0;
    //Print the received message
    printf("Data received: %s\n", buffer);
}

//Controller function
int main()
{
    int sock;
    struct sockaddr_in addr;

    quit = false;

    //Call by reference needed as sock is being assigned here
    if (init_conn(&sock, addr))
    {
        return -1;
    }

    //sock is not modified anymore
    while (!quit)
    {
        if (send_command(sock))
        {
            return -1;
        }

        if (receive_result(sock))
        {
            return -1;
        }

        quit = true;
    }

    close(sock);

    return 0;
}