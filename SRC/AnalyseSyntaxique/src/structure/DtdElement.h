
#ifndef HEXALOUTRE_DTDELEMENT_H
#define HEXALOUTRE_DTDELEMENT_H

#include "DtdAttribute.h"
#include "Tools.h"

#include <list>
#include <string>
#include <iostream>


#define INDETATION_PATTERN "  "

class DtdPossibleContent;

/**
 * Fournit les descriptions nécessaire à la validation d'un XmlElement.
 */ 
class DtdElement 
{ 
public:
  typedef std::list<DtdAttribute*> AttributeMap; //todo check if shouldn't be a pointer list
  typedef std::list<DtdPossibleContent*> PossibleContentList;
  typedef std::list<DtdPossibleContent*>::iterator DtdPossibleContentIterator;

  /**
   * Constructeur.
   */ 
  DtdElement(const std::string& name, PossibleContentList& possibleContentList)
  :  _name(name), _possibleContentList(possibleContentList) {
    CALL_MACRO
  }

  /**
   * revoie le nom de l'élément.
   */ 
  const std::string& name() const { return _name; }
  /**
   * Déprécié
   * TODO: ajouter les attributs un par un.
   */ 
  inline void setAttributeMap(AttributeMap& AttributeMap) {_attributes = AttributeMap;}

  // prints the rule
  // void toStream( std::ostream& stream, int indentation = 0 );
  
private:
  std::string _name;
  PossibleContentList _possibleContentList;
  AttributeMap _attributes; //warning, possible confusion with XmlAttribute
  
  
};



#endif
