#ifndef __SYNTABS__
#define __SYNTABS__

typedef struct n_l_instr_ n_l_instr;
typedef struct n_instr_ n_instr;
typedef struct n_exp_ n_exp;
typedef struct n_l_exp_ n_l_exp;
typedef struct n_var_ n_var;
typedef struct n_l_dec_ n_l_dec;
typedef struct n_dec_ n_dec;
typedef struct n_prog_ n_prog;
typedef struct n_appel_ n_appel;

/*-------------------------------------------------------------------------*/
struct n_prog_ {
  n_l_dec *variables;
  n_l_dec *fonctions;
};

n_prog *cree_n_prog(n_l_dec *variables, n_l_dec *fonctions);
/*-------------------------------------------------------------------------*/

struct n_dec_ {
  enum{foncDec, varDec, tabDec} type;
  char *nom;
  union {
    struct{n_l_dec *param; n_l_dec *variables; n_instr *corps;}foncDec_;
    struct{int type;}varDec_;
    struct{int taille;}tabDec_;
  } u;
};

n_dec *cree_n_dec_var(char *nom);
n_dec *cree_n_dec_tab(char *nom, int taille);
n_dec *cree_n_dec_fonc(char *nom, n_l_dec *param, n_l_dec *variables, n_instr *corps);

/*-------------------------------------------------------------------------*/

typedef enum {plus, moins, fois, divise, modulo, egal, diff, inf, sup, infeg, supeg, ou, et, non, negatif} operation; 

/* typedef enum {plus, moins, fois, divise, egal, diff, inf, infeg, ou, et, variable, entier} operation; */
struct n_exp_ {
  enum{varExp, opExp, intExp, appelExp, lireExp} type; /*, incrExp*/
  union{
    struct{operation op; struct n_exp_ *op1; struct n_exp_ *op2;} opExp_;
    /* n_var *incr; */
    n_var *var;
    int entier;
    n_appel *appel;
  }u;
};

n_exp *cree_n_exp_op(operation type, n_exp *op1, n_exp *op2);
n_exp *cree_n_exp_entier(int entier);
n_exp *cree_n_exp_var(n_var *var);
n_exp *cree_n_exp_appel(n_appel *app);
n_exp *cree_n_exp_lire(void);
n_exp *cree_n_exp_incr(n_var *var);

/*-------------------------------------------------------------------------*/

struct n_instr_ {
  enum {incrInst, affecteInst, siInst, faireInst, tantqueInst, appelInst, retourInst, ecrireInst, videInst, blocInst, pourInst} type;
  union{
    n_exp *incr;
    struct{n_exp *test; struct n_instr_ *alors; struct n_instr_ *sinon;} si_;
    struct{n_exp *test; struct n_instr_ *faire;} tantque_;
    struct{n_exp *test; struct n_instr_ *faire;} faire_;
    n_appel *appel;
    struct{n_var *var; n_exp *exp;} affecte_;
    struct{n_exp *expression;} retour_;
    struct{n_exp *expression;} ecrire_;
    n_l_instr *liste;
  }u;
};

n_instr *cree_n_instr_incr(n_exp *incr);
n_instr *cree_n_instr_si(n_exp *test, n_instr *alors, n_instr *sinon);
n_instr *cree_n_instr_bloc(n_l_instr *liste);
n_instr *cree_n_instr_tantque(n_exp *test, n_instr *faire);
n_instr *cree_n_instr_faire(n_instr *faire, n_exp *test);
n_instr *cree_n_instr_affect(n_var *var, n_exp *exp);
n_instr *cree_n_instr_appel(n_appel *appel);
n_instr *cree_n_instr_retour(n_exp *expression);
n_instr *cree_n_instr_ecrire(n_exp *expression);
n_instr *cree_n_instr_vide(void);



/*-------------------------------------------------------------------------*/
struct n_appel_{
  char *fonction; 
  n_l_exp *args;
};

n_appel *cree_n_appel(char *fonction, n_l_exp *args);

/*-------------------------------------------------------------------------*/
struct n_var_ {
  enum {simple, indicee} type;
  char *nom;
  union {
    struct{n_exp *indice;} indicee_;
  }u;
};

n_var *cree_n_var_simple(char *nom);
n_var *cree_n_var_indicee(char *nom, n_exp *indice);

/*-------------------------------------------------------------------------*/
struct n_l_exp_ {
  n_exp *tete;
  struct n_l_exp_ *queue;
};

n_l_exp *cree_n_l_exp(n_exp *tete, n_l_exp *queue);

/*-------------------------------------------------------------------------*/
struct n_l_instr_ {
  n_instr *tete;
  struct n_l_instr_ *queue;
};

n_l_instr *cree_n_l_instr(n_instr *tete, n_l_instr *queue);

/*-------------------------------------------------------------------------*/

struct n_l_dec_{
  n_dec *tete;
  struct n_l_dec_ *queue;
};

n_l_dec *cree_n_l_dec(n_dec *tete, n_l_dec *queue);
/*-------------------------------------------------------------------------*/

#endif
