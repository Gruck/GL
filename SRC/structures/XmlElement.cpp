
#include "XmlElement.h"
#include "Tools.h"

std::string XmlElement::fullName() const {
  CALL_MACRO
  if(_nameSpace != std::string("")) return _nameSpace+":"+_name;
  else return _name;
}

void XmlElement::addChild( XmlContent* toAdd ) {
  CALL_MACRO
  if(!toAdd) return;
  _childContentList.push_back( toAdd );
  toAdd->setParent(this);
}

  
void XmlElement::removeChild( XmlContent* toRemove ){
  CALL_MACRO
  // TODO
}


void XmlElement::toStream( std::ostream& stream ){
  CALL_MACRO
  stream << "< " << fullName() << " ";
  ContentListIterator iter = firstChild();
  ContentListIterator stop = childrenEnd();
  for(;iter != stop; ++iter)
    (*iter)->toStream( stream );
  stream << /* liste attributs */ " "; // TODO
  stream << " >\n";
}
