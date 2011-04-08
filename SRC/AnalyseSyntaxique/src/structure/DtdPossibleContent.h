
#ifndef HEXALOUTRE_DTDPOSSIBLECONTENT_H
#define HEXALOUTRE_DTDPOSSIBLECONTENT_H
#include <string>

#include "Tools.h"



/**
 * Décrit un contenu possible d'un noeud xml (XmlElement).
 */ 
class DtdPossibleContent {
public:
  typedef enum{
    QMARK,
    AST,
    PLUS} Multiplicity;
  typedef enum{
    SEQUENCE,
    CHOICE,
    ELEM} Type;
    
	/**
   * Constructeur.
   */ 
  DtdPossibleContent(){} 
 
private:
	Multiplicity _multiplicity;
	Type _type;
	std::string value;
 
};




#endif
