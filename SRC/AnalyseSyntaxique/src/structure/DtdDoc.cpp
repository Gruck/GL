

#include "DtdDoc.h"
#include "DtdElement.h"
#include "DtdPossibleContent.h"
#include "Tools.h"


void DtdDoc::AddElement(DtdElement *element)
{
	rules.push_back(element);
}

DtdDoc* DtdDoc::CreateDummyDtdForRap1()
{
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
DtdPossibleContent* pc1 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc2 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "titre", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc3 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "auteur", DtdPossibleContent::M_PLUS);
DtdPossibleContent* pc4 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "resume", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc5 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "chapitre", DtdPossibleContent::M_PLUS);
pc1->addChild(pc2);
pc1->addChild(pc3);
pc1->addChild(pc4);
pc1->addChild(pc5);
//DtdElement* el1 = new DtdElement(

DtdPossibleContent* pc11 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc12 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "prenom", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc13 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "nom", DtdPossibleContent::M_NONE);
pc1->addChild(pc2);
pc1->addChild(pc3);
//DtdElement* el1 = new DtdElement(


DtdPossibleContent* pc21 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc22 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "#PCDATA", DtdPossibleContent::M_NONE);
pc12->addChild(pc22);
//DtdElement* el1 = new DtdElement(

DtdPossibleContent* pc31 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc32 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "#PCDATA", DtdPossibleContent::M_NONE);
pc31->addChild(pc32);
//DtdElement* el1 = new DtdElement(

DtdPossibleContent* pc41 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc42 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "#PCDATA", DtdPossibleContent::M_NONE);
pc41->addChild(pc42);
//DtdElement* el1 = new DtdElement(

DtdPossibleContent* pc51 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc52 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "#PCDATA", DtdPossibleContent::M_NONE);
pc51->addChild(pc52);
//DtdElement* el1 = new DtdElement(

DtdPossibleContent* pc61 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc62 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "#PCDATA", DtdPossibleContent::M_NONE);
pc61->addChild(pc62);
//DtdElement* el1 = new DtdElement(

DtdPossibleContent* pc71 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc72 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "titre", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc73 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "p", DtdPossibleContent::M_PLUS);
pc71->addChild(pc72);
pc71->addChild(pc73);
//DtdElement* el1 = new DtdElement(

DtdPossibleContent* pc81 = new DtdPossibleContent(DtdPossibleContent::T_SEQUENCE, "", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc82 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "titre", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc83 = new DtdPossibleContent(DtdPossibleContent::T_CHOICE, "", DtdPossibleContent::M_PLUS);
DtdPossibleContent* pc831 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "p", DtdPossibleContent::M_NONE);
DtdPossibleContent* pc832 = new DtdPossibleContent(DtdPossibleContent::T_ELEM, "section", DtdPossibleContent::M_NONE);
pc83->addChild(pc831);
pc83->addChild(pc832);
pc81->addChild(pc82);
pc81->addChild(pc83);


return Rap1dtd;
}
