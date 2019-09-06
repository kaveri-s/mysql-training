#include "data_structs.h"

//Signal Handler
void signal_handler( int signal_num ){
    ConnectionManager *ConnMgr = ConnectionManager::getInstance();
    ConnMgr->closeCliConns();
    ConnMgr->closeSrvConn();
    exit(1);
}


//Entry point for Server program
int main(int argc, char const *argv[])
{
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    ConnectionManager *ConnMgr = ConnectionManager::getInstance();

    if (ConnMgr->initConn()) {
        return EXIT_FAILURE;
    }


    while (!ConnMgr->stopserver)
    {

        struct sockaddr_in client_addr;
        socklen_t len = sizeof(struct sockaddr_in);
        conn c_sock = ConnMgr->getNewConnection(&client_addr, &len);

        if(c_sock == 0) {
            raise(SIGTERM);
        }

        std::cout << "Client Accepted" << std::endl;

        //Temporary
        pthread_t threadid;

        if(pthread_create(&threadid, NULL, &ConnectionManager::pthread_wrapper, (void *)&c_sock)) {
            std::cout << "Unable to create Threads" << std::endl;
            raise(SIGTERM);
        }
    }

    return 0;
}
