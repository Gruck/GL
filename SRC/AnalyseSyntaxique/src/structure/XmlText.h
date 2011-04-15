
#ifndef HEXALOUTRE_XMLTEXT_H
#define HEXALOUTRE_XMLTEXT_H

#include "XmlContent.h"
#include <iostream>

class XmlValidatorVisitor;

/**
 * Contenu textuel pouvant figurer dans un document XML
 */ 
class XmlText : public XmlContent
{
public:
  XmlText(const std::string& text)
  : XmlContent(0), _data(text) { }


  /**
   * Affiche le contenu textuel dans un flux standard. 
   */ 
  void toStream( std::ostream& stream, int indentation = 0 );

  /**
   * Fournit un accès au texte sous forme std::string.
   */ 
  std::string& text() { CALL_MACRO return _data; }

  /**
   * Renvoie un nom fictif désignant en réalité le type de ce noeud xml, du texte.
   *
   * Cette entourloupe permet de valider BIEN PLUS FACILEMENT le xml via une dtd
   * (beaucoup moins de dynamic cast à faire pour rien)
   */ 
  std::string name() const { return "#CDATA"; }

  /**
   * Permet de réaliser le "double dispatch" nécessaire à l'application du design
   * pattern visitor implémenté au niveau de l'algorithme de validation. 
   */ 
  bool acceptValidator( XmlValidatorVisitor* validator );

  
  
private:
  std::string _data;
};




#endif
