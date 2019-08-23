#include "connection.h"

int init_conn(ConnectionManager *ConnMgr)
{
    // Creating socket file descriptor
    if ((ConnMgr->sock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        printf("Socket Creation failed");
        return 1;
    }

    printf("Socket created");
    fflush(stdout);

    ConnMgr->addr->sin_family = AF_INET;
    ConnMgr->addr->sin_addr.s_addr = INADDR_ANY;
    ConnMgr->addr->sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(ConnMgr->sock, (struct sockaddr *)ConnMgr->addr, sizeof(sockaddr_in)) < 0)
    {
        perror("Socket bind failed");
        return 1;
    }

        printf("Bound");
    fflush(stdout);

    if (listen(ConnMgr->sock, 3) < 0)
    {
        perror("Socket failed to listen");
        return 1;
    }

    printf("Listening....");

    return 0;
}

Connection *getIncomingConnection(ConnectionManager *ConnMgr) {


    printf("So far so good");
    fflush(stdout);

    Connection *conn = new Connection();

    socklen_t len = sizeof(struct sockaddr_storage);


    if ((conn->sock = accept(ConnMgr->sock, (struct sockaddr *)conn->addr, (socklen_t *)&len)) < 0)
    {
        printf("Connection accept error");
        conn = NULL;
    }

    return conn;
}

int main(int argc, char const *argv[])
{

    ConnectionManager *ConnMgr = ConnectionManager::getInstance();

    printf("Connection Manager created");
    fflush(stdout);

    if (init_conn(ConnMgr))
    {
        return -1;
    }

    while (1)
    {
        //Wait for new client
        Connection *conn = getIncomingConnection(ConnMgr);

        if(conn == NULL)
            return 1;

        printf("Conn accepted");
        fflush(stdout);

        //Serve new client on new socket
        if(ConnMgr->serveClient(conn)) {
            return 1;
        }

        delete conn;
        // break;
    };

    printf("Server Connection aborted");
    // ConnectionManager::~ConnectionManager();
}
