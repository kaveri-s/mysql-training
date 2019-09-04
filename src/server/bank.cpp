#include "bank.h"

std::string Bank::showAllAccounts(void) {
    std::map<int, Account *>::iterator itr;
    std::ostringstream os;
    pthread_rwlock_rdlock(&b_map);
    for (itr = bank.begin(); itr != bank.end(); ++itr) { 
        os << itr->first 
            << '\t' << itr->second->showName() << '\n'; 
    } 
    pthread_rwlock_unlock(&b_map);
    return os.str();
}

std::string Bank::showBankBalance(void) {
    std::map<int, Account *>::iterator itr;
    float bal = 0.0;
    std::ostringstream os;
    pthread_rwlock_rdlock(&b_map);
    for (itr = bank.begin(); itr != bank.end(); ++itr) { 
        bal = bal + itr->second->showAccountBalance(); 
    }
    pthread_rwlock_unlock(&b_map);
    os << "Balance: " << std::fixed << std::setprecision(2) << bal <<std::endl;
    return os.str();
}

//Managing Account Instances
int Bank::genAccountID() {

    pthread_mutex_lock(&b_info);
    int acc_no = a_counter++;
    pthread_mutex_unlock(&b_info);
    return acc_no;

}

int Bank::openAccount(char *name) {
    int acc_no = genAccountID();
    Account *acc = new Account(acc_no, name);

    pthread_rwlock_wrlock(&b_map);
    bank.insert(std::pair<int, Account *>(acc_no, acc));
    pthread_rwlock_unlock(&b_map);

    return acc_no;

}

int Bank::closeAccount(int acc_no) {
    pthread_rwlock_wrlock(&b_map);
    std::map<int, Account*>::iterator itr = bank.find(acc_no);
    delete itr->second;
    bank.erase(itr);
    pthread_rwlock_unlock(&b_map);
    return 0;
}

Account *Bank::getAccount(int acc_no) {
    pthread_rwlock_rdlock(&b_map);
    Account *acc = bank.find(acc_no)->second;
    pthread_rwlock_unlock(&b_map);
    return acc;
}