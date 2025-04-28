# mengo
Mengo Programing Language

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

math_operation = add_sub_mul_div
               | mod_operation ;

add_sub_mul_div = ("add" | "sub" | "mul" | "div") identifier identifier identifier ;

mod_operation = "mod" identifier ( identifier identifier | identifier ) ;

logical_operation = ("and" | "or") identifier identifier identifier
                  | "not" identifier identifier ;

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

print_command  = "print" identifier ;

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
