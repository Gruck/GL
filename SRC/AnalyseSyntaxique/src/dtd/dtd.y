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

typedef std::list<DtdPossibleContent*> ListContent;


/*list Elements */
std::list<DtdElement*> listElements;

/*root node of the dtd collection*/
DtdDoc *DtdDataStructure = 0;
%}

%union { 
   char *s;
   DtdPossibleContent::Multiplicity c;
   DtdPossibleContent* i;
   ListContent *lc;
   }

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA
%token <s> NAME TOKENTYPE DECLARATION STRING
%type <c> cardinalite
%type <i> item choix sequence choix_ou_sequence 
%type <lc> liste_choix_plus liste_sequence liste_choix
%%

main: dtd 
    {
        cout << "Création de la structure de base"<<endl;
        DtdDataStructure = new DtdDoc("");
        for (std::list<DtdElement*>::iterator it = listElements.begin(); it != listElements.end(); it++)
        {
            DtdDataStructure->AddElement(*it);
        }
    }                
    ; 

dtd: dtd ATTLIST NAME att_definition CLOSE 
   | dtd ELEMENT NAME choix_ou_sequence cardinalite CLOSE 
        {
            cout << "Création d'un élément"<<endl;
            $4->setMultiplicity($5);
            DtdElement *CurrentDtdNode = new DtdElement(string($3),$4);
            listElements.push_back(CurrentDtdNode);
        }
   | /* empty */                     
   ;

choix_ou_sequence: choix 
         {
            
            cout << "sélection d'un choix"<<endl;
            $$ = $1;   
         }
		 | sequence 
         {
            
            cout << "sélection d'une séquence"<<endl;
            $$ = $1;   
         }
		 ;

choix: OPENPAR liste_choix_plus CLOSEPAR
        {
            cout << "Créaton d'une Liste choix"<<endl;
            DtdPossibleContent *newContent = new DtdPossibleContent(DtdPossibleContent::T_CHOICE,"",DtdPossibleContent::M_NONE);
            for (std::list<DtdPossibleContent*>::iterator it = $2->begin(); it != $2->end(); it++)
            {
                newContent->addChild(*it);
            }
            $$ = newContent;
        }
     ;

sequence: OPENPAR liste_sequence CLOSEPAR
        {
            cout << "Création d'une liste séquence"<<endl;
            DtdPossibleContent *newContent = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE,"",DtdPossibleContent::M_NONE);
            for (std::list<DtdPossibleContent*>::iterator it = $2->begin(); it != $2->end(); it++)
            {
                newContent->addChild(*it);
            }
            $$ = newContent;
        }
        ;

cardinalite
       : AST
       {
            cout << "Cardinalité Astérisque"<<endl;
            $$ = DtdPossibleContent::M_AST;
       }
       |QMARK 
       {
        
            cout << "Cardinalité QMARK"<<endl;
            $$ = DtdPossibleContent::M_QMARK;
       }
       |PLUS 
       {
            cout << "Cardinalité PLUS"<<endl;
            $$ = DtdPossibleContent::M_PLUS;
       }
       | /* empty */ 
       {
            cout << "Cardinalité Bonne soeur"<<endl;
            $$ = DtdPossibleContent::M_NONE;
       }
	   ;

liste_choix_plus: liste_choix PIPE item
        {
            //
            $1->push_back($3);
            $$ = $1;
        }
		;

liste_sequence: item 
        {
            //
            ListContent *newList = new ListContent;
            newList->push_back($1);  
            $$= newList;
        } 
	      | liste_sequence COMMA item
        {
            //    
            $1->push_back($3);
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
        $1->setMultiplicity($2);
        $$ = $1;       
    }
    ;

liste_choix: item
           {
                ListContent *newList = new ListContent;
                newList->push_back($1);
                $$ = newList; 
           }
           | liste_choix PIPE item
           {
                $1->push_back($3);
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


