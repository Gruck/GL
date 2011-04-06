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

string DtdUrl;
XmlDoc *XmlDataStructure;
XmlElement *CurrentNode = 0;
XmlElement *tempNode;

%}

%union {
   char * s;
   ElementName * en;  /* le nom d'un element avec son namespace */
}

%token EQ SLASH CLOSE END CLOSESPECIAL DOCTYPE
%token <s> ENCODING VALUE DATA COMMENT NAME NSNAME
%token <en> NSSTART START STARTSPECIAL

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
	{
 		CurrentNode = new XmlElement(string(""), $1->second);
		XmlDataStructure->setRoot(CurrentNode);
	}
	else
	{
		tempNode = new XmlElement(string(""), $1->second);
		CurrentNode->addChild(tempNode);
		CurrentNode = tempNode;
	}
 }		
 | NSSTART	
 ;
empty_or_content
 : SLASH CLOSE 
 {
	CurrentNode = CurrentNode->parent();
 }	
 | close_content_and_end 
   name_or_nsname_opt CLOSE 
 {
	CurrentNode = CurrentNode->parent();
 }	
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

/*int main(int argc, char **argv)
{
  int err;

  err = yyparse();
  if (err != 0) printf("Parse ended with %d error(s)\n", err);
  	else  printf("Parse ended with sucess\n", err);
  return 0;
}*/
int yywrap(void)
{
  return 1;
}

void yyerror(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

