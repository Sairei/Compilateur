#include "analyseur_asynt.h"
#include "analyseur_lexical.h"

int main(int argc, char* argv[])
{
	yyin = fopen(argv[1], "r");
	uniteCourante = yylex();
	n_prog *n = programme();
	affiche_n_prog(n);

	return 0;
}
