CC = gcc

LIBS = -lm 
CCFLAGS = -Wall -ggdb -std=c99

#OBJ pour .lex
OBJlex = analyseur_lexical.o 
#OBJ pour .synt
OBJll = analyseur_LL1.o analyseur_lexical.o premiers.o suivants.o util.o
#OBJ pour .asynt
OBJabst = analyseur_lexical.o analyseur_asynt.o premiers.o suivants.o util.o syntabs.o affiche_arbre_abstrait.o
#OBJ pour .tab
OBJtab = tab.o analyseur_lexical.o analyseur_asynt.o premiers.o suivants.o util.o syntabs.o affiche_arbre_abstrait.o tabsymboles.o
OBJgen = generateur.o analyseur_lexical.o analyseur_asynt.o premiers.o suivants.o util.o syntabs.o affiche_arbre_abstrait.o tabsymboles.o


all: test_yylex test_synt test_asynt test_tab test_gen


test_yylex: test_yylex.c $(OBJlex)
	$(CC) $(CCFLAGS) -o test_yylex test_yylex.c $(OBJlex)

analyseur_lexical.o: analyseur_lexical.c
	$(CC) $(CCFLAGS) -c $^

test_synt: test_synt.c $(OBJll)
	$(CC) $(CCFLAGS) -o test_synt test_synt.c $(OBJll)
	
analyseur_LL1.o: analyseur_LL1.c analyseur_lexical.h analyseur_lexical.o util.o premiers.o suivants.o
	$(CC) $(CCFLAGS) -c analyseur_LL1.c
	
premiers.o: premiers.c
	$(CC) $(CCFLAGS) -c premiers.c

suivants.o: suivants.c
	$(CC) $(CCFLAGS) -c suivants.c
	
test_asynt : test_asynt.c $(OBJabst)
	$(CC) $(CCFLAGS) -o test_asynt test_asynt.c $(OBJabst)
	
analyseur_asynt.o: analyseur_asynt.c analyseur_lexical.h analyseur_lexical.o util.o premiers.o suivants.o syntabs.o affiche_arbre_abstrait.o
	$(CC) $(CCFLAGS) -c analyseur_asynt.c

syntabs.o : syntabs.c
	$(CC) $(CCFLAGS) -c syntabs.c

affiche_arbre_abstrait.o : affiche_arbre_abstrait.c
	$(CC) $(CCFLAGS) -c affiche_arbre_abstrait.c

test_tab : test_tab.c $(OBJtab)
	$(CC) $(CCFLAGS) -o test_tab test_tab.c $(OBJtab)

tab.o : tab.c tab.h analyseur_asynt.o analyseur_lexical.o util.o premiers.o suivants.o tabsymboles.o
	$(CC) $(CCFLAGS) -c tab.c

tabsymboles.o: tabsymboles.c
	$(CC) $(CCFLAGS) -c tabsymboles.c
    
test_gen : test_gen.c $(OBJgen)
	$(CC) $(CCFLAGS) -o test_gen test_gen.c $(OBJgen)
    
generateur.o : generateur.c generateur.h analyseur_asynt.o analyseur_lexical.o util.o premiers.o suivants.o tabsymboles.o
	$(CC) $(CCFLAGS) -c generateur.c
	


.PHONY : clean

clean:
	- rm -f $(OBJlex)
	- rm -f $(OBJll)
	- rm -f $(OBJabst)
	- rm -f $(OBJtab)
	- rm -f $(OBJgen)
	- rm -f test_yylex
	- rm -f test_synt
	- rm -f test_asynt
	- rm -f test_tab
	- rm -f test_gen
