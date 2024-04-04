#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

typedef struct nod
{
    int *intrari;
    int iesire;
    enum {
        AND,
        OR,
        NOT
    } tip_nod;
} *nod;

int** split_line_to_args(char *linie); 
int** node_to_out(nod t, int *nr_clauze,int *clauze_poarta);


#endif // UTILS_H
