
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

//Inidivdual Account Instances
class Account
{

private:
    int acc_no;
    std::string name;
    float balance;
    int Txns[10];
    int front;
    int txn_count;

    pthread_rwlock_t a_info; //Lock on account instance on the whole

public:
    Account(int acc_no, char *name)
        :acc_no(acc_no), balance(0.0), front(-1), txn_count(0), name(name)
    {
        free(name);
        pthread_rwlock_init(&a_info, NULL);
    }

    std::string showName() { return this->name; }
    float showAccountBalance();
    std::string deposit(float);
    std::string withdraw(float);
    std::string showMiniStmt();
    void insertTxn(float amt);
};

//Bank holding account instances
class Bank
{

private:
    int a_counter;
    float bbal;
    std::map<int, Account *> bank;

    pthread_mutex_t b_info; //Lock on a_counter
    pthread_rwlock_t b_map; //Lock on map and bbal

    static Bank *b_manager;

    Bank()
        :bbal(0.0), a_counter(100)
    {
        pthread_mutex_init(&b_info, NULL);
        pthread_rwlock_init(&b_map, NULL);
    }

    ~Bank()
    {
        std::map<int, Account *>::iterator itr;
        pthread_rwlock_rdlock(&b_map);
        for (itr = bank.begin(); itr != bank.end(); ++itr)
        {
            delete itr->second;
            itr->second = NULL;
        }
        pthread_rwlock_unlock(&b_map);
    }

public:
    static Bank *getInstance()
    {
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