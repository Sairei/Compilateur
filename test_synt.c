#include "analyseur_LL1.h"
#include "analyseur_lexical.h"

int uniteCourante;
FILE *yyin;


int main(int argc, char* argv[])
{
	yyin = fopen(argv[1], "r");
	uniteCourante = yylex();
	programme();
	
	return 0;
}
