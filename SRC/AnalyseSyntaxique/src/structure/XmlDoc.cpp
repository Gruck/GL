
#include "XmlDoc.h"
#include "Tools.h"
#include <iostream>

#include "XmlElement.h"
#include "XmlText.h"
#include "XmlValidatorVisitor.h"

XmlDoc::~XmlDoc(){ 
  CALL_MACRO
  if(_root) delete _root;
}

void XmlDoc::toStream(std::ostream& stream){
  stream << "<!DOCTYPE " << doctype() << " >\n";
  if(_root) _root->toStream(stream,0);
}

bool XmlDoc::acceptValidator( XmlValidatorVisitor* validator ){
  CALL_MACRO
  return validator->visit(this);
}

XmlDoc* XmlDoc::CreateDummyXmlForRap1()
{
	XmlDoc* rap1xml = new XmlDoc("xhtml");
	
	
  XmlElement* elt = new XmlElement("","rapport");
  rap1xml->setRoot(elt);


  elt->addChild( new XmlElement( "" ,"titre" ) );
  elt->childElement("titre")->addChild( new XmlText("le titre") );
  
  elt->addChild( new XmlElement( "" ,"auteur" ) );
  elt->childElement("auteur")->addChild(new XmlElement("","prenom"));
  elt->childElement("auteur")->addChild(new XmlElement("","nom"));
  
  
  
  elt->childElement("auteur")->childElement("prenom")->addChild(new XmlText("Nical" ));
  elt->childElement("auteur")->childElement("nom")->addChild(new XmlText("Silva" ));
  
  

  elt->addChild( new XmlElement( "" ,"resume" ) );
  elt->childElement("resume")->addChild(new XmlText("text de l'element resume" ));
  
  elt->addChild( new XmlElement( "" ,"chapitre" ) );
  elt->childElement("chapitre")->addChild(new XmlElement("","titre"));
  elt->childElement("chapitre")->childElement("titre")->addChild(new XmlText("ceci est un titre" ));
  
  elt->childElement("chapitre")->addChild(new XmlElement("","section"));
  elt->childElement("chapitre")->childElement("section")->addChild(new XmlElement("","titre"));
  elt->childElement("chapitre")->childElement("section")->childElement("titre")->addChild(new XmlText("titre de la section " ));
  elt->childElement("chapitre")->childElement("section")->addChild(new XmlElement("","p"));
  elt->childElement("chapitre")->childElement("section")->childElement("p")->addChild(new XmlText("voici le texte de la section, un joli paragraph de texte." ));
  
  elt->childElement("chapitre")->addChild(new XmlElement("","section"));
  elt->childElement("chapitre")->childElement("section",1)->addChild(new XmlElement("","titre"));
  elt->childElement("chapitre")->childElement("section",1)->childElement("titre")->addChild(new XmlText("titre de la section terrain2" ));
  elt->childElement("chapitre")->childElement("section",1)->addChild(new XmlElement("","p"));
  elt->childElement("chapitre")->childElement("section",1)->childElement("p")->addChild(new XmlText("encore un paragraph" ));



	return rap1xml;
	
	
}

XmlDoc* XmlDoc::CreateDummyXmlForNoob()
{
	XmlDoc* rap1xml = new XmlDoc("xhtml");
	
	
  XmlElement* elt = new XmlElement("","rapport");
  rap1xml->setRoot(elt);


  elt->addChild( new XmlElement( "" ,"titre" ) );
  
  
  elt->childElement("titre")->addChild(new XmlText("Ceci est un titre" ));
  
	return rap1xml;
}
