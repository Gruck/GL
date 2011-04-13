
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

bool XmlValidatorVisitor::visitContentRecurse(XmlElement* xmlElement, XmlElement::ContentListIterator& currentXmlChildIterator, DtdPossibleContent* possibleContent, DtdPossibleContent::PossibleContentIterator currentDtdChildIterator){
	CALL_MACRO
	
	//faire une copie des itérateurs.
	XmlElement::ContentListIterator SAVEcurrentXmlChildIterator = currentXmlChildIterator;
	DtdPossibleContent::PossibleContentIterator SAVEcurrentDtdChildIterator = currentDtdChildIterator;
	
	//faire la différence suivant les différents types de contenus possibles
	
	if(possibleContent->type() == DtdPossibleContent::T_CHOICE){
		return true;
	}else if(possibleContent->type() == DtdPossibleContent::T_SEQUENCE){
		//faire la différence suivant la multiplicité
		switch(possibleContent->multiplicity()){
			case DtdPossibleContent::M_QMARK : {return true; break;}
			case DtdPossibleContent::M_AST : {return true; break;}
			case DtdPossibleContent::M_PLUS : {return true; break;}
			case DtdPossibleContent::M_NONE : {/*visitContentRecurse(xmlElement, currentXmlChildIterator,*/   break;}
			default : std::cout<<"la multiplicité indiqué dans le possibleContent n'est pas légale\n";
		}
	}else if(possibleContent->type() == DtdPossibleContent::T_ELEM){
		
	}else{
		std::cout<<"dtd possible content invalide, n'est ni une sequance, ni un choix, un rien du tout ^^"<<std::endl;
		return false;
	}
	return true;
}

