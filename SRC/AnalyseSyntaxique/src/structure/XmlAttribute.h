
#ifndef HEXALOUTRE_XMLATTRIBUTE_H
#define HEXALOUTRE_XMLATTRIBUTE_H

#include "Tools.h"
#include <iostream>

/**
 * Attribut d'un Élément Xml.
 */ 
class XmlAttribute{
public:
  /**
   * Constructeur
   */ 
  XmlAttribute(const std::string& name, const std::string& value)
  : _name(name), _value(value){ }

  /**
   * Renvoie le nom de l'attribut.
   */ 
  const std::string& name() const { CALL_MACRO return _name; }
  /**
   * Renvoie la valeur de l'attribut.
   */ 
  const std::string& value() const { CALL_MACRO return _value; }
  /**
   * Opérateur d'égalité entre deux attributs.
   *
   * L'égalité ne repose que sur le nom des attributs et non leur valeurs.
   */ 
  bool operator == (const XmlAttribute& attrib) const{
    return _name == attrib.name();
  }

  /**
   * Affiche l'attribut dans un flux standard sous la forme <nom> = <valeur>.
   */ 
  void toStream( std::ostream& stream ){
    CALL_MACRO
    stream << _name <<"="<<_value;
  }
  
private:
  std::string _name;
  std::string _value;
};




#endif
