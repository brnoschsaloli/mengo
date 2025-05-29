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
               | list_command
               | list_insert
               | list_delete
               | list_in_check ;

assignment     = "set" identifier value ;

math_operation = add_sub_mul_div_mod
               | mod_operation ;

add_sub_mul_div_mod = ("add" | "sub" | "mul" | "div" | "mod") identifier value value ;

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

list_command   = "list" identifier ;

list_insert    = "insert" identifier identifier ;

list_delete    = "delete" identifier identifier ;

list_in_check  = "in" identifier identifier identifier ;

get_command    = "get" value identifier identifier ;

identifier     = letter { letter | digit } ;

value          = number | string | identifier ;

number         = ["-"] digit { digit } ;

string         = "'" { character } "'" ;

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

## Rodando os Testes

O projeto inclui uma suíte de testes que verifica todas as funcionalidades da linguagem. Para rodar os testes:

1. Certifique-se de que o compilador está compilado (veja seção "Compilação")
2. Entre no diretório de testes:
```bash
cd tests
```

3. Execute o script de testes:
```bash
./run_tests.sh
```

Os testes incluem:
- Operações aritméticas (arithmetic.fla)
- Operações lógicas (logical.fla)
- Controle de fluxo (control_flow.fla)
- Operações com listas (lists.fla)
- Entrada/Saída (io.fla)

Cada arquivo de teste demonstra diferentes aspectos da linguagem e inclui comentários explicativos sobre o que está sendo testado.

## Compilação

```bash
wsl (caso esteja rodando no windows)
flex compiler/lexer.l
bison -d parserLLVM.y
gcc -rdynamic -o mengo parserLLVM.tab.c lex.yy.c `llvm-config --cflags --ldflags --libs core` -Wno-deprecated-declarations
./mengo <seu_programa>.fla
```
