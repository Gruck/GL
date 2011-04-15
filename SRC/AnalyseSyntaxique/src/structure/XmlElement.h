#ifndef HEXALOUTRE_XMLELEMENT_H
#define HEXALOUTRE_XMLELEMENT_H

#include "XmlContent.h"
#include "XmlAttribute.h"
#include "Tools.h"

#include <list>
#include <map>
#include <string>
#include <iostream>


#define INDETATION_PATTERN "  "

class XmlValidatorVisitor;

/**
 * Elément XML correspondant à l'ouverture et la fermeture d'une balise, et pouvant
 * posséder des contenus fils.
 */ 
class XmlElement : public XmlContent
{ 
public:
  typedef std::map<std::string,std::string> AttributeMap;
  typedef std::list<XmlContent*> ContentList;
  typedef std::list<XmlContent*>::iterator ContentListIterator;

  /**
   * Constructor.
   */ 
  XmlElement(const std::string& nameSpace,const std::string& name)
  : XmlContent(0), _nameSpace(nameSpace), _name(name) {
    CALL_MACRO
  }

  /**
   * Renvoie le nom de la balise XML.
   */ 
  std::string name() const { return _name; }

  /**
   * Renvoie l'espace de nom de la balise XML.
   */ 
  inline std::string nameSpace() const { return _nameSpace; }

  /**
   * Renvoie le nom complet de la balise XML.
   *
   * Sous la forme <espace de nom>:<nom> si la balise est placée dans un namespace.
   * Sous la forme <nom> si la balise n'a pas d'espace de nom spécifié.
   */ 
  std::string fullName() const;

  /**
   * Ajoute un attribut à l'élément XML.
   *
   * cette méthode est dépréciée, elle fonctionne mais nous conseillons
   * l'utilisation de :
   * addAttribute(const std::string&, const std::string&)
   */ 
  void addAttribute( const XmlAttribute& attribute );
  /**
   * Ajoute un attribut à l'élément XML.
   */ 
  void addAttribute( const std::string& attributeName, const std::string& value );
  /**
   * Retire un attribut de l'élément XML.
   *
   * Cette méthode est dépressiée, elle fonctionne mais nous conseillons
   * l'utilisation de :
   * removeAttribute(const std::string&)
   */ 
  void removeAttribute( const XmlAttribute& attribute );
  /**
   * Retire un attribut de l'élément XML.
   */ 
  void removeAttribute( const std::string& attribute );
  
  /**
   * Ajoute un contenu fils à cet élément XML. 
   */ 
  void addChild( XmlContent* toAdd );
  /**
   * Retire et détruit un contenu fils de cet élément XML.
   */ 
  void deleteChild( XmlContent* toRemove );
  /**
   * Retire sans détruire un contenu fils de cet élément XML.
   *
   * Utile pour déplacer des sous-arbres du document XML.
   */ 
  XmlContent* detachChild( XmlContent* toRemove );
  /**
   * Renvoie le nombre de fils de cet élément XML.
   */ 
  int nbChildren() const { CALL_MACRO return _childContentList.size(); }

  /**
   * Fournit un itérateur pointant vers le premier contenu fils de cet élément.
   *
   * C'est la façon générique et "standard" d'accéder aux éléments de profondeur
   * N+1 du document XML.
   */ 
  inline ContentListIterator firstChild() {
    CALL_MACRO return _childContentList.begin();
  }
  /**
   * Fournit un itérateur pointant sur "la fin" de la liste des contenus fils
   * de cet élément.
   *
   * Cette méthode est à utiliser conjointement avec la méthode firstChild()
   * pour itérer sur les contenus fils de l'élément courant.
   * Attention: l'itérateur renvoyé par cette méthode ne pointe sur aucun
   * contenu, il doit être utilisé uniquement comme condition d'arrêt de boucle
   * d'itération. 
   */ 
  inline ContentListIterator childrenEnd() {
    CALL_MACRO return _childContentList.end();
  }

  /**
   * Méthode non générique pour accéder uniquement aux XmlElement fils.
   *
   * Cette méthode fournit un accès facile au n-ième XmlElement fils en ignorant
   * les XmlText fils. Préférez l'utilisation de firstChild() et childrenEnd()
   * lorsque celà est possible.
   * Cetté méthode est pratique lorsque l'on s'intéresse uniquement à la structure
   * du document XML, mais fournit un accès lent (O(N) avec un cast dynamique
   * par itération)
   */ 
  XmlElement* childElement(int nth);
  
  /**
   * Cette méthode fournit un accès facile au n-ième XmlContnet fils 
   */ 
  XmlContent* childContent(int nth);
  
  /**
   * Méthode non générique pour accéder uniquement aux XmlElement fils.
   *
   * Cette méthode fournit un accès facile aux XmlElement fils par leurs noms.
   * Préférez l'utilisation de firstChild() et childrenEnd() lorsque celà est
   * possible.
   * Cetté méthode est pratique lorsque l'on s'intéresse uniquement à la structure
   * du document XML, mais fournit un accès lent (O(N) avec un cast dynamique
   * par itération)
   */ 
  XmlElement* childElement(const std::string& name, int nth = 0);

  /**
   * Méthode non générique pour accéder uniquement aux XmlElement fils.
   *
   * Cette méthode fournit un accès facile aux XmlElement fils par leurs noms.
   * Préférez l'utilisation de firstChild() et childrenEnd() lorsque celà est
   * possible.
   * Cetté méthode est pratique lorsque l'on s'intéresse uniquement à la structure
   * du document XML, mais fournit un accès lent (O(N) avec un cast dynamique
   * par itération)
   */ 
  XmlElement* childElement(const std::string& name, const std::string& attributeName, int nth = 0);  	
	
  /**
   * Affiche dans un flux standard l'élément courant ainsi que ses contenu fils
   * récursivement.
   *
   * Le paramêtre indentation fixe le niveau d'indentation de l'élément et est
   * incrémenté par les éléments fils. Dans le cas général il n'a pas besoin
   * d'être précisé par l'utilisateur.
   */ 
  void toStream( std::ostream& stream, int indentation = 0 );

  /**
   * Permet de réaliser le "double dispatch" nécessaire à l'application du design
   * pattern visitor implémenté au niveau de l'algorithme de validation. 
   */ 
  bool acceptValidator( XmlValidatorVisitor* validator );

  ~XmlElement();
  
private:
  std::string _nameSpace;
  std::string _name;
  ContentList _childContentList;
  AttributeMap _attributes;
  
  
};



#endif
