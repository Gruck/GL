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

typedef std::list<DtdPossibleContent*> PossibleContentList;


void dtderror(char *msg);
int dtdwrap(void);
int dtdlex(void);
/*root node of the dtd collection*/
DtdDoc *DtdDataStructure;
/*Highlighted node in the collection*/
DtdElement *CurrentDtdNode = 0;
/*Possible content en liste choix*/
DtdPossibleContent *ChoicePossibleContent = 0;
/*Possible content en liste sequence*/
DtdPossibleContent *SequencePossibleContent =0;
/*Possible content actuellement traité */
DtdPossibleContent *CurrentPossibleContent =0;

%}

%union { 
   char *s; 
   }

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA
%token <s> NAME TOKENTYPE DECLARATION STRING
%%

main: dtd {DtdDataStructure = new DtdDoc("");}                
    ; 

dtd: dtd ATTLIST NAME att_definition CLOSE 
   | dtd ELEMENT NAME choix_ou_sequence cardinalite CLOSE 
        {
            // Instanciation du de l'élément et de sa liste a la detection du tag élément
            PossibleContentList  *currentPossibleContentList = new PossibleContentList;
            CurrentDtdNode = new DtdElement(string($3),*currentPossibleContentList);
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

cardinalite: AST|QMARK|PLUS| /* empty */
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


