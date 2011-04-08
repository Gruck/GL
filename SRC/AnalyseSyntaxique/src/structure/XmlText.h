
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
   * Renvoie une référence vers le texte sous forme std::string
   */ 
  std::string& text() { CALL_MACRO return _data; }

  /**
   * Permet de réaliser le "double dispatch" nécessaire à l'application du design
   * pattern visitor implémenté au niveau de l'algorithme de validation. 
   */ 
  bool acceptValidator( XmlValidatorVisitor* validator );
  
private:
  std::string _data;
};




#endif
