//Common Headers
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include "y.tab.h"

// For Parser
// int yylex(void);
int yyparse(void *);
extern FILE* yyin;
// void yyerror(const char *s);

//For Bank Transactions
struct Txn {
    enum type {Credit, Debit};
    float amount;
};

