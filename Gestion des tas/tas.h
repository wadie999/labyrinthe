#ifndef TAS__H
#define TAS__H

#include <stdio.h>
#include <stdlib.h>

typedef struct tas
{
    int capacity;
    int taille;
    int* tab;
}tas_t;

#endif