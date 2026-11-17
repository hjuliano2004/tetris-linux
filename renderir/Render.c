#include "Render.h"
#include "../janela/Janela.h"
#include "../cenario/Cenario.h"

void branco(Janela *janela){
    if (!janela || !janela->pixl){return;}

    uint32_t *pixel = (uint32_t *)janela->shm_data;

    for (int i = 0; i < janela->height * janela->width; i++) {
        x = i % janela->width;
        y = i / janela->width;

        pixel[i] = GRAY;
        drawList(pixel, i);

        if(x == (janela->width/4)*3){
            pixel[i] = BLACK;
        }
        if(x < (janela->width/4)*3){
            grade(janela, i);
        }



    }

}