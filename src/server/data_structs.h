//To resolve multiple declaration warnings from Flex/Bison

#ifndef __DATA_STRUCTS_H__
#define __DATA_STRUCTS_H__

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iterator>
#include <map>
#include <pthread.h>
#include <csignal>
#include <vector>

#define PORT 8080      //Must be same as client
#define BUFF_SIZE 1024 //Must be same as client

#include "bank.h"
#include "parse_struct.h"
#include "parser.h"
#include "lexer.h"

typedef int conn;

int yyparse(struct parseCommand *expression, yyscan_t scanner);

//Compiler
class Compiler
{

private:
    std::string buffer;
    struct parseCommand *command;

public:
    Compiler()
        : command(NULL) {}

    //Main parser functions
    struct parseCommand *getParams(const char *);
    int parse();


    //Getters and Setters
    void setBuffer(char *buff, int bufflen)
    {
        std::ostringstream os;

        os << buff << std::endl;
        this->buffer = os.str();

        return;
    }

    struct parseCommand *getCommand()
    {
        return this->command;
    }
};

class Thread
{

private:

    conn c_sock;
    bool stopthread;

public:
    pthread_t t_id;
    Compiler *compiler;
    std::string result;

    Thread(pthread_t t_id, conn c_sock)
        : t_id(t_id), stopthread(false), c_sock(c_sock), result("Server Error")
    {
        compiler = new Compiler();
    }

    ~Thread()
    {
        delete compiler;
    }

    void start_thd();
    int rcv_cmd();
    int exec_cmd();
    int send_cmd();

};

//Holds Metadata regarding active connections
class ConnectionManager
{

private:

    conn sock;
    struct sockaddr_in addr;

    ConnectionManager()
        : sock(0), stopserver(false)
    {
        pthread_mutex_init(&map_info, NULL);
        pthread_mutex_init(&conn_info, NULL);
    }

public:

    static ConnectionManager *getInstance()
    {
        static ConnectionManager instance;
        return &instance;
    }

    static void *pthread_wrapper(void *arg)
    {
        ConnectionManager *ConnMgr = ConnectionManager::getInstance();
        ConnMgr->serveClient(*(int *)arg);
        return 0;
    }

    //Public Data Members
    std::map<conn, in_addr> ActiveConn;
    pthread_mutex_t map_info;

    pthread_mutex_t conn_info;      //For closing socket accepting clients

    bool stopserver;

    //Public Member Functions
    int initConn();
    conn getNewConnection(struct sockaddr_in *client_addr, socklen_t *len);
    void addToActive(conn, in_addr);
    std::string printActive();
    void removeFromActive(conn c_sock);
    int serveClient(conn);
    void closeAllConn();
    void closeConn();       //Make sure no thread accesses this. Thread safe anyways

};

#endif