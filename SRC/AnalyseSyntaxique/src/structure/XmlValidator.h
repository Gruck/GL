
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

/**
 * Valide l'entête d'un document XML et fait appel à la class XmlValidatorVisitor
 * pour valider le reste du document.
 */ 
namespace XmlValidator
{ 

  /**
   * Valide un document XML selon une DTD.
   */ 
  bool validate( XmlDoc* xmlDoc, DtdDoc* dtdDoc);
   
  
};



#endif
