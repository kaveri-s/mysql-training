#include "controller.hpp"

using namespace std;

class Bank
{
private:
    typedef struct Account
    {
        //   Account* account;
        int acc_no;
        char *name;
        float balance;
        bool active;
        Txn Stmt[10];
        Account *next;
    };

    Account* head;
    int q_start;
    int q_end;

public:
    Bank();
    void openAccount(char *);
    int closeAccount(int);
    void showAccountBalance(int);
    void deposit(int, float);
    void showMiniStmt(int);
    void showAllAccounts(void);
    void showBankBalance(void);
    void showActiveConnections(void);

    void setActive(int);
    void setInactive(int);
    void getAccountID();

    void queue(enum, float);
};

Bank::Bank(){
    this->head = NULL;
    q_start = -1;
    q_end = -1;
}

Bank::~Bank(){
    cout << "LIST DELETED";
}

int Bank::openAccount(char *name){
    Account* acc = (Account *)malloc(sizeof(Account));
    acc->name = strdup(name);
    acc->acc_no = newAccountID();
    acc->balance = 0.00;
    this->head->next = acc;
    acc->next = NULL;
    free(name);
    cout << acc_no << ": " << head->name << "has been successfully opened"<< endl;
    return 1;
}

int Bank::closeAccount(int acc_no){
    Account* head = this->head;
    Account* temp = this->head;
    while(head){
        if(head->acc_no == acc_no) {
            temp->next = head->next;
            free(head);
            cout << acc_no << ": " << head->name << "has been successfully closed"<< endl;
            return 1;
        }
        temp = head;
        head = head->next;
    }
    cout << acc_no << ": not found"<< endl;
    return 0;
}

int Bank::showAccountBalance(int acc_no){
    Account* head = this->head;
    while(head){
        if(head->acc_no == acc_no) {
            cout << acc_no << ": " << head->name << "has " << head->balance << endl;
            return 1;
        }
        head = head->next;
    }
    return 0;
}

int Bank::deposit(int acc_no, float amt){
    Account* head = this->head;
    while(head){
        if(head->acc_no == acc_no) {
            head->balance = head->balance + amt;
            cout << acc_no << ": " << head->name << "'s new balance is " << head->balance << endl;
            return 1;
        }
        temp = head;
        head = head->next;
    }
    return 0;
}

int Bank::showMiniStmt(int acc_no){
    Account* head = this->head;
    Account* temp = this->head;
    int i = 1;
    while(head){
        if(head->acc_no == acc_no) {
            temp->next = head->next;
            free(head);
            return 1;
        }
        temp = head;
        head = head->next;
        i++;
    }
    return 0;
}

void Bank::showAllAccounts(){
    Account* head = this->head;
    while(head){
        cout << acc_no << ": " << head->name << "has " << head->balance << endl;
        head = head->next;
    }
}

void Bank::showBankBalance(){
    Account* head = this->head;
    int i = 1;
    while(head){
        cout << acc_no << ": " << head->name << "has " << head->balance << endl;
        head = head->next;
        i++;
    }
}

void Bank::showActiveConnections(){
    Account* head = this->head;
    int i = 1;
    while(head){
        cout << acc_no << ": " << head->name << "has " << head->balance << endl;
        head = head->next;
        i++;
    }
}

void Bank::setActive() {

}

void Bank::setInactive() {

}