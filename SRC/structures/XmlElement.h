
#ifndef HEXALOUTRE_XMLELEMENT_H
#define HEXALOUTRE_XMLELEMENT_H

#include "XmlContent.h"
#include "XmlAttribute.h"
#include "Tools.h"

#include <list>
#include <string>
#include <iostream>


class XmlElement : public XmlContent
{ 
public:
  typedef std::list<XmlAttribute> AttributeList;
  typedef std::list<XmlContent*> ContentList;
  typedef std::list<XmlContent*>::iterator ContentListIterator;

  XmlElement(XmlElement* parent, const std::string& nameSpace, const std::string& name)
  : XmlContent(parent), _nameSpace(nameSpace), _name(name) {
    CALL_MACRO
    if(parent)parent->addChild(this);
  }
  
  inline std::string name() const { CALL_MACRO return _name; }
  inline std::string nameSpace() const { CALL_MACRO return _nameSpace; }
  std::string fullName() const;

  void addChild( XmlContent* toAdd );
  void removeChild( XmlContent* toRemove );
  int nbChildren() const { CALL_MACRO return _attributes.size(); }
  inline ContentListIterator firstChild() { CALL_MACRO return _childContentList.begin(); } 
  inline ContentListIterator childrenEnd() { CALL_MACRO return _childContentList.end(); }

  void toStream( std::ostream& stream );
  
private:
  std::string _nameSpace;
  std::string _name;
  ContentList _childContentList;
  AttributeList _attributes;
};



#endif
