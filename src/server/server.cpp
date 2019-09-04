#include "data_structs.h"

//Signal Handler
void signal_handler( int signal_num ){
    ConnectionManager *ConnMgr = ConnectionManager::getInstance();
    ConnMgr->closeAllConn();
    ConnMgr->closeConn();
    exit(1);
}

//Entry point for Server program
int main(int argc, char const *argv[])
{
    signal(SIGINT, signal_handler);
    signal(SIGSEGV, signal_handler);
    signal(SIGTERM, signal_handler);

    ConnectionManager *ConnMgr = ConnectionManager::getInstance();

    if (ConnMgr->initConn()) {
        std::cout << std::strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }

    while (!ConnMgr->shutdown)
    {
        
        struct sockaddr_in client_addr;
        socklen_t len = sizeof(struct sockaddr_in);
        conn c_sock = ConnMgr->getNewConnection(&client_addr, &len);

        if(c_sock == 0) {
            std::cout << std::strerror(errno) << std::endl;
            return EXIT_FAILURE;
        }

        std::cout << "Client Accepted" << std::endl;

        if(ConnMgr->serveClient(c_sock)) {
            std::cout << std::strerror(errno) << std::endl;
            return EXIT_FAILURE;
        }

        std::cout << "Client Served" << std::endl;
    }

    return 0;
}
