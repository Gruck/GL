
#ifndef HEXALOUTRE_DTDDOC_H
#define HEXALOUTRE_DTDDOC_H
#include <string>
#include <list>

#include "Tools.h"


class DtdElement;

/**
 * Docment de DTD servant à réaliser la validation sémantique d'un document XML.
 */ 
class DtdDoc {
public:
  /**
   * constructeur
   */ 
  DtdDoc(const std::string& docType) : _doctype(docType) {}
  /**
   * Renvoie le doctype du document.
   */ 
  const std::string& doctype() const { CALL_MACRO return _doctype; }
  //todo add accessor to rules.

  void toStream(std::ostream& stream);
  
private:
  std::string _doctype;
  std::list<DtdElement *> rules;
 
};




#endif
