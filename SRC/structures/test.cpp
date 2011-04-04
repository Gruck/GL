
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
  XmlElement elt(0,"ns","bar");
  XmlText text(0, "Some text \n foo bar" );
  XmlAttribute attrib();

  std::cout << "...call addChild\n";
  elt.addChild( new XmlElement( &elt, "" ,"bar" ) );

  std::cout << "...add an element from constructor\n";
  new XmlElement( dynamic_cast<XmlElement*>(*elt.firstChild()),"", "foo" );

  std::cout << "...browse through the tree\n";
  std::string test =
    dynamic_cast<XmlElement*>(
      *dynamic_cast<XmlElement*>(
        *elt.firstChild()
      )->firstChild()
    )->fullName();

  assert( test == std::string("foo") );
  std::cout << "\nEnd of the test\n";
}
