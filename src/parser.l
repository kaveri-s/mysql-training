%{

#include <iostream>
#include <string>
#include <cstdlib>
#include "y.tab.h"
#include "parser.h"

using namespace std;

extern YYSTYPE yylval;
%}


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
SHUTDOWN    {return(SHUTDOWN);}
ACCOUNT 	{return(ACCOUNT);}
BALANCE 	{return(BALANCE);}
BANK	    {return(BANK);}

"MINI STATEMENT" 	    {return(STATEMENT);}
"ACTIVE CONNECTIONS"    {return(CONNECTIONS);}
"ALL ACCOUNTS"	        {return(ACCOUNTS);}

{name}      {yylval.strval = strdup(yytext); return(NAME);}
{float}     {yylval.floatval = atof(yytext); return(FLOAT);}
{number}    {yylval.intval = atoi(yytext); return(NUM);}

.   {;}


%%

// int main()
// {
//  yyin=fopen("../test/lex","r);
//  yylex();
//  return 0;
// }