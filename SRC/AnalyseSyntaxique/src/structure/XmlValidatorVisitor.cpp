
#include "XmlValidatorVisitor.h" 
#include "Tools.h"
#include "XmlContent.h"
#include "XmlElement.h"
#include "XmlText.h"

bool XmlValidatorVisitor::visit( XmlDoc* xmlDoc){
  CALL_MACRO
  //return content->acceptValidator(this);
}

bool XmlValidatorVisitor::visit( XmlContent* content){
  CALL_MACRO
  //return content->acceptValidator(this);
}

bool XmlValidatorVisitor::visit( XmlElement* xmlElement){
  CALL_MACRO
}

bool XmlValidatorVisitor::visit( XmlText* xmlText){
  CALL_MACRO
}
