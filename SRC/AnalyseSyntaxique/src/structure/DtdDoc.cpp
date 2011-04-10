
#include "DtdDoc.h"
#include "Tools.h"


void DtdDoc::AddElement(DtdElement *element)
{
	rules.push_back(element);
}
