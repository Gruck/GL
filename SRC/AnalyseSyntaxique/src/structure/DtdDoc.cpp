

#include "DtdDoc.h"
#include "DtdElement.h"
#include "DtdPossibleContent.h"
#include "Tools.h"
#include <string>

#include <iostream>

void DtdDoc::toStream(std::ostream& stream){
  stream << "<!DOCTYPE "<< _doctype <<" [\n" ;
  ElementList::iterator iter = _rules.begin();
  ElementList::iterator stop = _rules.end();
  for(;iter!=stop;++iter)
    (*iter)->toStream(stream);
  stream << "]>\n";
}
  
void DtdDoc::AddElement(DtdElement *element)
{
	_rules.push_back(element);
}



DtdElement* DtdDoc::element(const std::string& eltName){
  ElementList::iterator iter = _rules.begin();
  ElementList::iterator stop = _rules.end();
  for(;iter!=stop;++iter){
    if((*iter)->name() == eltName){
      return (*iter);
    }
  }
  return 0;
}



DtdDoc* DtdDoc::CreateDummyDtdForRap1()
{
	CALL_MACRO	
/*
<!ELEMENT rapport (titre, auteur+, resume, chapitre+)>
<!ELEMENT auteur (prenom, nom)>
<!ELEMENT nom (#PCDATA)>
<!ELEMENT prenom (#PCDATA)>
<!ELEMENT resume (#PCDATA)>
<!ELEMENT chapitre (titre, (p | section)+)>
<!ELEMENT section (titre, p+)>
<!ELEMENT p (#PCDATA)>
<!ELEMENT titre (#PCDATA)>
*/
// nous allons creer une instance qui représentera tout ca :)
DtdDoc* Rap1dtd = new DtdDoc();

//creation des diverses composantes de cette Dtd
DtdPossibleContent* pc1 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, std::string(), DtdPossibleContent::M_NONE);
DtdPossibleContent* pc2 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "titre", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc3 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "auteur", DtdPossibleContent::M_PLUS);
DtdPossibleContent* pc4 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, std::string("resume"), DtdPossibleContent::M_NONE);
DtdPossibleContent* pc5 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, std::string("chapitre"), DtdPossibleContent::M_PLUS);
pc1->addChild(pc2);
pc1->addChild(pc3);
pc1->addChild(pc4);
pc1->addChild(pc5);
DtdElement* el0 = new DtdElement("rapport", pc1);


DtdPossibleContent* pc11 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc12 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "prenom", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc13 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "nom", DtdPossibleContent::M_NONE);
pc11->addChild(pc12);
pc11->addChild(pc13);
DtdElement* el1 = new DtdElement("auteur", pc11);


DtdPossibleContent* pc21 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc22 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "#PCDATA", DtdPossibleContent::M_NONE);
pc21->addChild(pc22);
DtdElement* el2 = new DtdElement("prenom", pc21);

DtdPossibleContent* pc31 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc32 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "#PCDATA", DtdPossibleContent::M_NONE);
pc31->addChild(pc32);
DtdElement* el3 = new DtdElement("nom", pc31);

DtdPossibleContent* pc41 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc42 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "#PCDATA", DtdPossibleContent::M_NONE);
pc41->addChild(pc42);
DtdElement* el4 = new DtdElement("p", pc41);

DtdPossibleContent* pc51 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc52 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "#PCDATA", DtdPossibleContent::M_NONE);
pc51->addChild(pc52);
DtdElement* el5 = new DtdElement("titre", pc51);

DtdPossibleContent* pc61 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc62 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "#PCDATA", DtdPossibleContent::M_NONE);
pc61->addChild(pc62);
DtdElement* el6 = new DtdElement("resume", pc61);

DtdPossibleContent* pc71 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc72 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "titre", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc73 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "p", DtdPossibleContent::M_PLUS);
pc71->addChild(pc72);
pc71->addChild(pc73);
DtdElement* el7 = new DtdElement("section", pc71);

DtdPossibleContent* pc81 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc82 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "titre", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc83 = new DtdPossibleContent(DtdPossibleContent::T_CHOICE, "", DtdPossibleContent::M_PLUS);
DtdPossibleContent* pc831 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "p", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc832 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "section", DtdPossibleContent::M_NONE);
pc83->addChild(pc831);
pc83->addChild(pc832);
pc81->addChild(pc82);
pc81->addChild(pc83);
DtdElement* el8 = new DtdElement("chapitre", pc81);

Rap1dtd->AddElement(el0);
Rap1dtd->AddElement(el1);
Rap1dtd->AddElement(el2);
Rap1dtd->AddElement(el3);
Rap1dtd->AddElement(el4);
Rap1dtd->AddElement(el5);
Rap1dtd->AddElement(el6);
Rap1dtd->AddElement(el7);
Rap1dtd->AddElement(el8);



return Rap1dtd;
}

DtdDoc* DtdDoc::CreateDummyDtdForRap3()
{
	CALL_MACRO	
/*
<!ELEMENT rapport (titre, auteur+, resume, chapitre+)>
<!ELEMENT titre (#PCDATA)>
<!ELEMENT auteur (nom, prenom)>
<!ELEMENT nom (#PCDATA)>
<!ELEMENT prenom (#PCDATA)>
<!ELEMENT resume (#PCDATA)>
<!ELEMENT chapitre (p | section)+>
<!ATTLIST chapitre
        titre CDATA #IMPLIED
>
<!ELEMENT section (p)+>
<!ATTLIST section
        titre CDATA #IMPLIED
>
<!ELEMENT p (#PCDATA)>

*/
// nous allons creer une instance qui représentera tout ca :)
DtdDoc* Rap3dtd = new DtdDoc();

//creation des diverses composantes de cette Dtd
DtdPossibleContent* pc1 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, std::string(), DtdPossibleContent::M_NONE);
DtdPossibleContent* pc2 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "titre", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc3 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "auteur", DtdPossibleContent::M_PLUS);
DtdPossibleContent* pc4 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, std::string("resume"), DtdPossibleContent::M_NONE);
DtdPossibleContent* pc5 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, std::string("chapitre"), DtdPossibleContent::M_PLUS);
pc1->addChild(pc2);
pc1->addChild(pc3);
pc1->addChild(pc4);
pc1->addChild(pc5);
DtdElement* el0 = new DtdElement("rapport", pc1);


DtdPossibleContent* pc11 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc12 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "prenom", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc13 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "nom", DtdPossibleContent::M_NONE);
pc11->addChild(pc12);
pc11->addChild(pc13);
DtdElement* el1 = new DtdElement("auteur", pc11);


DtdPossibleContent* pc21 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc22 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "#PCDATA", DtdPossibleContent::M_NONE);
pc21->addChild(pc22);
DtdElement* el2 = new DtdElement("prenom", pc21);

DtdPossibleContent* pc31 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc32 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "#PCDATA", DtdPossibleContent::M_NONE);
pc31->addChild(pc32);
DtdElement* el3 = new DtdElement("nom", pc31);

DtdPossibleContent* pc41 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc42 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "#PCDATA", DtdPossibleContent::M_NONE);
pc41->addChild(pc42);
DtdElement* el4 = new DtdElement("p", pc41);

DtdPossibleContent* pc51 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc52 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "#PCDATA", DtdPossibleContent::M_NONE);
pc51->addChild(pc52);
DtdElement* el5 = new DtdElement("titre", pc51);

DtdPossibleContent* pc61 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc62 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "#PCDATA", DtdPossibleContent::M_NONE);
pc61->addChild(pc62);
DtdElement* el6 = new DtdElement("resume", pc61);

DtdPossibleContent* pc71 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
//DtdPossibleContent* pc72 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "titre", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc73 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "p", DtdPossibleContent::M_PLUS);
//pc71->addChild(pc72);
pc71->addChild(pc73);
DtdElement* el7 = new DtdElement("section", pc71);
el7->addAttribute("titre", "CDATA");

//DtdPossibleContent* pc81 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
//DtdPossibleContent* pc82 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "titre", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc83 = new DtdPossibleContent(DtdPossibleContent::T_CHOICE, "", DtdPossibleContent::M_PLUS);
DtdPossibleContent* pc831 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "p", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc832 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "section", DtdPossibleContent::M_NONE);
pc83->addChild(pc831);
pc83->addChild(pc832);
//pc81->addChild(pc82);
//pc81->addChild(pc83);
DtdElement* el8 = new DtdElement("chapitre", pc83);//pc81);
el8->addAttribute("titre", "CDATA");

Rap3dtd->AddElement(el0);
Rap3dtd->AddElement(el1);
Rap3dtd->AddElement(el2);
Rap3dtd->AddElement(el3);
Rap3dtd->AddElement(el4);
Rap3dtd->AddElement(el5);
Rap3dtd->AddElement(el6);
Rap3dtd->AddElement(el7);
Rap3dtd->AddElement(el8);

//attributs





return Rap3dtd;
}
