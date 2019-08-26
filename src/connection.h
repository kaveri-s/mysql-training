#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <iterator>
#include <map>

#include "utilities.h"

#define PORT 8080     //Must be same as client
#define BUFF_SIZE 256 //Must be same as client


typedef int conn;

//Holds Metadata regarding active connections
class ConnectionManager
{
    conn sock;                 //Listener
    struct sockaddr_in addr; //Server Address
    std::map<conn, in_addr> ActiveConn;
    pthread_mutex_t map_info;
    pthread_mutex_t conn_info;

    // static ConnectionManager *c_manager;

    ConnectionManager() {
        map_info = PTHREAD_MUTEX_INITIALIZER;
        conn_info = PTHREAD_MUTEX_INITIALIZER;
    }

public:

    static ConnectionManager *getInstance()
    {
        static ConnectionManager instance;
        return &instance;
    }

    int initConn();

    conn getNewConnection();

    int addToActive(conn, in_addr);

    int printActive();

    int removeFromActive();

    int serveClient(conn);

    int connActive(conn *);

    int connClose(conn *);
};