#ifndef __PREMIERS__
#define __PREMIERS__

#include"symboles.h"

int premiers[NB_NON_TERMINAUX+1][NB_TERMINAUX+1];

void initialise_premiers(void);
int est_premier(int non_terminal, int terminal);

#endif
