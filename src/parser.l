%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include "y.tab.h"

// extern YYSTYPE yylval; //temporary. should it be extern?
// extern int install_id(char *n);
%}


letter [A-Za-z]
digit  [0-9]
id {letter}({letter}|{digit})*
float {digit}+[.]{digit}+
number {digit}+

%%

\n[ \t]*	{printf("END_STATEMENT\n");}

<<EOF>>		{
                yyterminate();
            }

OPEN        {printf("OPEN ");}
CLOSE       {printf("CLOSE ");}
SHOW        {printf("SHOW ");}
DEPOSIT     {printf("DEPOSIT ");}
SHUTDOWN    {printf("SHUTDOWN ");}
ACCOUNT 	{printf("ACCOUNT ");}
BALANCE 	{printf("BALANCE ");}
BANK	    {printf("BANK ");}

"MINI STATEMENT" 	    {printf("STATEMENT ");}
"ALL ACCOUNTS"	        {printf("ACCOUNTS ");}
"ACTIVE	CONNECTIONS"    {printf("CONNECTIONS ");}

{id}        {printf("ID ");}
{float}     {printf("FLOAT ");}
{number}    {printf("NUM ");}

.   {;}


%%

int main()
{
 yyin=fopen("../test/lex","r");
 yylex();
 return 0;
}