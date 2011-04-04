

#include "XmlContent.h"
#include "XmlElement.h"
#include "Tools.h"

XmlContent::~XmlContent(){
  CALL_MACRO
  if(_parent) _parent->removeChild(this);
}
