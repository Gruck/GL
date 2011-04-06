

#include "XmlContent.h"
#include "XmlElement.h"
#include "Tools.h"

XmlContent::XmlContent( XmlElement* parent ) : _parent(parent) {
  CALL_MACRO
}

XmlContent::~XmlContent(){
  CALL_MACRO
  if(_parent) _parent->deleteChild(this);
}

