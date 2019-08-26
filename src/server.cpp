#include "connection.h"

//Entry point for Server program
int main(int argc, char const *argv[])
{

    ConnectionManager *ConnMgr = ConnectionManager::getInstance();
    // struct sockaddr_storage client_addr;

    //Generate server socket, bind to ip and port, listen for new connections
    if (ConnMgr->initConn())
        return EXIT_FAILURE;

    while (1)
    {
        //Accept incoming connection
        conn c_sock = ConnMgr->getNewConnection();

        if(c_sock == 0)
            return EXIT_FAILURE;

        std::cout << "Serving on: " << c_sock << std::endl;

        //Serve new client on new socket
        if(ConnMgr->serveClient(c_sock)) {
            return EXIT_FAILURE;
        }

        psuccess("Done");
        break;
    };

    return 0;
}
