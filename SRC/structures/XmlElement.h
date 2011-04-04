
#ifndef HEXALOUTRE_XMLELEMENT_H
#define HEXALOUTRE_XMLELEMENT_H

#include "XmlContent.h"

#include <list>
#include <string>
#include <iostream>

class XmlElement : public XmlContent
{ 
public:
  typedef std::list<XmlContent*> ContentList;
  typedef std::list<XmlContent*>::iterator ContentListIterator;

  XmlElement(XmlElement* parent, const std::string& nameSpace, const std::string& name)
  : XmlContent(parent), _nameSpace(nameSpace), _name(name) {}
  
  std::string name() const { return _name; }
  std::string nameSpace() const { return _nameSpace; }
  std::string fullName() const { return _nameSpace+":"+_name; }

  void addChildContent( XmlContent* toAdd );
  void removeChildContent( XmlContent* toRemove );
  
  ContentListIterator childContentBegin() { return _childContentList.begin(); } 
  ContentListIterator childContentEnd() { return _childContentList.end(); }

  void toStream( std::ostream& stream );
  
private:
  std::string _nameSpace;
  std::string _name;
  ContentList _childContentList;
  
};



#endif
