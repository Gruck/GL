

#include "DtdElement.h"
#include "Tools.h"


std::string* DtdElement::findAttribute(const std::string& attrName){
  AttributeMap::iterator it = _attributes.find( attrName );
  if(it != _attributes.end()){
    return &(it->second);
  }else return 0;
}

bool DtdElement::hasAttribute(const std::string& attrName) const {
  return _attributes.find( attrName ) != _attributes.end();
}

void DtdElement::toStream( std::ostream& stream, int indentation){
	
	
	
	
}
