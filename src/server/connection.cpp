#include "data_structs.h"

//Generate server socket, bind to ip and port, listen for new connections
int ConnectionManager::initConn()
{

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cout << "Socket Creation Error" << std::endl;
        return 1;
    }
    std::cout << "Server Socket Created" << std::endl;

    int optval = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(sock, (struct sockaddr *)&addr, sizeof(sockaddr_in)) < 0)
    {
        std::cout << "Socket Bind Error" << std::endl;
        return 1;
    }
    std::cout << "Bound" << std::endl;

    if (listen(sock, 3) < 0)
    {
        std::cout << "Can't listen!" << std::endl;
        return 1;
    }
    std::cout << "Listening..." << std::endl;

    return 0;
}

//Accept incoming connection
conn ConnectionManager::getNewConnection(struct sockaddr_in *client_addr, socklen_t *len)
{

    conn c_sock;
    if ((c_sock = accept(sock, (struct sockaddr *)client_addr, len)) < 0)
    {
        if(stopserver) {
            closeSrvConn();
            exit(0);
        }

        std::cout << "Client Accept Error" << std::endl;
        return 0;
    }

    addToActive(c_sock, (sockaddr_in)*client_addr);

    return c_sock;
}

//Serve new client on new socket
int ConnectionManager::serveClient(conn c_sock)
{

    if(pthread_detach(pthread_self())) {
        std::cout << "Unable to detach thread" << std::endl;
        return 1;
    }

    Thread *thd = new Thread(pthread_self(), c_sock);

    thd->start_thd();

    removeFromActive(c_sock);

    if(close(c_sock)) {
        std::cout << "Client socket close error" << std::endl;
        delete thd;
        return 1;
    }

    delete thd;

    if (stopserver)
    {
        closeCliConns();
        shutdown(sock, SHUT_RD);
    }

    pthread_exit(NULL);

    return 0;
}

//Add Connection to Active Connections
void ConnectionManager::addToActive(conn c_sock, sockaddr_in addr)
{
    pthread_mutex_lock(&map_info);
    ActiveConn.insert(std::pair<conn, sockaddr_in>(c_sock, addr));
    pthread_mutex_unlock(&map_info);
}

//Remove Connection from List
void ConnectionManager::removeFromActive(conn c_sock)
{

    pthread_mutex_lock(&map_info);
    ActiveConn.erase(c_sock);
    pthread_mutex_unlock(&map_info);
}

//Get Active Connections
std::string ConnectionManager::printActive()
{

    std::ostringstream os;

    pthread_mutex_lock(&map_info);
    std::map<conn, sockaddr_in>::iterator itr;
    for (itr = ActiveConn.begin(); itr != ActiveConn.end(); ++itr)
    {
        os << inet_ntoa(itr->second.sin_addr) << "\t" << ntohs(itr->second.sin_port) << '\n';
    }
    pthread_mutex_unlock(&map_info);

    return os.str();
}

//Close All Connections
void ConnectionManager::closeCliConns()
{
    std::map<conn, sockaddr_in>::iterator itr;
    pthread_mutex_lock(&map_info);
    std::cout << "Closing all connections" << std::endl;
    if (!ActiveConn.empty())
    {
        for (itr = ActiveConn.begin(); itr != ActiveConn.end(); ++itr)
        {
            std::cout << itr->first << std::endl;
            close(itr->first);
        }
    }
    pthread_mutex_unlock(&map_info);
}

//Close client acceptor socket
void ConnectionManager::closeSrvConn() {
    std::cout << "Shutting Down Server" << std::endl;
    pthread_mutex_lock(&conn_info);
    close(sock);
    pthread_mutex_unlock(&conn_info);
}
