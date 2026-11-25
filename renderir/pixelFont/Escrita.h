
#ifndef ESCRITA_H
#define ESCRITA_H

#include <stdint.h>

typedef struct {
    uint32_t **imagem;
    int width;
    int height;

}Quadro;

Quadro *new_Quadro(uint32_t *referencia, int width, int height);
uint32_t **lista2D(int width, int height);
void limpa2D(uint32_t **imagem, int height);
void limpaQuadro(Quadro *quadro);
void quadroLinha(Quadro *quadro, uint32_t *buffer);

void texto(uint32_t *shm_buffer, char *text, int width, int height, int x, int y, uint32_t color);


#endif