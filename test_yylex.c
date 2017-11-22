#include "analyseur_lexical.h"

int uniteCourante;
FILE *yyin;

int main(int argc, char* argv[])
{	
	int uniteCourante;
	char nom[100];
	char valeur[100];
	yyin = fopen(argv[1], "r");

	do {
	uniteCourante = yylex();
	nom_uniteCourante( uniteCourante, nom, valeur );
	printf("%s \t %s \t %s \n", yytext, nom, valeur);
	} while (uniteCourante != FIN);  

	return 0;	
}
