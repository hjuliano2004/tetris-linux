#ifndef CENARIO_H
#define CENARIO_H
#include <stdint.h>

extern int padrao;
extern int x;
extern int y;

typedef struct{
    int x;
    int y;
    int valido;
}Posicao;

typedef struct{
    Posicao **posicoes;
    int size;
    int length;
}ListaPosicao;

extern ListaPosicao *torre;
extern ListaPosicao *peca;

void draw(uint32_t *pixel, int i, Posicao *posicao);
//void drawList(uint32_t *pixel, int p);
void drawList(uint32_t *pixel, int p, ListaPosicao *lista);
//void grade(uint32_t *pixel, int i);
void grade(Janela *janela, int i);
Posicao *new_Posicao(int x, int y);
Posicao *delPosicao(Posicao *posicao);
ListaPosicao *new_ListaPosicao(int numero);
ListaPosicao *delListaPosicao(ListaPosicao *lista);
ListaPosicao *addPosicao(ListaPosicao *lista, Posicao *posicao);
ListaPosicao *new_Peca();
ListaPosicao *addPeca(ListaPosicao *peca, ListaPosicao *lista);

#endif