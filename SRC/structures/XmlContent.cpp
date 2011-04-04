

#include "XmlContent.h"
#include "XmlElement.h"


XmlContent::~XmlContent(){
  if(_parent) _parent->removeChildContent(this);
}
