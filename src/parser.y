%{
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

extern FILE* yyin;
int yylex();
void yyerror(const char *s);
%}

%union
{
    char* strval;
    float floatval;
    int intval;
};

%start statement
%token OPEN CLOSE SHOW DEPOSIT SHUTDOWN ACCOUNT BALANCE BANK
%token STATEMENT ACCOUNTS CONNECTIONS 
%token NAME FLOAT NUM
%token END_STATEMENT

%type<strval> NAME
%type<intval> NUM
%type<floatval> FLOAT

%%

statement
    : OPEN ACCOUNT NAME statement           {cout << "open " << $3 << "\n";}
    | CLOSE ACCOUNT NUM statement          {cout << "close" << $3 << "\n";}
    | SHOW ACCOUNT BALANCE NUM statement   {cout << "account balance" << $4;}
    | DEPOSIT NUM FLOAT statement           {cout << "deposit" << $2 << " " << $3 << "\n";}
    | SHOW STATEMENT NUM statement          {cout << "mini statement" << $3 << "\n";}
    | SHOW ACCOUNTS statement              {cout << "accounts\n";}
    | SHOW BANK BALANCE statement           {cout << "bank balance\n";}
    | SHOW CONNECTIONS statement            {cout << "connections\n";}
    | SHUTDOWN statement                    {cout << "shutdown\n";}
    | END_STATEMENT statement
    | END_STATEMENT
    ;

%%

int main()
{
    cout << "Hi\n";
    yyin = fopen("../test/lex", "r");
    yyparse();
    cout << "Bye\n";
    return 0;
}


void yyerror(const char *s)
{
 printf("%s", s);
//  exit(0);
}