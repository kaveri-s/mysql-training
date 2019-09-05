#include "data_structs.h"


//Actual Entry routine for Threads. All sub-routines return 1 on failure and 0 on success
void Thread::start_thd()
{
    while (!stopthread)
    {

        if (rcv_cmd())
            break;

        if (compiler->parse())
            break;

        if (exec_cmd())
            break;

        if (send_cmd())
            break;
        
    }

}

//Put input from Client in Compiler buffer
int Thread::rcv_cmd()
{
    char buffer[BUFF_SIZE] = {0};
    int bufflen;

    if ((bufflen = recv(c_sock, buffer, BUFF_SIZE - 1, 0)) <= 0)
    {
        stopthread = true;
        return 1;
    }

    buffer[bufflen] = '\0';
    compiler->setBuffer(buffer, bufflen);

    return 0;
}

//Use parsed output in Compiler to Execute commands on Bank, Account and ConnectionManager objects
int Thread::exec_cmd()
{

    ConnectionManager *CM = ConnectionManager::getInstance();
    Bank *bank = Bank::getInstance();
    Account *acc = NULL;

    struct parseCommand *command = compiler->getCommand();

    //Temporary variables used in some 'cases'
    std::ostringstream os;
    int acc_no = 0;
    float bal = -1;

    switch (command->cmd_type)
    {

    case ACCOP:
        if ((acc_no = bank->openAccount(command->name)))
        {
            os << "Account Opened " << acc_no << std::endl;
            result = os.str();
        }
        else
            result = "Account Open Error\n";
        break;

    case ACCCL:
        if ((acc = bank->getAccount(command->acc_no)) == NULL)
        {
            result = "Account Not Found\n";
            break;
        }
        if (bank->closeAccount(command->acc_no))
            result = "Account Closed\n";
        else
            result = "Account Close Error\n";
        break;

    case ACCBAL:
        if ((acc = bank->getAccount(command->acc_no)) == NULL)
        {
            result = "Account Not Found\n";
            break;
        }
        if((bal = acc->showAccountBalance()))
        {
            os << std::fixed << std::setprecision(2) << bal << std::endl;
            result = os.str();
        }
        else {
            result = "Account Balance Error\n";
        }
        break;

    case CR:
        if ((acc = bank->getAccount(command->acc_no)) == NULL)
        {
            result = "Account Not Found\n";
            break;
        }
        result = acc->deposit(command->amt);
        break;

    case DB:
        if ((acc = bank->getAccount(command->acc_no)) == NULL)
        {
            result = "Account Not Found\n";
            break;
        }
        result = acc->withdraw(command->amt);
        break;

    case MINI:
        if ((acc = bank->getAccount(command->acc_no)) == NULL)
        {
            result = "Account Not Found\n";
            break;
        }
        result = acc->showMiniStmt();
        break;

    case ALLACC:
        result = bank->showAllAccounts();
        break;

    case BBAL:
        result = bank->showBankBalance();
        break;

    case ACTIVE:
        result = CM->printActive(); //printActive is thread safe
        break;

    case SHUT:
        pthread_mutex_lock(&CM->map_info);
        if ((CM->ActiveConn.begin()->first == c_sock) && CM->ActiveConn.size() == 1)
        {
            stopthread = true;
            CM->stopserver = true;
            result = "Q";
        }
        else
            result = "Oops, unable to shut server\n";
        pthread_mutex_unlock(&CM->map_info);
        break;

    case NONE:
        result = "Error parsing command\n";
        break;

    default:
        free(command);
        return 1;
    }

    free(command);
    return 0;
}

//Send Saved result in Thread to client
int Thread::send_cmd()
{

    char buff[result.length() + 1];
    strcpy(buff, result.c_str());

    if (send(c_sock, buff, sizeof(buff), 0) < 0)
    {
        stopthread = true;
        std::cout << "Shutting down" << std::endl;
        return 1;
    }
    else
        return 0;
}
