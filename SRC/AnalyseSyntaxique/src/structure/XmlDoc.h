
#ifndef HEXALOUTRE_XMLDOC_H
#define HEXALOUTRE_XMLDOC_H
#include <string>
#include <iostream>

#include "Tools.h"


class XmlElement;
class XmlValidatorVisitor;

/**
 * Document Xml.
 *
 * Contient le doctype et un lien vers la racine de la structure XML.
 */ 
class XmlDoc {
public:
  /**
   * Constructeur.
   */ 
  XmlDoc(const std::string& docType) : _doctype(docType), _root(0) {}

  /**
   * Définit la racine du document XML.
   */ 
  void setRoot(XmlElement* newRoot) { CALL_MACRO _root = newRoot; }
  /**
   * Renvoie un pointeur vers la racine du document XML.
   */ 
  XmlElement* root() const { CALL_MACRO return _root; }
  /**
   * Renvoie le doctype du document XML.
   */ 
  std::string doctype() const { CALL_MACRO return _doctype; }

  /**
   * Affiche récursivement le document XML dans un flux standard.
   */ 
  void toStream(std::ostream& stream);

  /**
   * destructeur
   */ 
  ~XmlDoc();
  
  /**
   * Permet de réaliser le "double dispatch" nécessaire à l'application du design
   * pattern visitor implémenté au niveau de l'algorithme de validation. 
   */ 
  bool acceptValidator( XmlValidatorVisitor* validator );
  
private:
  std::string _doctype;
  XmlElement* _root; 

};




#endif
