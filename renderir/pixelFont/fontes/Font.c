#include "Font.h"
#include "../Escrita.h"
#include "alfabeto/Alfabeto.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

Bit *alfabeto[maximo] = {0};
int alfaLength = 0;//conta o tamanho do alfabeto atual

Bit *new_letra(char simbolo, uint8_t pixels[padrao][padrao]) {
    for (int i = 0; i < maximo; i++) {
        if (!alfabeto[i]) {

            Bit *bit = malloc(sizeof(Bit));
            if (!bit) {
                return NULL;
            }

            bit->pixels = malloc(padrao * sizeof(uint8_t *));
            if (!bit->pixels) {
                free(bit);
                return NULL;
            }

            for (int y = 0; y < padrao; y++) {
                bit->pixels[y] = malloc(padrao * sizeof(uint8_t));
                if (!bit->pixels[y]) {
                    for (int linha = 0; linha < y; linha++) {
                        free(bit->pixels[linha]);
                    }
                    free(bit->pixels);
                    free(bit);
                    return NULL;
                }
            }

            bit->simbolo = simbolo;
            for (int y = 0; y < padrao; y++) {
                for (int x = 0; x < padrao; x++) {
                    bit->pixels[y][x] = pixels[y][x];
                }
            }
            alfabeto[i] = bit;
            alfaLength++;
            return bit;
        }
    }
    return NULL;
}



void emprime(uint32_t *shm_buffer, char simbolo, int width, int x, int y, uint32_t color){
 iniciarAlfabeto();

    uint8_t **pixels = character(simbolo);

    for(int i=0;i<padrao;i++){
        for(int j =0;j<padrao;j++){
                if(pixels[i][j]){
                    shm_buffer[j + x + (i * width) + y * width] = color;
                }
        }
    }
}
