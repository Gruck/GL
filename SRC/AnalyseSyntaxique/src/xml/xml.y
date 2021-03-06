%{

using namespace std;
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include "commun.h"
#include "xml.tab.h"
#include "XmlDoc.h"
#include "XmlElement.h"
#include "XmlAttribute.h"
#include "XmlContent.h"
#include "XmlText.h"


int yywrap(void);
void yyerror(char *msg);
int yylex(void);

/* Name of the linked dtd in xml document */
string DtdUrl;
/* Root node of the tree */
XmlDoc *XmlDataStructure;
/* Highlighted node in the tree */
XmlElement *CurrentNode = 0;
/* New node of the tree, created when an open markup is detected */
XmlElement *tempNode;
	

%}

%union {
   char * s;
   ElementName * en;  /* le nom d'un element avec son namespace */
   AttList *la; 
}

%token EQ SLASH CLOSE END CLOSESPECIAL DOCTYPE
%token <s> ENCODING VALUE DATA COMMENT NAME NSNAME
%token <en> NSSTART START STARTSPECIAL

%type <la> attributes

%%

document
 : declarations element misc_seq_opt 
 ;
misc_seq_opt
 : misc_seq_opt misc
 | /*empty*/
 ;
misc
 : COMMENT		
 ;

declarations
 : declaration
 | /*empty*/
 ;
 
declaration
 : DOCTYPE NAME NAME VALUE CLOSE {DtdUrl = $4; XmlDataStructure = new XmlDoc(DtdUrl);} 
 ;

element
 : start          
   empty_or_content 
 ;
start
 : START 
 {
	if (!CurrentNode)
// When the parser meets an opening markup
// if the currentNde is 0, it means that we met the root node of tree
// We instanciate the object and set him root  
	{
 		CurrentNode = new XmlElement(string(""), $1->second);
		XmlDataStructure->setRoot(CurrentNode);
	}
	else
// Else we create a new tempNode, add it like a child
// of the current node, and set him as new Current Node
// because of the LALR analysis
	{
		tempNode = new XmlElement(string(""), $1->second);
		CurrentNode->addChild(tempNode);
		CurrentNode = tempNode;
	}
 }		
 | NSSTART
 {
	if (!CurrentNode)
	{
 		CurrentNode = new XmlElement($1->first, $1->second);
		XmlDataStructure->setRoot(CurrentNode);
	}
	else
	{
		tempNode = new XmlElement($1->first, $1->second);
		CurrentNode->addChild(tempNode);
		CurrentNode = tempNode;
	}
 }	
 ;
empty_or_content
 : attributes SLASH CLOSE 
 {
	 for ( AttList::iterator it = $1->begin() ; it != $1->end() ; it++ )
	 {
		 CurrentNode->addAttribute((*it).first, (*it).second);
	 }
	CurrentNode = CurrentNode->parent();
 }	
 | attributes close_content_and_end
   name_or_nsname_opt CLOSE 
 {
	for ( AttList::iterator it = $1->begin() ; it != $1->end() ; it++ )
	{
		CurrentNode->addAttribute((*it).first, (*it).second);
	}
	CurrentNode = CurrentNode->parent();
 }	
 ;

attributes
 : attributes NAME EQ VALUE
{
	$1->push_back(make_pair($2, $4));
}
| /* empty */ { $$ = new AttList }
 ;


name_or_nsname_opt 
 : NAME     
 | NSNAME  
 | /* empty */
 ;
close_content_and_end
 : CLOSE			
   content 
   END 
 ;
content 
 : content DATA	
 {
	CurrentNode->addChild(new XmlText($2));
 }	
 | content misc        
 | content element      
 | /*empty*/         
 ;
%%

int yywrap(void)
{
  return 1;
}

void yyerror(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

