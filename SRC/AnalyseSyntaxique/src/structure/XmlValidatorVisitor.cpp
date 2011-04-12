
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
	XmlElement::ContentListIterator itXml = xmlElement->firstChild();
	DtdPossibleContent::PossibleContentIterator itDtd_dtdDoc->element(xmlElement->name())->getPossibleContent()->firstChild());
	
	for(;it != xmlElement->childrenEnd(); it++){
		if(!visitContentRecurse(xmlElement, itXml, _dtdDoc->element(xmlElement->name())->getPossibleContent(), itDtd)
			return false;
	}
	return true;
	
}

bool XmlValidatorVisitor::visitContentRecurse(XmlElement* xmlElement, XmlElement::ContentListIterator& currentXmlChildIterator, DtdPossibleContent* possibleContent, DtdPossibleContent::PossibleContentIterator& currentDtdChildIterator)
{
	CALL_MACRO
	//trois choix possibles basé sur le type du possible content
	/* T_SEQUENCE, 
    T_CHOICE,
    T_ELEM*/
    if(possibleContent->type() ==   DtdPossibleContent::T_ELEM){
		//c'est simple, il faut que le nom corresponde ! 
		if(!(possibleContent->value() == xmlElement->name()))
			return false;
	}else if(possibleContent->type() ==  DtdPossibleContent::T_SEQUENCE){
		if(!visitContentRecurse(xmlElement, itXml, *itDtd , (*itDtd)->firstchild()));
		
	}else{
		
	}
	
	
}


bool XmlValidatorVisitor::visit( XmlText* xmlText){
  CALL_MACRO
  return true;
}

