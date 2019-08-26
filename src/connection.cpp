#include "connection.h"
// #include "thread.h"

int ConnectionManager::printActive() {
    pthread_mutex_lock(&map_info);
    std::map<conn, in_addr>::iterator itr;
    for (itr = ActiveConn.begin(); itr != ActiveConn.end(); ++itr) { 
        std::cout << inet_ntoa(itr->second) << '\n'; 
    } 
    std::cout << std::endl;
    pthread_mutex_unlock(&map_info);
}

int ConnectionManager::removeFromActive(conn c_sock) {
    
    pthread_mutex_lock(&map_info);
    // std::cout << "c_sock: " << c_sock << "ip: " << ip << std::endl;
    ActiveConn.erase(c_sock);
    pthread_mutex_unlock(&map_info);
    printActive();
}



int ConnectionManager::initConn()
{
    // Creating socket file descriptor
    if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perr();
        return 1;
    }

    psuccess("Server Socket Created");

    this->addr.sin_family = AF_INET;
    this->addr.sin_addr.s_addr = INADDR_ANY;
    this->addr.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(this->sock, (struct sockaddr *)&this->addr, sizeof(sockaddr_in)) < 0)
    {
        perr();
        return 1;
    }

    psuccess("Bound");

    if (listen(this->sock, 3) < 0)
    {
        perr();
        return 1;
    }

    psuccess("Listening...");

    return 0;
}


conn ConnectionManager::getNewConnection() {

    conn c_sock;
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(struct sockaddr_in);

    if ((c_sock = accept(this->sock, (struct sockaddr *)&client_addr, (socklen_t *)&len)) < 0)
    {
        perr();
        return 0;
    }

    this->addToActive(c_sock, client_addr.sin_addr);

    psuccess("Client Accepted");

    return c_sock;
}


int ConnectionManager::addToActive(conn c_sock, in_addr ip) {
    
    pthread_mutex_lock(&map_info);
    // std::cout << "c_sock: " << c_sock << "ip: " << ip << std::endl;
    ActiveConn.insert(std::pair<conn, in_addr>(c_sock, ip));
    pthread_mutex_unlock(&map_info);
    // printActive();
}

int ConnectionManager::serveClient(conn c_sock){

    // ThreadManager *ThdMgr = ThreadManager::get_instance();

    // int t_id = ThreadManager::assign_thd(conn);

    char buffer[1024] = {0};
    int bufflen = recv(c_sock , buffer , 1024, 0);

    send(c_sock, "Hello",5,0);

    close(c_sock);
    // c_sock = NULL;
    // free(c_sock);

    // close(this->sock);
    psuccess("Client Served");

    return 0;
}