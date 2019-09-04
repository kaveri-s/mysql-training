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

#define PORT 8080      //Must be same as client
#define BUFF_SIZE 1024 //Must be same as client

#include "bank.h"
#include "parse_struct.h"
#include "parser.h"
#include "lexer.h"

typedef int conn;

enum t_states
{
    READY,
    RECEIVING,
    PARSING,
    EXECUTING,
    SENDING,
    DONE
};

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

    enum t_states t_state;
    conn c_sock;
    bool shutdown;

public:
    pthread_t t_id;
    Compiler *compiler;
    std::string result;

    Thread(conn c_sock)
        : t_id(0), t_state(READY), shutdown(false), c_sock(c_sock), result("Server Error")
    {
        compiler = new Compiler();
    }

    ~Thread()
    {
        delete compiler;
    }

    void *start_thd();
    int rcv_cmd();
    int exec_cmd();
    int send_cmd();

    static void *pthread_wrapper(void *object)
    {
        reinterpret_cast<Thread *>(object)->start_thd();
        return 0;
    }

    //Getters and Setters
    void set_t_state(enum t_states t_state)
    {
        this->t_state = t_state;
    }

    enum t_states get_t_state()
    {
        return this->t_state;
    }

    void set_t_id(int t_id)
    {
        this->t_id = t_id;
    }

    pthread_t get_t_id()
    {
        return this->t_id;
    }

    conn getConnInfo()
    {
        return c_sock;
    }
};

//Holds Metadata regarding active connections
class ConnectionManager
{

private:

    conn sock;
    struct sockaddr_in addr;
    pthread_mutex_t conn_info;

    ConnectionManager()
        : sock(0), shutdown(false)
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

    //Public Data Members
    std::map<conn, in_addr> ActiveConn;
    pthread_mutex_t map_info;
    bool shutdown;

    //Public Member Functions
    int initConn();
    conn getNewConnection(struct sockaddr_in *client_addr, socklen_t *len);
    int addToActive(conn, in_addr);
    std::string printActive();
    int removeFromActive(conn c_sock);
    int serveClient(conn);
    int cleanup(Thread *);
    int getConnCount();
    void closeAllConn();        //Only to be used by Signal Handler
    void closeConn();

};

#endif