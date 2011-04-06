
#ifndef HEXALOUTRE_XMLCONTENT_H
#define HEXALOUTRE_XMLCONTENT_H

#include <iostream>
#include "Tools.h"

class XmlElement;
class XmlValidatorVisitor;

class XmlContent{
friend class XmlElement;
public:
  XmlContent( XmlElement* parent );
  
  XmlElement* parent() { CALL_MACRO return _parent; }

  // to override
  virtual void toStream( std::ostream& stream, int indentation = 0 ) = 0;

  virtual ~XmlContent();

  virtual bool acceptValidator( XmlValidatorVisitor* ) = 0;
  
protected:
  void setParent(XmlElement* parentElt){ CALL_MACRO _parent = parentElt; }
  void indent(std::ostream& stream, int indentation){
    for(int i = 0; i < indentation; ++i) stream << "  ";
  }
private:
  XmlElement* _parent;
};




#endif
