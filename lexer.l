%{
#include <llvm-c/Core.h>
#include <llvm-c/Support.h>
#include "parserLLVM.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylineno;

static char *copyString(const char *s) {
    char *p = malloc(strlen(s) + 1);
    if (p) strcpy(p, s);
    return p;
}
%}

%option noyywrap

%%

^[ ]+                   { return INDENT; }
"\n"                    { yylineno++; return NEWLINE; }
"`"[^\n]*               { yylval.sval = copyString(yytext); return COMMENT; }
[ \t\r]+                { /* ignora espaços e carriage return */ }

"set"                   { return SET; }
"add"                   { return ADD; }
"sub"                   { return SUB; }
"mul"                   { return MUL; }
"div"                   { return DIV; }
"pow"                   { return POW; }
"mod"                   { return MOD; }

"and"                   { return AND; }
"or"                    { return OR; }
"not"                   { return NOT; }

"if"                    { return IF; }
"equal"                 { return EQUAL; }
"notequal"              { return NOTEQUAL; }
"less"                  { return LESS; }
"greater"               { return GREATER; }
"lessequal"             { return LESSEQUAL; }
"greaterequal"          { return GREATEREQUAL; }

"label"                 { return LABEL; }
"goto"                  { return GOTO; }
"exit"                  { return EXIT; }

"input"                 { return INPUT; }
"print"                 { return PRINT; }

"bin"                   { return BIN; }
"list"                  { return LIST; }
"insert"                { return INSERT; }
"delete"                { return DELETE; }
"in"                    { return IN; }
"get"                   { return GET; }

"true"    { yylval.dval = 1.0;  return TRUE; }
"false"   { yylval.dval = 0.0;  return FALSE; }


[-]?[0-9]+(\.[0-9]+)?    { yylval.dval = atof(yytext); return NUMBER; }
\"([^\"\n])*\"          { yylval.sval = copyString(yytext); return STRING; }
[a-zA-Z_][a-zA-Z0-9_]*   { yylval.sval = copyString(yytext); return IDENTIFIER; }

.                       { printf("Unexpected character: %s\n", yytext); }

%%
