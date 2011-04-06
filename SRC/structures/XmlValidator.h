
#ifndef HEXALOUTRE_XMLVALIDATOR_H
#define HEXALOUTRE_XMLVALIDATOR_H


#include "Tools.h"

#include <list>
#include <string>
#include <iostream>


#define INDETATION_PATTERN "  "
class XmlDoc;
class XmlElement;
class XmlText;

class XmlValidator
{ 
public:
  XmlValidator(DtdDoc* dtdDoc)
   : _dtdDoc(dtdDoc){}
   
  bool Validate( XmlDoc* xmlDoc) const;
  bool Validate( XmlElement* xmlElement) const;
  bool Validate( XmlText* xmlText) const;
   
private:
 DtdDoc* _dtdDoc;
  
  
};



#endif
