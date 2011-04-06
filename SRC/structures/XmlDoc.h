
#ifndef HEXALOUTRE_XMLDOC_H
#define HEXALOUTRE_XMLDOC_H
#include <string>

#include "Tools.h"


class XmlElement;
class XmlValidator;

class XmlDoc {
public:
  XmlDoc(const std::string& docType) : _doctype(docType) {}

  void setRoot(XmlElement* newRoot) { CALL_MACRO _root = newRoot; } 
  XmlElement* root() const { CALL_MACRO return _root; }
  std::string doctype() const { CALL_MACRO return _doctype; }

  
  ~XmlDoc();
  
private:
  std::string _doctype;
  XmlElement* _root; 

};




#endif
