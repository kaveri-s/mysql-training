#include "data_structs.h"

/* Thread Operations */

//Put input from Client in Compiler buffer
int Thread::rcv_cmd() {

    char buffer[BUFF_SIZE] = {0};
    int bufflen;
    
    if((bufflen = recv(c_sock , buffer , BUFF_SIZE-1, 0)) <= 0) {
        this->shutdown = true;
        return 1;
    }

    buffer[bufflen] = '\0';
    this->compiler->setBuffer(buffer, bufflen);

    return 0;
}

//Use parsed output in Compiler to Execute commands on Bank, Account and ConnectionManager objects
int Thread::exec_cmd() {
    struct parseCommand *command = this->compiler->getCommand();

    ConnectionManager *CM = ConnectionManager::getInstance();
    Bank *bank = Bank::getInstance();
    Account *acc = NULL;

    std::ostringstream os;  //To handle return of type int
    
    switch (command->cmd_type) 
    {
    case ACCOP:
        if(bank->openAccount(command->name))
            this->result = "Account Opened\n";
        else
            this->result = "Account Open Error\n";
        break;
    case ACCCL:
        if((acc = bank->getAccount(command->acc_no)) == NULL) {
            this->result = "Account Not Found";
            break;
        }
        if(bank->closeAccount(command->acc_no))
            this->result = "Account Closed\n";
        else
            this->result = "Account Close Error\n";
        break;
    case ACCBAL:
        if((acc = bank->getAccount(command->acc_no)) == NULL) {
            this->result = "Account Not Found\n";
            break;
        }
        os << std::fixed << std::setprecision(2) << acc->showAccountBalance() << std::endl;
        this->result = os.str();
        break;
    case CR:
        if((acc = bank->getAccount(command->acc_no)) == NULL) {
            this->result = "Account Not Found\n";
            break;
        }
        this->result = acc->deposit(command->amt);
        break;
    case DB:
        if((acc = bank->getAccount(command->acc_no)) == NULL) {
            this->result = "Account Not Found\n";
            break;
        }
        os << acc->withdraw(command->amt) << std::endl;
        this->result = os.str();
        break;
    case MINI:
        if((acc = bank->getAccount(command->acc_no)) == NULL) {
            this->result = "Account Not Found\n";
            break;
        }
        this->result = acc->showMiniStmt();
        break;
    case ALLACC:
        this->result = bank->showAllAccounts();
        break;
    case BBAL:
        this->result = bank->showBankBalance();
        break;
    case ACTIVE:
        this->result = CM->printActive();           //printActive is thread safe
        break;
    case SHUT:
        pthread_mutex_lock(&CM->map_info);
        if(CM->ActiveConn.find(c_sock)!= CM->ActiveConn.end() && CM->ActiveConn.size() == 1) {
            this->set_t_state(DONE);
            this->shutdown = true;
            CM->shutdown = true;
            this->result = "Q";
        }
        else this->result = "Oops, unable to shut server";
        pthread_mutex_unlock(&CM->map_info);
        break;
    case NONE:
        this->result = "Error parsing command";
        break;

    default:
        free(command);
        return 1;
    }
    free(command);
    return 0;
}

//Send Saved result in Thread to client
int Thread::send_cmd() {
    char buff[this->result.length() + 1];
    strcpy(buff, this->result.c_str());
    if(send(this->c_sock, buff, sizeof(buff),0) < 0) {
        this->shutdown = true;
        std::cout << "Shutting down" << std::endl;
        return 1;
    }
    else
        return 0;
}

//Actual Entry routine for Threads. All sub-routines return 1 on failure and 0 on success
void *Thread::start_thd() {
    while(!this->shutdown) {

        this->set_t_state(RECEIVING);
        if(this->rcv_cmd()) break;

        this->set_t_state(PARSING);
        if(this->compiler->parse()) break;
    
        this->set_t_state(EXECUTING);
        if(this->exec_cmd()) break;

        this->set_t_state(SENDING);
        if(this->send_cmd()) break;
    }
    this->set_t_state(DONE);

}