
#ifndef HEXALOUTRE_DTDELEMENT_H
#define HEXALOUTRE_DTDELEMENT_H

//#include "DtdAttribute.h"
#include "Tools.h"

#include <list>
#include <map>
#include <string>
#include <iostream>


#define INDETATION_PATTERN "  "

class DtdPossibleContent;

/**
 * Fournit les descriptions nécessaire à la validation d'un XmlElement.
 */ 
class DtdElement 
{ 
public:
  typedef std::map<std::string,std::string> AttributeMap;

  /**
   * Constructeur.
   */ 
  DtdElement(const std::string& name, DtdPossibleContent* possibleContent)
  :  _name(name), _possibleContent(possibleContent) { CALL_MACRO }

  /**
   * revoie le nom de l'élément.
   */ 
  inline const std::string& name() const { return _name; }

  /**
   * Déprécié
   * TODO: ajouter les attributs un par un.
   */
  inline void addAttribute(const std::string& name,const std::string& type) {
    _attributes[name] = type;
  }

  /**
   * Renvoie un itérateur vers le premier attribut de cet élément.
   *
   * L'itérateur pointe vers une paire <nom_attribut,type_attribut>.
   */ 
  inline AttributeMap::iterator firstAttribute(){
    return _attributes.begin();
  } 

  /**
   * Renvoie un itérateur servant de condition d'arrêt lors de l'itération
   * sur les attributs.
   *
   * Notez que cet itérateur ne pointe sur aucun attribut, il n'est utile qu'en
   * tant que condition d'arrêt.
   */ 
  inline AttributeMap::iterator attributesEnd(){
    return _attributes.end();
  } 

  /**
   * Renvoie le nombre d'attributs pour cet élément.
   */ 
  inline int nbAttributes() const {
    return _attributes.size();
  }

  /**
   * Renvoie true si l'attribut possédant le nom spécifié existe dans cet élément.
   */ 
  bool hasAttribute(const std::string& attrName) const;

  /**
   * Renoie un pointeur vers le type de l'élément dont le nom est passé en paramêtre.
   *
   * Renvoie un pointeur nul dans si l'élément n'existe pas.
   */ 
  std::string* findAttribute(const std::string& attrName);
  
   /**
   * Affiche dans un flux standard l'élément courant ainsi que ses contenu fils
   * récursivement.
   *
   * Le paramêtre indentation fixe le niveau d'indentation de l'élément et est
   * incrémenté par les éléments fils. Dans le cas général il n'a pas besoin
   * d'être précisé par l'utilisateur.
   */ 
  void toStream( std::ostream& stream, int indentation = 0 );
  
private:
  std::string _name;
  DtdPossibleContent* _possibleContent;
  AttributeMap _attributes; //warning, possible confusion with XmlAttribute
  
  
};



#endif
