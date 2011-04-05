XMLPARSERPATH= src/xml 
DTDPARSERPATH= src/dtd
SRC= src
OBJ= obj
APP= FullAnalyzer
CPPFLAGS= -Wall -ansi 
DIRFLAGS= -I$(XMLPARSERPATH) -I$(DTDPARSERPATH)
DEPSXML= $(OBJ)/xml/xml.tab.o $(OBJ)/xml/lex.xml.o
DEPSDTD= $(OBJ)/dtd/dtd.tab.o $(OBJ)/dtd/lex.dtd.o
DEPSAPP= $(OBJ)/main.o

all : $(APP)

# Edition des liens, rajouter ici dans la listes de dépendances les ".o"
# constitués lors de la compilation.
$(APP) : $(DEPSXML) $(DEPSDTD) $(DEPSAPP)
	@echo "Edition des liens"
	g++ $(CPPFLAGS) $+ -o $@
	
# Compilation des fichiers .cpp situés a la racine du répertoire src
$(OBJ)/%.o : $(SRC)/%.cpp
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
	flex -P xml -o $(SRC)/xml/lex.xml.c $(SRC)/xml/xml.l

$(SRC)/xml/xml.tab.c : $(SRC)/xml/xml.y  $(SRC)/xml/lex.xml.c $(SRC)/xml/commun.h
	@echo "Création de la table de 'état XML"
	bison -p xml --debug --verbose --defines=$(SRC)/xml/xml.tab.h -o $(SRC)/xml/xml.tab.c $(SRC)/xml/xml.y 


#Parser DTD
#Chaine de compilation identique au parser XML
$(OBJ)/dtd/%.o : $(SRC)/dtd/%.c
	@echo "Compilation de $< "
	g++ $(CPPFLAGS) $(DIRFLAGS) -c $< -o $@	

$(SRC)/dtd/lex.dtd.c : $(SRC)/dtd/dtd.l
	@echo "Création du parser de grammaire DTD"
	flex -P dtd -o $(SRC)/dtd/lex.dtd.c $(SRC)/dtd/dtd.l

$(SRC)/dtd/dtd.tab.c : $(SRC)/dtd/dtd.y  $(SRC)/dtd/lex.dtd.c $(SRC)/xml/commun.h
	@echo "Création de la table de 'état DTD"
	bison -p dtd --debug --verbose --defines=$(SRC)/dtd/dtd.tab.h -o $(SRC)/dtd/dtd.tab.c $(SRC)/dtd/dtd.y 





# Regles de nettoyage  
clean: 
	rm $(SRC)/xml/*.c
	rm $(SRC)/xml/*.output
	rm $(SRC)/xml/xml.tab.h
	rm $(SRC)/dtd/*.c
	rm $(SRC)/dtd/*.output
	rm $(SRC)/dtd/dtd.tab.h
	
	rm $(OBJ)/xml/*.o
	rm $(OBJ)/dtd/*.o
	rm $(OBJ)/*.o

	rm ./$(APP)
