/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSERLLVM_TAB_H_INCLUDED
# define YY_YY_PARSERLLVM_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SET = 258,                     /* SET  */
    ADD = 259,                     /* ADD  */
    SUB = 260,                     /* SUB  */
    MUL = 261,                     /* MUL  */
    DIV = 262,                     /* DIV  */
    POW = 263,                     /* POW  */
    MOD = 264,                     /* MOD  */
    AND = 265,                     /* AND  */
    OR = 266,                      /* OR  */
    NOT = 267,                     /* NOT  */
    IF = 268,                      /* IF  */
    EQUAL = 269,                   /* EQUAL  */
    NOTEQUAL = 270,                /* NOTEQUAL  */
    LESS = 271,                    /* LESS  */
    GREATER = 272,                 /* GREATER  */
    LESSEQUAL = 273,               /* LESSEQUAL  */
    GREATEREQUAL = 274,            /* GREATEREQUAL  */
    LABEL = 275,                   /* LABEL  */
    GOTO = 276,                    /* GOTO  */
    EXIT = 277,                    /* EXIT  */
    INPUT = 278,                   /* INPUT  */
    PRINT = 279,                   /* PRINT  */
    BIN = 280,                     /* BIN  */
    LIST = 281,                    /* LIST  */
    INSERT = 282,                  /* INSERT  */
    DELETE = 283,                  /* DELETE  */
    IN = 284,                      /* IN  */
    IDENTIFIER = 285,              /* IDENTIFIER  */
    STRING = 286,                  /* STRING  */
    COMMENT = 287,                 /* COMMENT  */
    INDENT = 288,                  /* INDENT  */
    NEWLINE = 289,                 /* NEWLINE  */
    TRUE = 290,                    /* TRUE  */
    FALSE = 291,                   /* FALSE  */
    NUMBER = 292                   /* NUMBER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 99 "parserLLVM.y"

    double dval;
    char *sval;
    LLVMValueRef lval; /* For LLVM values */

#line 107 "parserLLVM.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSERLLVM_TAB_H_INCLUDED  */
