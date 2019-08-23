#include "connection.h"
// #include "thread.h"

int ConnectionManager::serveClient(Connection *conn){

    char buffer[1024] = {0};
    int bufflen = recv(conn->sock , buffer , 1024, 0);

    send(conn->sock, "Hello",5,0);

    close(conn->sock);

    return 0;
}