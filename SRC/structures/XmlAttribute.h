
#ifndef HEXALOUTRE_XMLATTRIBUTE_H
#define HEXALOUTRE_XMLATTRIBUTE_H


class XmlAttribute{
public:
  std::string name() const { return _name; }
private:
  std::string _name;
  std::string _value;
};




#endif
