# Mengo Programming Language

```ebnf
program        = { line } ;

line           = [ indent ] ( command | comment ) newline ;

indent         = "\t" ;

comment        = "`" { character_except_newline } ;

command        = assignment
               | math_operation
               | logical_operation
               | condition
               | while_loop
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

add_sub_mul_div_pow = ("add" | "sub" | "mul" | "div" | "mod") identifier value value ;

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

while_loop     = "while" comparison ;

exit_command   = "exit" ;

input_command  = "input" identifier ;

print_command  = "print" value ;

bin_command    = "bin" identifier identifier ;

list_command   = "list" identifier ;

list_insert    = "insert" identifier identifier ;

list_delete    = "delete" identifier identifier ;

list_in_check  = "in" identifier identifier identifier ;

get_command    = "get" value identifier identifier ;

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

## Exemplo de uso

```fla
input n
list numeros
set i 0
while i less n
    input temp
    insert temp numeros
    add i 1 i

set j 0
set soma 0
while j less n
    get j numeros atual
    print atual
    add soma atual soma
    add j 1 j
print "soma: "
print soma
if soma less 10
    print "soma menor que 10"
if soma greaterequal 10
    print "soma maior ou igual a 10"
exit

```

## Compilação

```bash
wsl
flex lexer.l
bison -d parserLLVM.y
gcc -rdynamic -o mengo parserLLVM.tab.c lex.yy.c `llvm-config --cflags --ldflags --libs core` -Wno-deprecated-declarations
./mengo <seu_programa>.fla
```
