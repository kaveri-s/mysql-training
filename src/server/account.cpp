#include "bank.h"

//Ad Transactions. Already locked
void Account::insertTxn(float amt) {
    front++;
    this->Txns[front%10] = amt;
    if(txn_count < 10) txn_count++;
}

float Account::showAccountBalance() {

    pthread_rwlock_rdlock(&this->a_info);
    float balance = this->balance;
    pthread_rwlock_unlock(&this->a_info);
    return balance;
}

std::string Account::deposit(float amt) {
    std::ostringstream os;
    pthread_rwlock_wrlock(&this->a_info);
    this->balance = this->balance + amt;
    this->insertTxn(amt);
    os << "New Balance" << this->balance << std::endl;
    pthread_rwlock_unlock(&this->a_info);
    return os.str();
}

std::string Account::withdraw(float amt) {
    std::ostringstream os;

    pthread_rwlock_wrlock(&this->a_info);
    float balance = this->balance - amt;

    if(balance < 0) {
        pthread_rwlock_unlock(&this->a_info);
        os << "Insufficient funds" << std::endl;
        return os.str();
    }

    this->balance = balance;
    this->insertTxn(-amt);
    os << "New Balance: " << this->balance << std::endl;
    pthread_rwlock_unlock(&this->a_info);
    return os.str();
}

std::string Account::showMiniStmt() {

    pthread_rwlock_rdlock(&a_info);
    std::ostringstream os;

    for(int i=0; front >= 0 && i < txn_count; i++) {
        int index = (front - i)%10;          //Latest Txn first
        index = (index < 0)?-index:index;       //No point including math just for abs
        float amt = 0.0;
        if((amt = this->Txns[index]) < 0.0)
            os << "Debit\t" << -amt << "\n";
        else
        {
            os << "Credit\t" << amt << "\n";
        }
        os << std::endl;
    }
    pthread_rwlock_unlock(&a_info);

    return os.str();
}