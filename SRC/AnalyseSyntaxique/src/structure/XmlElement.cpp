
#include "XmlElement.h"
#include "XmlValidatorVisitor.h"
#include "Tools.h"

std::string XmlElement::fullName() const {
  //CALL_MACRO
  if(_nameSpace != std::string("")) return _nameSpace+":"+_name;
  else return _name;
}

XmlElement* XmlElement::childElement(int nth){
  ContentListIterator iter = firstChild();
  ContentListIterator stop = childrenEnd();
  for(;iter != stop; ++iter){
    XmlElement* elt = dynamic_cast<XmlElement*>(*iter);
    if(elt){
      if(nth == 0) return elt;
      --nth;
    }
  }
  return 0;
}

XmlContent* XmlElement::childContent(int nth){
  ContentListIterator iter = firstChild();
  ContentListIterator stop = childrenEnd();
  for(;iter != stop; ++iter){
      if(nth == 0) return (*iter);
      --nth;
  }
  return 0;
}

XmlElement* XmlElement::childElement(const std::string& name, int nth){
  CALL_MACRO
  ContentListIterator iter = firstChild();
  ContentListIterator stop = childrenEnd();
  for(;iter != stop; ++iter){
    XmlElement* elt = dynamic_cast<XmlElement*>(*iter);
    if(elt && (elt->name() == name) ) {
		if(nth == 0) return elt;
		--nth;
	}
  }
  return 0;
}


XmlElement* XmlElement::childElement(const std::string& name, const std::string& attributeName, const std::string& attributeValue, int nth){
	CALL_MACRO
	ContentListIterator iter = firstChild();
	ContentListIterator stop = childrenEnd();
	for(;iter != stop; ++iter){
		XmlElement* elt = dynamic_cast<XmlElement*>(*iter);
		

		if(elt && (elt->name() == name) 
		   && (elt->_attributes.find(attributeName) != elt->_attributes.end())
		   && ( (*(elt->_attributes.find(attributeName))).second == attributeValue ) )
		{
			if(nth == 0) return elt;
			--nth;
		}
	}
	return 0;
}


void XmlElement::addChild( XmlContent* toAdd ) {
  CALL_MACRO
  if(!toAdd) return;
  _childContentList.push_back( toAdd );
  toAdd->setParent(this);
}


void XmlElement::deleteChild( XmlContent* toRemove ){
  CALL_MACRO
  XmlContent* found = detachChild(toRemove);
  if(found) delete found;
}

XmlContent* XmlElement::detachChild( XmlContent* toRemove ){
  CALL_MACRO
  ContentListIterator iter = _childContentList.begin();
  ContentListIterator stop = _childContentList.end();
  XmlContent* found = 0;
  for(;iter!=stop;++iter){
    if(*iter == toRemove){
      found = *iter;
      _childContentList.remove(toRemove);
      return found;
    }
  }
  return 0;
}

void XmlElement::addAttribute( const XmlAttribute& attribute ){
  CALL_MACRO
  _attributes[ attribute.name() ] = attribute.value();
}

void XmlElement::addAttribute( const std::string& attributeName, const std::string& value ){
  CALL_MACRO
  _attributes[ attributeName ] = value;
}

void XmlElement::removeAttribute( const XmlAttribute& attribute ){
  CALL_MACRO
  _attributes.erase( attribute.name() );
}

void XmlElement::removeAttribute( const std::string& attributeName ){
  CALL_MACRO
  _attributes.erase( attributeName );
}

void XmlElement::toStream( std::ostream& stream, int indentation ){
  //CALL_MACRO
  indent(stream,indentation);
  stream << "<" << fullName();
  AttributeMap::iterator attribIter = _attributes.begin();
  AttributeMap::iterator attribStop = _attributes.end();
  for(;attribIter != attribStop; ++attribIter){
    stream << " "<< (*attribIter).first << "=" <<(*attribIter).second;
  }
  //stream << /* liste attributs */; // TODO
  stream << ">\n";
  ContentListIterator iter = firstChild();
  ContentListIterator stop = childrenEnd();
  for(;iter != stop; ++iter){
    (*iter)->toStream( stream, indentation+1 );
  }
  indent(stream,indentation);
  stream << "</" << fullName() << ">\n";
  
}

XmlElement::~XmlElement(){
  CALL_MACRO
  ContentListIterator iter = firstChild();
  ContentListIterator stop = childrenEnd();
  for(;iter!=stop;++iter){
    (*iter)->setParent(0);
    delete *iter;
  }
}

bool XmlElement::acceptValidator( XmlValidatorVisitor* validator ){
	CALL_MACRO
  return validator->visit(this);
}
