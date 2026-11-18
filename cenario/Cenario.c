#include "../janela/Janela.h"
#include "Cenario.h"
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h> 
#include <stdio.h>
#include "modelos/Modelos.h"


int padrao = 50;
int x = 0;
int y = 0;

ListaPosicao *torre = NULL;
ListaPosicao *peca = NULL;


void draw(uint32_t *pixel, int i,  Posicao *posicao){
    if(!pixel || !posicao || !posicao->valido){return;}

    int left = posicao->x * padrao;
    int top = posicao->y * padrao;

    if (x >= left && x < left + padrao &&
        y >= top  && y < top  + padrao) {
        pixel[i] = WHITE;
    }
}

void drawList(uint32_t *pixel, int p, ListaPosicao *lista){

    if(!pixel || !lista || !lista->posicoes ||
       lista->length <= 0 || lista->length > lista->size){return;}

    for(int i=0;i<lista->length;i++){
        draw(pixel, p, lista->posicoes[i]);
    }
}

void grade(Janela *janela, int i){
    uint32_t *pixel = janela->shm_data;

    if((y % padrao == 0 || x % padrao == 0)){
        pixel[i] = BLACK;
    }
}


Posicao *new_Posicao(int x, int y){

    Posicao *p = malloc(sizeof(Posicao));
    if(!p){
        printf("não foi possivel reservar memoria pra posição de bloco\n");
        return NULL;
    }
    p->x = x;
    p->y = y;

    return p;
}

Posicao *delPosicao(Posicao *posicao){
    free(posicao);
    return posicao = NULL;
}

ListaPosicao *new_ListaPosicao(int numero){

    if(numero <= 0){
        return NULL;
    }

    ListaPosicao *lista = malloc(sizeof(ListaPosicao));

    if(!lista){
        printf("não foi possivel reservar memoria pra lista de posições/ etapa 1\n");
        return NULL;
    }

    lista->posicoes = calloc(numero, sizeof(Posicao *));

     if(!lista->posicoes){
        printf("não foi possivel reservar memoria pra lista de posições/ etapa 2\n");
        free(lista); 
        return NULL;
    }

    lista->size = numero;
    lista->length = 0;

    return lista;
}

ListaPosicao *new_Peca(){

    int *modelo_peca = modelo();
    if(!modelo_peca){
        printf("não foi possivel reservar memoria para copiar o modelo da peça\n");
        return NULL;
    }

    ListaPosicao *lista = new_ListaPosicao(9);
    if(!lista){
        free(modelo_peca);
        return NULL;
    }
        for(int i=0;i<9;i++){

            int coluna = i % 3;
            int linha = i / 3;
            Posicao *p = new_Posicao(5 + coluna, linha);
            if(!p){
                for(int j=0;j<lista->length;j++){
                    free(lista->posicoes[j]);
                }
                delListaPosicao(lista);
                free(modelo_peca);
                return NULL;
            }
            p->valido = modelo_peca[i];
            addPosicao(lista, p);
            
    }
    
    free(modelo_peca);//talvez seja necessário salvar o modelo de peça futuramente, por enquanto apenas apaga o modelo

    return lista;
}

ListaPosicao *delListaPosicao(ListaPosicao *lista){
    if (lista){
        free(lista->posicoes);
        free(lista);
    }
    return NULL;
}

ListaPosicao *addPosicao(ListaPosicao *lista, Posicao *posicao){

    lista->posicoes[lista->length] = posicao;
    lista->length++;

    return lista;
};

ListaPosicao *addPeca(ListaPosicao *peca, ListaPosicao *lista){//adiciona uma peça a uma lista
    if(!peca){
        printf("não é possivel adicionar peça nula\n");
        return NULL;
    }

    if(!lista){
        printf("não é possivel adicionar peça em uma lista nula\n");
        return NULL;
    }

    int quantidade = 0;
    for(int i=0;i<peca->length;i++){
        if(peca->posicoes[i] && peca->posicoes[i]->valido){
            quantidade++;
        }
    }

    if(lista->length + quantidade > lista->size){
        printf("\nlista muito cheia, não é possivel adicionar mais uma peça\n");
        return NULL;
    }

    for(int i=0;i<peca->length;i++){
        if(peca->posicoes[i] && peca->posicoes[i]->valido){
            lista->posicoes[lista->length] = peca->posicoes[i];
            lista->length++;
        }
    }

    return lista;

}