
#include "XmlDoc.h"
#include "Tools.h"
#include <iostream>

#include "XmlElement.h"
#include "XmlValidatorVisitor.h"

XmlDoc::~XmlDoc(){ 
  CALL_MACRO
  if(_root) delete _root;
}

void XmlDoc::toStream(std::ostream& stream){
  stream << "<!DOCTYPE " << doctype() << " >\n";
  if(_root) _root->toStream(stream,0);
}

bool XmlDoc::acceptValidator( XmlValidatorVisitor* validator ){
  return validator->visit(this);
}
