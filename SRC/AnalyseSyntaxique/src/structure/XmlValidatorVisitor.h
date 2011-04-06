
#ifndef HEXALOUTRE_XMLVALIDATORVISITOR_H
#define HEXALOUTRE_XMLVALIDATORVISITOR_H

class XmlContent;
class XmlElement;
class XmlText;

class XmlValidatorVisitor{
public:

  bool visit( XmlContent* content);
  bool visit( XmlElement* xmlElement);
  bool visit( XmlText* xmlText);

};


#endif
