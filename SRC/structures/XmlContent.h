
#ifndef HEXALOUTRE_XMLCONTENT_H
#define HEXALOUTRE_XMLCONTENT_H

#include <iostream>

class XmlElement;

class XmlContent{
public:
  XmlContent( XmlElement* parent ) : _parent(parent) {}
  XmlElement* parent() { return _parent; }

  // to override
  virtual void toStream( std::ostream& stream ) = 0;

  virtual ~XmlContent();
  
private:
  XmlElement* _parent;
};




#endif
