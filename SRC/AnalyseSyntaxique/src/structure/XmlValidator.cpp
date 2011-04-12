
#include "XmlValidator.h"
#include "Tools.h"

#include "XmlDoc.h"
#include "XmlElement.h"
#include "XmlText.h"
#include "XmlValidatorVisitor.h"
  
  
  //bool XmlValidator::validate( XmlDoc* xmlDoc) const
  bool XmlValidator::validate( XmlDoc* xmlDoc, DtdDoc* dtdDoc)
  {
	CALL_MACRO
	//creer le XmlValidatorVisitor
	//demander au XmlDoc d'accepter la visite sur visitor
	XmlValidatorVisitor* xmlValidatorVisitor = new XmlValidatorVisitor( dtdDoc );
	xmlDoc->acceptValidator(xmlValidatorVisitor);
	delete xmlValidatorVisitor;
  }
  
