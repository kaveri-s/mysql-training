#include "data_structs.h"

//Generate server socket, bind to ip and port, listen for new connections
int ConnectionManager::initConn()
{

    if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cout << std::strerror(errno) << std::endl;
        return 1;
    }
    std::cout << "Server Socket Created" << std::endl;

    int optval = 1;
    setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    this->addr.sin_family = AF_INET;
    this->addr.sin_addr.s_addr = INADDR_ANY;
    this->addr.sin_port = htons(PORT);

    if (bind(this->sock, (struct sockaddr *)&this->addr, sizeof(sockaddr_in)) < 0)
    {
        std::cout << std::strerror(errno) << std::endl;
        return 1;
    }
    std::cout << "Bound" << std::endl;

    if (listen(this->sock, 3) < 0)
    {
        std::cout << std::strerror(errno) << std::endl;
        return 1;
    }
    std::cout << "Listening..." << std::endl;

    return 0;
}

//Accept incoming connection
conn ConnectionManager::getNewConnection(struct sockaddr_in *client_addr, socklen_t *len)
{

    conn c_sock;

    if ((c_sock = accept(this->sock, (struct sockaddr *)client_addr, len)) < 0)
    {
        std::cout << std::strerror(errno) << std::endl;
        return 0;
    }

    this->addToActive(c_sock, client_addr->sin_addr);

    return c_sock;
}

//Add Connection to Active Connections
int ConnectionManager::addToActive(conn c_sock, in_addr ip)
{
    pthread_mutex_lock(&map_info);
    ActiveConn.insert(std::pair<conn, in_addr>(c_sock, ip));
    pthread_mutex_unlock(&map_info);
    return 0;
}

//Serve new client on new socket
int ConnectionManager::serveClient(conn c_sock)
{

    Thread *thd = new Thread(pthread_self(), c_sock);
    addThread(pthread_self());
    thd->start_thd();
    delete thd;
    removeFromActive(c_sock);
    pthread_exit(NULL);
    return 0;
}

void ConnectionManager::addThread(pthread_t tid)
{
    pthread_mutex_lock(&t_list);
    Threads.push_back(tid);
    pthread_mutex_unlock(&t_list);
}

//Free up thread memory
int ConnectionManager::cleanup()
{

    pthread_mutex_lock(&map_info);
    int* ids = Threads.data(); 
    for (int i = 0; i < Threads.size(); ++i) {
        pthread_join(ids[i], NULL);
    }
    
    ActiveConn.clear();
    pthread_mutex_unlock(&map_info);

    closeConn();
    return 0;
}

//Remove Connection from List
int ConnectionManager::removeFromActive(conn c_sock)
{

    pthread_mutex_lock(&map_info);
    ActiveConn.erase(c_sock);
    pthread_mutex_unlock(&map_info);
    return 0;
}

//Get Active Connections
std::string ConnectionManager::printActive()
{

    std::ostringstream os;

    pthread_mutex_lock(&map_info);
    std::map<conn, in_addr>::iterator itr;
    for (itr = ActiveConn.begin(); itr != ActiveConn.end(); ++itr)
    {
        os << inet_ntoa(itr->second) << '\n';
    }
    pthread_mutex_unlock(&map_info);

    return os.str();
}

//Close All Connections
void ConnectionManager::closeAllConn()
{
    std::map<conn, in_addr>::iterator itr;
    for (itr = ActiveConn.begin(); itr != ActiveConn.end(); ++itr)
    {
        close(itr->first);
    }
}

//Close Server connection
void ConnectionManager::closeConn()
{
    pthread_mutex_lock(&conn_info);
    close(this->sock);
    pthread_mutex_unlock(&conn_info);
}
