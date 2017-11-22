#include <stdio.h>
#include "syntabs.h"
#include "util.h"
#include "generateur.h"

void ajoute_n_prog(n_prog *n);
void ajoute_l_instr(n_l_instr *n);
void ajoute_instr(n_instr *n);
void ajoute_instr_vide(n_instr *n);
void ajoute_instr_si(n_instr *n);
void ajoute_instr_tantque(n_instr *n);
void ajoute_instr_faire(n_instr *n);
void ajoute_instr_pour(n_instr *n);       /* MODIFIE POUR EVAL */
void ajoute_instr_affect(n_instr *n);
void ajoute_instr_appel(n_instr *n);
void ajoute_instr_retour(n_instr *n);
void ajoute_instr_ecrire(n_instr *n);
void ajoute_l_exp(n_l_exp *n);
int ajoute_exp(n_exp *n);
int ajoute_varExp(n_exp *n);
int ajoute_opExp(n_exp *n);
int ajoute_intExp(n_exp *n);
int ajoute_lireExp(n_exp *n);
void ajoute_appelExp(n_exp *n);
void ajoute_l_dec(n_l_dec *n);
void ajoute_dec(n_dec *n);
void ajoute_foncDec(n_dec *n);
void ajoute_varDec(n_dec *n);
void ajoute_tabDec(n_dec *n);
void ajoute_var(n_var *n);
void ajoute_var_simple(n_var *n);
void ajoute_var_indicee(n_var *n);
void ajoute_appel(n_appel *n);

void compteDecParam(n_l_dec* n);
void compteExpParam(n_l_exp* n);
void pop(int r);
void push(int r);
void entree(n_dec* reg);
void sortie();
void text();

int nbLocale;
int nbParam;
int etiquette = 0;
int flagRetour = 0;

/*-------------------------------------------------------------------------*/

void ajoute_n_prog(n_prog *n)
{
    printf("\t.data\n");
    ajoute_l_dec(n->variables);

    text();
    ajoute_l_dec(n->fonctions);

    if(rechercheExecutable("main") < 0)
    {
        erreur("fonction main introuvable");
    }
}

/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/

void ajoute_l_instr(n_l_instr *n)
{
  if(n)
  {
    ajoute_instr(n->tete);
    ajoute_l_instr(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

void ajoute_instr(n_instr *n)
{
  if(n)
  {
      if(n->type == blocInst)
          ajoute_l_instr(n->u.liste);
      else if(n->type == affecteInst)
          ajoute_instr_affect(n);
      else if(n->type == siInst)
          ajoute_instr_si(n);
      else if(n->type == tantqueInst)
          ajoute_instr_tantque(n);
      else if(n->type == faireInst)
          ajoute_instr_faire(n);
      else if(n->type == appelInst)
          ajoute_instr_appel(n);
      else if(n->type == retourInst)
          ajoute_instr_retour(n);
      else if(n->type == ecrireInst)
          ajoute_instr_ecrire(n);
      else if(n->type == videInst)
          ajoute_instr_vide(n);
  }
}

/*-------------------------------------------------------------------------*/

void ajoute_instr_si(n_instr *n)
{
    int deb, fin;

    deb = etiquette;
    etiquette++;
    fin = etiquette;
    etiquette++;

    ajoute_exp(n->u.si_.test);
    pop(1);
    printf("\tbeq\t$t1, $zero, i_e%d\n", deb);
    ajoute_instr(n->u.si_.alors);

    if(n->u.si_.sinon)
    {
        printf("\tj\ti_e%d\n", fin);
    }

    printf("i_e%d:\n", deb);

    if(n->u.si_.sinon)
    {
        ajoute_instr(n->u.si_.sinon);
        printf("i_e%d:\n", fin);
    }
}

/*-------------------------------------------------------------------------*/

void ajoute_instr_tantque(n_instr *n)
{
    int deb, fin;

    deb = etiquette;
    etiquette++;
    fin = etiquette;
    etiquette++;

    printf("i_e%d:\n", deb);
    ajoute_exp(n->u.tantque_.test);
    pop(1);

    printf("\tbeq\t$t1, $zero, i_e%d\n", fin);

    ajoute_instr(n->u.tantque_.faire);

    printf("\tj\ti_e%d\n", deb);
    printf("i_e%d:\n", fin);
}

/*-------------------------------------------------------------------------*/

void ajoute_instr_faire(n_instr *n)
{
    int etiq;

    etiq = etiquette;
    etiquette++;

    printf("i_e%d:\n", etiq);
    ajoute_instr(n->u.faire_.faire);
    ajoute_exp(n->u.faire_.test);

    pop(1);
    printf("\tbne\t$t1, $zero, i_e%d\n", etiq);
}

/*-------------------------------------------------------------------------*/

void ajoute_instr_affect(n_instr *n)
{
    int ligne, adr, tmp, nbARG;

    if((ligne = rechercheExecutable(n->u.affecte_.var->nom)) < 0)
    {
        printf("ERREUR : variable %s non déclarée\n", n->u.affecte_.var->nom);
        exit(1);
    }

    ajoute_var(n->u.affecte_.var);
    ajoute_exp(n->u.affecte_.exp);

    if(n->u.affecte_.var->type == indicee)
    {
        pop(1);
        pop(0);
        printf("\tadd\t$t0, $t0, $t0\n");
        printf("\tadd\t$t0, $t0, $t0\n");
        printf("\tsw\t$t1, v%s($t0)\n", n->u.affecte_.var->nom);
    }
    else
    {
        if(tabsymboles.tab[ligne].portee == P_VARIABLE_GLOBALE)
        {
            pop(1);
            printf("\tsw\t$t1, v%s\n", n->u.affecte_.var->nom);
        }
        if(tabsymboles.tab[ligne].portee == P_VARIABLE_LOCALE)
        {
            pop(1);
            adr = 8 + tabsymboles.tab[ligne].adresse    ;
            printf("\tsw\t$t1, -%d($fp)\n", adr);
        }
        if(tabsymboles.tab[ligne].portee == P_ARGUMENT)
        {
            pop(1);
            tmp = ligne;
            while(tabsymboles.tab[tmp].type != T_FONCTION)
            {
                tmp--;
            }
            /*nbARG = tabsymboles.tab[tmp].complement;
            adr = 4 * (nbARG - (tabsymboles.tab[ligne].adresse/4)) ;*/
            adr = 4 + tabsymboles.tab[tmp].adresse;
            printf("\tsw\t$t1, %d($fp)\n", adr);
        }
    }
}

/*-------------------------------------------------------------------------*/

void ajoute_instr_appel(n_instr *n)
{
    ajoute_appel(n->u.appel);
    printf("\taddi\t$sp, $sp, 4\t\t#ignore valeur de retour\n");
}
/*-------------------------------------------------------------------------*/

void ajoute_appel(n_appel *n)
{
    int l;
    int tmp = nbParam;

    if((l = rechercheExecutable(n->fonction)) < 0)
    {
        printf("ERREUR : fonction %s inconnue\n", n->fonction);
        exit(1);
    }

    nbParam = 0;
    compteExpParam(n->args);

    if(tabsymboles.tab[l].complement != nbParam)
    {
        printf("ERREUR : nombre de parametres incorrect pour la fonction %s\n", n->fonction);
        exit(1);
    }

    printf("\tsubi\t$sp, $sp, 4\n");

    ajoute_l_exp(n->args);

    printf("\tjal\tf_%s\n", n->fonction);
    printf("\taddi\t$sp, $sp, %d\n", 4 * nbParam);

    nbParam = tmp;
}

/*-------------------------------------------------------------------------*/

void ajoute_instr_retour(n_instr *n)
{
    ajoute_exp(n->u.retour_.expression);

    pop(1);
    printf("\tsw\t$t1, %d($fp)\n", (nbParam + 1) * 4);
    if(nbLocale > 0)
    {
        printf("\taddi\t$sp, $sp, %d\t\t#desallocation locales\n", 4*nbLocale);
    }
    sortie();
    flagRetour = 1;
}

/*-------------------------------------------------------------------------*/

void ajoute_instr_ecrire(n_instr *n)
{
    ajoute_exp(n->u.ecrire_.expression);
    pop(0);
    printf("\tmove\t$a0, $t0\n");
    printf("\tli\t$v0, 1\n");
    printf("\tsyscall\n");
    printf("\tli\t$a0, \'\\n\'\n");
    printf("\tli\t$v0, 11\n");
    printf("\tsyscall\n");
}

/*-------------------------------------------------------------------------*/

void ajoute_instr_vide(n_instr *n)
{

}

/*-------------------------------------------------------------------------*/

void ajoute_l_exp(n_l_exp *n)
{
  if(n)
  {
    ajoute_exp(n->tete);
    ajoute_l_exp(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

int ajoute_exp(n_exp *n)
{
    if(n->type == varExp)
        return ajoute_varExp(n);
    else if(n->type == opExp)
        return ajoute_opExp(n);
    else if(n->type == intExp)
        return ajoute_intExp(n);
    else if(n->type == appelExp)
        ajoute_appelExp(n);
    else if(n->type == lireExp)
        return ajoute_lireExp(n);

    return 0;
}

/*-------------------------------------------------------------------------*/

int ajoute_varExp(n_exp *n)
{
    int ligne, adr, tmp, nbARG;

    if((ligne = rechercheExecutable(n->u.var->nom)) < 0)
    {
        printf("ERREUR : variable %s non declaree\n", n->u.var->nom);
        exit(1);
    }

    ajoute_var(n->u.var);

    if(n->u.var->type == indicee)
    {
        pop(0);
        printf("\tadd\t$t0, $t0, $t0\n");
        printf("\tadd\t$t0, $t0, $t0\n");
        printf("\tlw\t$t1, v%s($t0)\n", n->u.var->nom);
        push(1);
    }
    else
    {
        if(tabsymboles.tab[ligne].portee == P_VARIABLE_GLOBALE)
        {
            printf("\tlw\t$t0, v%s\n", n->u.var->nom);
            push(0);
        }
        if(tabsymboles.tab[ligne].portee == P_VARIABLE_LOCALE)
        {
            adr = 8 + tabsymboles.tab[ligne].adresse    ;
            printf("\tlw\t$t0, -%d($fp)\n", adr);
            push(0);
        }
        if(tabsymboles.tab[ligne].portee == P_ARGUMENT)
        {
            tmp = ligne;
            while(tabsymboles.tab[tmp].type != T_FONCTION)
            {
                tmp--;
            }
            nbARG = tabsymboles.tab[tmp].complement;
            adr = 4 * (nbARG - (tabsymboles.tab[ligne].adresse/4)) ;
            printf("\tlw\t$t0, %d($fp)\n", adr);
            push(0);
        }
    }
    return 1;
}

/*-------------------------------------------------------------------------*/
int ajoute_opExp(n_exp *n)
{
  int tmp;



    switch(n->u.opExp_.op)
    {
        /*case negatif:
            ajoute_exp(n->u.opExp_.op1)
            pop(1);
            printf("\tli\t$t2, -1\n");
            printf("\tmultu\t$t1, $t2\n");
            printf("\tmflo\t$t0\n");
            push(0);
            break;*/
        case plus:
            ajoute_exp(n->u.opExp_.op1);
            ajoute_exp(n->u.opExp_.op2);
            pop(2);
            pop(1);
            printf("\tadd\t$t0, $t1, $t2\n");
            push(0);
            break;
        case moins:

            ajoute_exp(n->u.opExp_.op1);
            ajoute_exp(n->u.opExp_.op2);
            pop(2);
            pop(1);
            printf("\tsub\t$t0, $t1, $t2\n");
            push(0);
            break;
        case fois:

            ajoute_exp(n->u.opExp_.op1);
            ajoute_exp(n->u.opExp_.op2);
            pop(2);
            pop(1);
            printf("\tmult\t$t1, $t2\n");
            printf("\tmflo\t$t0\n");
            push(0);
            break;
        case divise:

            ajoute_exp(n->u.opExp_.op1);
            ajoute_exp(n->u.opExp_.op2);
            pop(2);
            pop(1);
            printf("\tdiv\t$t1, $t2\n");
            printf("\tmflo\t$t0\n");
            push(0);
            break;
        case modulo:
            ajoute_exp(n->u.opExp_.op1);
            ajoute_exp(n->u.opExp_.op2);
            pop(2);
            pop(1);
            printf("\tdiv\t$t1, $t2\n");
            printf("\tmfhi\t$t0\n");
            push(0);
            break;
        case et:
            tmp = etiquette;
            etiquette++;
            ajoute_exp(n->u.opExp_.op1);
            pop(1);

            printf("\tbeq $t%d, $0, i_e%d\n",1,tmp);

            ajoute_exp(n->u.opExp_.op2);
            pop(2);
            printf("i_e%d:",tmp);

            push(0);
            break;
        case ou:
            tmp = etiquette;
            etiquette++;
            ajoute_exp(n->u.opExp_.op1);
            pop(1);
            printf("\tbne $t%d, $0, i_e%d\n",1,tmp);


            ajoute_exp(n->u.opExp_.op2);
            pop(2);
            printf("i_e%d:",tmp);
            push(0);
            break;
        case non:
            ajoute_exp(n->u.opExp_.op1);
            pop(1);
            printf("\tli\t$t0, 0");
            printf("\tbeq\t$t1, $zero, i_e%d\n", etiquette);
            printf("\tli\t$t0, 1\n");
            printf("i_e%d:\n", etiquette);
            etiquette++;
            push(0);
            break;
        case inf:
            ajoute_exp(n->u.opExp_.op1);
            ajoute_exp(n->u.opExp_.op2);
            pop(2);
            pop(1);
            printf("\tli\t$t0, -1\n");
            printf("\tblt\t$t1, $t2, i_e%d\n", etiquette);
            printf("\tli\t$t0, 0\n");
            printf("i_e%d:\n", etiquette);
            etiquette++;
            push(0);
            break;
        case sup:
            ajoute_exp(n->u.opExp_.op1);
            ajoute_exp(n->u.opExp_.op2);
            pop(2);
            pop(1);
            printf("\tli\t$t0, -1\n");
            printf("\tbgt\t$t1, $t2, i_e%d\n", etiquette);
            printf("\tli\t$t0, 0\n");
            printf("i_e%d:\n", etiquette);
            etiquette++;
            push(0);
            break;
        case infeg:
            ajoute_exp(n->u.opExp_.op1);
            ajoute_exp(n->u.opExp_.op2);
            pop(2);
            pop(1);
            printf("\tli\t$t0, -1\n");
            printf("\tble\t$t1, $t2, i_e%d\n", etiquette);
            printf("\tli\t$t0, 0\n");
            printf("i_e%d:\n", etiquette);
            etiquette++;
            push(0);
            break;
        case supeg:
            ajoute_exp(n->u.opExp_.op1);
            ajoute_exp(n->u.opExp_.op2);
            pop(2);
            pop(1);
            printf("\tli\t$t0, -1\n");
            printf("\tbge\t$t1, $t2, i_e%d\n", etiquette);
            printf("\tli\t$t0, 0\n");
            printf("i_e%d:\n", etiquette);
            etiquette++;
            push(0);
            break;
        case egal:
            ajoute_exp(n->u.opExp_.op1);
            ajoute_exp(n->u.opExp_.op2);
            pop(2);
            pop(1);
            printf("\tli\t$t0, -1\n");
            printf("\tbeq\t$t1, $t2, i_e%d\n", etiquette);
            printf("\tli\t$t0, 0\n");
            printf("i_e%d:\n", etiquette);
            etiquette++;
            push(0);
            break;
        case diff:
            ajoute_exp(n->u.opExp_.op1);
            ajoute_exp(n->u.opExp_.op2);
            pop(2);
            pop(1);
            printf("\tli\t$t0, -1\n");
            printf("\tbne\t$t1, $t2, i_e%d\n", etiquette);
            printf("\tli\t$t0, 0\n");
            printf("i_e%d:\n", etiquette);
            etiquette++;
            push(0);
            break;
    }
    return 0;
}

/*-------------------------------------------------------------------------*/

int ajoute_intExp(n_exp *n)
{
    printf("\tli\t$t0, %d\n", n->u.entier);
    push(0);
    return 0;
}

/*-------------------------------------------------------------------------*/
int ajoute_lireExp(n_exp *n)
{
    printf("\tli\t$v0, 5\n");
    printf("\tsyscall\n");
    printf("\tmove\t$t0, $v0\n");
    push(0);
    return 0;
}

/*-------------------------------------------------------------------------*/

void ajoute_appelExp(n_exp *n)
{
  ajoute_appel(n->u.appel);
}

/*-------------------------------------------------------------------------*/

void ajoute_l_dec(n_l_dec *n)
{
  if( n )
  {
    ajoute_dec(n->tete);
    ajoute_l_dec(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

void ajoute_dec(n_dec *n)
{
  if(n)
  {
    if(n->type == foncDec)
    {
      ajoute_foncDec(n);
    }
    else if(n->type == varDec)
    {
      ajoute_varDec(n);
    }
    else if(n->type == tabDec)
    {
      ajoute_tabDec(n);
    }
  }
}

/*-------------------------------------------------------------------------*/

void ajoute_foncDec(n_dec *n)
{
    int ligne;
    nbParam = 0;
    nbLocale = 0;

    if((ligne = rechercheDeclarative(n->nom)) >= 0)
    {
		printf("ERREUR : redeclaration de la variable %s\n",n->nom);
        printf("NOTE : premiere declaration ligne %d de la table\n", ligne);
		exit(-1);
	}

    compteDecParam(n->u.foncDec_.param);
    ajouteIdentificateur(n->nom, P_VARIABLE_GLOBALE, T_FONCTION, 0, nbParam);

    entreeFonction();
    entree(n);
    portee = P_ARGUMENT;

    ajoute_l_dec(n->u.foncDec_.param);

    portee = P_VARIABLE_LOCALE;

    ajoute_l_dec(n->u.foncDec_.variables);

    if(nbLocale > 0)
    {
        printf("\tsubi\t$sp, $sp, %d\t\t#allocation locales\n", 4*nbLocale);
    }

    ajoute_instr(n->u.foncDec_.corps);

    if(nbLocale > 0)
    {
        printf("\taddi\t$sp, $sp, %d\t\t#desallocation locales\n", 4*nbLocale);
    }

    tabsymboles.tab[ligne].retour = flagRetour;
    flagRetour = 0;

    sortie();
    sortieFonction();
}

/*-------------------------------------------------------------------------*/

void ajoute_varDec(n_dec *n)
{
    int l;

    if((l = rechercheDeclarative(n->nom)) >= 0)
    {
		printf("ERREUR : redeclaration de la variable %s\n",n->nom);
        printf("NOTE : premiere declaration ligne %d de la table\n", l);
		exit(-1);
	}

   if(portee == P_VARIABLE_GLOBALE)
   {
		ajouteIdentificateur(n->nom, portee, T_ENTIER, adresseGlobaleCourante, 1);
		adresseGlobaleCourante += 4;

        printf("v%s:\t.word\t4\n", n->nom);

		return;
	}
	if(portee == P_VARIABLE_LOCALE)
    {
		ajouteIdentificateur(n->nom, portee, T_ENTIER, adresseLocaleCourante, 1);
		adresseLocaleCourante += 4;
        nbLocale++;

		return;
	}
	else
    {
		ajouteIdentificateur(n->nom, portee, T_ENTIER, adresseArgumentCourant, 1);
		adresseArgumentCourant += 4;


		return;
	}
}

/*-------------------------------------------------------------------------*/

void ajoute_tabDec(n_dec *n)
{
    int l;

    if((l = rechercheDeclarative(n->nom)) >= 0)
    {
		printf("ERREUR : redeclaration de la variable %s\n",n->nom);
        printf("NOTE : premiere declaration ligne %d de la table\n", l);
		exit(-1);
	}

	if(portee == P_VARIABLE_GLOBALE)
    {
		ajouteIdentificateur(n->nom, portee, T_TABLEAU_ENTIER, adresseGlobaleCourante, n->u.tabDec_.taille);
		adresseGlobaleCourante += (n->u.tabDec_.taille*4);

        printf("v%s:\t.space\t%d\n", n->nom, n->u.tabDec_.taille*4);

		return;
	}
	else
    {
		printf("ERREUR : tableau locaux interdit : %s\n", n->nom);
		exit(-1);
	}
}

/*-------------------------------------------------------------------------*/

void ajoute_var(n_var *n)
{
    if(n->type == simple)
    {
        ajoute_var_simple(n);
    }
    else if(n->type == indicee)
    {
        ajoute_var_indicee(n);
    }
}

/*-------------------------------------------------------------------------*/

void ajoute_var_simple(n_var *n)
{
    int l = rechercheExecutable(n->nom);

    if(tabsymboles.tab[l].type != T_ENTIER)
    {
        printf("ERREUR : mauvais type de la variable %s\n", n->nom);
        exit(1);
    }
}

/*-------------------------------------------------------------------------*/

void ajoute_var_indicee(n_var *n)
{
    int l = rechercheExecutable(n->nom);

    if(tabsymboles.tab[l].type != T_TABLEAU_ENTIER)
    {
        printf("ERREUR : mauvais type de la variable %s\n", n->nom);
        exit(1);
    }

    ajoute_exp( n->u.indicee_.indice );
}

/*-------------------------------------------------------------------------*/


void compteDecParam(n_l_dec* n)
{
    if(n){

		    nbParam++;
		      compteDecParam(n->queue);
	  }
}

/*-------------------------------------------------------------------------*/

void compteExpParam(n_l_exp* n)
{
    if(n)
    {
		nbParam++;
		compteExpParam(n->queue);
	}
}

/*--------------------------------------------------------------------------*/

void push(int reg)
{
    printf("\tsubu\t$sp, $sp, 4\t\t#empile\n");
    printf("\tsw\t$t%d, 0($sp)\t\t#\n", reg);
}

/*--------------------------------------------------------------------------*/

void pop(int reg)
{
    printf("\tlw\t$t%d, 0($sp)\t\t#depile\n", reg);
    printf("\taddu\t$sp, $sp, 4\t\t#\n");
}

/*--------------------------------------------------------------------------*/

void entree(n_dec* n)
{
    printf("f_%s:\n", n->nom);
    printf("\tsubi\t$sp, $sp, 4\n");
    printf("\tsw\t$fp, 0($sp)\n");
    printf("\tmove\t$fp, $sp\n");
    printf("\tsubi\t$sp, $sp, 4\n");
    printf("\tsw\t$ra, 0($sp)\t\t# entree\n");
}

/*--------------------------------------------------------------------------*/

void sortie()
{
    printf("\tlw\t$ra, 0($sp)\t\t# sortie\n");
    printf("\taddi\t$sp, $sp, 4\n");
    printf("\tlw\t$fp, 0($sp)\n");
    printf("\taddi\t$sp, $sp, 4\n");
    printf("\tjr\t$ra\n");
}

/*--------------------------------------------------------------------------*/

void text()
{
    printf("\n\t.text\n");
	printf("__start:\n");
	printf("\tjal \tf_main\n");
	printf("\tli \t$v0, 10\n");
	printf("\tsyscall\n");
}
