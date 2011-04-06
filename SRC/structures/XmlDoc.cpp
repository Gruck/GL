
#include "XmlDoc.h"
#include "Tools.h"


#include "XmlElement.h"

XmlDoc::~XmlDoc(){ 
  CALL_MACRO
  delete _root;
}
