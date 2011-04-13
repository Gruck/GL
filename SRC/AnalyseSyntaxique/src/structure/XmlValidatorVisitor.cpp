
#include "XmlValidatorVisitor.h" 
#include "Tools.h"
#include "XmlContent.h"
#include "XmlElement.h"
#include "XmlText.h"
#include "XmlDoc.h"
#include "DtdDoc.h"
#include "DtdElement.h"
#include "DtdPossibleContent.h"

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

 std::cout<<"visiting element called : "<<xmlElement->name()<<std::endl;
  XmlElement::ContentListIterator it = xmlElement->firstChild();
  for(;it != xmlElement->childrenEnd();it++){
		if(!(*it)->acceptValidator(this)){
			std::cout<<"un de mes fils est invalide"<<std::endl;
			return false;
		}
	}
  if(!checkAttributes(xmlElement)){//mes attributs
  std::cout<<"mes attributs sont invalides"<<std::endl;
		return false;
	}else if(!checkContent(xmlElement)){//mon contenu
	std::cout<<"mon contenu est invalide"<<std::endl;
		return false;
	}
	std::cout<<"l'element "<< xmlElement->name() << " est valide"<<std::endl;  
  return true; //un noeud est valide tant qu'on a pas prouvé qu'il était invalide
}

bool XmlValidatorVisitor::checkAttributes(XmlElement* xmlElement){
	CALL_MACRO
	
	//trouver la définition dtd de cet element,
	//verifier que pour tout element de la map d'attributs, on ai un équivalent dans la dtd
	return true;
}

bool XmlValidatorVisitor::checkContent(XmlElement* xmlElement){
	CALL_MACRO
	
	//trouver la définition dtd de cet element,
	//verifier que le contenu de cet element est valide vis a vis de la dtd
	
	
	
	return true;
}


bool XmlValidatorVisitor::visit( XmlText* xmlText){
  CALL_MACRO
  return true;
}

bool XmlValidatorVisitor::visitContentRecurse(
  DtdPossibleContent* possibleContent
  , ContentListIterator& xmlIter
  , ContentListIterator& xmlIterStop )
{
  ContentListIterator& xmlIterCopy; // copie l'avancement actuel dans les fils de l'elt xml

  // en fonction du type d'opération (Et, Ou, element)
  switch( possibleContent->type() ){
    case T_SEQ : { // --------------------------------------------- Sequence (ET)
      // en fonction de la multiplicité
      switch(possibleContent->multiplicity() ){
        case : M_NONE{ 
          bool status = true;
          // préparation de l'itérateur et de la condition d'arrete de boucle
          DtdPossibleContent::PossibleContentIterator
            dtdIter = possibleContent->firstChild();
          DtdPossibleContent::PossibleContentIterator
            dtdIterStop = possibleContent->childrenEnd();
          // iteration sur les contenus possibles fils   
          for(; dtdIter != dtdIterStop; ++dtdIter ){
            status &= contentRecurse(*dtdIter, xmlIter, xmlIterStop);
          }
          return status; // retour
          
        }case M_AST : { // multiplicite "*" 
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
              status &= contentRecurse(*dtdIter, xmlIter, xmlIterStop);
            }
            //xmlIterCopy représente la dernière position "valide" (sorte de backtrack)
            if(status) xmlIterCopy = xmlIter;//on avance la dernière position valide
          }
          xmlIter = xmlIterCopy; //on revient à la dernière position valide
          // dans le cas multiplicité * on renvoie toutjour true, mais on est
          // content d'avoir fait les opérations précédents car on a pu faire
          // avancer l'itérateur xmlIter
          return true; 
        }case M_PLUS : {
          bool status = true;
          bool foundOne = false;
          while(status){
            for(dtdIter in possibleContent.children ){
              status &= contentRecurse(*dtdIter, xmlIter, xmlIterStop);
              foundOne |= status; // si on en a trouvé un foundOne = true
            }
            if(status) xmlIterCopy = xmlIter;//on avance la dernière position valide
          }
          xmlIter = xmlIterCopy; //on revient à la dernière position valide
          return foundOne;
        }
      }
    }
    case : T_CHOICE { // -------------------------------------------------------
      assert("Choice" == "not supported yet!");
    }
    case : T_ElT { // ----------------------------------------------------------
      switch( possibleContent->multiplicity() ){
        case M_NONE : {  
          bool status = ( possibleContent->name() == (*xmlIter)->name() )
          ++xmlIter;
          return status;
        }
        case M_AST : {
          while( possibleContent->name() == (*xmlIter)->name() ){
            ++xmlIter;
            // ne pas oublier de vérifier qu'on itère pas en dehors de la liste
            if(xmlIter == xmlIterEnd) return true;
          }
          return true;
        }
        case M_PLUS : {
          bool foundOne = false;
          while( possibleContent->name() == (*xmlIter)->name() ){
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
