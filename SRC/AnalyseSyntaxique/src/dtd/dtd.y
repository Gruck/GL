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

/*Noeud root de l'arborescence*/
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
		/*Instanciation du socle de la structure de donnee */
        DtdDataStructure = new DtdDoc("");
		/* GESTION DES ELEMENTS */
        for (std::list<DtdElement*>::iterator it = listElements.begin(); it != listElements.end(); it++)
		{
            DtdDataStructure->AddElement(*it);
        }
		/* GESTION DES ATTRIBUTS */
		for (ListAttributesPerElement::iterator it = listAttributesPerElement.begin();
				it != listAttributesPerElement.end(); it++)
		/* Pour chaque attribut détecté dans le fichier */
		{
			/* On recherche l'element concerné par cet attribut */
			DtdElement* element = DtdDataStructure->element((*it)->element);
			if(element != 0)
			{
				/* Si il est valide, on copie tout les attributs dans la structure 
				 * dans les éléments */
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
        /*Détection d'une ATTLIST*/
		{
            S_Attribute *newAttribute = new S_Attribute;
            newAttribute->attributes = *$4;
			delete $4; /* destruction de la liste de pointeur utilisée */
            newAttribute->element = string($3);
            listAttributesPerElement.push_back(newAttribute);
        }
   | dtd ELEMENT NAME choix_ou_sequence cardinalite CLOSE 
        /*Détection d'un élément*/
		{
			/*Recuperation de la cardinalite liee a la liste de contenu detecte*/
            $4->setMultiplicity($5);
			/*Instanciation et stockage de l'element dans la liste d'elements*/
            DtdElement *CurrentDtdNode = new DtdElement(string($3),$4);
            listElements.push_back(CurrentDtdNode);
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
		/* L'element de choix fait office de noeud dans notre arborecence 
		 * ainsi, nous instancions un nouvel objet de type DtdPossibleContent
		 * qui sera ensuite retourné, qui va encapsuler la liste de choix 
		 * construite auparavant par le parser.
		 */
        {
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
		/* Nous récupérons une séquence de possible Content 
		 * que nous encapsulons dans un objet de type DtdPossibleContent
		 */
        {
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
        /* Etape permettant d'éviter un conflit
		 */
		{
            $1->push_back($3);
            $$ = $1;
        }
		;

liste_sequence: item 
		/* Lorsque l'on rencontre un item simple
		 * c'est que nous sommes en début de liste
		 * ainsi on instancie une nouvelle liste 
		 * et on ajoute le premier element
		 */
		{
            ListContent *newList = new ListContent;
            newList->push_back($1);  
            $$= newList;
        } 
	      | liste_sequence COMMA item
		/* On ajoute en fin de liste l'élément détecté
		 * et on remonte la liste
		 */
        {
            $1->push_back($3);
            $$ = $1;
        }    
	      ;

item: NAME cardinalite
	/* Instanciation d'un DtdPossibleContent*/
    {
        DtdPossibleContent *newDtdContentNode = 
        new DtdPossibleContent(DtdPossibleContent::T_ELEM,string($1),$2);
        $$ = newDtdContentNode;    
    }
    | PCDATA cardinalite
	/* Un #PCDATA est condsidere comment element normal au nom fixe
	 * #PCDATA
	 */
    {
        DtdPossibleContent *newDtdContentNode = 
            new DtdPossibleContent(DtdPossibleContent::T_ELEM,string("#PCDATA"),$2);
        $$ = newDtdContentNode;  
    }
    | choix_ou_sequence cardinalite
	/* Cas ou nous récupérons un sous enssemble d'attribut
	 * Nous récupérons ainsi sa multiplicté et retournons
	 * l'objet de type DtdPossibleContent contenant tous
	 * les noeuds fils
	 */ 
    {       
        $1->setMultiplicity($2);
        $$ = $1;       
    }
    ;

liste_choix: item
           /* Même principe que la construction qu'une liste
			* sequence
			*/
		   {
                ListContent *newList = new ListContent;
                newList->push_back($1);
                $$ = newList; 
           }
           | liste_choix PIPE item
			/* On ajoute en fin de liste l'élément détecté
			 * et on remonte la liste
			 */
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
/* Le type est forcé à #CDATA d'après l'ennoncé*/
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


