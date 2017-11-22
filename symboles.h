/* symboles non terminaux */

#define EPSILON 0

#define NB_NON_TERMINAUX 41

#define _listeDecVariables_ 1
#define _listeDecFonctions_ 2
#define _declarationVariable_ 3
#define _declarationFonction_ 4
#define _listeParam_ 5
#define _listeInstructions_ 6
#define _instruction_ 8
#define _instructionAffect_ 9  
#define _instructionBloc_ 10
#define _instructionSi_ 11
#define _instructionTantque_ 12 
#define _instructionAppel_ 13
#define _instructionRetour_ 14
#define _instructionEcriture_ 15
#define _instructionVide_ 16
#define _var_ 17
#define _expression_ 18
#define _appelFct_ 19
#define _conjonction_ 20
#define _negation_ 21
#define _comparaison_ 22
#define _expArith_ 23
#define _terme_ 24
#define _facteur_ 25
#define _argumentsEffectifs_ 26 
#define _listeExpressions_ 27
#define _listeExpressionsBis_ 7
#define _programme_ 28
#define _conjonctionBis_ 29
#define _optTailleTableau_ 30
#define _expArithBis_ 31
#define _optSinon_ 32
#define _comparaisonBis_ 33
#define _optDecVariables_ 34
#define _optIndice_ 35
#define _listeDecVariablesBis_ 36
#define _instructionPour_ 37
#define _termeBis_ 38
#define _expressionBis_ 39
#define _instructionFaire_ 40
#define _optListeDecVariables_ 41


/* symboles terminaux */
#define NB_TERMINAUX 36

#define POINT_VIRGULE 1
#define PLUS 2
#define MOINS 3
#define FOIS 4
#define DIVISE 5
#define PARENTHESE_OUVRANTE 6
#define PARENTHESE_FERMANTE 7
#define CROCHET_OUVRANT 8
#define CROCHET_FERMANT 9
#define ACCOLADE_OUVRANTE 10
#define ACCOLADE_FERMANTE 11
#define EGAL 12
#define INFERIEUR 13
#define ET 14
#define OU 15
#define NON 16
#define SI 17
#define ALORS 18
#define SINON 19
#define TANTQUE 20
#define FAIRE 21
#define ENTIER 22
#define RETOUR 23
#define LIRE 24
#define ECRIRE 25
#define ID_VAR 26
#define ID_FCT 27
#define NOMBRE 28
#define FIN 29
#define VIRGULE 30
#define MODULO 31
#define SUPERIEUR 32
#define INF_EGAL 33
#define SUP_EGAL 34
#define DIFF 35
