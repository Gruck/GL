

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
//DtdElement* el1 = new DtdElement(



return Rap1dtd;
}
