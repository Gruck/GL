#include <string>
#include <stdio.h>
#include "XmlDoc.h"
#include "XmlElement.h"
#include "XmlValidator.h"

#include "DtdDoc.h"

#include <iostream>

extern int xmlparse();
extern FILE *xmlin;
extern int dtdparse();
extern FILE *dtdin;

extern std::string DtdUrl;
extern XmlDoc* XmlDataStructure;
extern DtdDoc* DtdDataStructure;

int main(int argc, char **argv)
{
  FILE * fid;
  int err;
  fid = fopen(argv[1], "r");
  if(!argv[1])
  {
	  printf("Erreur d'ouverture du fichier");
	  return 1;
  }

  xmlin = fid;
  err = xmlparse();
  XmlDataStructure->root()->toStream(std::cout);
  if (err != 0) printf("Parse ended with %d error(s)\n", err);
        else  printf("Parse ended with sucess\n");
 fclose(fid);

  printf("Le nombre d'erreurs est %d \n", err);

	printf("%s \n", DtdUrl.c_str());
  fid = fopen(DtdUrl.c_str(), "r");

  dtdin = fid;

  err = dtdparse();
  fclose(fid);

  printf("%i \n", err);

  if (err != 0) printf("Parse ended with %d error(s)\n", err);
        else  printf("Parse ended with sucess\n");
        
  //ici doit être mis l'apel au validateur  
  bool status = XmlValidator::validate( XmlDataStructure, DtdDataStructure); 
  DtdDataStructure->toStream(std::cout);
    
  printf("Coucou j'ai dilété la datastructure.\n");
  delete XmlDataStructure;
  delete DtdDataStructure;
  if(status){
    std::cout<<"reussite de l'analyse"<<std::endl;
    return 0;
  }else{
  std::cout<<"echec de l'analyse"<<std::endl;
  return 1;
  }
} 
