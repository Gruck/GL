

#include "DtdElement.h"
#include "DtdPossibleContent.h"
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

void DtdElement::toStream( std::ostream& stream ){
  // element
  stream << "<!ELEMENT " << name() << " ";
  if(_possibleContent)
    _possibleContent->toStream(stream);
  stream << " >\n";
  // attributs
  AttributeMap::iterator iter = firstAttribute();
  AttributeMap::iterator stop = attributesEnd();
  for(;iter!=stop;++iter){
    stream << "<!ATTLIST "<< name() <<" " << iter->first  <<" " << iter->second << " #IMPLIED>\n";
  }
	
}
