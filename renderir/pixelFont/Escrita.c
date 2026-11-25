#include "Escrita.h"
#include <stdio.h>
#include <stdlib.h>
#include "fontes/Font.h"



void limpa2D(uint32_t **imagem, int height) {//destroi lista de pixels 2D
    for (int i = 0; i < height; i++) {
        free(imagem[i]);   // libera cada linha
    }
    free(imagem);          // libera o vetor de ponteiros
    imagem = NULL;
}

uint32_t **lista2D(int width, int height) { //aloca memoria e cria lista 2D vazia com as proporçoes desejadas
    uint32_t **imagem = malloc(height * sizeof(uint32_t*));
    for (int i = 0; i < height; i++) {
        imagem[i] = malloc(width * sizeof(uint32_t));
    }
    return imagem;
}

void limpaQuadro(Quadro *quadro){
    limpa2D(quadro->imagem, quadro->height);
    free(quadro);
    quadro = NULL;
}


Quadro *new_Quadro(uint32_t *referencia, int width, int height) { //transforma a referencia em um quadro 2D com as proporçoes desejadas
    Quadro *quadro = calloc(1, sizeof(Quadro));
    quadro->width = width;
    quadro->height = height;

    quadro->imagem = lista2D(width, height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            quadro->imagem[i][j] = referencia[i * width + j];//passa cada pixel da referencia pra lista 2D
        }
    }
    return quadro;
}

void quadroLinha(Quadro *quadro, uint32_t *buffer) {
    for (int i = 0; i < quadro->height; i++) {
        for (int j = 0; j < quadro->width; j++) {
            buffer[i * quadro->width + j] = quadro->imagem[i][j];
        }
    }
}

void texto(uint32_t *shm_buffer, char *text, int width, int height, int x, int y, uint32_t color){
    int startX = x;
    int posX = x;
    int posY = y;

    for(int i=0;text[i]!= '\0';i++){
        if (posX >= (width - padrao)) {
            posX = startX;       // volta para o início da linha
            posY += padrao;      // desce uma linha
        }

        

        if(posY >= 0 && posY < height - padrao){
            emprime(shm_buffer, text[i], width, posX, posY, color);
        }

        posX += padrao;
    }

}