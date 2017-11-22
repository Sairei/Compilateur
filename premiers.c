#include"symboles.h"
#include"premiers.h"

void initialise_premiers(void){
  int i,j;

  // Initialiser toutes les cases du tableau à 0
  for(i=0; i <= NB_NON_TERMINAUX; i++)
    for(j=0; j <= NB_TERMINAUX; j++)
      premiers[i][j] = 0;

  premiers[_programme_][EPSILON] = 1;
  premiers[_programme_][ENTIER] = 1;
  premiers[_programme_][ID_FCT] = 1;

  premiers[_optDecVariables_][EPSILON] = 1;
  premiers[_optDecVariables_][ENTIER] = 1;

  premiers[_listeDecVariables_][ENTIER] = 1;

  premiers[_listeDecVariablesBis_][EPSILON] = 1;
  premiers[_listeDecVariablesBis_][VIRGULE] = 1;

  premiers[_declarationVariable_][ENTIER] = 1;

  premiers[_optTailleTableau_][EPSILON] = 1;
  premiers[_optTailleTableau_][CROCHET_OUVRANT] = 1;

  premiers[_listeDecFonctions_][EPSILON] = 1;
  premiers[_listeDecFonctions_][ID_FCT] = 1;

  premiers[_declarationFonction_][ID_FCT] = 1;

  premiers[_listeParam_][PARENTHESE_OUVRANTE] = 1;

  premiers[_optListeDecVariables_][EPSILON] = 1;
  premiers[_optListeDecVariables_][ENTIER] = 1;

  premiers[_instruction_][ACCOLADE_OUVRANTE] = 1;
  premiers[_instruction_][ID_VAR] = 1;
  premiers[_instruction_][ID_FCT] = 1;
  premiers[_instruction_][SI] = 1;
  premiers[_instruction_][TANTQUE] = 1;
  premiers[_instruction_][FAIRE] = 1;
  premiers[_instruction_][RETOUR] = 1;
  premiers[_instruction_][POINT_VIRGULE] = 1;
  premiers[_instruction_][ECRIRE] = 1;

  premiers[_instructionAffect_][ID_VAR] = 1;

  premiers[_instructionBloc_][ACCOLADE_OUVRANTE] = 1;

  premiers[_listeInstructions_][EPSILON] = 1;
  premiers[_listeInstructions_][ACCOLADE_OUVRANTE] = 1;
  premiers[_listeInstructions_][ID_VAR] = 1;
  premiers[_listeInstructions_][ID_FCT] = 1;
  premiers[_listeInstructions_][SI] = 1;
  premiers[_listeInstructions_][TANTQUE] = 1;
  premiers[_listeInstructions_][FAIRE] = 1;
  premiers[_listeInstructions_][RETOUR] = 1;
  premiers[_listeInstructions_][ECRIRE] = 1;
  premiers[_listeInstructions_][POINT_VIRGULE] = 1;

  premiers[_instructionSi_][SI] = 1;

  premiers[_optSinon_][EPSILON] = 1;
  premiers[_optSinon_][SINON] = 1;

  premiers[_instructionTantque_][TANTQUE] = 1;

  premiers[_instructionFaire_][FAIRE] = 1;

  premiers[_instructionAppel_][ID_FCT] = 1;

  premiers[_instructionRetour_][RETOUR] = 1;

  premiers[_instructionEcriture_][ECRIRE] = 1;

  premiers[_instructionVide_][POINT_VIRGULE] = 1;

  premiers[_expression_][NON] = 1;
  premiers[_expression_][PARENTHESE_OUVRANTE] = 1;
  premiers[_expression_][NOMBRE] = 1;
  premiers[_expression_][ID_VAR] = 1;
  premiers[_expression_][ID_FCT] = 1;
  premiers[_expression_][LIRE] = 1;

  premiers[_expressionBis_][EPSILON] = 1;
  premiers[_expressionBis_][OU] = 1;

  premiers[_conjonction_][NON] = 1;
  premiers[_conjonction_][PARENTHESE_OUVRANTE] = 1;
  premiers[_conjonction_][NOMBRE] = 1;
  premiers[_conjonction_][ID_VAR] = 1;
  premiers[_conjonction_][ID_FCT] = 1;
  premiers[_conjonction_][LIRE] = 1;

  premiers[_conjonctionBis_][EPSILON] = 1;
  premiers[_conjonctionBis_][ET] = 1;

  premiers[_comparaison_][NON] = 1;
  premiers[_comparaison_][PARENTHESE_OUVRANTE] = 1;
  premiers[_comparaison_][NOMBRE] = 1;
  premiers[_comparaison_][ID_VAR] = 1;
  premiers[_comparaison_][ID_FCT] = 1;
  premiers[_comparaison_][LIRE] = 1;

  premiers[_comparaisonBis_][EPSILON] = 1;
  premiers[_comparaisonBis_][EGAL] = 1;
  premiers[_comparaisonBis_][INFERIEUR] = 1;
  premiers[_comparaisonBis_][SUPERIEUR] = 1;
  premiers[_comparaisonBis_][INF_EGAL] = 1;
  premiers[_comparaisonBis_][SUP_EGAL] = 1;
  premiers[_comparaisonBis_][DIFF] = 1;

  premiers[_expArith_][NON] = 1;
  premiers[_expArith_][PARENTHESE_OUVRANTE] = 1;
  premiers[_expArith_][NOMBRE] = 1;
  premiers[_expArith_][ID_VAR] = 1;
  premiers[_expArith_][ID_FCT] = 1;
  premiers[_expArith_][LIRE] = 1;

  premiers[_expArithBis_][EPSILON] = 1;
  premiers[_expArithBis_][PLUS] = 1;
  premiers[_expArithBis_][MOINS] = 1;

  premiers[_terme_][NON] = 1;
  premiers[_terme_][PARENTHESE_OUVRANTE] = 1;
  premiers[_terme_][NOMBRE] = 1;
  premiers[_terme_][ID_VAR] = 1;
  premiers[_terme_][ID_FCT] = 1;
  premiers[_terme_][LIRE] = 1;

  premiers[_termeBis_][EPSILON] = 1;
  premiers[_termeBis_][FOIS] = 1;
  premiers[_termeBis_][DIVISE] = 1;
  premiers[_termeBis_][MODULO] = 1;

  premiers[_negation_][NON] = 1;
  premiers[_negation_][PARENTHESE_OUVRANTE] = 1;
  premiers[_negation_][NOMBRE] = 1;
  premiers[_negation_][ID_VAR] = 1;
  premiers[_negation_][ID_FCT] = 1;
  premiers[_negation_][LIRE] = 1;

  premiers[_facteur_][PARENTHESE_OUVRANTE] = 1;
  premiers[_facteur_][NOMBRE] = 1;
  premiers[_facteur_][ID_VAR] = 1;
  premiers[_facteur_][ID_FCT] = 1;
  premiers[_facteur_][LIRE] = 1;

  premiers[_var_][ID_VAR] = 1;

  premiers[_optIndice_][EPSILON] = 1;
  premiers[_optIndice_][CROCHET_OUVRANT] = 1;

  premiers[_appelFct_][ID_FCT] = 1;

  premiers[_listeExpressions_][EPSILON] = 1;
  premiers[_listeExpressions_][NON] = 1;
  premiers[_listeExpressions_][PARENTHESE_OUVRANTE] = 1;
  premiers[_listeExpressions_][NOMBRE] = 1;
  premiers[_listeExpressions_][ID_VAR] = 1;
  premiers[_listeExpressions_][ID_FCT] = 1;
  premiers[_listeExpressions_][LIRE] = 1;

  premiers[_listeExpressionsBis_][EPSILON] = 1;
  premiers[_listeExpressionsBis_][VIRGULE] = 1;
}

int est_premier(int non_terminal, int terminal)
{
  return premiers[non_terminal][terminal];
}
