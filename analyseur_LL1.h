#ifndef ANALYSEUR_LL1_H_INCLUDED
#define ANALYSEUR_LL1_H_INCLUDED

#include "analyseur_lexical.h"
#include "symboles.h"
#include "util.h"
#include "premiers.h"
#include "suivants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void programme();
void optDecVariables();
void listeDecVariables();
void listeDecVariablesBis();
void declarationVariable();
void optTailleTableau();
void listeDecFonctions();
void declarationFonction();
void listeParam();
void optListeDecVariables();
void instruction();
void instructionAffect();
void instructionBloc();
void listeInstructions();
void instructionSi();
void optSinon();
void instructionTantque();
void instructionFaire();
void instructionAppel();
void instructionRetour();
void instructionEcrire();
void instructionVide();
void expression();
void expressionBis();
void conjonction();
void conjonctionBis();
void comparaison();
void comparaisonBis();
void expArith();
void expArithBis();
void terme();
void termeBis();
void negation();
void facteur();
void var();
void optIndice();
void appelFct();
void listeExpressions();
void listeExpressionsBis();


#endif // ANALYSEUR_LL1_H_INCLUDED
