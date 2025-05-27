# Mengo Programing Language

```ebnf
program        = { line } ;

line           = [ indent ] ( command | comment ) newline ;

indent         = "\t" ;

comment        = "`" { character_except_newline } ;

command        = assignment
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
               | list_in_check ;

assignment     = "set" identifier value ;

math_operation = add_sub_mul_div_pow
               | mod_operation ;

add_sub_mul_div_pow = ("add" | "sub" | "mul" | "div" | "pow") identifier value value ;

mod_operation = "mod" identifier ( value value | value ) ;


logical_operation = ("and" | "or") identifier value value
                  | "not" identifier value ;

condition      = "if" comparison ;

comparison     = identifier comparator value ;

comparator     = "equal" 
               | "notequal" 
               | "less" 
               | "greater" 
               | "lessequal" 
               | "greaterequal" ;

label_def      = "label" identifier ;

goto_command   = "goto" identifier ;

exit_command   = "exit" ;

input_command  = "input" identifier ;

print_command  = "print" value ;

bin_command    = "bin" identifier identifier ;

list_command   = "list" identifier ;

list_insert    = "insert" identifier identifier ;

list_delete    = "delete" identifier identifier ;

list_in_check  = "in" identifier identifier identifier ;

identifier     = letter { letter | digit | "_" } ;

value          = number | string | identifier ;

number         = ["-"] digit { digit } ;

string         = '"' { character } '"' ;

letter         = "A".."Z" | "a".."z" ;

digit          = "0".."9" ;

character      = ? qualquer caractere exceto '"' ? ;

character_except_newline = ? qualquer caractere exceto "\n" ? ;

newline        = "\n" ;
```

compiler: 
```bash
wsl
flex lexer.l
bison -d parserLLVM.y
gcc -rdynamic -o mengo parserLLVM.tab.c lex.yy.c `llvm-config --cflags --ldflags --libs core` -Wno-deprecated-declarations
./mengo <seu_programa>.fla
```

implementando true e false:

brnoschsaloli@schnolisg15:/mnt/c/Users/brnos/OneDrive/Documentos/insper/7comp/logcomp/mengo$ ./mengo test.fla
Error: Variável não definida at line 1
0.000000

verificar codigo do test.fla

chat: definicao de label llvm