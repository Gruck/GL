#include <list>
#include <string>

#include "XsltTransformer.h"
#include "XmlText.h"
const std::string TEMPLATE = "template";
const std::string MATCH = "match";




XmlElement* XsltTransformer::StartProcessing()
{
	XmlElement* outputRootNode = new XmlElement("","output");
	// Entourloupe : Nous sommes obligé d'encapsuler le noeud racine 
	// dans un nouveau noeud temporaire de façon à pouvoir appliquer
	// un traitement sur ce dernier si il y en à un
	XmlElement* Entourloupe = new XmlElement("","Entourloupe");
	Entourloupe->addChild(_xmlRootNode);
	this->processXslt(Entourloupe,outputRootNode);
	Entourloupe->detachChild(_xmlRootNode);
	delete Entourloupe;
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
			std::cout << (*childIterator)->name() << std::endl;
			if((*childIterator)->name() == std::string("#PCDATA"))
			// Ce test permet d'effectuer une differenciation entre 
			// XmlText et XmlElement, en effet XmlText::name() retourne
			// systematiquement #PCDATA, ainsi le cast est autorisé
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
				XmlElement* T_Element = _xsltRootNode->childElement(TEMPLATE, MATCH, (*childIterator)->name());
				if(T_Element != 0)
				// Si il existe un template pour le noeud
				{
					for ( XmlElement::ContentListIterator it = T_Element->firstChild() ; it != T_Element->childrenEnd() ; it++ )
					// Nous traitons tout les fils du noeud template
					{
						if ( (*it)->name() == std::string("#PCDATA") )
						// Si le noeud est un XmlText (par la même magouille que précedemment)
						//  on ajoute le noeud dans l'arbre xslt crée
						{
							NodeInNewTree->addChild(new XmlText(((XmlText*)(*it))->text()));
						}
						else
						// Sinon on appelle récursivement la methode copyTree sur le noeud de type XmlElement
						{
							this->copyTree((XmlElement*)(*it),(XmlElement*)(*childIterator),NodeInNewTree);
					    }
					}
				}
			}
		}
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
		this->processXslt(C_Node, NodeInNewTree);
	}
	else 
	//Cas du noeud normal
	{
		if(T_Node->name() == std::string("#PCDATA"))
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
				// Pour tout les noeuds du du Template
				{
					if((*childIterator)->name() == std::string("#PCDATA"))
					// Cas si le fils est un XmlText
					{
						child->addChild(new XmlText(((XmlText*)(*childIterator))->text()));
					}
					else
					// Cas si il s'agit d'un xmlElement
					{
						this->copyTree((XmlElement*)(*childIterator), C_Node, child);
					}
				}
			}
		}
	}
}