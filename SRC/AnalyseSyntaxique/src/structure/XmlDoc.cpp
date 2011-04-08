
#include "XmlDoc.h"
#include "Tools.h"
#include <iostream>

#include "XmlElement.h"

XmlDoc::~XmlDoc(){ 
  CALL_MACRO
  if(_root) delete _root;
}

void XmlDoc::toStream(std::ostream& stream){
  // TODO print the doctype !
  if(_root) _root->toStream(stream,0);
}
