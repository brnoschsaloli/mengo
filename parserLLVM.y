/* parserLLVM.y */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <llvm-c/Core.h>
#include <llvm-c/Support.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>
#include "parserLLVM.tab.h"

/* yylineno is updated by Flex */
extern int yylineno;

/* LLVM globals */
LLVMContextRef context;
LLVMModuleRef module;
LLVMBuilderRef builder;
LLVMValueRef main_func; /* Main function for code generation */

/* Simple symbol table to store variable mappings */
struct Symbol {
    char *name;
    LLVMValueRef value;
};
struct Symbol symbol_table[100]; /* Adjust size as needed */
int symbol_count = 0;

/* Find or create a variable in the symbol table */
LLVMValueRef find_or_create_variable(const char *name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return symbol_table[i].value;
        }
    }
    /* Create new global variable */
    LLVMValueRef var = LLVMAddGlobal(module, LLVMDoubleTypeInContext(context), name);
    LLVMSetInitializer(var, LLVMConstReal(LLVMDoubleTypeInContext(context), 0.0));
    symbol_table[symbol_count].name = strdup(name);
    symbol_table[symbol_count].value = var;
    symbol_count++;
    return var;
}

#define MAX_LABELS 100
static LLVMBasicBlockRef if_then_bb;
static LLVMBasicBlockRef if_merge_bb;
static int exit_cont = 0;
static int cont_count = 0;
static char*   label_names[MAX_LABELS];
static LLVMBasicBlockRef label_blocks[MAX_LABELS];
static int     label_count = 0;

/* parserLLVM.y, no prólogo */
extern void delete_list(double elem, double *data, long *len);
extern double in_list(double elem, double *data, long len);


/* retorna NULL se a variável não existe */
LLVMValueRef find_variable(const char *name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0)
            return symbol_table[i].value;
    }
    return NULL;
}

void registerLabel(const char *name, LLVMBasicBlockRef bb) {
    label_names[label_count] = strdup(name);
    label_blocks[label_count] = bb;
    label_count++;
}

LLVMBasicBlockRef findLabel(const char *name) {
    for (int i = 0; i < label_count; i++)
        if (strcmp(label_names[i], name) == 0)
            return label_blocks[i];
    return NULL;
}

/* Error handling */
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
}

/* String duplication for portability */
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
    LLVMValueRef lval; /* For LLVM values */
}

/* Tokens with string values */
%token <sval> SET ADD SUB MUL DIV POW MOD
%token <sval> AND OR NOT
%token <sval> IF EQUAL NOTEQUAL LESS GREATER LESSEQUAL GREATEREQUAL
%token <sval> LABEL GOTO EXIT INPUT PRINT BIN LIST INSERT DELETE IN
%token <sval> IDENTIFIER STRING COMMENT INDENT NEWLINE

%token TRUE FALSE


/* Numeric token */
%token <dval> NUMBER

/* Types for non-terminals */
%type <sval> comparator
%type <lval> value

%left ADD SUB
%left MUL DIV
%right POW
%nonassoc EQUAL NOTEQUAL LESS GREATER LESSEQUAL GREATEREQUAL
%left AND OR
%right NOT

%%

program:
    /* empty */
  | program line
  ;

line:
    if_stmt
    | opt_indent statement NEWLINE
  ;

opt_indent:
    /* empty */
  | INDENT
  ;

statement:
      assignment
    | math_operation
    | logical_operation
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
        LLVMBuildStore(builder, $3, find_or_create_variable($2));
        free($2);
    }
  ;

math_operation:
    ADD IDENTIFIER value value {
        LLVMValueRef result = LLVMBuildFAdd(builder, $3, $4, "addtmp");
        LLVMBuildStore(builder, result, find_or_create_variable($2));
        free($2);
    }
  | SUB IDENTIFIER value value {
        LLVMValueRef result = LLVMBuildFSub(builder, $3, $4, "subtmp");
        LLVMBuildStore(builder, result, find_or_create_variable($2));
        free($2);
    }
  | MUL IDENTIFIER value value {
        LLVMValueRef result = LLVMBuildFMul(builder, $3, $4, "multmp");
        LLVMBuildStore(builder, result, find_or_create_variable($2));
        free($2);
    }
  | DIV IDENTIFIER value value {
        LLVMValueRef result = LLVMBuildFDiv(builder, $3, $4, "divtmp");
        LLVMBuildStore(builder, result, find_or_create_variable($2));
        free($2);
    }
  | POW IDENTIFIER value value {
        printf("Math op pow: %s (not implemented)\n", $2);
        free($2);
    }
  | MOD IDENTIFIER value {
        printf("Math op mod: %s (not implemented)\n", $2);
        free($2);
    }
  | MOD IDENTIFIER value value {
        LLVMValueRef result = LLVMBuildFRem(builder, $3, $4, "modtmp");
        LLVMBuildStore(builder, result, find_or_create_variable($2));
        free($2);
    }
  ;

logical_operation:
    AND IDENTIFIER IDENTIFIER IDENTIFIER {
        printf("Logical and: %s %s %s (not implemented)\n", $2, $3, $4);
        free($2); free($3); free($4);
    }
  | OR IDENTIFIER IDENTIFIER IDENTIFIER {
        printf("Logical or: %s %s %s (not implemented)\n", $2, $3, $4);
        free($2); free($3); free($4);
    }
  | NOT IDENTIFIER IDENTIFIER {
        printf("Logical not: %s %s (not implemented)\n", $2, $3);
        free($2); free($3);
    }
  ;

if_stmt:
    IF IDENTIFIER comparator value NEWLINE
    { 
        // 1) carrega a variável e faz a comparação
        LLVMValueRef var = LLVMBuildLoad2(
            builder,
            LLVMDoubleTypeInContext(context),
            find_variable($2),
            "if.load"
        );
        
        LLVMValueRef cmp;
        if      (strcmp($3, "==")==0) cmp = LLVMBuildFCmp(builder, LLVMRealOEQ, var, $4, "if.cmp");
        else if (strcmp($3, "!=")==0) cmp = LLVMBuildFCmp(builder, LLVMRealONE,var, $4, "if.cmp");
        else if (strcmp($3, "<" )==0) cmp = LLVMBuildFCmp(builder, LLVMRealOLT,var, $4, "if.cmp");
        else if (strcmp($3, ">" )==0) cmp = LLVMBuildFCmp(builder, LLVMRealOGT,var, $4, "if.cmp");
        else if (strcmp($3, "<=")==0) cmp = LLVMBuildFCmp(builder, LLVMRealOLE,var, $4, "if.cmp");
        else                           cmp = LLVMBuildFCmp(builder, LLVMRealOGE,var, $4, "if.cmp");

        // 2) cria os blocos THEN e MERGE
        if_then_bb  = LLVMAppendBasicBlockInContext(context, main_func, "if.then");
        if_merge_bb = LLVMAppendBasicBlockInContext(context, main_func, "if.end");

        // 3) faz o branch condicional
        LLVMBuildCondBr(builder, cmp, if_then_bb, if_merge_bb);

        // 4) posiciona o builder no início do THEN
        LLVMPositionBuilderAtEnd(builder, if_then_bb);

        free($2);
        free($3);
    }
    then_block
    {
        // 6) ao sair do bloco indentado, fecha o THEN com um branch para o MERGE
        LLVMBuildBr(builder, if_merge_bb);
        // 7) reposiciona o builder no MERGE, para as instruções depois do if
        LLVMPositionBuilderAtEnd(builder, if_merge_bb);
    }
;

then_block:
    /* uma ou mais linhas com INDENT */
    INDENT statement NEWLINE then_block
  | /* vazio */
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
        LLVMBasicBlockRef bb = LLVMAppendBasicBlockInContext(
            context,
            main_func,
            $2
        );
        // Registra no mapa
        registerLabel($2, bb);
        // Fecha o bloco anterior com um branch
        LLVMBuildBr(builder, bb);
        // Move o builder para o rótulo
        LLVMPositionBuilderAtEnd(builder, bb);
        free($2);
    }
  ;



goto_command:
  GOTO IDENTIFIER {
    LLVMBasicBlockRef target = findLabel($2);
    if (!target) {
      yyerror("Label não encontrada");
    } else {
      // 1) branch para o bloco-alvo
      LLVMBuildBr(builder, target);

      // 2) cria um bloco de continuação único
      char cont_name[32];
      sprintf(cont_name, "cont.%d", cont_count++);
      LLVMBasicBlockRef cont_bb = LLVMAppendBasicBlockInContext(
        context,
        main_func,
        cont_name
      );

      // 3) reposiciona o builder nesse bloco de continuação
      LLVMPositionBuilderAtEnd(builder, cont_bb);
    }
    free($2);
  }
;



exit_command:
    EXIT {
        // 1) termina a função aqui
        LLVMBuildRetVoid(builder);

        // 2) cria um bloco de continuação único, para qualquer código após o exit
        char cont_name[32];
        snprintf(cont_name, sizeof(cont_name), "cont.exit.%d", exit_cont++);
        LLVMBasicBlockRef cont = LLVMAppendBasicBlockInContext(
            context,
            main_func,
            cont_name
        );

        // 3) move o builder para dentro desse bloco de continuação
        LLVMPositionBuilderAtEnd(builder, cont);
    }
  ;


input_command:
    INPUT IDENTIFIER {
        // 0) Garante que temos a função printf disponível
        LLVMValueRef printf_func = LLVMGetNamedFunction(module, "printf");
        LLVMTypeRef printf_ty;
        if (!printf_func) {
            LLVMTypeRef param_types[] = { LLVMPointerType(LLVMInt8TypeInContext(context), 0) };
            printf_ty = LLVMFunctionType(LLVMInt32TypeInContext(context), param_types, 1, /*isVarArg=*/1);
            printf_func = LLVMAddFunction(module, "printf", printf_ty);
            LLVMSetLinkage(printf_func, LLVMExternalLinkage);
        } else {
            printf_ty = LLVMGetElementType(LLVMTypeOf(printf_func));
        }
        // 0.1) Imprime uma mensagem padrao de input
        LLVMValueRef prompt = LLVMBuildGlobalStringPtr(builder, "input: ", "prompt");
        LLVMBuildCall2(builder, printf_ty, printf_func, (LLVMValueRef[]){ prompt }, 1, "");
        // 1) Obtem (ou adiciona) a declaração de scanf
        LLVMValueRef scanf_func = LLVMGetNamedFunction(module, "scanf");
        if (!scanf_func) {
            // scanf retorna int e recebe (i8*, double*)
            LLVMTypeRef param_types[] = {
                LLVMPointerType(LLVMInt8TypeInContext(context), 0),
                LLVMPointerType(LLVMDoubleTypeInContext(context), 0)
            };
            LLVMTypeRef scanf_type = LLVMFunctionType(
                LLVMInt32TypeInContext(context),
                param_types, 2, /*isVarArg=*/1
            );
            scanf_func = LLVMAddFunction(module, "scanf", scanf_type);
            LLVMSetLinkage(scanf_func, LLVMExternalLinkage);
        }

        // 2) Constroi a string de formato "%lf"
        LLVMValueRef fmt = LLVMBuildGlobalStringPtr(
            builder, "%lf", "fmt_scanf"
        );

        // 3) Passa (&variavel) diretamente, pois globals já são ponteiros
        LLVMValueRef var_ptr = find_or_create_variable($2);

        // 4) Chama scanf(fmt, var_ptr)
        LLVMBuildCall2(
            builder,
            LLVMGetElementType(LLVMTypeOf(scanf_func)),
            scanf_func,
            (LLVMValueRef[]){ fmt, var_ptr },
            2,
            ""
        );

        free($2);
    }
  ;

print_command:
    PRINT value {
        LLVMValueRef printf_func = LLVMGetNamedFunction(module, "printf");
        LLVMTypeRef printf_type;
        if (!printf_func) {
            LLVMTypeRef param_types[] = { LLVMPointerType(LLVMInt8TypeInContext(context), 0) };
            printf_type = LLVMFunctionType(LLVMInt32TypeInContext(context), param_types, 1, 1);
            printf_func = LLVMAddFunction(module, "printf", printf_type);
            LLVMSetLinkage(printf_func, LLVMExternalLinkage);
        } else {
            printf_type = LLVMGetElementType(LLVMTypeOf(printf_func));
        }
        char *format_str = "%f\n";
        LLVMValueRef format = LLVMBuildGlobalStringPtr(builder, format_str, "format");
        LLVMValueRef args[] = { format, $2 };
        LLVMBuildCall2(builder, printf_type, printf_func, args, 2, "");
    }
  ;

bin_command:
    BIN IDENTIFIER IDENTIFIER {
        printf("Bin: %s to %s (not implemented)\n", $2, $3);
        free($2); free($3);
    }
  ;

/* LIST: cria vetor estático e variável de comprimento */
list_command:
    LIST IDENTIFIER {
        // Nome dos globals: "<nome>_data" e "<nome>_len"
        char data_name[256], len_name[256];
        snprintf(data_name, sizeof(data_name), "%s_data", $2);
        snprintf(len_name,  sizeof(len_name),  "%s_len",  $2);

        // 1) Se ainda não existir, cria o array [1024 x double]
        if (!LLVMGetNamedGlobal(module, data_name)) {
            LLVMTypeRef elem_ty  = LLVMDoubleTypeInContext(context);
            // vetor de tamanho fixo 1024
            LLVMTypeRef array_ty = LLVMArrayType(elem_ty, 1024);
            LLVMValueRef data_g  = LLVMAddGlobal(module, array_ty, data_name);
            // inicializa tudo a zero
            LLVMSetInitializer(data_g, LLVMConstNull(array_ty));
        }

        // 2) Se ainda não existir, cria o global i64 para o length
        if (!LLVMGetNamedGlobal(module, len_name)) {
            LLVMTypeRef i64_ty = LLVMInt64TypeInContext(context);
            LLVMValueRef len_g = LLVMAddGlobal(module, i64_ty, len_name);
            // inicializa em 0
            LLVMSetInitializer(len_g, LLVMConstInt(i64_ty, 0, /*isSigned=*/0));
        }

        free($2);
    }
  ;

/* INSERT <valor_var> <lista> */
list_insert:
    INSERT IDENTIFIER IDENTIFIER {
        // Monta nomes dos globals: "<lista>_data" e "<lista>_len"
        char data_name[256], len_name[256];
        snprintf(data_name, sizeof(data_name), "%s_data", $3);
        snprintf(len_name,  sizeof(len_name),  "%s_len",  $3);

        // Obtém os globals já criados em `list_command`
        LLVMValueRef data_g = LLVMGetNamedGlobal(module, data_name);
        LLVMValueRef len_g  = LLVMGetNamedGlobal(module, len_name);
        if (!data_g || !len_g) {
            yyerror("Lista não existe");
            free($2);
            free($3);
            YYABORT;  /* aborta o parse aqui */
        } else {
            LLVMTypeRef i64_ty = LLVMInt64TypeInContext(context);

            // 1) carrega o comprimento atual
            LLVMValueRef len_val = LLVMBuildLoad2(builder, i64_ty, len_g, "len");

            // 2) calcula ponteiro para data[len]
            LLVMValueRef zero    = LLVMConstInt(i64_ty, 0, 0);
            LLVMValueRef indices[2] = { zero, len_val };
            LLVMValueRef elem_ptr = LLVMBuildInBoundsGEP(
                builder,
                data_g,
                indices,
                2,
                "elem_ptr"
            );

            // 3) carrega o valor da variável a inserir
            LLVMValueRef var = find_variable($2);
            if (!var) {
                yyerror("Variável não definida");
                var = find_or_create_variable($2);
            }
            LLVMValueRef val = LLVMBuildLoad2(
                builder,
                LLVMDoubleTypeInContext(context),
                var,
                "val"
            );

            // 4) armazena no array e incrementa len
            LLVMBuildStore(builder, val, elem_ptr);
            LLVMValueRef one     = LLVMConstInt(i64_ty, 1, 0);
            LLVMValueRef new_len = LLVMBuildAdd(builder, len_val, one, "newlen");
            LLVMBuildStore(builder, new_len, len_g);
        }

        free($2);
        free($3);
    }
  ;



/* DELETE <valor_var> <lista> */
list_delete:
    DELETE IDENTIFIER IDENTIFIER {
        // $2 = variável cujo valor será removido
        // $3 = nome da lista
        char data_name[256], len_name[256];
        snprintf(data_name, sizeof(data_name), "%s_data", $3);
        snprintf(len_name,  sizeof(len_name),  "%s_len",  $3);

        // recupera os globals gerados em list_command
        LLVMValueRef data_g = LLVMGetNamedGlobal(module, data_name);
        LLVMValueRef len_g  = LLVMGetNamedGlobal(module, len_name);
        if (!data_g || !len_g) {
            yyerror("Lista não existe");
            free($2);
            free($3);
            YYABORT;
        }

        LLVMTypeRef dbl_ty = LLVMDoubleTypeInContext(context);
        LLVMTypeRef i64_ty = LLVMInt64TypeInContext(context);

        // carrega o valor a ser removido
        LLVMValueRef var = find_variable($2);
        if (!var) {
            yyerror("Variável não definida");
            var = find_or_create_variable($2);
        }
        LLVMValueRef elem_val = LLVMBuildLoad2(
            builder,
            dbl_ty,
            var,
            "elem"
        );

        // bitcast do array estático para double*
        LLVMValueRef data_ptr = LLVMBuildBitCast(
            builder,
            data_g,
            LLVMPointerType(dbl_ty, 0),
            "data_ptr"
        );

        // declara ou recupera a função auxiliar delete_list
        LLVMValueRef del_fn = LLVMGetNamedFunction(module, "delete_list");
        if (!del_fn) {
            LLVMTypeRef params[] = {
                dbl_ty,
                LLVMPointerType(dbl_ty, 0),
                LLVMPointerType(i64_ty, 0)
            };
            LLVMTypeRef fty = LLVMFunctionType(
                LLVMVoidTypeInContext(context),
                params,
                3,
                /*isVarArg=*/0
            );
            del_fn = LLVMAddFunction(module, "delete_list", fty);
            LLVMSetLinkage(del_fn, LLVMExternalLinkage);
        }

        // call delete_list(elem_val, data_ptr, &len)
        LLVMBuildCall2(
            builder,
            LLVMGetElementType(LLVMTypeOf(del_fn)),
            del_fn,
            (LLVMValueRef[]){ elem_val, data_ptr, len_g },
            3,
            ""
        );

        free($2);
        free($3);
    }
  ;



/* IN <elemento_var> <lista> <dest_var> */
list_in_check:
    IN IDENTIFIER IDENTIFIER IDENTIFIER {
        // monta nomes dos globals
        char data_name[256], len_name[256];
        snprintf(data_name, sizeof(data_name), "%s_data",  $3);
        snprintf(len_name,  sizeof(len_name),  "%s_len",   $3);

        // pega o array e o length
        LLVMValueRef data_g = LLVMGetNamedGlobal(module, data_name);
        LLVMValueRef len_g  = LLVMGetNamedGlobal(module, len_name);
        if (!data_g || !len_g) {
            yyerror("Lista não existe");
            free($2); free($3); free($4);
            YYABORT;
        }

        LLVMTypeRef dbl_ty = LLVMDoubleTypeInContext(context);
        LLVMTypeRef i64_ty = LLVMInt64TypeInContext(context);

        // carrega o length
        LLVMValueRef len_val = LLVMBuildLoad2(builder, i64_ty, len_g, "len");

        // carrega o elemento a testar
        LLVMValueRef var = find_variable($2);
        if (!var) {
            yyerror("Variável não definida");
            var = find_or_create_variable($2);
        }
        LLVMValueRef elem_val = LLVMBuildLoad2(builder, dbl_ty, var, "elem");

        // bitcast do global array para double*
        LLVMValueRef data_ptr = LLVMBuildBitCast(
            builder,
            data_g,
            LLVMPointerType(dbl_ty, 0),
            "data_ptr"
        );

        // declara ou recupera a função in_list
        LLVMValueRef in_func = LLVMGetNamedFunction(module, "in_list");
        if (!in_func) {
            LLVMTypeRef fparams[] = { dbl_ty,
                                     LLVMPointerType(dbl_ty,0),
                                     i64_ty };
            LLVMTypeRef fty = LLVMFunctionType(dbl_ty, fparams, 3, /*isVarArg=*/0);
            in_func = LLVMAddFunction(module, "in_list", fty);
            LLVMSetLinkage(in_func, LLVMExternalLinkage);
        }

        // chama in_list(elem_val, data_ptr, len_val)
        LLVMValueRef result = LLVMBuildCall2(
            builder,
            LLVMGetElementType(LLVMTypeOf(in_func)),
            in_func,
            (LLVMValueRef[]){ elem_val, data_ptr, len_val },
            3,
            "inres"
        );

        // armazena o resultado em $4
        LLVMValueRef dest_p = find_or_create_variable($4);
        LLVMBuildStore(builder, result, dest_p);

        free($2); free($3); free($4);
    }
  ;


value:
    NUMBER {
        $$ = LLVMConstReal(LLVMDoubleTypeInContext(context), $1);
    }
  | STRING {
        $$ = LLVMBuildGlobalStringPtr(builder, $1, "str");
        free($1);
    }
  | TRUE         { $$ = LLVMConstReal(LLVMDoubleTypeInContext(context), 1.0); }
  | FALSE        { $$ = LLVMConstReal(LLVMDoubleTypeInContext(context), 0.0); }
  | IDENTIFIER {
      LLVMValueRef var = find_variable($1);
      if (!var) {
          yyerror("Variável não definida");
          /* para não quebrar o parser, cria provisoriamente
             ou aponta para um dummy, conforme seu gosto */
          var = find_or_create_variable($1);
      }
      $$ = LLVMBuildLoad2(builder,
                          LLVMDoubleTypeInContext(context),
                          var,
                          "loadtmp");
      free($1);
  }

%%

/* parserLLVM.y, no epílogo */
void delete_list(double elem, double *data, long *len) {
    /* encontra o índice da primeira ocorrência */
    long i;
    for (i = 0; i < *len; ++i) {
        if (data[i] == elem) break;
    }
    /* se achou, desloca tudo para “fechar o buraco” */
    if (i < *len) {
        for (; i + 1 < *len; ++i) {
            data[i] = data[i+1];
        }
        --*len;
    }
}


double in_list(double elem, double *data, long len) {
    for (long i = 0; i < len; ++i) {
        if (data[i] == elem) return 1.0;
    }
    return 0.0;
}


int main(int argc, char **argv) {
    /* Initialize LLVM */
    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();
    context = LLVMContextCreate();
    module = LLVMModuleCreateWithNameInContext("mengo", context);
    builder = LLVMCreateBuilderInContext(context);

    /* Create main function */
    LLVMTypeRef main_type = LLVMFunctionType(LLVMVoidTypeInContext(context), NULL, 0, 0);
    main_func = LLVMAddFunction(module, "main", main_type);
    LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(context, main_func, "entry");
    LLVMPositionBuilderAtEnd(builder, entry);

    /* Parse input */
    if (argc > 1) yyin = fopen(argv[1], "r");
    int result = yyparse();

    /* Finish main function */
    LLVMBuildRetVoid(builder);

    /* Verify module */
    char *error = NULL;
    if (LLVMVerifyModule(module, LLVMReturnStatusAction, &error)) {
        fprintf(stderr, "Module verification error: %s\n", error);
        LLVMDisposeMessage(error);
        return 1;
    }

    /* Write bitcode (for debugging) */
    LLVMWriteBitcodeToFile(module, "mengo.bc");

    /* Execute with JIT */
    LLVMExecutionEngineRef engine;
    if (LLVMCreateExecutionEngineForModule(&engine, module, &error)) {
        fprintf(stderr, "Error creating execution engine: %s\n", error);
        LLVMDisposeMessage(error);
        return 1;
    }
    
    LLVMLoadLibraryPermanently(NULL);

    LLVMRunFunction(engine, main_func, 0, NULL);

    /* Cleanup */
    for (int i = 0; i < symbol_count; i++) {
        free(symbol_table[i].name);
    }
    LLVMDisposeExecutionEngine(engine);
    LLVMDisposeBuilder(builder);
    LLVMContextDispose(context);

    return result;
}
