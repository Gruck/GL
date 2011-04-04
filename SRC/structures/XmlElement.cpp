
#include "XmlElement.h"


void XmlElement::addChildContent( XmlContent* toAdd ) {
  if(toAdd)_childContentList.push_back(toAdd);
}

  
void XmlElement::removeChildContent( XmlContent* toRemove ){
  // TODO
}


void XmlElement::toStream( std::ostream& stream ){
  stream << "< " << fullName() << " ";
  stream << /* liste attributs */ " "; // TODO
  stream << " >\n";
}
