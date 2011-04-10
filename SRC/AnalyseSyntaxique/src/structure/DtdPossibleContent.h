
#ifndef HEXALOUTRE_DTDPOSSIBLECONTENT_H
#define HEXALOUTRE_DTDPOSSIBLECONTENT_H

#include <string>
#include <list>
#include "Tools.h"



/**
 * Décrit un contenu possible d'un noeud xml (XmlElement).
 */ 
class DtdPossibleContent {
public:
  typedef enum{
    M_QMARK,     /*M(ultiplicity)_QMARK */
    M_AST,
    M_PLUS} Multiplicity;
  typedef enum{
    T_SEQUENCE, /*T(ype)_SEQUENCE */
    T_CHOICE,
    T_ELEM} Type;

  typedef std::list<DtdPossibleContent*> PossibleContentList;
    
	/**
   * Constructeur.
   */ 
  DtdPossibleContent(Type type, const std::string& value, Multiplicity multiplicity)
  : _multiplicity(multiplicity), _type(type), _value(value){ CALL_MACRO }

  /**
   * Renvoie le type.
   */ 
  inline Type type() const {
    return _type;
  }
  
  /**
   * Renvoie la multiplicité.
   */ 
  inline Multiplicity multiplicity() const {
    return _multiplicity;
  }

  /**
   * Renvoie la valeur.
   */
  inline const std::string& value() const{
    return _value;
  }

  /**
   * Ajoute un contenu possible fils.
   */ 
  inline void addChild( DtdPossibleContent* child ){
    _children.push_back(child);
  } 

  /**
   * Renvoie le nombre de contenus possibles fils.
   */ 
  inline int nbChildren() const{
    return _children.size();
  }

  /**
   * Renvoie un itérateur vers le premier contenu possible fils.
   */ 
  inline PossibleContentList::iterator firstChild(){
    return _children.begin();
  }

  /**
   * renvoie un itérateur servant de condition d'arrêt sur l'itération des fils.
   */ 
  inline PossibleContentList::iterator childrenEnd(){
    return _children.end();
  }
  
 
private:
	Multiplicity _multiplicity;
	Type _type;
	std::string _value;
  std::list<DtdPossibleContent*> _children;
 
};




#endif
