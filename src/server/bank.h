
#ifndef __BANK_H__
#define __BANK_H__


#include <string>
#include <cstring>
#include <iostream>
#include <iterator>
#include <pthread.h>
#include <map>
#include <bits/stdc++.h> 
#include <sstream>
#include <errno.h>
#include <error.h>

class Account
{
    int acc_no;
    std::string name;
    float balance;
    int Txns[10];
    int front;
    int txn_count;

    pthread_rwlock_t a_info;

public:
    Account(int acc_no, char *name) {
        this->acc_no = acc_no;
        this->name = std::string(name);
        free(name);
        this->balance = 0.0;
        this->front = -1;
        this->txn_count = 0;
        pthread_rwlock_init(&a_info, NULL);
    }

    std::string showName() {return this->name; }
    float showAccountBalance();
    std::string deposit(float);
    std::string withdraw(float);
    std::string showMiniStmt();
    void insertTxn(float amt);
};

class Bank
{
private:

    int a_counter;
    float bbal;
    std::map<int, Account *> bank;  //Thread objects being used

    pthread_mutex_t b_info;
    pthread_rwlock_t b_map;

    static Bank *b_manager;

    //Called only once so no locking required
    Bank() {
        bbal = 0.0;
        a_counter = 100;
        pthread_mutex_init(&b_info, NULL);
        pthread_rwlock_init(&b_map, NULL);
    }

    ~Bank() {
        std::map<int, Account *>::iterator itr;
        pthread_rwlock_rdlock(&b_map);
        for (itr = bank.begin(); itr != bank.end(); ++itr) { 
            delete itr->second;
            itr->second = NULL;
        } 
        pthread_rwlock_unlock(&b_map);
    }

public:

    static Bank *getInstance() {
        static Bank b_inst;
        return &b_inst;
    }

    //Global Functions
    std::string showAllAccounts(void);
    std::string showBankBalance(void);

    //Managing Account Instances
    int genAccountID();
    int openAccount(char *);
    int closeAccount(int acc_no);
    Account *getAccount(int);

};

#endif