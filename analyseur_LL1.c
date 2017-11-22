#include "analyseur_LL1.h"

int uniteCourante;

// PG -> ODV LDF

void programme()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);
    initialise_premiers();
    initialise_suivants();

    if ( premiers[_optDecVariables_][uniteCourante] == 1
        || premiers[_listeDecFonctions_][uniteCourante] == 1
        || suivants[_programme_][uniteCourante] == 1)
    {
        optDecVariables();
        listeDecFonctions();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

   erreur("Erreur PG");
}


// ODV -> LDV ;
//     -> ε

void optDecVariables()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if ( premiers[_listeDecVariables_][uniteCourante] == 1 )
    {
        listeDecVariables();
        if(uniteCourante == POINT_VIRGULE)
        {
            affiche_element("symbole", "POINT_VIRGULE", 1);
            uniteCourante = yylex();
            affiche_balise_fermante(__FUNCTION__, 1);
            return;
        }
        erreur("Erreur ODV");
    }
    if(suivants[_optDecVariables_][uniteCourante] == 1)
    {
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur ODV");
}


// LDV -> DV LDVB

void listeDecVariables()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(premiers[_declarationVariable_][uniteCourante] == 1)
    {
        declarationVariable();
        listeDecVariablesBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur LDV");
}


// LDVB -> , DV LDVB
//      -> ε

void listeDecVariablesBis()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == VIRGULE)
    {
        affiche_element("symbole", "VIRGULE", 1);
        uniteCourante = yylex();
        declarationVariable();
        listeDecVariablesBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(suivants[_listeDecVariablesBis_][uniteCourante] == 1)
    {
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur LDVB");
}


// DV -> int idv OTT

void declarationVariable()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == ENTIER)
    {
        affiche_element("mot_clef", "entier", 1);
        uniteCourante = yylex();
        if(uniteCourante == ID_VAR);
        {
            affiche_element("id_variable", getNom(), 1);
            uniteCourante = yylex();
            optTailleTableau();
            affiche_balise_fermante(__FUNCTION__, 1);
            return;
        }
        erreur("Erreur DV");
    }

    erreur("Erreur DV");
}


// OTT -> [ nb ]
//     -> ε

void optTailleTableau()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == CROCHET_OUVRANT)
    {
        affiche_element("symbole", "CROCHET_OUVRANT", 1);
        uniteCourante = yylex();
        if(uniteCourante == NOMBRE)
        {
            affiche_element("nombre", getNom(), 1);
            uniteCourante = yylex();
            if(uniteCourante == CROCHET_FERMANT)
            {
                affiche_element("symbole", "CROCHET_FERMANT", 1);
                uniteCourante = yylex();
                affiche_balise_fermante(__FUNCTION__, 1);
                return;
            }
            erreur("Erreur OTT");
        }
        erreur("Erreur OTT");
    }
    if(suivants[_optTailleTableau_][uniteCourante] == 1)
    {
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur OTT");
}


// LDF -> DF LDF
//     -> ε

void listeDecFonctions()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(premiers[_declarationFonction_][uniteCourante] == 1)
    {
        declarationFonction();
        listeDecFonctions();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(suivants[_listeDecFonctions_][uniteCourante] == 1)
    {
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur LDF");
}


// DF -> idf LP ODV IB

void declarationFonction()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == ID_FCT)
    {
        affiche_element("id_fonction", getNom(), 1);
        uniteCourante = yylex();
        listeParam();
        optDecVariables();
        instructionBloc();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur DF");
}


// LP -> ( OLDV )

void listeParam()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == PARENTHESE_OUVRANTE)
    {
        affiche_element("symbole", "PARENTHESE_OUVRANTE", 1);
        uniteCourante = yylex();
        optListeDecVariables();
        if(uniteCourante == PARENTHESE_FERMANTE)
        {
            affiche_element("symbole", "PARENTHESE_FERMANTE", 1);
            uniteCourante = yylex();
            affiche_balise_fermante(__FUNCTION__, 1);
            return;
        }
        erreur("Erreur LP");
    }

    erreur("Erreur LP");
}


// OLDV -> LDV
//      -> ε

void optListeDecVariables()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(premiers[_listeDecVariables_][uniteCourante] == 1)
    {
        listeDecVariables();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(suivants[_optListeDecVariables_][uniteCourante] == 1)
    {
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur OLDV");
}


// I -> IAFF
//   -> IB
//   -> ISI
//   -> ITQ
//   -> IFR
//   -> IAPP
//   -> IRET
//   -> IECR
//   -> IVIDE

void instruction()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);
    if(premiers[_instructionAffect_][uniteCourante] == 1)
    {
        instructionAffect();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(premiers[_instructionBloc_][uniteCourante] == 1)
    {
        instructionBloc();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(premiers[_instructionSi_][uniteCourante] == 1)
    {
        instructionSi();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(premiers[_instructionTantque_][uniteCourante] == 1)
    {
        instructionTantque();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(premiers[_instructionFaire_][uniteCourante] == 1)
    {
        instructionFaire();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(premiers[_instructionAppel_][uniteCourante] == 1)
    {
        instructionAppel();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(premiers[_instructionRetour_][uniteCourante] == 1)
    {
        instructionRetour();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(premiers[_instructionEcriture_][uniteCourante] == 1)
    {
        instructionEcrire();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(premiers[_instructionVide_][uniteCourante] == 1)
    {
        instructionVide();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur I");
}



// IAFF -> VAR = EXP ;

void instructionAffect()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(premiers[_var_][uniteCourante] == 1)
    {
        var();
        if(uniteCourante == EGAL)
        {
            affiche_element("symbole", "EGAL", 1);
            uniteCourante = yylex();
            expression();
            if(uniteCourante == POINT_VIRGULE)
            {
                affiche_element("symbole", "POINT_VIRGULE", 1);
                uniteCourante = yylex();
                affiche_balise_fermante(__FUNCTION__, 1);
                return;
            }
            erreur("Erreur IAFF");
        }
        erreur("Erreur IAFF");
    }

    erreur("Erreur IAFF");
}


// IB -> { LI }

void instructionBloc()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == ACCOLADE_OUVRANTE)
    {
        affiche_element("symbole", "ACCOLADE_OUVRANTE", 1);
        uniteCourante = yylex();
        listeInstructions();
        if(uniteCourante == ACCOLADE_FERMANTE)
        {
            affiche_element("symbole", "ACCOLADE_FERMANTE", 1);
            uniteCourante = yylex();
            affiche_balise_fermante(__FUNCTION__, 1);
            return;
        }
        erreur("Erreur IB");
    }

    erreur("Erreur IB");
}


// LI -> I LI
//    -> ε

void listeInstructions()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(premiers[_instruction_][uniteCourante] == 1)
    {
        instruction();
        listeInstructions();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(suivants[_listeInstructions_][uniteCourante] == 1)
    {
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur LI");
}


// ISI -> si EXP alr IB OSINON

void instructionSi()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == SI)
    {
        affiche_element("mot_clef", "si", 1);
        uniteCourante = yylex();
        expression();
        if(uniteCourante == ALORS)
        {
            affiche_element("mot_clef", "alors", 1);
            uniteCourante = yylex();
            instructionBloc();
            optSinon();
            affiche_balise_fermante(__FUNCTION__, 1);
            return;
        }
        erreur("Erreur ISI");
    }

    erreur("Erreur ISI");
}


// OSINON -> sin IB
//        -> ε

void optSinon()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == SINON)
    {
        affiche_element("mot_clef", "sinon", 1);
        uniteCourante = yylex();
        instructionBloc();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(suivants[_optSinon_][uniteCourante] == 1)
    {
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur OSINON");
}


// ITQ -> tq EXP fr IB

void instructionTantque()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == TANTQUE)
    {
        affiche_element("mot_clef", "tantque", 1);
        uniteCourante = yylex();
        expression();
        if(uniteCourante == FAIRE)
        {
            affiche_element("mot_clef", "faire", 1);
            uniteCourante = yylex();
            instructionBloc();
            affiche_balise_fermante(__FUNCTION__, 1);
            return;
        }
        erreur("Erreur ITQ");
    }

    erreur("Erreur ITQ");
}

// IFR -> fr IB tq EXP

void instructionFaire()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == FAIRE)
    {
        affiche_element("mot_clef", "faire", 1);
        uniteCourante = yylex();
        instructionBloc();
        if(uniteCourante == TANTQUE)
        {
            affiche_element("mot_clef", "tantque", 1);
            uniteCourante = yylex();
            expression();
            affiche_balise_fermante(__FUNCTION__, 1);
            return;
        }
        erreur("Erreur IFR");
    }

    erreur("Erreur IFR");
}


// IAPP -> APPF ;

void instructionAppel()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(premiers[_appelFct_][uniteCourante] == 1)
    {
        appelFct();
        if(uniteCourante == POINT_VIRGULE)
        {
            affiche_element("symbole", "POINT_VIRGULE", 1);
            uniteCourante = yylex();
            affiche_balise_fermante(__FUNCTION__, 1);
            return;
        }
        erreur("Erreur IAPP");
    }

    erreur("Erreur IAPP");
}


// IRET -> ret EXP ;

void instructionRetour()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == RETOUR)
    {
        affiche_element("mot_clef", "retour", 1);
        uniteCourante = yylex();
        expression();
	if(uniteCourante == POINT_VIRGULE)
	{
	    affiche_element("symbole", "POINT_VIRGULE", 1);
	    uniteCourante = yylex();
            affiche_balise_fermante(__FUNCTION__, 1);
            return;
	}    
    }

    erreur("Erreur IRET");
}


// IECR -> ecr ( EXP ) ;

void instructionEcrire()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == ECRIRE)
    {
        affiche_element("mot_clef", "ecrire", 1);
        uniteCourante = yylex();
        if(uniteCourante == PARENTHESE_OUVRANTE)
        {
            affiche_element("symbole", "PARENTHESE_OUVRANTE", 1);
            uniteCourante = yylex();
            expression();
            if(uniteCourante == PARENTHESE_FERMANTE)
            {
                affiche_element("symbole", "PARENTHESE_FERMANTE", 1);
                uniteCourante = yylex();
                if(uniteCourante == POINT_VIRGULE)
                {
                    affiche_element("symbole", "POINT_VIRGULE", 1);
                    uniteCourante = yylex();
                    affiche_balise_fermante(__FUNCTION__, 1);
                    return;
                }
                erreur("Erreur IECR");
            }
            erreur("Erreur IECR");
        }
        erreur("Erreur IECR");
    }

    erreur("Erreur IECR");
}


// IVIDE -> ;

void instructionVide()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == POINT_VIRGULE)
    {
        affiche_element("symbole", "POINT_VIRGULE", 1);
        uniteCourante = yylex();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur IVIDE");
}


// EXP -> CONJ EXPB

void expression()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(premiers[_conjonction_][uniteCourante] == 1)
    {
        conjonction();
        expressionBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur EXP");
}


// EXPB -> | CONJ EXPB
//      -> ε

void expressionBis()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == OU)
    {
        affiche_element("symbole", "OU", 1);
        uniteCourante = yylex();
        conjonction();
        expressionBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(suivants[_expressionBis_][uniteCourante] == 1)
    {
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur EXPB");
}


// CONJ -> COMP CONJB

void conjonction()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(premiers[_comparaison_][uniteCourante] == 1)
    {
        comparaison();
        conjonctionBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur CONJ");
}


// CONJB -> & COMP CONJB
//       -> ε

void conjonctionBis()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == ET)
    {
        affiche_element("symbole", "ET", 1);
        uniteCourante = yylex();
        comparaison();
        conjonctionBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(suivants[_conjonctionBis_][uniteCourante] == 1)
    {
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur CONJB");
}


// COMP -> E COMPB

void comparaison()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(premiers[_expArith_][uniteCourante] == 1)
    {
        expArith();
        comparaisonBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur COMP");
}


// COMPB -> = E COMPB
//       -> < E COMPB
//       -> > E COMPB
//       -> <= E COMPB
//       -> >= E COMPB
//       -> != E COMPB
//       -> ε

void comparaisonBis()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == EGAL)
    {
        affiche_element("symbole", "EGAL", 1);
        uniteCourante = yylex();
        expArith();
        comparaisonBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(uniteCourante == INFERIEUR)
    {
        affiche_element("symbole", "INFERIEUR", 1);
        uniteCourante = yylex();
        expArith();
        comparaisonBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(uniteCourante == SUPERIEUR)
    {
        affiche_element("symbole", "SUPERIEUR", 1);
        uniteCourante = yylex();
        expArith();
        comparaisonBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(uniteCourante == INF_EGAL)
    {
        affiche_element("symbole", "INFERIEUR OU EGAL", 1);
        uniteCourante = yylex();
        expArith();
        comparaisonBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(uniteCourante == SUP_EGAL)
    {
        affiche_element("symbole", "SUPERIEUR OU EGAL", 1);
        uniteCourante = yylex();
        expArith();
        comparaisonBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(uniteCourante == DIFF)
    {
        affiche_element("symbole", "DIFFERENT", 1);
        uniteCourante = yylex();
        expArith();
        comparaisonBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(suivants[_comparaisonBis_][uniteCourante])
    {
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur COMPB");
}


// E -> T EB

void expArith()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(premiers[_terme_][uniteCourante] == 1)
    {
        terme();
        expArithBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur E");
}


// EB -> + T EB
//    -> - T EB
//    -> ε

void expArithBis()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == PLUS)
    {
        affiche_element("symbole", "PLUS", 1);
        uniteCourante = yylex();
        terme();
        expArithBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(uniteCourante == MOINS)
    {
        affiche_element("symbole", "MOINS", 1);
        uniteCourante = yylex();
        terme();
        expArithBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(suivants[_expArithBis_][uniteCourante] == 1)
    {
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur EB");
}


// T -> NEG TB

void terme()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(premiers[_negation_][uniteCourante] == 1)
    {
        negation();
        termeBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur T");
}


// TB -> * NEG TB
//    -> / NEG TB
//    -> % NEG TB
//    -> ε

void termeBis()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == FOIS)
    {
        affiche_element("symbole", "FOIS", 1);
        uniteCourante = yylex();
        negation();
        termeBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(uniteCourante == DIVISE)
    {
        affiche_element("symbole", "DIVISE", 1);
        uniteCourante = yylex();
        negation();
        termeBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(uniteCourante == MODULO)
    {
        affiche_element("symbole", "MODULO", 1);
        uniteCourante = yylex();
        negation();
        termeBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(suivants[_termeBis_][uniteCourante] == 1)
    {
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur TB");
}


// NEG -> ! NEG
//     -> F

void negation()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == NON)
    {
        affiche_element("symbole", "NON", 1);
        uniteCourante = yylex();
        negation();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(premiers[_facteur_][uniteCourante] == 1)
    {
        facteur();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur NEG");
}


// F -> ( EXP )
//   -> nb
//   -> APPF
//   -> VAR
//   -> lire ( )

void facteur()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == PARENTHESE_OUVRANTE)
    {
        affiche_element("symbole", "PARENTHESE_OUVRANTE", 1);
        uniteCourante = yylex();
        expression();
        if(uniteCourante == PARENTHESE_FERMANTE)
        {
            affiche_element("symbole", "PARENTHESE_FERMANTE", 1);
            uniteCourante = yylex();
            affiche_balise_fermante(__FUNCTION__, 1);
            return;
        }
        erreur("Erreur F");
    }
    if(uniteCourante == NOMBRE)
    {
        affiche_element("nombre", getNom(), 1);
        uniteCourante = yylex();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(premiers[_appelFct_][uniteCourante] == 1)
    {
        appelFct();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(premiers[_var_][uniteCourante] == 1)
    {
        var();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(uniteCourante == LIRE)
    {
        affiche_element("mot_clef", "lire", 1);
        uniteCourante = yylex();
        if(uniteCourante == PARENTHESE_OUVRANTE)
        {
            affiche_element("symbole", "PARENTHESE_OUVRANTE", 1);
            uniteCourante = yylex();
            if(uniteCourante == PARENTHESE_FERMANTE)
            {
                affiche_element("symbole", "PARENTHESE_FERMANTE", 1);
                uniteCourante = yylex();
                affiche_balise_fermante(__FUNCTION__, 1);
                return;
            }
            erreur("Erreur F");
        }
        erreur("Erreur F");
    }

    erreur("Erreur F");
}


// VAR -> idv OIND

void var()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == ID_VAR)
    {
        affiche_element("id_variable", getNom(), 1);
        uniteCourante = yylex();
        optIndice();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur VAR");
}


// OIND -> [ EXP ]
//      -> ε

void optIndice()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == CROCHET_OUVRANT)
    {
        affiche_element("symbole", "CROCHET_OUVRANT", 1);
        uniteCourante = yylex();
        expression();
        if(uniteCourante == CROCHET_FERMANT)
        {
            affiche_element("symbole", "CROCHET_FERMANT", 1);
            uniteCourante = yylex();
            affiche_balise_fermante(__FUNCTION__, 1);
            return;
        }
        erreur("Erreur OIND");
    }
    if(suivants[_optIndice_][uniteCourante] == 1)
    {
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur OIND");
}


// APPF -> idf ( LEXP )

void appelFct()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == ID_FCT)
    {
        affiche_element("id_fonction", getNom(), 1);
        uniteCourante = yylex();
        if(uniteCourante == PARENTHESE_OUVRANTE)
        {
            affiche_element("symbole", "PARENTHESE_OUVRANTE", 1);
            uniteCourante = yylex();
            listeExpressions();
            if(uniteCourante == PARENTHESE_FERMANTE)
            {
                affiche_element("symbole", "PARENTHESE_FERMANTE", 1);
                uniteCourante = yylex();
                affiche_balise_fermante(__FUNCTION__, 1);
                return;
            }
            erreur("Erreur APPF");
        }
        erreur("Erreur APPF");
    }

    erreur("Erreur APPF");
}


// LEXP -> EXP LEXPB
//      -> ε

void listeExpressions()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(premiers[_expression_][uniteCourante] == 1)
    {
        expression();
        listeExpressionsBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(suivants[_listeExpressions_][uniteCourante] == 1)
    {
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur LEXP");
}


// LEXPB -> , EXP LEXPB
//       -> ε

void listeExpressionsBis()
{
    affiche_balise_ouvrante(__FUNCTION__, 1);

    if(uniteCourante == VIRGULE)
    {
        affiche_element("symbole", "VIRGULE", 1);
        uniteCourante = yylex();
        expression();
        listeExpressionsBis();
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }
    if(suivants[_listeExpressionsBis_][uniteCourante] == 1)
    {
        affiche_balise_fermante(__FUNCTION__, 1);
        return;
    }

    erreur("Erreur LEXPB");
}
