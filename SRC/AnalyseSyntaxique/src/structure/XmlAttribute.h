
#ifndef HEXALOUTRE_XMLATTRIBUTE_H
#define HEXALOUTRE_XMLATTRIBUTE_H

#include "Tools.h"
#include <iostream>

class XmlAttribute{
public:
  XmlAttribute(const std::string& name, const std::string& value)
  : _name(name), _value(value){ }
  
  std::string name() const { CALL_MACRO return _name; }
  std::string value() const { CALL_MACRO return _value; }
  bool operator == (const XmlAttribute& attrib) const{
    return _name == attrib.name();
  }

  void toStream( std::ostream& stream ){
    CALL_MACRO
    stream << _name <<"="<<_value;
  }
  
private:
  std::string _name;
  std::string _value;
};




#endif
