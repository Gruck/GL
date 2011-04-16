
#include <assert.h>

#include "XmlElement.h"
#include "XmlContent.h"
#include "XmlAttribute.h"
#include "XmlText.h"
#include "XmlDoc.h"
#include "DtdDoc.h"
#include "DtdElement.h"
#include "XmlValidator.h"



int main(){
  /*std::cout << "Xml::Test\n";

  std::cout << "...instanciate some stuff\n";
  XmlDoc doc("xhtml");
  XmlElement* elt = new XmlElement("ns","root");
  doc.setRoot(elt);
  elt->addAttribute( XmlAttribute("id","42") );
  std::cout << "...call addChild\n";

  
  


  elt->addChild( new XmlElement( "" ,"pipo" ) );
  XmlText* text = new XmlText("Il faut revaloriser la dynamique manageriale par une revalorisation de l'experience leadership.\n" );

  elt->childElement("pipo")->addChild(text);
  elt->childElement("pipo")->addAttribute( XmlAttribute("plus_produit","transversale") );
  elt->childElement("pipo")->addAttribute( XmlAttribute("id","1337") );
  
  elt->childElement(0)->addChild( new XmlElement( "" ,"hey" ) );
  assert( (elt->childElement(0)->childElement(0)->parent() == elt->childElement(0) ) );
  std::cout << "...add an element from constructor\n";
  
*/
  std::cout << "--------------------------------------- create xml\n"; 
  XmlDoc* xml = XmlDoc::CreateDummyXmlForRap1();
  std::cout << "--------------------------------------- create dtd\n";
  DtdDoc* dtd = DtdDoc::CreateDummyDtdForRap1();
  std::cout << "--------------------------------------- print xml\n";
  xml->toStream(std::cout);
  std::cout << "--------------------------------------- print dtd\n";
  dtd->toStream(std::cout); 
  assert( dtd->element("titre")->name() == std::string("titre") );
  
  std::cout << "--------------------------------------- Validation du Xml\n";
  assert( XmlValidator::validate(xml, dtd) );

  std::cout << "--------------------------------------- delete xml\n";
  delete xml;
  std::cout << "--------------------------------------- delete dtd\n";
  delete dtd;
}
