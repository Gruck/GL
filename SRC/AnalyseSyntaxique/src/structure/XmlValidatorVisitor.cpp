
#include "XmlValidatorVisitor.h" 
#include "Tools.h"
#include "XmlContent.h"
#include "XmlElement.h"
#include "XmlText.h"
#include "XmlDoc.h"
#include "DtdDoc.h"
#include "DtdElement.h"
#include "DtdPossibleContent.h"

#include <assert.h>

bool XmlValidatorVisitor::visit( XmlDoc* xmlDoc){
  CALL_MACRO
  //verifier toutes les informations générales du XML
    //doctype
    std::cout<<"Validation du header du xml"<<std::endl;
  //vérifier que le noeud racine est valide
  if(xmlDoc->root()->acceptValidator(this))
	return true;
  else
	return false;
	
  
}

bool XmlValidatorVisitor::visit( XmlContent* content){
  CALL_MACRO
  
  std::cout<<"on ne devrait jamais passer par ici"<<std::endl;
  
}

bool XmlValidatorVisitor::visit( XmlElement* xmlElement){
  CALL_MACRO

 std::cout<<xmlElement->name()<<" : visite de l'élement "<<std::endl;
 
 //si aucune définition dtd pour moi, c'est que je suis en erreur 
 DtdElement* elem = _dtdDoc->element(xmlElement->name());
 if(elem == 0){
   	std::cout<< xmlElement->name() << " : l'element n'existe pas dans la dtd"<<std::endl;  
    return false;
  }
  
 //elem->toStream(std::cout);
 
  XmlElement::ContentListIterator it = xmlElement->firstChild();
  for(;it != xmlElement->childrenEnd();it++){
		if(!(*it)->acceptValidator(this)){
			std::cout<< xmlElement->name() << " : un de mes fils est invalide"<<std::endl;
			return false;
		}
	}
  if(!checkAttributes(xmlElement)){//mes attributs
  std::cout<<xmlElement->name() << " : mes attributs sont invalides"<<std::endl;
		return false;
	}else if(!checkContent(xmlElement)){//mon contenu
	std::cout<<xmlElement->name() << " : mon contenu est invalide"<<std::endl;
		return false;
	}
	std::cout<< xmlElement->name() << " : l'element est valide"<<std::endl;  
  return true; //un noeud est valide tant qu'on a pas prouvé qu'il était invalide
}

bool XmlValidatorVisitor::checkAttributes(XmlElement* xmlElement){
	CALL_MACRO
	
	//trouver la définition dtd de cet element,
	//verifier que pour tout element de la map d'attributs, on ai un équivalent dans la dtd
  DtdElement* elem = _dtdDoc->element(xmlElement->name());
  
  XmlElement::AttributeIterator iterEnd = xmlElement.attributesEnd(); 
  for(XmlElement::AttributeIterator iter = xmlElement.firstAttribute(); iter != iterEnd; iter++){ 
    if(!(elem->hasAttribute(iter->first)))
      return false;
  }
  
  
  
	return true;
}

bool XmlValidatorVisitor::checkContent(XmlElement* xmlElement){
	CALL_MACRO
	
	//trouver la définition dtd de cet element,
	//verifier que le contenu de cet element est valide vis a vis de la dtd
  
  DtdElement* elem = _dtdDoc->element(xmlElement->name());
  
  XmlElement::ContentListIterator first =  xmlElement->firstChild();
  visitContentRecurse(elem->getPossibleContent(), first, xmlElement->childrenEnd());
	
	
	return true;
}


bool XmlValidatorVisitor::visit( XmlText* xmlText){
  CALL_MACRO
  return true;
}

bool XmlValidatorVisitor::visitContentRecurse(
  DtdPossibleContent* possibleContent
  , XmlElement::ContentListIterator& xmlIter
  , const XmlElement::ContentListIterator& xmlIterEnd )
{
  // on copie l'avancement actuel dans les fils de l'elt xml pour pouvoir backtracker
  // si besoin
  XmlElement::ContentListIterator xmlIterCopy; 

  // en fonction du type d'opération (Et, Ou, element)
  switch( possibleContent->type() ){
    case DtdPossibleContent::T_SEQUENCE : { // --------------------- Sequence (ET)
      // en fonction de la multiplicité
      switch(possibleContent->multiplicity() ){
        case DtdPossibleContent::M_NONE :{ 
          bool status = true;
          // préparation de l'itérateur et de la condition d'arrete de boucle
          DtdPossibleContent::PossibleContentIterator
            dtdIter = possibleContent->firstChild();
          DtdPossibleContent::PossibleContentIterator
            dtdIterStop = possibleContent->childrenEnd();
          // iteration sur les contenus possibles fils   
          for(; dtdIter != dtdIterStop; ++dtdIter ){
            status &= visitContentRecurse(*dtdIter, xmlIter, xmlIterEnd);
          }
          return status; // retour
          
        }case DtdPossibleContent::M_AST : { // multiplicite "*" 
          bool status = true;
          // tant que le contenu xml correspon, on récurse pour faire avancer
          // l'itérateur xmlIter (c'est une référence, gardons le à l'esprit)
          while(status){ 
            // préparation de l'itérateur et de la condition d'arrete de boucle
            DtdPossibleContent::PossibleContentIterator
              dtdIter = possibleContent->firstChild();
            DtdPossibleContent::PossibleContentIterator
              dtdIterStop = possibleContent->childrenEnd();
            // iteration sur les contenus possibles fils   
            for(; dtdIter != dtdIterStop; ++dtdIter ){
              status &= visitContentRecurse(*dtdIter, xmlIter, xmlIterEnd);
            }
            //xmlIterCopy représente la dernière position "valide" (sorte de backtrack)
            if(status) xmlIterCopy = xmlIter;//on avance la dernière position valide
          }
          xmlIter = xmlIterCopy; //on revient à la dernière position valide
          // dans le cas multiplicité * on renvoie toutjour true, mais on est
          // content d'avoir fait les opérations précédents car on a pu faire
          // avancer l'itérateur xmlIter
          return true; 
        }case DtdPossibleContent::M_PLUS : {
          bool status = true;
          bool foundOne = false;
          while(status){
            // préparation de l'itérateur et de la condition d'arrete de boucle
            DtdPossibleContent::PossibleContentIterator
              dtdIter = possibleContent->firstChild();
            DtdPossibleContent::PossibleContentIterator
              dtdIterStop = possibleContent->childrenEnd();
            // iteration sur les contenus possibles fils   
            for(; dtdIter != dtdIterStop; ++dtdIter ){
              status &= visitContentRecurse(*dtdIter, xmlIter, xmlIterEnd);
              foundOne |= status; // si on en a trouvé un foundOne = true
            }
            if(status) xmlIterCopy = xmlIter;//on avance la dernière position valide
          }
          xmlIter = xmlIterCopy; //on revient à la dernière position valide
          return foundOne;
        }
      }
    }
    case DtdPossibleContent::T_CHOICE : { // ------------------------Choix (OU)
      //assert("Choice" == "not supported yet!");
      
      // en fonction de la multiplicité
      switch(possibleContent->multiplicity() ){
        case DtdPossibleContent::M_NONE :{ 
          bool status = true;
          // préparation de l'itérateur et de la condition d'arrete de boucle
          DtdPossibleContent::PossibleContentIterator
            dtdIter = possibleContent->firstChild();
          DtdPossibleContent::PossibleContentIterator
            dtdIterStop = possibleContent->childrenEnd();
          // iteration sur les contenus possibles fils   
          for(; dtdIter != dtdIterStop; ++dtdIter ){
            XmlElement::ContentListIterator xmlIterCopy2 = xmlIter; 
            status |= visitContentRecurse(*dtdIter, xmlIter, xmlIterEnd);
             if(!status) xmlIter = xmlIterCopy2; // backtarck
          }
          return status; // retour
          
        }case DtdPossibleContent::M_AST : { // multiplicite "*" 
          bool status = true;
          // tant que le contenu xml correspon, on récurse pour faire avancer
          // l'itérateur xmlIter (c'est une référence, gardons le à l'esprit)
          while(status){ 
            // préparation de l'itérateur et de la condition d'arrete de boucle
            DtdPossibleContent::PossibleContentIterator
              dtdIter = possibleContent->firstChild();
            DtdPossibleContent::PossibleContentIterator
              dtdIterStop = possibleContent->childrenEnd();
            // iteration sur les contenus possibles fils   
            for(; dtdIter != dtdIterStop; ++dtdIter ){
              XmlElement::ContentListIterator xmlIterCopy2 = xmlIter; 
              status |= visitContentRecurse(*dtdIter, xmlIter, xmlIterEnd);
               if(!status) xmlIter = xmlIterCopy2; // backtarck
            }
            //xmlIterCopy représente la dernière position "valide" (sorte de backtrack)
            if(status) xmlIterCopy = xmlIter;//on avance la dernière position valide
          }
          xmlIter = xmlIterCopy; //on revient à la dernière position valide
          // dans le cas multiplicité * on renvoie toutjour true, mais on est
          // content d'avoir fait les opérations précédents car on a pu faire
          // avancer l'itérateur xmlIter
          return true; 
        }case DtdPossibleContent::M_PLUS : {
          bool status = true;
          bool foundOne = false;
          while(status){
            // préparation de l'itérateur et de la condition d'arrete de boucle
            DtdPossibleContent::PossibleContentIterator
              dtdIter = possibleContent->firstChild();
            DtdPossibleContent::PossibleContentIterator
              dtdIterStop = possibleContent->childrenEnd();
            // iteration sur les contenus possibles fils   
            for(; dtdIter != dtdIterStop; ++dtdIter ){
              XmlElement::ContentListIterator xmlIterCopy2 = xmlIter; 
              status |= visitContentRecurse(*dtdIter, xmlIter, xmlIterEnd);
              if(!status) xmlIter = xmlIterCopy2; //backtrack
              foundOne |= status; // si on en a trouvé un foundOne = true
            }
            if(status) xmlIterCopy = xmlIter;//on avance la dernière position valide
          }
          xmlIter = xmlIterCopy; //on revient à la dernière position valide
          return foundOne;
        }
      }
    }  
    
    case DtdPossibleContent::T_ELEM : { // --------------------------------------
      switch( possibleContent->multiplicity() ){
        case DtdPossibleContent::M_NONE : {  
          bool status = ( possibleContent->value() == (*xmlIter)->name() );
          ++xmlIter;
          return status;
        }
        case DtdPossibleContent::M_AST : {
          while( possibleContent->value() == (*xmlIter)->name() ){
            ++xmlIter;
            // ne pas oublier de vérifier qu'on itère pas en dehors de la liste
            if(xmlIter == xmlIterEnd) return true;
          }
          return true;
        }
        case DtdPossibleContent::M_PLUS : {
          bool foundOne = false;
          while( possibleContent->value() == (*xmlIter)->name() ){
            foundOne = true;
            ++xmlIter;
            // ne pas oublier de vérifier qu'on itère pas en dehors de la liste
            if(xmlIter == xmlIterEnd) return foundOne;
          }
          return foundOne;
        }
      }
    }
  }
}
