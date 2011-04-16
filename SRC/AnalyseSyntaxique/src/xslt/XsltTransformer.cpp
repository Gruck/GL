#include <list>
#include <string>

#include "XsltTransformer.h"
#include "XmlText.h"
const std::string TEMPLATE = "template";




XmlElement* XsltTransformer::StartProcessing()
{
	XmlElement* outputRootNode = new XmlElement("","output");
	this->processXslt(_xmlRootNode,outputRootNode);
	return outputRootNode;
}


void XsltTransformer::processXslt(XmlElement* ParentNode, XmlElement* NodeInNewTree)
{
	XmlElement::ContentListIterator childIterator = ParentNode->firstChild();
	if(ParentNode->nbChildren() !=0)
	// Test pour verifier que nous somme sur un noeud, et non une feuille
	{
		XmlElement::ContentListIterator childIterator = ParentNode->firstChild();
		for (; childIterator != ParentNode->childrenEnd(); childIterator++)
		// Pour tout les fils du noeud courant
		{
			if((*childIterator)->name() == std::string("#CDATA"))
			// Ce test permet d'effectuer une differenciation entre 
			// XmlText et XmlElement, en effet XmlText::name() retourne
			// systematiquement #CDATA, ainsi le cast est autorisé
			// Cas XmlText : On recopie le noeud dans le nouvel arbre
			{
				XmlText* C_node = (XmlText*) (*childIterator);
				XmlText* newNode = new XmlText(C_node->text());
				NodeInNewTree->addChild(newNode);
			}
			else
			// Cas XmlElement : Recherche de template pour le fils pointé
			// Les templates sont obligatoirement de type XmlElement
			{
				XmlElement* T_Element = _xsltRootNode->childElement(TEMPLATE,(*childIterator)->name());
				if(T_Element != 0)
				// Si il existe un template pour le noeud
				{
					this->copyTree(T_Element,(XmlElement*)*(childIterator),NodeInNewTree);
					// Cast autorisé en XmlElement*
					// et safe, car nous sommes sur qu'il s'agit d'un XmlElement
				}
			}
		}
	}
	else 
	// Cas ou nous travaillons sur une feuille : Recherche de template 
	// A appliquer, similaire au cas d'un fils
	{
		// TODO être sur de ce qui viens d'etre dit, ce cas est peutêtre a négliger, car il aura fait 
		// la cible du même traitement au niveau n+1
	}

}

void XsltTransformer::copyTree(XmlElement* T_Node, 
					XmlElement* C_Node,XmlElement* NodeInNewTree)
{
	if (T_Node->name() == std::string("apply-templates")) 
	// Si nous sommes dans le cas "apply-template" , alors nous appelons 
    // recursivement la methode process Xslt, sur tout les fils du noeud
	// ciblé par apply template, comme stipulé dans le sujet
	{
		// TODO possible erreur ici, par tout ses fils il entend tout les fils du 
		// noeud courant, ou tout les fils du noeud cilbé par l'attribut spécifié
		this->processXslt(C_Node, NodeInNewTree);
	}
	else 
	//cas du neoud normal
	{
		if(T_Node->name() == std::string("#CDATA"))
		{
			// Si le noeud template est de type text, alors on ajoute
			// le noeud dans l'architecture du nouveau 
			XmlText* newNode = new XmlText(T_Node->name());
			NodeInNewTree->addChild(newNode);
		}
		else
		// Sinon nous sommes dans le cas d'un noeud de type 
		// XmlElement, qui devra etre traite recursivement
		{
			// On applique le noeud actuel
			XmlElement* Node = (XmlElement*)(T_Node);
			XmlElement* child = new XmlElement(Node->nameSpace(), Node->name());
			NodeInNewTree->addChild(child);
			// et on regarde pour traiter recursivement ses fils
			if(T_Node->nbChildren() != 0)
			{
				XmlElement::ContentListIterator childIterator = T_Node->firstChild();
				for(; childIterator != T_Node->childrenEnd() ; childIterator++)
				{
					if((*childIterator)->name() == std::string("#CDATA"))
					{
						
					}
					else
					{
						this->copyTree((XmlElement*)(*childIterator), C_Node, child);
					}
				}
			}
		}
	}
}