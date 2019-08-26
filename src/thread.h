#include <pthread.h>
#include "connection.h"



class Thread {
protected:
    int thd_id;
    enum t_states{BUSY, PARSING, EXECUTING, IDLE}thd_state;
    pthread_mutex_t thd_info;
    // bool ro;
    Connection *conn;

public:

    Thread() {
        thd_id = 0;
        thd_state = IDLE;
        conn = NULL;
    }

    bool kill_thread();

    int parse(char *stmt, struct args);
    int execute(struct args);
    
    int set_thd_state(enum t_states);
    enum t_states get_thd_state();
    
    int set_conn_info();

    int set_thd_id(int thd_id) {this.thd_id};
    int get_thd_id() {return this.thd_id};

    //Add Constructor and Destructor
}


//Thread Manager - only one can exist as long as the server is running
//Do all operations on Thread using Thread Manager ONLY
class ThreadManager {

private:

    int t_count;    //No of Active threadss
    std::map<int, char> t_pool;

    static ThreadManager *t_manager;

    pthread_mutex_t thd_counter;
    pthread_mutex_t thd_pool;

    //Called only once so no locking required
    ThreadManager() {
        t_count = 0;
        thd_counter = PTHREAD_MUTEX_INITIALIZER;
        thd_pool = PTHREAD_MUTEX_INITIALIZER;
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
    void destroy_manager();

    //Thread ID Generator
    void gen_t_id();

    //Updating Thread Pool
    int assign_thd(Connection *);
    Thd *get_thd(int t_id);
    void stop_thd(Thread *thd);

    //Thread Count Actions
    void dec_t_count();
    void inc_t_count();
    int get_t_count();
};

ThreadManager *ThreadManager::t_manager = NULL;