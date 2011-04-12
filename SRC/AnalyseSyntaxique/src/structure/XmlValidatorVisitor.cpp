
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
  
  
  
}

bool XmlValidatorVisitor::visit( XmlElement* xmlElement){
  CALL_MACRO


  XmlElement::ContentListIterator it = xmlElement->firstChild();
  for(;it != xmlElement->childrenEnd();it++){
	 
	  if(!((*it)->acceptValidator(this)))
		return false;
	  else if(!visitContent(xmlElement))
		return false;
	  else {
	  }
		//do nothing
  }
  
  return true; //un noeud est valide tant qu'on a pas prouvé qu'il était invalide
}

bool XmlValidatorVisitor::visitContent(XmlElement* xmlElement)
{
	CALL_MACRO
	//trouver la définition dtd de cet element
	//comparer avec ce qui peut etre fait
	//XmlElement::ContentListIterator itXml = xmlElement->firstChild();
	//DtdPossibleContent::PossibleContentIterator itDtd_dtdDoc->element(xmlElement->name())->getPossibleContent()->firstChild());
	/*
	int i=0,j=0;
	
	for(;it != xmlElement->childrenEnd(); it++){
		if(!visitContentRecurse(xmlElement, itXml, _dtdDoc->element(xmlElement->name())->getPossibleContent(), itDtd)
			return false;
	}*/
	return true;
	
}

bool XmlValidatorVisitor::visitContentRecurse(XmlElement* xmlElement, int currentXmlChildIndex, DtdPossibleContent* possibleContent, int currentDtdChildIndex)
{
	//DANGER : 
	/*POURQUOI DES REFERENCES
	 * Car celles ci sont pour interet de permettre de transmettre plus facilement aux autres niveaux
	 * POURQUOI SANS REFERENCES
	 * Car plus évident pour l'implementation du backtracking
	 */
	/*
	CALL_MACRO
	//trois choix possibles basé sur le type du possible content

    if(possibleContent->type() ==   DtdPossibleContent::T_ELEM){
		//c'est simple, il faut que le nom corresponde ! 
		if(!(possibleContent->value() == xmlElement->name()))
			return false;
	}else if(possibleContent->type() ==  DtdPossibleContent::T_SEQUENCE){
		//il faut que tout ses dtdPossibleContents fils matchent qqc
		
		
	}else{
		
	}
	*/
	
}


bool XmlValidatorVisitor::visit( XmlText* xmlText){
  CALL_MACRO
  return true;
}

