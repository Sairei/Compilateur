#include <stdio.h>
#include <stdlib.h>
#include "symboles.h"
#include <string.h>

#define YYLENGTHMAX 100
char yytext[YYLENGTHMAX];
FILE *yyin;
int uniteCourante;


char *getNom();
int est_symbole(char c);
int est_motcle();
char lire_char();
void delire_char();
int est_nombre();
void nom_uniteCourante( int uniteCourante, char *nom, char *valeur );
int placer_curseur();
int yylex();



