%{
using namespace std;
#include <stack>
#include <list>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#include "communDtd.h"

#include "DtdDoc.h"
#include "DtdElement.h"
#include "DtdPossibleContent.h"

void dtderror(char *msg);
int dtdwrap(void);
int dtdlex(void);

/*list Elements */
std::list<DtdElement*> listElements;

/*liste d'attributs*/
ListAttributesPerElement listAttributesPerElement;

/*root node of the dtd collection*/
DtdDoc *DtdDataStructure = 0;
%}

%union { 
   char *s;
   DtdPossibleContent::Multiplicity c;
   DtdPossibleContent* i;
   ListContent *lc;
   ListAttributes *da;
   DtdAttribute *a;
   }

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA
%token <s> NAME TOKENTYPE DECLARATION STRING
%type <c> cardinalite
%type <i> item choix sequence choix_ou_sequence 
%type <lc> liste_choix_plus liste_sequence liste_choix
%type <da> att_definition
%type <a> attribut
%%

main: dtd 
    {
        cout << "Création de la structure de base"<<endl;
        DtdDataStructure = new DtdDoc("");
        for (std::list<DtdElement*>::iterator it = listElements.begin(); it != listElements.end(); it++)
        {
            DtdDataStructure->AddElement(*it);
        }
		for (ListAttributesPerElement::iterator it = listAttributesPerElement.begin();
				it != listAttributesPerElement.end(); it++) 
		{
			printf((*it)->element.c_str());
			DtdElement* element = DtdDataStructure->element((*it)->element);
			if(element != 0)
			{
				for (ListAttributes::iterator itAt = (*it)->attributes.begin();
												itAt != (*it)->attributes.end() ; itAt++) 
				{
					element->addAttribute((*itAt)->first,(*itAt)->second);
				}
			}
		}
    }                
    ; 

dtd: dtd ATTLIST NAME att_definition CLOSE 
        {
            S_Attribute *newAttribute = new S_Attribute;
            newAttribute->attributes = *$4;
			delete $4;
            newAttribute->element = string($3);
            listAttributesPerElement.push_back(newAttribute);
        }
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
            delete $2;
            $$ = newContent;
        }
     ;

sequence: OPENPAR liste_sequence CLOSEPAR
        {
            cout << "Création d'une liste séquence"<<endl;
            DtdPossibleContent *newContent = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE,"",DtdPossibleContent::M_NONE);
            for(std::list<DtdPossibleContent*>::iterator it = $2->begin(); it != $2->end(); it++)
            {
                newContent->addChild(*it);
            }
            delete $2;
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
{
    $1->push_back($2);
}
| /* empty */
{
    $$ = new std::list<DtdAttribute*>
}
;

attribut
: NAME att_type defaut_declaration
{
    $$ = new DtdAttribute(string($1),string("#CDATA"));   
}
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


