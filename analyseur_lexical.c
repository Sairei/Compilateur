#include "analyseur_lexical.h"


extern FILE *yyin;
int yylength;
int uniteCourante;

char *tableMotsClefs[] = {
  "si", "alors", "sinon", "tantque", "faire", "entier", "retour", "lire",
  "ecrire"
};

int codeMotClefs[] = {
  SI, ALORS, SINON, TANTQUE, FAIRE, ENTIER, RETOUR, LIRE, ECRIRE
};

int motClefLength = 9;


char *getNom()
{
    return yytext;
}

//Renvoie l'unité du symbole.
int est_symbole(char c){
	switch(c){
		case '+' : 	return PLUS;
		case '-' :	return MOINS;
		case '*' : 	return FOIS;
		case '/' : 	return DIVISE;
		case '(' : 	return PARENTHESE_OUVRANTE;
		case ')' : 	return PARENTHESE_FERMANTE;
		case '[' : 	return CROCHET_OUVRANT;
		case ']' : 	return CROCHET_FERMANT;
		case '{' : 	return ACCOLADE_OUVRANTE;
		case '}' : 	return ACCOLADE_FERMANTE;
		case '%' : 	return MODULO;
		//case '^' : 	return 321;
		case '&' : 	return ET;
		case '|' : 	return OU;
		case '!' : 	return NON;
		case '=' :	return EGAL;
		case '<' :	return INFERIEUR;
		case '>' :	return SUPERIEUR;
		case ',' :	return VIRGULE;
		case ';' :	return POINT_VIRGULE;
		default	 :	return -1;
	}

}

//Renvoie l'unité du mot clé.
int est_motcle()
{
    if (strncmp(yytext,"sinon", 5) == 0) 		return SINON;
	if (strncmp(yytext,"si", 2) == 0)			return SI;
	if (strncmp(yytext,"alors", 5) == 0) 		return ALORS;
	if (strncmp(yytext,"tantque", 7) == 0) 		return TANTQUE;
	if (strncmp(yytext,"faire", 5) == 0) 		return FAIRE;
	if (strncmp(yytext,"entier", 6) == 0) 		return ENTIER;
	if (strncmp(yytext,"retour", 6) == 0)		return RETOUR;
	if (strncmp(yytext,"lire", 4) == 0)			return LIRE;
	if (strncmp(yytext,"ecrire", 6) == 0) 		return ECRIRE;
	return -1;

}



//Lis le prochain caractère dans yyin.
char lire_char(){

	yytext[yylength++] = fgetc(yyin);
	yytext[yylength] = '\0';
	return yytext[yylength-1];

}

void delire_char()
{
  char c;
  c = yytext[yylength - 1];
  yytext[--yylength] = '\0';
  ungetc(c, yyin);
}

int est_nombre(){
int i;

	for(i = 0; i < yylength-1; i++){
		if (!(yytext[i] < 58 && yytext[i] > 47)) return -1;
	}
	return NOMBRE;

}


void nom_uniteCourante(int uniteCourante, char *nom, char *valeur ) {
  int i;

	strcpy( nom, "symbole" );
	if(uniteCourante == POINT_VIRGULE) strcpy( valeur, "POINT_VIRGULE");
	else if(uniteCourante == PLUS) strcpy(valeur, "PLUS");
	else if(uniteCourante == MOINS) strcpy(valeur, "MOINS");
	else if(uniteCourante == FOIS) strcpy(valeur, "FOIS");
	else if(uniteCourante == DIVISE) strcpy(valeur, "DIVISE");
	else if(uniteCourante == MODULO) strcpy(valeur, "MODULO");
	else if(uniteCourante == PARENTHESE_OUVRANTE) strcpy(valeur, "PARENTHESE_OUVRANTE");
	else if(uniteCourante == PARENTHESE_FERMANTE) strcpy(valeur, "PARENTHESE_FERMANTE");
	else if(uniteCourante == CROCHET_OUVRANT) strcpy(valeur, "CROCHET_OUVRANT");
	else if(uniteCourante == CROCHET_FERMANT) strcpy(valeur, "CROCHET_FERMANT");
	else if(uniteCourante == ACCOLADE_OUVRANTE) strcpy(valeur, "ACCOLADE_OUVRANTE");
	else if(uniteCourante == ACCOLADE_FERMANTE) strcpy(valeur, "ACCOLADE_FERMANTE");
	else if(uniteCourante == EGAL) strcpy(valeur, "EGAL");
	else if(uniteCourante == DIFF) strcpy(valeur, "DIFFERENT");
	else if(uniteCourante == INFERIEUR) strcpy(valeur, "INFERIEUR");
	else if(uniteCourante == SUPERIEUR) strcpy(valeur, "SUPERIEUR");
	else if(uniteCourante == INF_EGAL) strcpy(valeur, "INFERIEUR OU EGAL");
	else if(uniteCourante == SUP_EGAL) strcpy(valeur, "SUPERIEUR OU EGAL");
	else if(uniteCourante == ET) strcpy(valeur, "ET");
	else if(uniteCourante == OU) strcpy(valeur, "OU");
	else if(uniteCourante == NON) strcpy(valeur, "NON");
	else if(uniteCourante == FIN) strcpy(valeur, "FIN");
	else if(uniteCourante == VIRGULE) strcpy(valeur, "VIRGULE");

	else if( uniteCourante == ID_VAR ) {
	    strcpy( nom, "id_variable" );
	    strcpy( valeur, yytext );
	}
	else if( uniteCourante == ID_FCT ) {
	    strcpy( nom, "id_fonction" );
	    strcpy( valeur, yytext );
	}
	else if( uniteCourante == NOMBRE ) {
	    strcpy( nom, "nombre" );
	    strcpy( valeur, yytext );
	}
	else {
	    strcpy( nom, "mot_clef" );
	    for(i=0; i < motClefLength; i++){
	      if( uniteCourante ==  codeMotClefs[i] ){
		strcpy( valeur, tableMotsClefs[i] );
		break;
	      }
	    }
	}
}

//Place le curseur en ignorant tout les blancs/tabulations/retour à la ligne/commentaires. Retourne -1 si EOF, 0 sinon.
int placer_curseur()
{
  char c = fgetc(yyin);
  int comment = 0;
  while( comment || (c == ' ') || (c == '\n') || (c == '\t') || (c == '#' ) ) {
    if( c == '#' ) {
        comment = 1;
    }
    if( c == '\n' ) {
      comment = 0;
    }
    c = fgetc(yyin);
  }
  if ( feof(yyin) ) {
    return -1;
  }
  ungetc(c, yyin);
  return 0;

}

void vider_yytext(){

	yylength = 0;
	yytext[yylength] = '\0';

}


//Renvoie le code de l'unité lexicale dont c'est le tour.
int yylex(){

	vider_yytext();
	char c; 	//caractère courant
	int a = 1; 	//condition d'arrêt
	int s, s2;	//id du/des symbole(s)
	int m;		//id du mot clé

	//Passer les blancs/commentaires :
	if (placer_curseur() != 0)
        return FIN; //retourner EOF

	while(a)
    {
		//lecture de l'unité lexical :
		c = lire_char();

		//Le mot est un symbole simple
		if ((s = est_symbole(c)) > 0 && yylength == 1)
        {
            if(!(s == NON || s == INFERIEUR || s == SUPERIEUR))
            {
                return s;
            }
            else
            {
                c = lire_char();
                if((s2 = est_symbole(c)) == EGAL)
                {
                    if(s == NON)
                        return DIFF;
                    if(s == INFERIEUR)
                        return INF_EGAL;
                    if(s == SUPERIEUR)
                        return SUP_EGAL;
                }
                else
                {
                    delire_char();
                    return s;
                }
            }
		}

		//Fin de mot
		else if ((s > 0) || c == ' ' || c == '\t' || c == '\n' || c == '#') {

			//renvoie d'un mot clé :
			if ((m = est_motcle()) > 0) {
				delire_char();
				return m;
			}
			//renvoie d'un nombre
			if ((m = est_nombre()) > 0){
				delire_char();
				return NOMBRE;
			}
			//renvoie d'un nom de variable :
			if (yytext[0] == '$'){
				delire_char();
				return ID_VAR;
			}
			//renvoie d'un nom de fonction :
			else {
				delire_char();
				return ID_FCT;
			}

		}



	}
	return -1; //Problème
}
