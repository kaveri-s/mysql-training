/* A Bison parser, made by GNU Bison 3.4.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    OPEN = 258,
    CLOSE = 259,
    SHOW = 260,
    DEPOSIT = 261,
    SHUTDOWN = 262,
    ACCOUNT = 263,
    BALANCE = 264,
    BANK = 265,
    STATEMENT = 266,
    ACCOUNTS = 267,
    CONNECTIONS = 268,
    NAME = 269,
    FLOAT = 270,
    NUM = 271,
    END_STATEMENT = 272
  };
#endif
/* Tokens.  */
#define OPEN 258
#define CLOSE 259
#define SHOW 260
#define DEPOSIT 261
#define SHUTDOWN 262
#define ACCOUNT 263
#define BALANCE 264
#define BANK 265
#define STATEMENT 266
#define ACCOUNTS 267
#define CONNECTIONS 268
#define NAME 269
#define FLOAT 270
#define NUM 271
#define END_STATEMENT 272

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
<<<<<<< HEAD
#line 12 "parser.y"
=======
#line 15 "parser.y" /* yacc.c:1909  */
>>>>>>> 43d06b8a21b7adf1d22008a70f5bc894bc3a7793

    char* strval;
    float floatval;
    int intval;

#line 97 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
