
#include "XmlText.h"
#include "XmlValidatorVisitor.h"



bool XmlText::acceptValidator( XmlValidatorVisitor* validator ){
	CALL_MACRO
  return validator->visit(this);
}

void XmlText::toStream(std::ostream& stream, int indentation){
  indent(stream, indentation);
  stream << _data;
}
