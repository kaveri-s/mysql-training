%{

#include "parse_struct.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>

%}

%option outfile="lexer.c" header-file="lexer.h"
%option warn nodefault

%option reentrant noyywrap never-interactive nounistd
%option bison-bridge

letter  [A-Za-z]
digit   [0-9]
name    {letter}+
float   {digit}+[.]{digit}+
number  {digit}+

%%

\n	{return(END_STATEMENT);}

<<EOF>>		{yyterminate();}

OPEN        {return(OPEN);}
CLOSE       {return(CLOSE);}
SHOW        {return(SHOW);}
DEPOSIT     {return(DEPOSIT);}
WITHDRAW    {return(WITHDRAW);}
SHUTDOWN    {return(SHUTDOWN);}
ACCOUNT 	{return(ACCOUNT);}
BALANCE 	{return(BALANCE);}
BANK	    {return(BANK);}

"MINI STATEMENT" 	    {return(STATEMENT);}
"ACTIVE CONNECTIONS"    {return(CONNECTIONS);}
"ALL ACCOUNTS"	        {return(ACCOUNTS);}

{name}      {yylval->strval = strdup(yytext); return(NAME);}
{float}     {sscanf(yytext, "%f", &yylval->floatval); return(FLOAT);}
{number}    {sscanf(yytext, "%d", &yylval->intval); return(NUM);}

.   {;}

%%

int yyerror(const char *msg) {
    fprintf(stderr, "Error Lexer: %s\n", msg);
    return 0;
}