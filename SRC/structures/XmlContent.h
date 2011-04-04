
#ifndef HEXALOUTRE_XMLCONTENT_H
#define HEXALOUTRE_XMLCONTENT_H

#include <iostream>
#include "Tools.h"

class XmlElement;

class XmlContent{
friend class XmlElement;
public:
  XmlContent( XmlElement* parent ) : _parent(parent) { CALL_MACRO }
  XmlElement* parent() { CALL_MACRO return _parent; }

  // to override
  virtual void toStream( std::ostream& stream ) = 0;

  virtual ~XmlContent();
protected:
  void setParent(XmlElement* parentElt){ CALL_MACRO _parent = parentElt; }

private:
  XmlElement* _parent;
};




#endif
