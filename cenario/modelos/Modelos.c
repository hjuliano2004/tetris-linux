#include "Modelos.h"
#include <stdlib.h>
#include <string.h>

#include <stdlib.h>

int barra[] = {0, 1, 0,
               0, 1, 0,
               0, 1, 0};

int engr[] = {0, 1, 0,
              1, 1, 1, 
              0, 0, 0};

int blk[] = {0, 1, 1, 
             0, 1, 1, 
             0, 0, 0};

int eze[] = {0, 0, 0,
             1, 1, 0,
             0, 1, 1};

int ese[] = {0, 0, 0,
             0, 1, 1,
             1, 1, 0};


int *pecas[] =  {barra, engr, blk, eze, ese};

static int sorteio(void) {
    int quantidade = sizeof pecas / sizeof pecas[0];
    return rand() % quantidade;
}


int *modelo(void){

    int num = sorteio();

    int *peca = malloc(sizeof blk);
    if(!peca){
        return NULL;
    }

    for(int i=0;i<9;i++){
        peca[i] = pecas[num][i];
    }
    return peca;
}