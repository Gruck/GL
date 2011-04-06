#include <string>
#include <stdio.h>

extern int xmlparse();
extern FILE *xmlin;
extern int dtdparse();
extern FILE *dtdin;

extern std::string DtdUrl;

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
  return 0;
} 
