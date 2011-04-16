XMLPARSERPATH= src/xml 
DTDPARSERPATH= src/dtd
XSLTPARSERPATH= src/xslt
STRUCTPATH= src/structure
SRC= src
OBJ= obj
APP= FullAnalyzer
TRANS= Transformer
CPPFLAGS= -Wall -ansi 
DIRFLAGS= -I$(XMLPARSERPATH) -I$(DTDPARSERPATH) -I$(STRUCTPATH) -I$(XSLTPARSERPATH)
DEPSXML= $(OBJ)/xml/xml.tab.o $(OBJ)/xml/lex.xml.o
DEPSDTD= $(OBJ)/dtd/dtd.tab.o $(OBJ)/dtd/lex.dtd.o
DEPSAPP= $(OBJ)/main.o
DEPSSTRXML= $(OBJ)/structure/XmlContent.o $(OBJ)/structure/XmlDoc.o $(OBJ)/structure/XmlElement.o $(OBJ)/structure/XmlText.o $(OBJ)/structure/XmlValidatorVisitor.o $(OBJ)/structure/XmlValidator.o 
DEPSSTRDTD= $(OBJ)/structure/DtdDoc.o $(OBJ)/structure/DtdElement.o $(OBJ)/structure/DtdPossibleContent.o
DEPSXSLT = $(OBJ)/xslt/main.o $(OBJ)/xslt/XsltTransformer.o $(OBJ)/xslt/xslt.tab.o $(OBJ)/xslt/lex.xslt.o
STRH= $(SRC)/structure/*.h
MKDIR= MKDIR 

all : $(MKDIR) $(APP) $(TRANS)

# Edition des liens, rajouter ici dans la listes de dépendances les ".o"
# constitués lors de la compilation.

$(MKDIR) :
	@mkdir -p obj $(OBJ)/xml $(OBJ)/dtd $(OBJ)/structure $(OBJ)/xslt

$(APP) : $(DEPSXML) $(DEPSDTD) $(DEPSAPP) $(DEPSSTRXML) $(DEPSSTRDTD)
	@echo "Edition des liens pour l'application princpale"
	g++ $(CPPFLAGS) $+ -o $@
	
$(TRANS) : $(DEPSXML) $(DEPSSTRXML) $(DEPSXSLT) $(DEPSSTRDTD)
	@echo "Edition des liens pour l'application de transformation xslt"
	g++ $(CPPFLAGS) $+ -o $@

# Compilation des fichiers .cpp situés a la racine du répertoire src
	@echo "Compilation de $< "
	g++ $(CPPFLAGS) $(DIRFLAGS) -c $< -o $@

# Compilation des fichiers .cpp situés a la racine du répertoire src
$(OBJ)/structure/%.o : $(SRC)/structure/%.cpp $(STRH)
	@echo "Compilation de $< "
	g++ $(CPPFLAGS) $(DIRFLAGS) -c $< -o $@

#Parser XML 
#Compilation des fichiers ".c" génrés dans le répertoire /src/xml placés dans le répertoire /obj du projet
$(OBJ)/xml/%.o : $(SRC)/xml/%.c
	@echo "Compilation de $< "
	g++ $(CPPFLAGS) $(DIRFLAGS) -c $< -o $@	

#Generation des fichiers .c par flex et bison pour le parser XML
$(SRC)/xml/lex.xml.c : $(SRC)/xml/xml.l
	@echo "Création du parser de grammaire XML"
	flex -Pxml -o$(SRC)/xml/lex.xml.c $(SRC)/xml/xml.l

$(SRC)/xml/xml.tab.c : $(SRC)/xml/xml.y  $(SRC)/xml/lex.xml.c $(SRC)/xml/commun.h
	@echo "Création de la table de 'état XML"
	bison -p xml --debug --verbose --defines=$(SRC)/xml/xml.tab.h -o $(SRC)/xml/xml.tab.c $(SRC)/xml/xml.y 

#Parser XSLT
#Chaine de compilation identique au parser XML 

#Compilation des fichiers ".c" génrés dans le répertoire /src/xslt placés dans le répertoire /obj du projet

$(OBJ)/xslt/%.o : $(SRC)/xslt/%.cpp
	@echo "Compilation de $< "
	g++ $(CPPFLAGS) $(DIRFLAGS) -c $< -o $@	

$(OBJ)/xslt/%.o : $(SRC)/xslt/%.c
	@echo "Compilation de $< "
	g++ $(CPPFLAGS) $(DIRFLAGS) -c $< -o $@	

#Generation des fichiers .c par flex et bison pour le parser XSLT
$(SRC)/xslt/lex.xslt.c : $(SRC)/xslt/xslt.l
	@echo "Création du parser de grammaire XSLT"
	flex -Pxslt -o$(SRC)/xslt/lex.xslt.c $(SRC)/xslt/xslt.l

$(SRC)/xslt/xslt.tab.c : $(SRC)/xslt/xslt.y  $(SRC)/xslt/lex.xslt.c $(SRC)/xml/commun.h
	@echo "Création de la table de 'état XSLT"
	bison -p xslt --debug --verbose --defines=$(SRC)/xslt/xslt.tab.h -o $(SRC)/xslt/xslt.tab.c $(SRC)/xslt/xslt.y 

#Parser DTD
#Chaine de compilation identique au parser XML
$(OBJ)/dtd/%.o : $(SRC)/dtd/%.c
	@echo "Compilation de $< "
	g++ $(CPPFLAGS) $(DIRFLAGS) -c $< -o $@	

$(SRC)/dtd/lex.dtd.c : $(SRC)/dtd/dtd.l
	@echo "Création du parser de grammaire DTD"
	flex -Pdtd -o$(SRC)/dtd/lex.dtd.c $(SRC)/dtd/dtd.l

$(SRC)/dtd/dtd.tab.c : $(SRC)/dtd/dtd.y  $(SRC)/dtd/lex.dtd.c $(SRC)/xml/commun.h
	@echo "Création de la table de 'état DTD"
	bison -p dtd --debug --verbose --defines=$(SRC)/dtd/dtd.tab.h -o $(SRC)/dtd/dtd.tab.c $(SRC)/dtd/dtd.y 





# Regles de nettoyage  
clean: 
	rm -f $(SRC)/xml/*.c
	rm -f $(SRC)/xml/*.output
	rm -f $(SRC)/xml/xml.tab.h
	rm -f $(SRC)/xslt/*.c
	rm -f $(SRC)/xslt/*.output
	rm -f $(SRC)/xslt/xslt.tab.h
	rm -f $(SRC)/dtd/*.c
	rm -f $(SRC)/dtd/*.output
	rm -f $(SRC)/dtd/dtd.tab.h
	
	rm -f $(OBJ)/xml/*.o $(OBJ)/dtd/*.o $(OBJ)/structure/*.o $(OBJ)/xslt/*.o

	rm -f ./$(APP)
