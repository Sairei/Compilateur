#include <stdio.h>
#include "syntabs.h"
#include "util.h"
#include "tab.h"

void ajoute_n_prog(n_prog *n);
void ajoute_l_instr(n_l_instr *n);
void ajoute_instr(n_instr *n);
void ajoute_instr_vide(n_instr *n);
void ajoute_instr_si(n_instr *n);
void ajoute_instr_tantque(n_instr *n);
void ajoute_instr_faire(n_instr *n);
void ajoute_instr_affect(n_instr *n);
void ajoute_instr_appel(n_instr *n);
void ajoute_instr_retour(n_instr *n);
void ajoute_instr_ecrire(n_instr *n);
void ajoute_l_exp(n_l_exp *n);
void ajoute_exp(n_exp *n);
void ajoute_varExp(n_exp *n);
void ajoute_opExp(n_exp *n);
void ajoute_intExp(n_exp *n);
void ajoute_lireExp(n_exp *n);
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

int nbParam;

/*-------------------------------------------------------------------------*/

void ajoute_n_prog(n_prog *n)
{
    ajoute_l_dec(n->variables);
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
  ajoute_exp(n->u.si_.test);
  ajoute_instr(n->u.si_.alors);
  if(n->u.si_.sinon)
  {
    ajoute_instr(n->u.si_.sinon);
  }
}

/*-------------------------------------------------------------------------*/

void ajoute_instr_tantque(n_instr *n)
{
  ajoute_exp(n->u.tantque_.test);
  ajoute_instr(n->u.tantque_.faire);
}

/*-------------------------------------------------------------------------*/

void ajoute_instr_faire(n_instr *n)
{
  ajoute_instr(n->u.faire_.faire);
  ajoute_exp(n->u.faire_.test);
}  

/*-------------------------------------------------------------------------*/

void ajoute_instr_affect(n_instr *n)
{
    int ligne;
    
    if((ligne = rechercheExecutable(n->u.affecte_.var->nom)) < 0)
    {
        printf("ERREUR : variable %s non déclarée\n", n->u.affecte_.var->nom);
        exit(1);
    }
    
    ajoute_var(n->u.affecte_.var);
    ajoute_exp(n->u.affecte_.exp);
}

/*-------------------------------------------------------------------------*/

void ajoute_instr_appel(n_instr *n)
{
  ajoute_appel(n->u.appel);
}
/*-------------------------------------------------------------------------*/

void ajoute_appel(n_appel *n)
{
    int l;
    
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
    
    ajoute_l_exp(n->args);
}

/*-------------------------------------------------------------------------*/

void ajoute_instr_retour(n_instr *n)
{
    ajoute_exp(n->u.retour_.expression);
}

/*-------------------------------------------------------------------------*/

void ajoute_instr_ecrire(n_instr *n)
{
  ajoute_exp(n->u.ecrire_.expression);
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

void ajoute_exp(n_exp *n)
{
  if(n->type == varExp) 
      ajoute_varExp(n);
  else if(n->type == opExp) 
      ajoute_opExp(n);
  else if(n->type == intExp) 
      ajoute_intExp(n);
  else if(n->type == appelExp) 
      ajoute_appelExp(n);
  else if(n->type == lireExp)
      ajoute_lireExp(n);
}

/*-------------------------------------------------------------------------*/

void ajoute_varExp(n_exp *n)
{
    int ligne;
    
    if((ligne = rechercheExecutable(n->u.var->nom)) < 0)
    {
        printf("ERREUR : variable %s non declaree\n", n->u.var->nom);
        exit(1);
    }
    
    ajoute_var(n->u.var);
}

/*-------------------------------------------------------------------------*/
void ajoute_opExp(n_exp *n)
{ 
  if( n->u.opExp_.op1 != NULL ) 
  {
    ajoute_exp(n->u.opExp_.op1);
  }
  if( n->u.opExp_.op2 != NULL ) 
  {
    ajoute_exp(n->u.opExp_.op2);
  }
}

/*-------------------------------------------------------------------------*/

void ajoute_intExp(n_exp *n)
{
    
}

/*-------------------------------------------------------------------------*/
void ajoute_lireExp(n_exp *n)
{
    
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
    
    if((ligne = rechercheDeclarative(n->nom)) >= 0)
    {
		printf("ERREUR : redeclaration de la variable %s\n",n->nom);
        printf("NOTE : premiere declaration ligne %d de la table\n", ligne);
		exit(-1);
	}
    
    compteDecParam(n->u.foncDec_.param);
    ajouteIdentificateur(n->nom, P_VARIABLE_GLOBALE, T_FONCTION, 0, nbParam);
    
    entreeFonction();
    portee = P_ARGUMENT;
    
    ajoute_l_dec(n->u.foncDec_.param);
    
    portee = P_VARIABLE_LOCALE;
    
    ajoute_l_dec(n->u.foncDec_.variables);    
    ajoute_instr(n->u.foncDec_.corps);
    
    afficheTabsymboles();
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

		return;
	}
	if(portee == P_VARIABLE_LOCALE)
    {
		ajouteIdentificateur(n->nom, portee, T_ENTIER, adresseLocaleCourante, 1);
		adresseLocaleCourante += 4;

		return;
	}
	else
    {
		ajouteIdentificateur(n->nom, portee, T_ENTIER, adresseArgumentCourant, 1);
		adresseArgumentCourant += 4;
		nbParam++;
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
    if(n)
    {
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