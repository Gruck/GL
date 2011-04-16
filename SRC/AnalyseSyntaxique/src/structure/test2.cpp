
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



bool test2a();
bool test2b();
bool test2c();
bool test2d();
bool test2e();


int main(){
  assert( test2a() );
  std::cout << "\n\n\n";
  assert( test2b() );
  std::cout << "\n\n\n";
  assert( test2c() );
  std::cout << "\n\n\n";
  assert( test2d() );
  std::cout << "\n\n\n";
  assert( test2e() );
  std::cout << "\n\n\n";
 
}

/**
 * @test Le XML suivant ne doit pas être validé.
 *
 * validation d'un xml de type
 * root
 *    foo
 *       bar
 * Alors que bar ne peut pas être contenu par foo (il peut l'être par root)
 */ 
bool test2a(){
  std::cout << "--------------------------------------- create xml\n"; 
  XmlDoc* xml = new XmlDoc("html");
  xml->setRoot( new XmlElement("root") );
  xml->root()->addChild( new XmlElement("foo") );
  xml->root()->childElement( "foo" )->addChild( new XmlText("du text") );
  xml->root()->childElement( "foo" )->addChild( new XmlElement("bar") );
  xml->root()->childElement( "foo" )->childElement( "bar" )->addChild( new XmlText("encore du text") );
  std::cout << "--------------------------------------- create dtd\n";
  DtdDoc* dtd = new DtdDoc("html");
  DtdPossibleContent* pc1 = new DtdPossibleContent(DtdPossibleContent::T_CHOICE);
  pc1->addChild(new DtdPossibleContent(DtdPossibleContent::T_ELEM,"foo"));
  pc1->addChild(new DtdPossibleContent(DtdPossibleContent::T_ELEM,"bar"));
  dtd->AddElement( new DtdElement("root",pc1) );
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

/**
 * @test Le XML suivant ne doit pas être validé.
 *
 * validation d'un xml de type
 * root
 *    foo
 *    bar
 * Alors que root peut contenir foo OU bar (ou exclusif)
 */ 
bool test2b(){
  std::cout << "--------------------------------------- create xml\n"; 
  XmlDoc* xml = new XmlDoc("html");
  xml->setRoot( new XmlElement("root") );
  xml->root()->addChild( new XmlElement("foo") );
  xml->root()->childElement( "foo" )->addChild( new XmlText("du text") );
  xml->root()->addChild( new XmlElement("bar") );
  xml->root()->childElement( "bar" )->addChild( new XmlText("encore du text") );
  std::cout << "--------------------------------------- create dtd\n";
  DtdDoc* dtd = new DtdDoc("html");
  DtdPossibleContent* pc1 = new DtdPossibleContent(DtdPossibleContent::T_CHOICE);
  pc1->addChild(new DtdPossibleContent(DtdPossibleContent::T_ELEM,"foo"));
  pc1->addChild(new DtdPossibleContent(DtdPossibleContent::T_ELEM,"bar"));
  dtd->AddElement( new DtdElement("root",pc1) );
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

/**
 * @test Le XML suivant doit être validé.
 *
 * validation de 3 xml de la forme
 * root
 *    foo
 *    bar
 * ---------------
 * root
 * ---------------
 * root
 *    foo
 *    foo
 *    bar
 * 
 * avec T_CHOICE multiplicité PLUS 
 */ 
bool test2c(){
  std::cout << "--------------------------------------- create xml\n"; 
  XmlDoc* xml = new XmlDoc("html");
  xml->setRoot( new XmlElement("root") );
  xml->root()->addChild( new XmlElement("foo") );
  xml->root()->childElement( "foo" )->addChild( new XmlText("du text") );
  xml->root()->addChild( new XmlElement("bar") );
  xml->root()->childElement( "bar" )->addChild( new XmlText("encore du text") );
  std::cout << "--------------------------------------- create dtd\n";
  DtdDoc* dtd = new DtdDoc("html");
  DtdPossibleContent* pc1 = new DtdPossibleContent(
    DtdPossibleContent::T_CHOICE, ""
    , DtdPossibleContent::M_PLUS);
  pc1->addChild(new DtdPossibleContent(DtdPossibleContent::T_ELEM,"foo"));
  pc1->addChild(new DtdPossibleContent(DtdPossibleContent::T_ELEM,"bar"));
  dtd->AddElement( new DtdElement("root",pc1) );
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

/**
 * @test Le XML suivant doit être validé.
 *
 * validation d'un xml de type
 * root
 *    foo
 *    bar
 * avec T_CHOICE multiplicité * 
 */ 
bool test2d(){
  std::cout << "--------------------------------------- create xml\n"; 
  XmlDoc* xml = new XmlDoc("html");
  xml->setRoot( new XmlElement("root") );
  xml->root()->addChild( new XmlElement("foo") );
  xml->root()->childElement( "foo" )->addChild( new XmlText("du text") );
  xml->root()->addChild( new XmlElement("bar") );
  xml->root()->childElement( "bar" )->addChild( new XmlText("encore du text") );

  XmlDoc* xml2 = new XmlDoc("html");
  xml2->setRoot( new XmlElement("root") );

  XmlDoc* xml3 = new XmlDoc("html");
  xml3->setRoot( new XmlElement("root") );
  xml3->root()->addChild( new XmlElement("foo") );
  xml3->root()->childElement( "foo" )->addChild( new XmlText("du texte") );
  xml3->root()->addChild( new XmlElement("foo") );
  xml3->root()->childElement( "foo", 1 )->addChild( new XmlText("oh oui du texte") );
  xml3->root()->addChild( new XmlElement("bar") );
  xml3->root()->childElement( "bar" )->addChild( new XmlText("encore du texte") );

  std::cout << "--------------------------------------- create dtd\n";
  DtdDoc* dtd = new DtdDoc("html");
  DtdPossibleContent* pc1 = new DtdPossibleContent(
    DtdPossibleContent::T_CHOICE, ""
    , DtdPossibleContent::M_AST);
  pc1->addChild(new DtdPossibleContent(DtdPossibleContent::T_ELEM,"foo"));
  pc1->addChild(new DtdPossibleContent(DtdPossibleContent::T_ELEM,"bar"));
  dtd->AddElement( new DtdElement("root",pc1) );
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
  bool status = ( (XmlValidator::validate(xml, dtd) )
    && (XmlValidator::validate(xml2, dtd) ) 
    && (XmlValidator::validate(xml3, dtd) )
  );

  std::cout << "--------------------------------------- delete xml\n";
  delete xml;
  std::cout << "--------------------------------------- delete dtd\n";
  delete dtd;

  return status;
}

/**
 * @test Le XML suivant doit être validé.
 *
 * validation d'un xml de type
 * root
 *    foo
 *    bar
 * --------------
 * root
 * --------------
 * root
 *    foo
 *    bar
 *    foo
 *    bar
 * avec T_SEQUENCE multiplicité * 
 */ 
bool test2e(){
  std::cout << "--------------------------------------- create xml\n"; 
  XmlDoc* xml = new XmlDoc("html");
  xml->setRoot( new XmlElement("root") );
  xml->root()->addChild( new XmlElement("foo") );
  xml->root()->childElement( "foo" )->addChild( new XmlText("du text") );
  xml->root()->addChild( new XmlElement("bar") );
  xml->root()->childElement( "bar" )->addChild( new XmlText("encore du text") );

  XmlDoc* xml2 = new XmlDoc("html");
  xml2->setRoot( new XmlElement("root") );

  XmlDoc* xml3 = new XmlDoc("html");
  xml3->setRoot( new XmlElement("root") );
  xml3->root()->addChild( new XmlElement("foo") );
  xml3->root()->childElement( "foo" )->addChild( new XmlText("du texte") );
  xml3->root()->addChild( new XmlElement("bar") );
  xml3->root()->childElement( "bar" )->addChild( new XmlText("encore du texte") );
  xml3->root()->addChild( new XmlElement("foo") );
  xml3->root()->childElement( "foo", 1 )->addChild( new XmlText("oh oui du texte") );
  xml3->root()->addChild( new XmlElement("bar") );
  xml3->root()->childElement( "bar", 1 )->addChild( new XmlText("oh oui du texte") );
  
  std::cout << "--------------------------------------- create dtd\n";
  DtdDoc* dtd = new DtdDoc("html");
  DtdPossibleContent* pc1 = new DtdPossibleContent(
    DtdPossibleContent::T_SEQUENCE, ""
    , DtdPossibleContent::M_AST);
  pc1->addChild(new DtdPossibleContent(DtdPossibleContent::T_ELEM,"foo"));
  pc1->addChild(new DtdPossibleContent(DtdPossibleContent::T_ELEM,"bar"));
  dtd->AddElement( new DtdElement("root",pc1) );
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
  bool status = ( (XmlValidator::validate(xml, dtd) )
    && (XmlValidator::validate(xml2, dtd) ) );

  std::cout << "--------------------------------------- delete xml\n";
  delete xml;
  std::cout << "--------------------------------------- delete dtd\n";
  delete dtd;

  return status;
}

