%{
using namespace std;
#include <stack>
#include <list>
#include <cstring>
#include <cstdio>
#include <cstdlib>


void yyerror(char *msg);
int yywrap(void);
int yylex(void);
%}

%union { 
   char *s; 
   }

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA
%token <s> NAME TOKENTYPE DECLARATION STRING
%%

main: dtd                           
    ;

dtd: dtd ATTLIST NAME 
     att_definition CLOSE            
   | dtd ELEMENT NAME choix_ou_sequence cardinalite CLOSE
   | /* empty */                     
   ;

choix_ou_sequence: choix
		 | sequence
		 ;

choix: OPENPAR liste_choix_plus CLOSEPAR
     ;

sequence: OPENPAR liste_sequence CLOSEPAR
        ;

cardinalite: AST|QMARK|PLUS| /* empty */
	   ;

liste_choix_plus: liste_choix PIPE item
		;

liste_sequence: item 
	      | liste_sequence COMMA item
	      ;

item: NAME cardinalite
    | PCDATA cardinalite
    | choix_ou_sequence cardinalite
    ;

liste_choix: item
           | liste_choix PIPE item
           ;


att_definition
: att_definition attribut
| /* empty */
;

attribut
: NAME att_type defaut_declaration
;

att_type
: CDATA    
| TOKENTYPE
| type_enumere
;

type_enumere
: OPENPAR liste_enum_plus CLOSEPAR
;

liste_enum_plus
: liste_enum PIPE item_enum
;

liste_enum
: item_enum               
| liste_enum PIPE item_enum
;

item_enum
: NAME
;

defaut_declaration
: DECLARATION 
| STRING     
| FIXED STRING 
;
%%
int main(int argc, char **argv)
{
  int err;

  err = yyparse();
  if (err != 0) printf("Parse ended with %d error(s)\n", err);
        else  printf("Parse ended with sucess\n", err);
  return 0;
}
int yywrap(void)
{
  return 1;
}

void yyerror(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}


