
#include "DtdPossibleContent.h"
#include "Tools.h"


void DtdPossibleContent::toStream( std::ostream& stream, int indentation )
{
	//le parcours ici est assez simple
	
	if(this->_type == T_ELEM){//si c'est un element, ne pas le faire précéder
                            //par une parenthese
		stream<<this->_value;
		stream<<ToStr(this->_multiplicity);		
		
	}else{	//si c'est un choix ou une séquence, ajouter une parenthèse
		stream<<"(";
		//afficher le premier fils
		PossibleContentList::iterator  it = this->firstChild();
		(*it)->toStream(stream);
		
		//parcourir le reste et afficher le bon type de séparateur "|" ou ","
		if(_type == T_CHOICE){
			for(it++; it != childrenEnd(); it++)
			{
				stream<<"|";
				(*it)->toStream(stream);
			}	
		}else{
			for(it++; it != childrenEnd(); it++)
			{
				stream<<",";
				(*it)->toStream(stream);
			}	
		}
				
		//ajouter la parenthese fermante
		stream<<")";
		//ajouter la multiplicité
		stream<<ToStr(this->_multiplicity);
		
	}
	
	
}
