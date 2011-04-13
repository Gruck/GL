
#ifndef HEXALOUTRE_XMLCONTENT_H
#define HEXALOUTRE_XMLCONTENT_H

#include <iostream>
#include "Tools.h"

class XmlElement;
class XmlValidatorVisitor;

/**
 * Contenu d'un document XML.
 *
 * Cette classe abstraite peut représenter soit un contenu textuel (@see XmlText),
 * soit l'ouverture et la fermeture d'une balise XML (@see XmlElement).
 *
 */ 
class XmlContent{
friend class XmlElement;
public:
  /**
   * Constructeur.
   */ 
  XmlContent( XmlElement* parent );

  /**
   * Fournit un pointeur vers le XmlElement parent ce contenu XML, s'il existe.
   */  
  XmlElement* parent() { CALL_MACRO return _parent; }

  virtual std::string name() const = 0;

  /**
   * Affiche le contenu XML dans un flux standard.
   *
   * Surchargé par XmlElement et XmlText
   */ 
  virtual void toStream( std::ostream& stream, int indentation = 0 ) = 0;

  /**
   * Destructeur.
   */ 
  virtual ~XmlContent();

  /**
   * Permet de réaliser le "double dispatch" nécessaire à l'application du design
   * pattern visitor implémenté au niveau de l'algorithme de validation.
   *
   * Surchargé par XmlElement et XmlText.  
   */ 
  virtual bool acceptValidator( XmlValidatorVisitor* ) = 0;
  
protected:
  /**
   * Fournit aux classes dérivées la possibilité de définir leur noeud parent
   */ 
  void setParent(XmlElement* parentElt){ CALL_MACRO _parent = parentElt; }

  /**
   * méthode outil envooyant des espaces dans un flux standard pour faciliter
   * l'indentation dans les méthodes toStream.
   */ 
  void indent(std::ostream& stream, int indentation){
    for(int i = 0; i < indentation; ++i) stream << "  ";
  }
private:
  XmlElement* _parent;
};




#endif
