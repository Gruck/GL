
#ifndef HEXALOUTRE_XMLTEXT_H
#define HEXALOUTRE_XMLTEXT_H

#include "XmlContent.h"
#include <iostream>

class XmlText : public XmlContent
{
public:
  XmlText(const std::string& text)
  : XmlContent(0), _data(text) { }
  
  void toStream( std::ostream& stream, int indentation = 0 ) {
    indent(stream, indentation);
    stream << _data;
  }
  std::string& text() { CALL_MACRO return _data; }
  
private:
  std::string _data;
};




#endif
