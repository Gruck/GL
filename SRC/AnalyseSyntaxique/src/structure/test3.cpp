
#include <assert.h>

#include "XmlElement.h"
#include "XmlContent.h"
#include "XmlAttribute.h"
#include "XmlText.h"
#include "XmlDoc.h"
#include "DtdDoc.h"
#include "DtdPossibleContent.h"
#include "DtdElement.h"
#include "XmlValidator.h"


bool test3a();
bool test3b();


int main(){
  std::cout<<"Ce jeu de test a pour objectif de tester les fonctionalités liées à la validation des attributs\n";
  assert( test3a() );
  std::cout << "\n\n\n";
  assert( test3b() );
  std::cout << "\n\n\n";
 
}

bool test3a(){
  std::cout << "======================================= Test Attrib a\n"; 
  std::cout << "--------------------------------------- create xml\n"; 
  XmlDoc* xml = new XmlDoc("html");
  xml->setRoot( new XmlElement("root") );
  xml->root()->addAttribute("paramqeg","bouh");
  xml->root()->addChild( new XmlElement("foo") );
  xml->root()->childElement( "foo" )->addChild( new XmlText("du text") );
  xml->root()->childElement( "foo" )->addChild( new XmlElement("bar") );
  xml->root()->childElement( "foo" )->childElement( "bar" )->addChild( new XmlText("encore du text") );
  std::cout << "--------------------------------------- create dtd\n";
  DtdDoc* dtd = new DtdDoc("html");
  DtdPossibleContent* pc1 = new DtdPossibleContent(DtdPossibleContent::T_CHOICE);

  pc1->addChild(new DtdPossibleContent(DtdPossibleContent::T_ELEM,"foo"));
  pc1->addChild(new DtdPossibleContent(DtdPossibleContent::T_ELEM,"bar"));
  DtdElement* root = new DtdElement("root",pc1);
  dtd->AddElement( root );
  root->addAttribute("param","#PCDATA");
  dtd->AddElement(new DtdElement("foo"
    , new DtdPossibleContent(DtdPossibleContent::T_ELEM,"#PCDATA") ) );
  dtd->AddElement(new DtdElement("bar"
    , new DtdPossibleContent(DtdPossibleContent::T_ELEM,"#PCDATA") ) );
  std::cout << "--------------------------------------- print xml\n";
  xml->toStream(std::cout);
  std::cout << "--------------------------------------- print dtd\n";
  dtd->toStream(std::cout); 
  assert( dtd->element("foo")->name() == std::string("foo") );
  
  std::cout << "--------------------------------------- Validation du Xml\n";
  bool status = !XmlValidator::validate(xml, dtd);

  std::cout << "--------------------------------------- delete xml\n";
  delete xml;
  std::cout << "--------------------------------------- delete dtd\n";
  delete dtd;
  
  return status;
}

bool test3a(){
  std::cout << "======================================= Test Attrib b\n"; 
  std::cout << "--------------------------------------- create xml\n"; 
  XmlDoc* xml = new XmlDoc("html");
  xml->setRoot( new XmlElement("root") );
  xml->root()->addAttribute("param","bouh");
  xml->root()->addChild( new XmlElement("foo") );
  xml->root()->childElement( "foo" )->addChild( new XmlText("du text") );
  xml->root()->childElement( "foo" )->addChild( new XmlElement("bar") );
  xml->root()->childElement( "foo" )->childElement( "bar" )->addChild( new XmlText("encore du text") );
  std::cout << "--------------------------------------- create dtd\n";
  DtdDoc* dtd = new DtdDoc("html");
  DtdPossibleContent* pc1 = new DtdPossibleContent(DtdPossibleContent::T_CHOICE);

  pc1->addChild(new DtdPossibleContent(DtdPossibleContent::T_ELEM,"foo"));
  pc1->addChild(new DtdPossibleContent(DtdPossibleContent::T_ELEM,"bar"));
  DtdElement* root = new DtdElement("root",pc1);
  dtd->AddElement( root );
  root->addAttribute("param","#PCDATA");
  dtd->AddElement(new DtdElement("foo"
    , new DtdPossibleContent(DtdPossibleContent::T_ELEM,"#PCDATA") ) );
  dtd->AddElement(new DtdElement("bar"
    , new DtdPossibleContent(DtdPossibleContent::T_ELEM,"#PCDATA") ) );
  std::cout << "--------------------------------------- print xml\n";
  xml->toStream(std::cout);
  std::cout << "--------------------------------------- print dtd\n";
  dtd->toStream(std::cout); 
  assert( dtd->element("foo")->name() == std::string("foo") );
  
  std::cout << "--------------------------------------- Validation du Xml\n";
  bool status = XmlValidator::validate(xml, dtd);

  std::cout << "--------------------------------------- delete xml\n";
  delete xml;
  std::cout << "--------------------------------------- delete dtd\n";
  delete dtd;
  
  return status;
}
