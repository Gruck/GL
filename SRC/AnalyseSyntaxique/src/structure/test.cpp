
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
