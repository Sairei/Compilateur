#include "analyseur_asynt.h"

int uniteCourante;

// PG -> ODV LDF

n_prog *programme()
{
    n_l_dec *S1 = NULL;
    n_l_dec *S2 = NULL;
    n_prog *SS = NULL;

    initialise_premiers();
    initialise_suivants();

    if ( premiers[_optDecVariables_][uniteCourante] == 1
        || premiers[_listeDecFonctions_][uniteCourante] == 1
        || suivants[_programme_][uniteCourante] == 1)
    {
        S1 = optDecVariables();
        S2 = listeDecFonctions();
        SS = cree_n_prog(S1, S2);
        return SS;
    }

   erreur("Erreur PG");
   return NULL;
}


// ODV -> LDV ;
//     -> ε

n_l_dec *optDecVariables()
{
    n_l_dec *SS = NULL;

    if ( premiers[_listeDecVariables_][uniteCourante] == 1 )
    {
        SS = listeDecVariables();
        if(uniteCourante == POINT_VIRGULE)
        {
            uniteCourante = yylex();
            return SS;
        }
        erreur("Erreur ODV");
    }
    if(suivants[_optDecVariables_][uniteCourante] == 1)
    {
        return SS;
    }

    erreur("Erreur ODV");
    return NULL;
}


// LDV -> DV LDVB

n_l_dec *listeDecVariables()
{
    n_dec *S1 = NULL;
    n_l_dec *S2 = NULL;
    n_l_dec *SS = NULL;

    if(premiers[_declarationVariable_][uniteCourante] == 1)
    {
        S1 = declarationVariable();
        S2 = listeDecVariablesBis();
        SS = cree_n_l_dec(S1, S2);
        return SS;
    }

    erreur("Erreur LDV");
    return NULL;
}


// LDVB -> , DV LDVB
//      -> ε

n_l_dec *listeDecVariablesBis()
{
    n_dec *S1 = NULL;
    n_l_dec *S2 = NULL;
    n_l_dec *SS = NULL;


    if(uniteCourante == VIRGULE)
    {
        uniteCourante = yylex();
	S1 = declarationVariable();
        S2 = listeDecVariablesBis();
        SS = cree_n_l_dec(S1, S2);
        return SS;
    }
    if(suivants[_listeDecVariablesBis_][uniteCourante] == 1)
    {
        return SS;
    }

    erreur("Erreur LDVB");
    return NULL;
}


// DV -> int idv OTT

n_dec *declarationVariable()
{
    char *idv = malloc(YYLENGTHMAX);
    n_dec *SS = NULL;

    if(uniteCourante == ENTIER)
    {
        uniteCourante = yylex();
        if(uniteCourante == ID_VAR);
        {
	    strcpy(idv, yytext);
            uniteCourante = yylex();
            SS = optTailleTableau(idv);
            return SS;
        }
        erreur("Erreur DV");
    }

    erreur("Erreur DV");
    return NULL;
}


// OTT -> [ nb ]
//     -> ε

n_dec *optTailleTableau(char *idv)
{
    int nb;
    n_dec *SS = NULL;
    
    if(uniteCourante == CROCHET_OUVRANT)
    {
        uniteCourante = yylex();
        if(uniteCourante == NOMBRE)
        {
	    nb = atoi(yytext);
	    uniteCourante = yylex();
            if(uniteCourante == CROCHET_FERMANT)
            {
                uniteCourante = yylex();
                SS = cree_n_dec_tab(idv, nb);
		return SS;
            }
            erreur("Erreur OTT");
        }
        erreur("Erreur OTT");
    }
    if(suivants[_optTailleTableau_][uniteCourante] == 1)
    {
	SS = cree_n_dec_var(idv);
        return SS;
    }

    erreur("Erreur OTT");
    return NULL;
}


// LDF -> DF LDF
//     -> ε

n_l_dec *listeDecFonctions()
{
    n_dec *S1 = NULL;
    n_l_dec *S2 = NULL;
    n_l_dec *SS = NULL;

    if(premiers[_declarationFonction_][uniteCourante] == 1)
    {
        S1 = declarationFonction();
        S2 = listeDecFonctions();
        SS = cree_n_l_dec(S1, S2);
	return SS;
    }
    if(suivants[_listeDecFonctions_][uniteCourante] == 1)
    {
        return SS;
    }

    erreur("Erreur LDF");
    return NULL;
}


// DF -> idf LP ODV IB

n_dec *declarationFonction()
{
    char *idf = malloc(YYLENGTHMAX);
    n_l_dec *S1 = NULL;
    n_l_dec *S2 = NULL;
    n_instr *S3 = NULL;
    n_dec *SS = NULL;
  
    if(uniteCourante == ID_FCT)
    {
	strcpy(idf, yytext);
        uniteCourante = yylex();
        S1 = listeParam();
        S2 = optDecVariables();
        S3 = instructionBloc();
	SS = cree_n_dec_fonc(idf, S1, S2, S3);
	return SS;
    }

    erreur("Erreur DF");
    return NULL;
}


// LP -> ( OLDV )

n_l_dec *listeParam()
{
    n_l_dec *SS = NULL;
  
    if(uniteCourante == PARENTHESE_OUVRANTE)
    {
        uniteCourante = yylex();
        SS = optListeDecVariables();
        if(uniteCourante == PARENTHESE_FERMANTE)
        {
            uniteCourante = yylex();
            return SS;
        }
        erreur("Erreur LP");
    }

    erreur("Erreur LP");
    return NULL;
}


// OLDV -> LDV
//      -> ε

n_l_dec *optListeDecVariables()
{
     n_l_dec *SS = NULL;
  
    if(premiers[_listeDecVariables_][uniteCourante] == 1)
    {
	SS = listeDecVariables();
        return SS;
    }
    if(suivants[_optListeDecVariables_][uniteCourante] == 1)
    {
        return SS;
    }

    erreur("Erreur OLDV");
    return NULL;
}


// I -> IAFF
//   -> IB
//   -> ISI
//   -> ITQ
//   -> IAPP
//   -> IRET
//   -> IECR
//   -> IVIDE

n_instr *instruction()
{
    n_instr *SS = NULL;

    if(premiers[_instructionAffect_][uniteCourante] == 1)
    {
        SS = instructionAffect();
	return SS;
    }
    if(premiers[_instructionBloc_][uniteCourante] == 1)
    {
        SS = instructionBloc();
	return SS;
    }
    if(premiers[_instructionSi_][uniteCourante] == 1)
    {
        SS = instructionSi();
        return SS;
    }
    if(premiers[_instructionTantque_][uniteCourante] == 1)
    {
        SS = instructionTanque();
        return SS;
    }
    if(premiers[_instructionFaire_][uniteCourante] == 1)
    {
        SS = instructionFaire();
        return SS;
    }
    if(premiers[_instructionAppel_][uniteCourante] == 1)
    {
        SS = instructionAppel();
        return SS;
    }
    if(premiers[_instructionRetour_][uniteCourante] == 1)
    {
        SS = instructionRetour();
        return SS;
    }
    if(premiers[_instructionEcriture_][uniteCourante] == 1)
    {
        SS = instructionEcrire();
        return SS;
    }
    if(premiers[_instructionVide_][uniteCourante] == 1)
    {
        SS = instructionVide();
        return SS;
    }

    erreur("Erreur I");
    return NULL;
}



// IAFF -> VAR = EXP ;

n_instr *instructionAffect()
{
    n_var *S1 = NULL;
    n_exp *S2 = NULL;
    n_instr *SS = NULL;
  
    if(premiers[_var_][uniteCourante] == 1)
    {
        S1 = var();
        if(uniteCourante == EGAL)
        {
            uniteCourante = yylex();
            S2 = expression();
            if(uniteCourante == POINT_VIRGULE)
            {
                uniteCourante = yylex();
		SS = cree_n_instr_affect(S1, S2);
                return SS;
            }
            erreur("Erreur IAFF");
        }
        erreur("Erreur IAFF");
    }

    erreur("Erreur IAFF");
    return NULL;
}


// IB -> { LI }

n_instr *instructionBloc()
{
    n_l_instr *S1 = NULL;
    n_instr *SS = NULL;
  
    if(uniteCourante == ACCOLADE_OUVRANTE)
    {
        uniteCourante = yylex();
        S1 = listeInstructions();
        if(uniteCourante == ACCOLADE_FERMANTE)
        {
            uniteCourante = yylex();
	    SS = cree_n_instr_bloc(S1);
	    return SS;
        }
        erreur("Erreur IB");
    }

    erreur("Erreur IB");
    return NULL;
}


// LI -> I LI
//    -> ε

n_l_instr *listeInstructions()
{
    n_instr *S1 = NULL;
    n_l_instr *S2 = NULL;
    n_l_instr *SS = NULL;
    
    if(premiers[_instruction_][uniteCourante] == 1)
    {
        S1 = instruction();
        S2 = listeInstructions();
	SS = cree_n_l_instr(S1, S2);
	return SS;
    }
    if(suivants[_listeInstructions_][uniteCourante] == 1)
    {
        return SS;
    }

    erreur("Erreur LI");
    return NULL;
}


// ISI -> si EXP alr IB OSINON

n_instr *instructionSi()
{
    n_exp *S1 = NULL;
    n_instr *S2 = NULL;
    n_instr *S3 = NULL;
    n_instr *SS = NULL;
  
    if(uniteCourante == SI)
    {
        uniteCourante = yylex();
        S1 = expression();
        if(uniteCourante == ALORS)
        {
            uniteCourante = yylex();
            S2 = instructionBloc();
            S3 = optSinon();
	    SS = cree_n_instr_si(S1, S2, S3);
	    return SS;
        }
        erreur("Erreur ISI");
    }

    erreur("Erreur ISI");
    return NULL;
}


// OSINON -> sin IB
//        -> ε

n_instr *optSinon()
{
    n_instr *SS = NULL;
  
    if(uniteCourante == SINON)
    {
        uniteCourante = yylex();
        SS = instructionBloc();
        return SS;
    }
    if(suivants[_optSinon_][uniteCourante] == 1)
    {
        return SS;
    }

    erreur("Erreur OSINON");
    return NULL;
}


// ITQ -> tq EXP fr IB

n_instr *instructionTanque()
{
    n_exp *S1 = NULL;
    n_instr *S2 = NULL;
    n_instr *SS = NULL;
  
    if(uniteCourante == TANTQUE)
    {
        uniteCourante = yylex();
        S1 = expression();
        if(uniteCourante == FAIRE)
        {
            uniteCourante = yylex();
            S2 = instructionBloc();
	    SS = cree_n_instr_tantque(S1, S2);
            return SS;
        }
        erreur("Erreur ITQ");
    }

    erreur("Erreur ITQ");
    return NULL;
}

// IFR -> fr IB tq EXP

n_instr *instructionFaire()
{
    n_instr *S1 = NULL;
    n_exp *S2 = NULL;
    n_instr *SS = NULL;
  
    if(uniteCourante == FAIRE)
    {
        uniteCourante = yylex();
        S1 = instructionBloc();
        if(uniteCourante == TANTQUE)
        {
            uniteCourante = yylex();
            S2 = expression();
	    SS = cree_n_instr_faire(S1, S2);
            return SS;
        }
        erreur("Erreur ITQ");
    }

    erreur("Erreur ITQ");
    return NULL;
}


// IAPP -> APPF ;

n_instr *instructionAppel()
{
    n_appel *S1 = NULL;
    n_instr *SS = NULL;
  
    if(premiers[_appelFct_][uniteCourante] == 1)
    {
        S1 = appelFct();
        if(uniteCourante == POINT_VIRGULE)
        {
            uniteCourante = yylex();
	    SS = cree_n_instr_appel(S1);
            return SS;
        }
        erreur("Erreur IAPP");
    }

    erreur("Erreur IAPP");
    return NULL;
}


// IRET -> ret EXP ;

n_instr *instructionRetour()
{
    n_exp *S1 = NULL;
    n_instr *SS = NULL;
    
    if(uniteCourante == RETOUR)
    {
        uniteCourante = yylex();
        S1 = expression();
	if(uniteCourante == POINT_VIRGULE)
	{
	    uniteCourante = yylex();
	    SS = cree_n_instr_retour(S1);
            return SS;
	}
	erreur("Erreur IRET");
    }

    erreur("Erreur IRET");
    return NULL;
}


// IECR -> ecr ( EXP ) ;

n_instr *instructionEcrire()
{
    n_exp *S1 = NULL;
    n_instr *SS = NULL;
    
    if(uniteCourante == ECRIRE)
    {
        uniteCourante = yylex();
        if(uniteCourante == PARENTHESE_OUVRANTE)
        {
            uniteCourante = yylex();
            S1 = expression();
            if(uniteCourante == PARENTHESE_FERMANTE)
            {
                uniteCourante = yylex();
                if(uniteCourante == POINT_VIRGULE)
                {
                    uniteCourante = yylex();
		    SS = cree_n_instr_ecrire(S1);
                    return SS;
                }
                erreur("Erreur IECR");
            }
            erreur("Erreur IECR");
        }
        erreur("Erreur IECR");
    }

    erreur("Erreur IECR");
    return NULL;
}


// IVIDE -> ;

n_instr *instructionVide()
{
    n_instr *SS = NULL;
  
    if(uniteCourante == POINT_VIRGULE)
    {
        uniteCourante = yylex();
	SS = cree_n_instr_vide();
        return SS;
    }

    erreur("Erreur IVIDE");
    return NULL;
}


// EXP -> CONJ EXPB

n_exp *expression()
{
    n_exp *S1 = NULL;
    n_exp *SS = NULL;
  
    if(premiers[_conjonction_][uniteCourante] == 1)
    {
        S1 = conjonction();
        SS = expressionBis(S1);
	return SS;
    }

    erreur("Erreur EXP");
    return NULL;
}


// EXPB -> | CONJ EXPB
//      -> ε

n_exp *expressionBis(n_exp *herite)
{
    n_exp *S1 = NULL;
    n_exp *SS = NULL;
    n_exp *fils = NULL;
    
    if(uniteCourante == OU)
    {
        uniteCourante = yylex();
        S1 = conjonction();
	fils = cree_n_exp_op(ou, herite, S1);
        SS = expressionBis(fils);
	return SS;
    }
    if(suivants[_expressionBis_][uniteCourante] == 1)
    {
        return herite;
    }

    erreur("Erreur EXPB");
    return NULL;
}


// CONJ -> COMP CONJB

n_exp *conjonction()
{
    n_exp *S1 = NULL;
    n_exp *SS = NULL;
    
    if(premiers[_comparaison_][uniteCourante] == 1)
    {
        S1 = comparaison();
        SS = conjonctionBis(S1);
        return SS;
    }

    erreur("Erreur CONJ");
    return NULL;
}


// CONJB -> & COMP CONJB
//       -> ε

n_exp *conjonctionBis(n_exp *herite)
{
    n_exp *S1 = NULL;
    n_exp *SS = NULL;
    n_exp *fils = NULL;
    
    if(uniteCourante == ET)
    {
        uniteCourante = yylex();
        S1 = comparaison();
	fils = cree_n_exp_op(et, herite, S1);
        SS = conjonctionBis(fils);
        return SS;
    }
    if(suivants[_conjonctionBis_][uniteCourante] == 1)
    {
        return herite;
    }

    erreur("Erreur CONJB");
    return NULL;
}


// COMP -> E COMPB

n_exp *comparaison()
{
    n_exp *S1 = NULL;
    n_exp *SS = NULL;
    
    if(premiers[_expArith_][uniteCourante] == 1)
    {
        S1 = expArith();
        SS = comparaisonBis(S1);
        return SS;
    }

    erreur("Erreur COMP");
    return NULL;
}


// COMPB -> = E COMPB
//       -> < E COMPB
//       -> > E COMPB
//       -> <= E COMPB
//       -> >= E COMPB
//       -> != E COMPB
//       -> ε

n_exp *comparaisonBis(n_exp *herite)
{
    n_exp *S1 = NULL;
    n_exp *SS = NULL;
    n_exp *fils = NULL;
    
    if(uniteCourante == EGAL)
    {
        uniteCourante = yylex();
        S1 = expArith();
        fils = cree_n_exp_op(egal, herite, S1);
        SS = comparaisonBis(fils);
        return SS;
    }
    if(uniteCourante == INFERIEUR)
    {
        uniteCourante = yylex();
        S1 = expArith();
        fils = cree_n_exp_op(inf, herite, S1);
        SS = comparaisonBis(fils);
        return SS;
    }
    if(uniteCourante == SUPERIEUR)
    {
        uniteCourante = yylex();
        S1 = expArith();
        fils = cree_n_exp_op(sup, herite, S1);
        SS = comparaisonBis(fils);
        return SS;
    }
    if(uniteCourante == INF_EGAL)
    {
        uniteCourante = yylex();
        S1 = expArith();
        fils = cree_n_exp_op(infeg, herite, S1);
        SS = comparaisonBis(fils);
        return SS;
    }
    if(uniteCourante == SUP_EGAL)
    {
        uniteCourante = yylex();
        S1 = expArith();
        fils = cree_n_exp_op(supeg, herite, S1);
        SS = comparaisonBis(fils);
        return SS;
    }
    if(uniteCourante == DIFF)
    {
        uniteCourante = yylex();
        S1 = expArith();
        fils = cree_n_exp_op(diff, herite, S1);
        SS = comparaisonBis(fils);
        return SS;
    }
    if(suivants[_comparaisonBis_][uniteCourante])
    {
        return herite;
    }

    erreur("Erreur COMPB");
    return NULL;
}


// E -> T EB

n_exp *expArith()
{
    n_exp *S1 = NULL;
    n_exp *SS = NULL;
    
    if(premiers[_terme_][uniteCourante] == 1)
    {
        S1 = terme();
        SS = expArithBis(S1);
        return SS;
    }

    erreur("Erreur E");
    return NULL;
}


// EB -> + T EB
//    -> - T EB
//    -> ε

n_exp *expArithBis(n_exp *herite)
{
    n_exp *S1 = NULL;
    n_exp *SS = NULL;
    n_exp *fils = NULL;
    
    if(uniteCourante == PLUS)
    {
        uniteCourante = yylex();
        S1 = terme();
        fils = cree_n_exp_op(plus, herite, S1);
	SS = expArithBis(fils);
        return SS;
    }
    if(uniteCourante == MOINS)
    {
        uniteCourante = yylex();
        S1 = terme();
	fils = cree_n_exp_op(moins, herite, S1);
        SS = expArithBis(fils);
        return SS;
    }
    if(suivants[_expArithBis_][uniteCourante] == 1)
    {
        return herite;
    }

    erreur("Erreur EB");
    return NULL;
}


// T -> NEG TB

n_exp *terme()
{
    n_exp *S1 = NULL;
    n_exp *SS = NULL;
    
    if(premiers[_negation_][uniteCourante] == 1)
    {
        S1 = negation();
        SS = termeBis(S1);
        return SS;
    }

    erreur("Erreur T");
    return NULL;
}


// TB -> * NEG TB
//    -> / NEG TB
//    -> % NEG TB
//    -> ε

n_exp *termeBis(n_exp *herite)
{
    n_exp *S1 = NULL;
    n_exp *SS = NULL;
    n_exp *fils = NULL;
    
    if(uniteCourante == FOIS)
    {
        uniteCourante = yylex();
        S1 = negation();
        fils = cree_n_exp_op(fois, herite, S1);
        SS = termeBis(fils);
        return SS;
    }
    if(uniteCourante == DIVISE)
    {
        uniteCourante = yylex();
        S1 = negation();
        fils = cree_n_exp_op(divise, herite, S1);
        SS = termeBis(fils);
        return SS;
    }
    if(uniteCourante == MODULO)
    {
        uniteCourante = yylex();
        S1 = negation();
        fils = cree_n_exp_op(modulo, herite, S1);
        SS = termeBis(fils);
        return SS;
    }
    if(suivants[_termeBis_][uniteCourante] == 1)
    {
        return herite;
    }

    erreur("Erreur TB");
    return NULL;
}


// NEG -> ! NEG
//     -> F

n_exp *negation()
{
    n_exp *S1 = NULL;
    n_exp *SS = NULL;
    
    if(uniteCourante == NON)
    {
        uniteCourante = yylex();
        S1 = negation();
	SS = cree_n_exp_op(non, S1, NULL);
        return SS;
    }
    if(premiers[_facteur_][uniteCourante] == 1)
    {
        SS = facteur();
        return SS;
    }

    erreur("Erreur NEG");
    return NULL;
}


// F -> ( EXP )
//   -> nb
//   -> APPF
//   -> VAR
//   -> lire ( )

n_exp *facteur()
{
    int nb;
    n_appel *S_app = NULL;
    n_var *S_var = NULL;    
    n_exp *SS = NULL;
    
    if(uniteCourante == PARENTHESE_OUVRANTE)
    {
        uniteCourante = yylex();
        SS = expression();
        if(uniteCourante == PARENTHESE_FERMANTE)
        {
            uniteCourante = yylex();
            return SS;
        }
        erreur("Erreur F");
    }
    if(uniteCourante == NOMBRE)
    {
	nb = atoi(yytext);
        uniteCourante = yylex();
	SS = cree_n_exp_entier(nb);
        return SS;
    }
    if(premiers[_appelFct_][uniteCourante] == 1)
    {
        S_app = appelFct();
	SS = cree_n_exp_appel(S_app);
        return SS;
    }
    if(premiers[_var_][uniteCourante] == 1)
    {
        S_var = var();
	SS = cree_n_exp_var(S_var);
        return SS;
    }
    if(uniteCourante == LIRE)
    {
        uniteCourante = yylex();
        if(uniteCourante == PARENTHESE_OUVRANTE)
        {
            uniteCourante = yylex();
            if(uniteCourante == PARENTHESE_FERMANTE)
            {
                uniteCourante = yylex();
		SS = cree_n_exp_lire();
                return SS;
            }
            erreur("Erreur F");
        }
        erreur("Erreur F");
    }

    erreur("Erreur F");
    return NULL;
}


// VZR -> idv OIND

n_var *var()
{
    char *idv = malloc(YYLENGTHMAX);
    n_var *SS = NULL;
    
    if(uniteCourante == ID_VAR)
    {
	strcpy(idv, yytext);
        uniteCourante = yylex();
        SS = optIndice(idv);
        return SS;
    }

    erreur("Erreur VAR");
    return NULL;
}


// OIND -> [ EXP ]
//      -> ε

n_var *optIndice(char *idv)
{
    n_exp *S1 = NULL;
    n_var *SS = NULL;
    
    if(uniteCourante == CROCHET_OUVRANT)
    {
        uniteCourante = yylex();
        S1 = expression();
        if(uniteCourante == CROCHET_FERMANT)
        {
            uniteCourante = yylex();
	    SS = cree_n_var_indicee(idv, S1);
            return SS;
        }
        erreur("Erreur OIND");
    }
    if(suivants[_optIndice_][uniteCourante] == 1)
    {
	SS = cree_n_var_simple(idv);
        return SS;
    }

    erreur("Erreur OIND");
    return NULL;
}


// APPF -> idf ( LEXP )

n_appel *appelFct()
{
    char *idf = malloc(YYLENGTHMAX);
    n_l_exp *S1 = NULL;
    n_appel *SS = NULL;
  
    if(uniteCourante == ID_FCT)
    {
	strcpy(idf, yytext);
        uniteCourante = yylex();
        if(uniteCourante == PARENTHESE_OUVRANTE)
        {
            uniteCourante = yylex();
            S1 = listeExpressions();
            if(uniteCourante == PARENTHESE_FERMANTE)
            {
                uniteCourante = yylex();
		SS = cree_n_appel(idf, S1);
                return SS;
            }
            erreur("Erreur APPF");
        }
        erreur("Erreur APPF");
    }

    erreur("Erreur APPF");
    return NULL;
}


// LEXP -> EXP LEXPB
//      -> ε

n_l_exp *listeExpressions()
{
    n_exp *S1 = NULL;
    n_l_exp *S2 = NULL;
    n_l_exp *SS = NULL;

    if(premiers[_expression_][uniteCourante] == 1)
    {
        S1 = expression();
        S2 = listeExpressionsBis();
	SS  = cree_n_l_exp(S1, S2);
        return SS;
    }
    if(suivants[_listeExpressions_][uniteCourante] == 1)
    {
        return SS;
    }

    erreur("Erreur LEXP");
    return NULL;
}


// LEXPB -> , EXP LEXPB
//       -> ε

n_l_exp *listeExpressionsBis()
{
    n_exp *S1 = NULL;
    n_l_exp *S2 = NULL;
    n_l_exp *SS = NULL;

    if(uniteCourante == VIRGULE)
    {
        uniteCourante = yylex();
        S1 = expression();
        S2 = listeExpressionsBis();
	SS = cree_n_l_exp(S1, S2);
        return SS;
    }
    if(suivants[_listeExpressionsBis_][uniteCourante] == 1)
    {
        return SS;
    }

    erreur("Erreur LEXPB");
    return NULL;
}
