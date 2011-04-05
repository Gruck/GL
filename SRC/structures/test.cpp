
#include <assert.h>

#include "XmlElement.h"
#include "XmlContent.h"
#include "XmlAttribute.h"
#include "XmlText.h"
#include "XmlDoc.h"




int main(){
  std::cout << "Xml::Test\n";

  std::cout << "...instanciate some stuff\n";
  XmlDoc("xhtml");
  XmlElement elt("ns","root");
  elt.addAttribute( XmlAttribute("id","42") );
  std::cout << "...call addChild\n";

  
  
  XmlAttribute attrib();

  elt.addChild( new XmlElement( "" ,"pipo" ) );
  XmlText* text = new XmlText("Il faut revaloriser la dynamique manageriale par une revalorisation de l'experience leadership.\n" );

  elt.childElement("pipo")->addChild(text);
  
  elt.childElement(0)->addChild( new XmlElement( "" ,"hey" ) );
  assert( (elt.childElement(0)->childElement(0)->parent() == elt.childElement(0) ) );
  std::cout << "...add an element from constructor\n";
  
  

  elt.toStream(std::cout);
  std::cout << "\nEnd of the test\n";
}
