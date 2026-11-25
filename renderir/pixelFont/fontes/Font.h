#ifndef FONT_H
#define FONT_H

#include <stdint.h>


#define padrao 9  //tamanho padrap da fonte
#define maximo 256
//#define X 0
//#define o 0xFF000000


typedef struct {
    uint8_t **pixels;
    char simbolo;
}Bit;

extern Bit *alfabeto[];
extern int alfaLength;//conta o tamanho do alfabeto atual

void emprime(uint32_t *shm_buffer, char simbolo, int width, int x, int y, uint32_t color);

Bit *new_letra(char simbolo, uint8_t pixels[padrao][padrao]);

#endif