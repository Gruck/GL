
#ifndef HEXALOUTRE_XMLATTRIBUTE_H
#define HEXALOUTRE_XMLATTRIBUTE_H

#include "Tools.h"
#include <iostream>

class XmlAttribute{
public:
  std::string name() const { CALL_MACRO return _name; }
  std::string value() const { CALL_MACRO return _value; }

  void toStream( std::ostream& stream ){
    CALL_MACRO
    stream << _name <<"="<<_value;
  }
  
private:
  std::string _name;
  std::string _value;
};




#endif
