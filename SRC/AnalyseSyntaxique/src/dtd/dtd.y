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
   DtdPossibleContent* i;
   }

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA
%token <s> NAME TOKENTYPE DECLARATION STRING
%type <c> cardinalite
%type <i> item choix sequence choix_ou_sequence liste_choix_plus liste_sequence liste_choix
%%

main: dtd 
    {
        DtdDataStructure = new DtdDoc("");
    }                
    ; 

dtd: dtd ATTLIST NAME att_definition CLOSE 
   | dtd ELEMENT NAME choix_ou_sequence cardinalite CLOSE 
        {
            // Instanciation du de l'élément et de sa liste a la detection du tag élément
            CurrentDtdNode = new DtdElement(string($3),RootPossibleContent); 
            RootPossibleContent = new DtdPossibleContent(DtdPossibleContent::T_ELEM,string(""),$5);
            // On initialise le noeud root comme premier noeud parent
            DtdDataStructure->AddElement(CurrentDtdNode);
        }
   | /* empty */                     
   ;

choix_ou_sequence: choix 
         {
            $$ = $1;   
         }
		 | sequence 
         {
            $$ = $1;   
         }
		 ;

choix: OPENPAR liste_choix_plus CLOSEPAR
        {
            $$ = $2;
        }
     ;

sequence: OPENPAR liste_sequence CLOSEPAR
        {
            $$ = $2;
        }
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
            //
            $1->addChild($3);
            $$ = $1;
        }
		;

liste_sequence: item 
        {
            //    
            $$=$1;
        }
	      | liste_sequence COMMA item
        {
            //    
            $1->addChild($3);
            $$ = $1;
        }    
	      ;

item: NAME cardinalite
    {
        DtdPossibleContent *newDtdContentNode = 
            new DtdPossibleContent(DtdPossibleContent::T_ELEM,string($1),$2);
        $$ = newDtdContentNode;    
    }
    | PCDATA cardinalite
    {
        DtdPossibleContent *newDtdContentNode = 
            new DtdPossibleContent(DtdPossibleContent::T_ELEM,string("#PCDATA"),$2);
        $$ = newDtdContentNode;  
    }
    | choix_ou_sequence cardinalite
    {       
        // TODO AJOUTER L'IMPLEMENTATION DU SETTER VERS CARDINALITE
        $1->setMultiplicity($2);
        $$ = $1;       
    }
    ;

liste_choix: item
           {
                $$ = $1; 
           }
           | liste_choix PIPE item
           {
                $1->addChild($3);
                $$ = $1;
           }
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


