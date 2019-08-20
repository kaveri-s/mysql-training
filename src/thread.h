#include <pthread.h>
#include "connection.hpp"


class Thread {
private:
    int thd_id;
    pthread_mutex_t thd_data;
    pthread_mutex_t thd_info;
    enum stmt_state {TODO, PARSED, EXECUTED};
    // bool ro;
    ConnInfo *conn;

public:

    Thread *get_thread() {return this;}
    bool kill_thread();

    int parse(char *stmt, struct args);
    int execute(struct args);
    
    int set_state(enum stmt_state);
    
    int set_conn_info();

    int set_thread_id(int thd_id) {this.thd_id};
    int get_thread_id() {return this.thd_id};

    //Add Constructor and Destructor
}


//Thread Manager - only one can exist as long as the server is running
class ThreadManager {

private:

    int num_threads;
    Thread *head;

    static ThreadManager *t_manager;

    pthread_mutex_t thd_id_gen;
    pthread_mutex_t thd_counter;
    pthread_mutex_t thd_list;

public:
    static ThreadManager *get_instance() {
        return t_manager;
    }


    //Thread Manager instance handler
    bool create_manager();
    void destroy_manager();

    //Thread ID Generator
    void get_thd_id();

    //Updating Array of Threads
    void add_thd(THD *thd);
    void remove_thd(THD *thd);

    //Thread Count Actions
    void dec_thd_count();
    void inc_thd_count();
    int get_thd_count();
}