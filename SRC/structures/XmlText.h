
#ifndef HEXALOUTRE_XMLTEXT_H
#define HEXALOUTRE_XMLTEXT_H

#include "XmlContent.h"
#include <iostream>

class XmlText : public XmlContent
{
public:
  XmlText(XmlElement* parent, const std::string& text )
  : XmlContent(parent), _data(text) { }
  
  void toStream( std::ostream& stream ) { stream << _data; }
  std::string& text() { return _data; }
private:
  std::string _data;
};




#endif
