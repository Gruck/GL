
#ifndef HEXALOUTRE_XMLELEMENT_H
#define HEXALOUTRE_XMLELEMENT_H

#include "XmlContent.h"
#include "XmlAttribute.h"
#include "Tools.h"

#include <list>
#include <string>
#include <iostream>


#define INDETATION_PATTERN "  "


class XmlElement : public XmlContent
{ 
public:
  typedef std::list<XmlAttribute> AttributeList;
  typedef std::list<XmlContent*> ContentList;
  typedef std::list<XmlContent*>::iterator ContentListIterator;

  XmlElement(const std::string& nameSpace,const std::string& name)
  : XmlContent(0), _nameSpace(nameSpace), _name(name) {
    CALL_MACRO
  }
  
  inline std::string name() const { return _name; }
  inline std::string nameSpace() const { return _nameSpace; }
  std::string fullName() const;


  void addAttribute( const XmlAttribute& attribute );
  void removeAttribute( const XmlAttribute& attribute );
  
  void addChild( XmlContent* toAdd );
  void deleteChild( XmlContent* toRemove );
  XmlContent* detachChild( XmlContent* toRemove );
  int nbChildren() const { CALL_MACRO return _childContentList.size(); }

  // iterators to child content
  inline ContentListIterator firstChild() {
    CALL_MACRO return _childContentList.begin();
  } 
  inline ContentListIterator childrenEnd() {
    CALL_MACRO return _childContentList.end();
  }
  // to get the nth element child (slow but easy to use)
  XmlElement* childElement(int nth);
  XmlElement* childElement(const std::string& name);

  // prints the tree
  void toStream( std::ostream& stream, int indentation = 0 );
  
private:
  std::string _nameSpace;
  std::string _name;
  ContentList _childContentList;
  AttributeList _attributes;
  
  
};



#endif
