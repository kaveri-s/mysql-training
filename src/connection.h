#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#define PORT 8080     //Must be same as client
#define BUFF_SIZE 256 //Must be same as client

using namespace std;

class Connection
{
public:
    int sock;                      //Acceptor
    struct sockaddr_storage *addr; //Client Address

    //Buffer variables
    //char *buff; //buffer for request from client and response

public:
    Connection()
    {
        this->sock = 0;
        this->addr = (struct sockaddr_storage *)malloc(sizeof(struct sockaddr_storage));
    }

    ~Connection()
    {
        free(this->addr);
    }
};

class ConnectionManager
{

    static ConnectionManager *c_manager;

    ConnectionManager()
    {
        this->sock = 0;
        this->addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    }


    ~ConnectionManager()
    {
        free(this->addr);
    }

public:
    int sock;                 //Listener
    struct sockaddr_in *addr; //Server Address
    static ConnectionManager *getInstance()
    {
        static ConnectionManager instance;
        return &instance;
    }

    int initConnInfo();

    int serveClient(Connection *);
};