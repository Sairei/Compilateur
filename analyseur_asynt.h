#ifndef ANALYSEUR_ASYNT_H_INCLUDED
#define ANALYSEUR_ASYNT_H_INCLUDED

#include "analyseur_lexical.h"
#include "symboles.h"
#include "util.h"
#include "premiers.h"
#include "suivants.h"
#include "syntabs.h"
#include "affiche_arbre_abstrait.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


n_prog *programme();
n_l_dec *optDecVariables();
n_l_dec *listeDecVariables();
n_l_dec *listeDecVariablesBis();
n_dec *declarationVariable();
n_dec *optTailleTableau();
n_l_dec *listeDecFonctions();
n_dec *declarationFonction();
n_l_dec *listeParam();
n_l_dec *optListeDecVariables();
n_instr *instruction();
n_instr *instructionAffect();
n_instr *instructionBloc();
n_l_instr *listeInstructions();
n_instr *instructionSi();
n_instr *optSinon();
n_instr *instructionTanque();
n_instr *instructionFaire();
n_instr *instructionAppel();
n_instr *instructionRetour();
n_instr *instructionEcrire();
n_instr *instructionVide();
n_exp *expression();
n_exp *expressionBis();
n_exp *conjonction();
n_exp *conjonctionBis();
n_exp *comparaison();
n_exp *comparaisonBis();
n_exp *expArith();
n_exp *expArithBis();
n_exp *terme();
n_exp *termeBis();
n_exp *negation();
n_exp *facteur();
n_var *var();
n_var *optIndice();
n_appel *appelFct();
n_l_exp *listeExpressions();
n_l_exp *listeExpressionsBis();

#endif // ANALYSEUR_ASYNT_H_INCLUDED
