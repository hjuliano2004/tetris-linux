#ifndef RENDER_H
#define RENDER_H
#include "../janela/Janela.h"
#include "../tempo/Setts.h"

void branco(Janela *janela);
void gravidade();
void esquerda();
void direita();
void rotacao();
void rapido(SetTimer *time);
void vNormal(SetTimer *time);
void destroiInvalido();
void pilha();
void linhaFechada();

#endif