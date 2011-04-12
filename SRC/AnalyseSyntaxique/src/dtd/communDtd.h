#ifndef HEXALOUTRE_COMMUNDTD_H
#define HEXALOUTRE_COMMUNDTD_H

#include  <string>

#include "DtdPossibleContent.h"


typedef std::list<DtdPossibleContent*> ListContent;
typedef std::pair<std::string,std::string> DtdAttribute;
typedef std::list<DtdAttribute*> ListAttributes;

typedef struct{
            ListAttributes attributes; 
            std::string element;
        }S_Attribute;       
typedef std::list<S_Attribute*> ListAttributesPerElement;


#endif
