#include <pthread.h>
#include "connection.h"

#define MINTHREADS 10


class Thread {
private:
    int thd_id;
    pthread_mutex_t thd_data;
    pthread_mutex_t thd_info;
    enum stmt_state {TODO, PARSED, EXECUTED};
    // bool ro;
    Connection *conn;

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

    int t_count;
    int *t_pool;
    int t_id;

    static ThreadManager *t_manager;

    pthread_mutex_t thd_id_gen;
    pthread_mutex_t thd_counter;
    pthread_mutex_t thd_pool;

    //Called only once so no locking required
    ThreadManager() {
        this.t_id = 1;
        this.t_pool = (int *)malloc(MINTHREADS*sizeof(int));    //Increase as more clients join
        this.t_count = 0;
    }

    ThreadManager(const ThreadManager &);
    ThreadManager &operator=(const ThreadnManager &);

public:
    static ThreadManager *get_instance() {
        if(t_manager == NULL)
            t_manager = new ThreadManager();
        return t_manager;
    }


    //Thread Manager instance handler
    bool create_manager();
    void destroy_manager();

    //Thread ID Generator
    void get_t_id();

    //Updating Array of Threads
    void add_thd(THD *thd);
    void remove_thd(THD *thd);

    //Thread Count Actions
    void dec_t_count();
    void inc_t_count();
    int get_t_count();
};

ThreadManager *ThreadManager::t_manager = NULL;