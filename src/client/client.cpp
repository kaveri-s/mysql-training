#include "client.h"

using namespace std;


//Initiates connection
int init_conn(int *sock, struct sockaddr_in addr)
{

    if ((*sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "Socket Error: " << std::strerror(errno) << std::endl;
        return 1;
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(PORT);

    if (connect(*sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        std::cout << "Connection Error: " << std::strerror(errno) << std::endl;
        return 1;
    }

    return 0;
}

//Read command typed by user
char *read_command()
{

    char * buff;
    fflush(stdout);
    if ((buff = readline("Lorem >>")) != NULL)
    {
        if (strlen(buff) > 0)
            add_history(buff);
        else
            buff[0]='\n';
    }
    return buff;
}


//Send user command to server
int send_command(int sock, char * buff)
{

    if (send(sock, buff, strlen(buff), 0) == -1)
    {
        close(sock);
        free(buff);
        std::cout << "Send Error: " << std::strerror(errno) << std::endl;
        return 1;
    }

    // std::cout << "Sent: " << buff << std::endl; 

    free(buff);
    buff = NULL;

    return 0;
}

int receive_result(int sock)
{
    char buffer[BUFF_SIZE];
    int len = 0;

    while ((len = recv(sock, buffer, BUFF_SIZE - 1, 0)) > 0)
    {
        buffer[len] = '\0';
        cout << buffer;
        if (len == 0 || len < BUFF_SIZE - 1)
        {
            cout << endl;
            return 0;
        }
    }
    if(len == 0) {
        std::cout << "Server disconnected. Shutting down client..." << endl;
        quit = true;
        return 0;
    }
    
    return 1;
}

//Controller function
int main()
{
    int sock;
    struct sockaddr_in addr;
    char *buff;

    FILE *fp = fopen("test.txt","r");

    quit = false;

    //Call by reference needed as sock is being assigned here
    if (init_conn(&sock, addr))
    {
        return -1;
    }

    //sock is not modified anymore
    while (!quit)
    {
        if ((buff = read_command()) == NULL) {
            break;
        }

        if(buff[0] == '\n') continue;

        if (send_command(sock, buff))
        {
            free(buff);
            close(sock);
            return -1;
        }

        if (receive_result(sock))
        {
            close(sock);
            return -1;
        }
    }

    free(buff);
    fclose(fp);
    close(sock);

    return 0;
}