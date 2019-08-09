%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// extern FILE* yyin;
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
    : OPEN ACCOUNT NAME statement           {printf("open %s\n", $3);}
    | CLOSE ACCOUNT NUM statement          {printf("close %d\n", $3);}
    | SHOW ACCOUNT BALANCE NUM statement   {printf("account balance %d\n", $4);}
    | DEPOSIT NUM FLOAT statement           {printf("deposit %d %f\n", $2, $3);}
    | SHOW STATEMENT NUM statement          {printf("mini statement %d\n", $3);}
    | SHOW ACCOUNTS statement              {printf("accounts\n");}
    | SHOW BANK BALANCE statement           {printf("bank balance\n");}
    | SHOW CONNECTIONS statement            {printf("connections\n");}
    | SHUTDOWN statement                    {printf("shutdown\n");}
    | END_STATEMENT statement
    | END_STATEMENT
    ;

%%

// int main()
// {
//     printf("Hi\n");
//     yyin = fopen("../test/lex", "r");
//     yyparse();
//     printf("Bye\n");
//     return 0;
// }


void yyerror(const char *s)
{
 printf("%s", s);
//  exit(0);
}