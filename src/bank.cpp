#include "account.h"

class Bank{
  private:
    typedef struct Node{
      Account* account;
      Node *next;
    }* node;

    node cur;
    node temp; 
    node head;

  public:
    Bank();
    void add_account(Account*);
    void del_node(Account*);
    void print();
};