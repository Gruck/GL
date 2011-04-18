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


int xsltwrap(void);
void xslterror(char *msg);
int xsltlex(void);

/* Name of the linked dtd in xml document */
string Xslt_DtdUrl;
/* Root node of the tree */
XmlDoc *XsltDataStructure;
/* Highlighted node in the tree */
XmlElement *Xslt_CurrentNode = 0;
/* New node of the tree, created when an open markup is detected */
XmlElement *Xslt_tempNode;

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
: DOCTYPE NAME NAME VALUE CLOSE {Xslt_DtdUrl = $4; XsltDataStructure = new XmlDoc(Xslt_DtdUrl);} 
;

element
: start          
empty_or_content 
;
start
: START 
{
	if (!Xslt_CurrentNode)
		// When the parser meets an opening markup
		// if the currentNde is 0, it means that we met the root node of tree
		// We instanciate the object and set him root  
	{
 		Xslt_CurrentNode = new XmlElement(string(""), $1->second);
		XsltDataStructure->setRoot(Xslt_CurrentNode);
	}
	else
		// Else we create a new tempNode, add it like a child
		// of the current node, and set him as new Current Node
		// because of the LALR analysis
	{
		Xslt_tempNode = new XmlElement(string(""), $1->second);
		Xslt_CurrentNode->addChild(Xslt_tempNode);
		Xslt_CurrentNode = Xslt_tempNode;
	}
}		
| NSSTART
{
	if (!Xslt_CurrentNode)
	{
 		Xslt_CurrentNode = new XmlElement($1->first, $1->second);
		XsltDataStructure->setRoot(Xslt_CurrentNode);
	}
	else
	{
		Xslt_tempNode = new XmlElement($1->first, $1->second);
		Xslt_CurrentNode->addChild(Xslt_tempNode);
		Xslt_CurrentNode = Xslt_tempNode;
	}
}	
;
empty_or_content
: attributes SLASH CLOSE 
{
	for ( AttList::iterator it = $1->begin() ; it != $1->end() ; it++ )
	{
		Xslt_CurrentNode->addAttribute((*it).first, (*it).second);
	}
	Xslt_CurrentNode = Xslt_CurrentNode->parent();
}	
| attributes close_content_and_end
name_or_nsname_opt CLOSE 
{
	for ( AttList::iterator it = $1->begin() ; it != $1->end() ; it++ )
	{
		Xslt_CurrentNode->addAttribute((*it).first, (*it).second);
	}
	Xslt_CurrentNode = Xslt_CurrentNode->parent();
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
	Xslt_CurrentNode->addChild(new XmlText($2));
}	
| content misc        
| content element      
| /*empty*/         
;	
%%

int xsltwrap(void)
{
  return 1;
}

void xslterror(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

