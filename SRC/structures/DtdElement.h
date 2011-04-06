
#ifndef HEXALOUTRE_DTDELEMENT_H
#define HEXALOUTRE_DTDELEMENT_H

#include "DtdAttribute.h"
#include "Tools.h"

#include <list>
#include <string>
#include <iostream>


#define INDETATION_PATTERN "  "


class DtdElement 
{ 
public:
  typedef std::list<DtdAttribute> AttributeList; //todo check if shouldn't be a pointer list
  typedef std::list<DtdPossibleContents*> PossibleContentList;
  typedef std::list<DtdPossibleContents*>::iterator DtdPossibleContentsIterator;

  /*DtdElement(const std::string& nameSpace,const std::string& name)
  : XmlContent(0), _nameSpace(nameSpace), _name(name) {
    CALL_MACRO
  }*/
  
  inline std::string name() const { return _name; }
  inline std::string nameSpace() const { return _nameSpace; }
  std::string fullName() const;

 
 

  // prints the rule
  // void toStream( std::ostream& stream, int indentation = 0 );
  
private:
  std::string _nameSpace;
  std::string _name;
  PossibleContentList _possibleContentList;
  AttributeList _attributes; //warning, possible confusion with XmlAttribute
  
  
};



#endif
