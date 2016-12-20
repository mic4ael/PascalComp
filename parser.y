%{

int yylex();
int yyerror(char *s);

%}

%token DONE 0

%left '-' '+'
%left '*' '/'

%%

program: 
    program id ( identifier_list );
    declarations
    subprogram_declarations
    compound_statement
    ;

identifier_list: id
    | identifier-list , id
    ;

declarations:
    declarations var identifier-list : type ;
    | \n
    ;

type: standard_type
    | array [ num . . num ] of standard_type
    ;

standard_type: integer
    | real
    ;

subprogram_declarations:
    subprogram_declarations subprogram_declaration ;
    | \n
    ;

subprogram_declaration:
    subprogram_head declarations compound_statement
    ;

subprogram_head: function id arguments : standard_type ;
    | procedure id arguments
    ;

arguments:
    ( parameter-list )
    | \n
    ;

parameter_list: identifier_list : type
    | parameter_list ; identifier_list : type
    ;

compound_statement:
    begin
    optional_statements
    end
    ;

optional_statements: statement_list
    | \n
    ;

statement_list: statement
    | statement_list ; statement
    ;

statement: variable assignop expression
    | procedure_statement
    | compound-statement
    | if expression then statement else statement
    | while expression do statement
    ;

variable: id
    | id [ expression ]
    ;

procedure_statement: id
    | id ( expression-list )
    ;

expression_list: expression
    | expression_list , expression
    ;

expression: simple_expression
    | simple_expression relop simple_expression
    ;

simple_expression: term
    | sign term
    | simple_expression sign term
    | simple_expression or term
    ;

term: factor
    | term mulop factor
    ;

factor: variable
    | id ( expression_list )
    | num
    | ( expression )
    | not factor
    ;

%%

int yyerror(char *err)
{
    return 0;
}