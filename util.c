#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-------------------------------------------------------------------------*/

int nb_ligne;
int indent_xml = 0;
int indent_step = 1; // set to 0 for no indentation

/*-------------------------------------------------------------------------*/
/* Affiche le message d'alerte donné en paramètre, avec le numéro de ligne */
/*-------------------------------------------------------------------------*/
void warning(char *message) {
  fprintf (stderr, "WARNING ligne %d : ", nb_ligne);
  fprintf (stderr, "%s\n", message);
}

/*-------------------------------------------------------------------------*/
/* Affiche le message d'erreur donné en paramètre, avec le numéro de ligne */
/*-------------------------------------------------------------------------*/
void erreur(char *message) {
  fprintf (stderr, "ERREUR ligne %d : ", nb_ligne);
  fprintf (stderr, "%s\n", message);
  exit(1);
}

/*-------------------------------------------------------------------------
 * Affiche le message d'alerte donné en paramètre, avec le numéro de ligne.
 * Le message d'alerte peut contenir un %s variable, qui sera donné en
 * argument s
 -------------------------------------------------------------------------*/
void warning_1s(char *message, char *s) {
  fprintf (stderr, "WARNING ligne %d : ", nb_ligne);
  fprintf( stderr, message, s );
  fprintf( stderr, "\n" );
}

/*-------------------------------------------------------------------------
 * Affiche le message d'erreur donné en paramètre, avec le numéro de ligne.
 * Le message d'erreur peut contenir un %s variable, qui sera donné en
 * argument s
 -------------------------------------------------------------------------*/
void erreur_1s(char *message, char *s) {
  fprintf( stderr, "Ligne %d : ", nb_ligne );
  fprintf( stderr, message, s );
  fprintf( stderr, "\n" );
  exit(1);
}

/*-------------------------------------------------------------------------*/

char *duplique_chaine(char *src) {
  char *dest = malloc(sizeof(char) * strlen(src));
  strcpy(dest, src);
  return dest;
}

/*-------------------------------------------------------------------------*/
void indent() {
    int i;
    for( i = 0; i < indent_xml; i++ ) {
      printf( "  " );
    }
}
/*-------------------------------------------------------------------------*/
void affiche_balise_ouvrante(const char *fct_, int trace_xml) {
  if( trace_xml ) {
    indent();
    indent_xml += indent_step ;
	  fprintf (stdout, "<%s>\n", fct_);
	}
}

/*-------------------------------------------------------------------------*/

void affiche_balise_fermante(const char *fct_, int trace_xml) {
  if(trace_xml) {
    indent_xml -= indent_step ;
    indent();
    fprintf (stdout, "</%s>\n", fct_);
  }
}

/*-------------------------------------------------------------------------*/

void affiche_texte(char *texte_, int trace_xml) {
  if(trace_xml) {
    indent();
    fprintf (stdout, "%s\n", texte_);
  }
}

/*-------------------------------------------------------------------------*/

void affiche_xml_texte( char *texte_ ) {
  int i = 0;
  while( texte_[ i ] != '\0' ) {
    if( texte_[ i ] == '<' ) {
      fprintf( stdout, "&lt;" );
    }
    else if( texte_[ i ] == '>' ) {
      fprintf( stdout, "&gt;" );
    }
    else if( texte_[ i ] == '&' ) {
      fprintf( stdout, "&amp;" );
    }
    else {
      putchar( texte_[i] );
    }
    i++;
  }
}

/*-------------------------------------------------------------------------*/

void affiche_element(char *fct_, char *texte_, int trace_xml) {
  if(trace_xml) {
    indent();
    fprintf (stdout, "<%s>", fct_ );
    affiche_xml_texte( texte_ );
    fprintf (stdout, "</%s>\n", fct_ );
  }
}
