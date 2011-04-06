
#include "XmlDoc.h"
#include "Tools.h"


#include "XmlElement.h"

XmlDoc::~XmlDoc(){ 
  CALL_MACRO
  if(_root) delete _root;
}
