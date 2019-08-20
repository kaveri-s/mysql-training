class Connection {
    int socket;     //Socket fd

    //Buffer variables
    char *buf;
    char *buff_end;
    char *read_pos;
    char *write_pos;

    Connection(int fd){
        // Allocate memory
        // init buffer
        // init socket
    }
};

class ConnectionManager {
    
};