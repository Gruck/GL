
#ifndef HEXALOUTRE_XMLVALIDATOR_H
#define HEXALOUTRE_XMLVALIDATOR_H


#include "Tools.h"

#include <list>
#include <string>
#include <iostream>


#define INDETATION_PATTERN "  "
class DtdDoc;
class XmlDoc;
class XmlElement;
class XmlText;

class XmlValidator
{ 
public:
  XmlValidator(DtdDoc* dtdDoc)
   : _dtdDoc(dtdDoc){}

   
  bool validate( XmlDoc* xmlDoc) const;
  
   
private:
 DtdDoc* _dtdDoc;
  
  
};



#endif
