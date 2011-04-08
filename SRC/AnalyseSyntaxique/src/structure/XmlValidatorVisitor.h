
#ifndef HEXALOUTRE_XMLVALIDATORVISITOR_H
#define HEXALOUTRE_XMLVALIDATORVISITOR_H

class XmlContent;
class XmlElement;
class XmlText;

/**
 * Implémentation, sur le modèle du design pattern visitor, de la validation d'un
 * document XML à l'aide d'une DTD.
 */ 
class XmlValidatorVisitor{
public:

  /**
   * Visite et valide un un contenu Xml
   *
   * Réalise un "double dispatch" afin de sélectionner la bonne méthode entre :
   * visit(XmlElement*) et visit(XmlText*).
   */ 
  bool visit( XmlContent* content);
  /**
   * Visite et valide un XmlElement selon une Dtd.
   */ 
  bool visit( XmlElement* xmlElement);
  /**
   * Visite et valide un contenu Textuel dans un document Xml.
   */ 
  bool visit( XmlText* xmlText);

};


#endif
