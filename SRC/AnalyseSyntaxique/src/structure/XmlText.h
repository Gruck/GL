
#ifndef HEXALOUTRE_XMLTEXT_H
#define HEXALOUTRE_XMLTEXT_H

#include "XmlContent.h"
#include <iostream>

class XmlValidatorVisitor;

class XmlText : public XmlContent
{
public:
  XmlText(const std::string& text)
  : XmlContent(0), _data(text) { }

  ~XmlText(){}
  
  void toStream( std::ostream& stream, int indentation = 0 );
  
  std::string& text() { CALL_MACRO return _data; }

  bool acceptValidator( XmlValidatorVisitor* validator );

  
private:
  std::string _data;
};




#endif
