
#ifndef HEXALOUTRE_DTDELEMENT_H
#define HEXALOUTRE_DTDELEMENT_H

#include "DtdAttribute.h"
#include "Tools.h"

#include <list>
#include <string>
#include <iostream>


#define INDETATION_PATTERN "  "

class DtdPossibleContent;

class DtdElement 
{ 
public:
  typedef std::list<DtdAttribute*> AttributeList; //todo check if shouldn't be a pointer list
  typedef std::list<DtdPossibleContent*> PossibleContentList;
  typedef std::list<DtdPossibleContent*>::iterator DtdPossibleContentIterator;

  DtdElement(const std::string& name, PossibleContentList& possibleContentList)
  :  _name(name), _possibleContentList(possibleContentList) {
    CALL_MACRO
  }
  
  inline std::string name() const { return _name; }
  inline void setAttributeList(AttributeList& attributeList) {_attributes = attributeList;}

  // prints the rule
  // void toStream( std::ostream& stream, int indentation = 0 );
  
private:
  std::string _name;
  PossibleContentList _possibleContentList;
  AttributeList _attributes; //warning, possible confusion with XmlAttribute
  
  
};



#endif
