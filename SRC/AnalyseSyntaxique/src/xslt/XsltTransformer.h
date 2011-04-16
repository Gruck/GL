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
	 * Effectue le traitement de l'arbre xml en fonction de l'arbre Xslt
	 */
	void ProcessXslt(XmlElement* ParentNode,XmlElement* NodeInNewTree);
	
	/**
	 *
	 */
	void CopyTree(const XmlElement* T_Node, const XmlContent* C_Node,XmlElement* NodeInNewTree);
/**
 * Attributs
 */

private:
/**
 * Noeud root de la structure a transformer et
 * de l'arborescence xslt a appliquer
 */
 XmlElement* _xmlRootNode;
 XmlElement* _xsltRootNode;

};


#endif