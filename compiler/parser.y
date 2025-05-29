/* mengo.y */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

/* yylineno é atualizado pelo Flex */
extern int yylineno;

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
}

/* Mesma rotina de duplicação de string para portabilidade */
static char *copyString(const char *s) {
    char *p = malloc(strlen(s) + 1);
    if (p) strcpy(p, s);
    return p;
}

extern int yylex();
extern FILE *yyin;
%}

%union {
    double dval;
    char *sval;
}

/* tokens com valor de string */
%token <sval> SET ADD SUB MUL DIV POW MOD
%token <sval> AND OR NOT
%token <sval> IF EQUAL NOTEQUAL LESS GREATER LESSEQUAL GREATEREQUAL
%token <sval> LABEL GOTO EXIT INPUT PRINT BIN LIST INSERT DELETE IN
%token <sval> IDENTIFIER STRING COMMENT INDENT NEWLINE

/* token numérico */
%token <dval> NUMBER

/* não há mais %type <dval> expression, pois usamos actions inline */
%type <sval> value comparator

/* precedências */
%left ADD SUB
%left MUL DIV
%right POW
%nonassoc EQUAL NOTEQUAL LESS GREATER LESSEQUAL GREATEREQUAL
%left AND OR
%right NOT

%%

program:
    /* vazio */
  | program line
  ;

line:
    opt_indent statement NEWLINE
  ;

opt_indent:
    /* vazio */
  | INDENT
  ;

statement:
      assignment
    | math_operation
    | logical_operation
    | condition
    | label_def
    | goto_command
    | exit_command
    | input_command
    | print_command
    | bin_command
    | list_command
    | list_insert
    | list_delete
    | list_in_check
    | COMMENT
  ;

assignment:
    SET IDENTIFIER value {
        printf("Assignment: %s = %s\n", $2, $3);
        free($2); free($3);
    }
  ;

math_operation:
    ADD IDENTIFIER value value {
        printf("Math op add: %s %s %s\n", $2, $3, $4);
        free($2); free($3); free($4);
    }
  | SUB IDENTIFIER value value {
        printf("Math op sub: %s %s %s\n", $2, $3, $4);
        free($2); free($3); free($4);
    }
  | MUL IDENTIFIER value value {
        printf("Math op mul: %s %s %s\n", $2, $3, $4);
        free($2); free($3); free($4);
    }
  | DIV IDENTIFIER value value {
        printf("Math op div: %s %s %s\n", $2, $3, $4);
        free($2); free($3); free($4);
    }
  | POW IDENTIFIER value value {
        printf("Math op pow: %s %s %s\n", $2, $3, $4);
        free($2); free($3); free($4);
    }
  | MOD IDENTIFIER value {
        printf("Math op mod: %s %s \n", $2, $3);
        free($2); free($3);
    }
  | MOD IDENTIFIER value value{
        printf("Math op mod: %s %s %s\n", $2, $3, $4);
        free($2); free($3); free($4);
    }
  ;

logical_operation:
    AND IDENTIFIER IDENTIFIER IDENTIFIER {
        printf("Logical and: %s %s %s\n", $2, $3, $4);
        free($2); free($3); free($4);
    }
  | OR IDENTIFIER IDENTIFIER IDENTIFIER {
        printf("Logical or: %s %s %s\n", $2, $3, $4);
        free($2); free($3); free($4);
    }
  | NOT IDENTIFIER IDENTIFIER {
        printf("Logical not: %s %s\n", $2, $3);
        free($2); free($3);
    }
  ;

condition:
    IF IDENTIFIER comparator value {
        printf("If %s %s %s\n", $2, $3, $4);
        free($2); free($3); free($4);
    }
  ;

comparator:
      EQUAL       { $$ = copyString("=="); }
    | NOTEQUAL    { $$ = copyString("!="); }
    | LESS        { $$ = copyString("<"); }
    | GREATER     { $$ = copyString(">"); }
    | LESSEQUAL   { $$ = copyString("<="); }
    | GREATEREQUAL{ $$ = copyString(">="); }
  ;

label_def:
    LABEL IDENTIFIER {
        printf("Label: %s\n", $2);
        free($2);
    }
  ;

goto_command:
    GOTO IDENTIFIER {
        printf("Goto: %s\n", $2);
        free($2);
    }
  ;

exit_command:
    EXIT {
        printf("Exit\n");
    }
  ;

input_command:
    INPUT IDENTIFIER {
        printf("Input: %s\n", $2);
        free($2);
    }
  ;

print_command:
    PRINT value {
        printf("Print: %s\n", $2);
        free($2);
    }
  ;

bin_command:
    BIN IDENTIFIER IDENTIFIER {
        printf("Bin: %s to %s\n", $2, $3);
        free($2); free($3);
    }
  ;

list_command:
    LIST IDENTIFIER {
        printf("List: %s\n", $2);
        free($2);
    }
  ;

list_insert:
    INSERT IDENTIFIER IDENTIFIER {
        printf("Insert into %s %s\n", $3, $2);
        free($2); free($3);
    }
  ;

list_delete:
    DELETE IDENTIFIER IDENTIFIER {
        printf("Delete %s from %s\n", $3, $2);
        free($2); free($3);
    }
  ;

list_in_check:
    IN IDENTIFIER IDENTIFIER IDENTIFIER {
        printf("In check: %s in %s? %s\n", $4, $2, $3);
        free($2); free($3); free($4);
    }
  ;

value:
    NUMBER {
        char buf[64];
        snprintf(buf, sizeof(buf), "%f", $1);
        $$ = copyString(buf);
    }
  | STRING    { $$ = $1; }
  | IDENTIFIER{ $$ = $1; }
  ;

%%

int main(int argc, char **argv) {
    if (argc > 1) yyin = fopen(argv[1], "r");
    return yyparse();
}
