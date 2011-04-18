using namespace std;

#include <string>
#include <stdio.h>
#include "XmlDoc.h"
#include "XmlElement.h"

#include "XsltTransformer.h"

#include <iostream>

extern int xmlparse();
extern FILE *xmlin;
extern int xsltparse();
extern FILE *xsltin;

extern XmlDoc* XmlDataStructure;
extern XmlDoc* XsltDataStructure;

int main(int argc, char **argv)
{
	FILE * fid;
	int err;
	fid = fopen(argv[1], "r");
	if(!argv[1])
	{
		cout << "Erreur d'ouverture du fichier" << endl;
		return 1;
	}
	xmlin = fid;
	err = xmlparse();
	cout << endl;
	cout << "===== Parse du fichier XML ====="  << endl;
	cout << endl;
	XmlDataStructure->root()->toStream(std::cout);
	if (err != 0) cout << "Parse ended with error" << err << endl;
	else  cout << "Parse ended with sucess" << endl;
	fclose(fid);
	
	cout << "Le nombre d'erreurs est "<< err << endl;
	cout << endl;
	cout << "===== Parse du fichier Xslt ====="  << endl;
	cout << endl;
	
	fid = fopen(argv[2], "r");
	
	xsltin = fid;
	
	err = xsltparse();
	fclose(fid);
	
	if (err != 0) cout << "Parse ended with error" << err << endl;
	else  cout << "Parse ended with sucess" << endl;
	XsltDataStructure->toStream(std::cout);
	
	cout << endl;
	cout << "===== Les deux structures ont été crées ====="  << endl;
	cout << "===== Résultat de la transformation ====="  << endl;
	cout << endl;
	
	XmlDoc* XsltResultTree = new XmlDoc("toto");
	XsltTransformer* Transformerz = new XsltTransformer(XmlDataStructure,XsltDataStructure);
	XmlElement* resultRootNode = Transformerz->StartProcessing();
	XsltResultTree->setRoot(resultRootNode);
	
	resultRootNode->toStream(std::cout);

	delete XsltResultTree;
	delete XmlDataStructure;
}