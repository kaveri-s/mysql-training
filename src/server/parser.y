%{

#include "parse_struct.h"
#include "parser.h"
#include "lexer.h"

int yyerror(struct parseCommand *Command, yyscan_t scanner, const char *msg) {
    puts(msg);
    printf("Returning\n");
    return 0;
}



%}

%code requires {
  typedef void* yyscan_t;
}

%output  "parser.c"
%defines "parser.h"

%define api.pure
%lex-param   { yyscan_t scanner }
%parse-param { struct parseCommand *expression }
%parse-param { yyscan_t scanner }

%union
{
    char* strval;
    float floatval;
    int intval;
}

%start statement
%token OPEN CLOSE SHOW DEPOSIT SHUTDOWN ACCOUNT BALANCE BANK WITHDRAW
%token STATEMENT ACCOUNTS CONNECTIONS 
%token NAME FLOAT NUM
%token END_STATEMENT

%type<strval> NAME
%type<intval> NUM
%type<floatval> FLOAT


%destructor { free($$); } NAME


%%

statement
    : OPEN ACCOUNT NAME statement           {expression->name = strdup($3); expression->cmd_type = ACCOP; free($3);}
    | CLOSE ACCOUNT NUM statement           {expression->acc_no = $3; expression->cmd_type = ACCCL;}
    | SHOW ACCOUNT BALANCE NUM statement    {expression->acc_no = $4; expression->cmd_type = ACCBAL;}
    | DEPOSIT NUM FLOAT statement           {expression->acc_no = $2; expression->amt = $3; expression->cmd_type = CR;}
    | WITHDRAW NUM FLOAT statement          {expression->acc_no = $2; expression->amt = $3; expression->cmd_type = DB;}
    | SHOW STATEMENT NUM statement          {expression->acc_no = $3; expression->cmd_type = MINI;}
    | SHOW ACCOUNTS statement               {expression->cmd_type = ALLACC;}
    | SHOW BANK BALANCE statement           {expression->cmd_type = BBAL;}
    | SHOW CONNECTIONS statement            {expression->cmd_type = ACTIVE;}
    | SHUTDOWN statement                    {expression->cmd_type = SHUT;}
    | END_STATEMENT
    | error END_STATEMENT                   {yyclearin; yyerrok; }
    ;

%%