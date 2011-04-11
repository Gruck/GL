%{
using namespace std;
#include <stack>
#include <list>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#include "DtdDoc.h"
#include "DtdElement.h"
#include "DtdAttribute.h"
#include "DtdPossibleContent.h"

void dtderror(char *msg);
int dtdwrap(void);
int dtdlex(void);


/*root node of the dtd collection*/
DtdDoc *DtdDataStructure;
/*Highlighted node in the collection*/
DtdElement *CurrentDtdNode = 0;
/*Root possible content*/
DtdPossibleContent *RootPossibleContent =0;


%}

%union { 
   char *s;
   DtdPossibleContent::Multiplicity c;
   }

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA
%token <s> NAME TOKENTYPE DECLARATION STRING
%type <c> cardinalite
%%

main: dtd {DtdDataStructure = new DtdDoc("");}                
    ; 

dtd: dtd ATTLIST NAME att_definition CLOSE 
   | dtd ELEMENT NAME choix_ou_sequence cardinalite CLOSE 
        {
            // Instanciation du de l'élément et de sa liste a la detection du tag élément
            RootPossibleContent = new DtdPossibleContent(DtdPossibleContent::T_ELEM,string("root"),$5);
            CurrentDtdNode = new DtdElement(string($3),RootPossibleContent);
        }
   | /* empty */                     
   ;

choix_ou_sequence: choix
		 | sequence
		 ;

choix: OPENPAR liste_choix_plus CLOSEPAR
     ;

sequence: OPENPAR liste_sequence CLOSEPAR
        ;

cardinalite
       : AST
       {
            $$ = DtdPossibleContent::M_AST;
       }
       |QMARK 
       {
            $$ = DtdPossibleContent::M_QMARK;
       }
       |PLUS 
       {
            $$ = DtdPossibleContent::M_PLUS;
       }
       | /* empty */ 
       {
            $$ = DtdPossibleContent::M_NONE;
       }
	   ;

liste_choix_plus: liste_choix PIPE item
        {
            // A  la détection d'une liste de choix on instancie un possible Content    
            //CurrentChoicePossibleContent = new DtdPossibleContent*();
        }
		;

liste_sequence: item 
	      | liste_sequence COMMA item
        {
            // A  la détection d'une liste de sequence on instancie un possible Content    
            //CurrentChoicePossibleContent = new DtdPossibleContent*();
        }    
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
int dtdwrap(void)
{
  return 1;
}

void dtderror(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}


