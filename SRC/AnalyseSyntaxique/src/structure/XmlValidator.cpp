
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
    bool status = xmlDoc->acceptValidator(xmlValidatorVisitor);
    delete xmlValidatorVisitor;
    if(status)
    std::cout <<"tout c'est bien passé"<<std::endl;
    else
    std::cout<<"on a un probleme dans XmlValidator"<<std::endl;
    return status;
  }
  
