
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
    M_PLUS,
    M_NONE} Multiplicity;
    
  inline std::string ToStr( Multiplicity multiplicity){
	 switch(multiplicity){
		 M_QMARK : return std::string( "?" );
		 M_AST : return std::string( "*" );
		 M_PLUS : return std::string( "+" );
		 M_NONE : return std::string( "" );
	 }
  }
  
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
  
  /**
   * Affiche dans un flux standard l'élément courant ainsi que ses contenu fils
   * récursivement.
   *
   * Le paramêtre indentation fixe le niveau d'indentation de l'élément et est
   * incrémenté par les éléments fils. Dans le cas général il n'a pas besoin
   * d'être précisé par l'utilisateur.
   */ 
  void toStream( std::ostream& stream, int indentation = 0 );
  
 
private:
	Multiplicity _multiplicity;
	Type _type;
	std::string _value;
  std::list<DtdPossibleContent*> _children;
 
};




#endif
