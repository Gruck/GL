
#ifndef HEXALOUTRE_DTDDOC_H
#define HEXALOUTRE_DTDDOC_H
#include <string>

#include "Tools.h"


class DtdElement;

class DtdDoc {
public:
  DtdDoc(const std::string& docType) : _doctype(docType) {}
  std::string doctype() const { CALL_MACRO return _doctype; }
  //todo add accessor to rules.
private:
  std::string _doctype;
  std::list<DtdElement *> rules;
 
};




#endif
