
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
  typedef std::list<DtdElement*> ElementList;
  /**
   * constructeur
   */ 
  DtdDoc(const std::string& docType = "") : _doctype(docType) {}
  /**
   * Renvoie le doctype du document.
   */ 
  const std::string& doctype() const { CALL_MACRO return _doctype; }
  //todo add accessor to_rules.

  void toStream(std::ostream& stream);
  
  /**
   * Renvoie une DtdDoc* correspondant a ce qui aurait pu etre obtenu par parsing.
   */ 
  static DtdDoc* CreateDummyDtdForRap1();
  /**
   * Renvoie une DtdDoc* correspondant a ce qui aurait pu etre obtenu par parsing.
   */ 
  static DtdDoc* CreateDummyDtdForRap3();
  
  static DtdDoc* CreateDummyDtdForNoob();
  
  /**
   * Permet l'ajout d'un element Dtd.
   */ 
  void AddElement(DtdElement *element);

  /**
   * 
   */  
  DtdElement* element(const std::string& eltNmae);
  
private:
  std::string _doctype;
  ElementList _rules;
 
};


#endif
