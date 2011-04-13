
#ifndef HEXALOUTRE_XMLVALIDATORVISITOR_H
#define HEXALOUTRE_XMLVALIDATORVISITOR_H

#include "DtdPossibleContent.h"
#include "XmlElement.h"
class DtdDoc;
class XmlDoc;
class XmlContent;
class XmlElement;
class XmlText;
class DtdPossibleContent;
//class DtdPossibleContent::PossibleContentIterator;

/**
 * Implémentation, sur le modèle du design pattern visitor, de la validation d'un
 * document XML à l'aide d'une DTD.
 */ 
class XmlValidatorVisitor{
public:
	XmlValidatorVisitor( DtdDoc* dtdDoc)
		:_dtdDoc(dtdDoc){}


  /**
   * Visite et valide un un Document Xml.
   */ 
  bool visit( XmlDoc* xmlDoc);

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
  
private:
  DtdDoc* _dtdDoc;
  
  bool visitContent(XmlElement* xmlElement);
  bool checkAttributes(XmlElement* xmlElement);
  bool checkContent(XmlElement* xmlElement);
  //bool visitContentRecurse(XmlElement* xmlElement, int& currentXmlChildIndex, DtdPossibleContent* possibleContent, int& currentDtdChildIndex);


};


#endif
