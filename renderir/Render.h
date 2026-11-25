#ifndef RENDER_H
#define RENDER_H
#include "../janela/Janela.h"
#include "../tempo/Setts.h"
#include "../cenario/Cenario.h"

extern int pontuacao;
void branco(Janela *janela);
void gravidade();
void esquerda();
void direita();
void rotacaoPeca();
ListaPosicao *rotacao(ListaPosicao *peca);
void rapido(SetTimer *time);
void vNormal(SetTimer *time);
void destroiInvalido();
void pilha();
void linhaFechada();

#endif