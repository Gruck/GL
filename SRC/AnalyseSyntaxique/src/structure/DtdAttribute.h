
#ifndef HEXALOUTRE_DTDATTRIBUTE_H
#define HEXALOUTRE_DTDATTRIBUTE_H

#include "Tools.h"
#include <iostream>

/**
 * Décrit un attribut d'un noeud XML par son nom et son type.
 */ 
class DtdAttribute{
public:
  /**
   * Constructeur.
   */ 
  DtdAttribute(const std::string& name, const std::string& type)
  : _name(name), _type(type){ }

  /**
   * Renvoie le nom de l'attribut.
   */ 
  const std::string& name() const { CALL_MACRO return _name; }
  /**
   * Renvoie le type de l'attribut.
   */ 
  const std::string& type() const { CALL_MACRO return _type; }
  /*bool operator == (const XmlAttribute& attrib) const{
    return _name == attrib.name();
  }*/

  /*void toStream( std::ostream& stream ){
    CALL_MACRO
    stream << _name <<"="<<_value;
  }
  */
  
private:
  std::string _name;
  std::string _type;
};




#endif
