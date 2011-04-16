#ifndef HEXALOUTRE_XSLTTRANSFORMER_H
#define HEXALOUTRE_XSLTTRANSFORMER_H

#include "XmlElement.h"
#include "XmlDoc.h"


class XsltTransformer {

public:
	/**
	 * Classe en charge de la transformation
	 * de l'arbre xml en fonction de l'arbre 
	 * xslt fourni precedement
	 */
	
	/**
	 * Constructeur
	 */
	XsltTransformer(const XmlDoc* Xml, const XmlDoc* Xslt) :  _xmlRootNode(Xml->root()), _xsltRootNode(Xslt->root()) {}
	
	/**
	 * Destructeur
	 */
	~XsltTransformer();
	
	/**
	 * Lance le processing;
	 */
	XmlElement* StartProcessing();
	
private:
	/**
	 * Effectue le traitement de l'arbre xml en fonction de l'arbre Xslt
	 */
	void processXslt(XmlElement* ParentNode,XmlElement* NodeInNewTree);
	
	/**
	 * Copie le segment d'arbre T_node dans le nouvel arbre indique par NodeInNewTree
	 * en tenant compte du noeud actuel (C_Node) 
	 */
	void copyTree(XmlElement* T_Node, XmlElement* C_Node,XmlElement* NodeInNewTree);

	/**
	 * Attributs
	 */
	
	/**
	 * Noeud root de la structure a transformer et
	 * de l'arborescence xslt a appliquer
	 */
	XmlElement* _xmlRootNode;
	XmlElement* _xsltRootNode;

};


#endif