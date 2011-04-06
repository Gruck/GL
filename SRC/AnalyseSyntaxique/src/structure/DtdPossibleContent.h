
#ifndef HEXALOUTRE_DTDPOSSIBLECONTENT_H
#define HEXALOUTRE_DTDPOSSIBLECONTENT_H
#include <string>

#include "Tools.h"




class DtdPossibleContent {
public:
  typedef enum{
    QMARK,
    AST,
    PLUS} Multiplicity;
  typedef enum{
    SEQUENCE,
    CHOICE,
    ELEM} Type;
	
  DtdPossibleContent(){} 
 
private:
	Multiplicity _multiplicity;
	Type _type;
	std::string value;
 
};




#endif
