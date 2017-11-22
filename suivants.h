#ifndef __SUIVANTS__
#define __SUIVANTS__

#include"symboles.h"

int suivants[NB_NON_TERMINAUX+1][NB_TERMINAUX+1];

void initialise_suivants(void);
int est_suivant(int non_terminal, int terminal);

#endif
