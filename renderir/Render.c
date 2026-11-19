#include "Render.h"
#include "../janela/Janela.h"
#include "../cenario/Cenario.h"
#include "../janela/teclado/Teclado.h"
#include <stdlib.h>

void branco(Janela *janela){
    if (!janela || !janela->pixl){return;}

    uint32_t *pixel = (uint32_t *)janela->shm_data;

    for (int i = 0; i < janela->height * janela->width; i++) {
        x = i % janela->width;
        y = i / janela->width;

        pixel[i] = GRAY;
        drawList(pixel, i, peca);
        drawList(pixel, i, torre);

        if(x <= padrao*10){
            grade(janela, i);
        }

    }

}



void gravidade(){
    if(!peca || !peca->posicoes ||
       peca->length <= 0 || peca->length > peca->size){
        printf("a peça está nula, não é possivel aplicar gravidade\n");
        return;
    }

    int chegou_ao_chao = 0;
    for(int i=0;i<peca->length;i++){
        Posicao *posicao = peca->posicoes[i];
        if(posicao && posicao->valido && posicao->y >= 19){
            chegou_ao_chao = 1;
            break;
        }
    }

    if(chegou_ao_chao){
        if(!addPeca(peca, torre)){
            fprintf(stderr, "gravidade: não foi possível guardar a peça na torre\n");
            return;
        }

        for(int i=0;i<peca->length;i++){
            Posicao *posicao = peca->posicoes[i];
            if(posicao && !posicao->valido){
                free(posicao);
            }
        
        }
        delListaPosicao(peca);
        peca = new_Peca();
        if(!peca){
            fprintf(stderr, "gravidade: peça guardada, mas não foi possível criar a próxima\n");
        }
        return;
    }

    
    for(int i=0;i<peca->length;i++){
        if(peca->posicoes[i]){
            peca->posicoes[i]->y++;
        }
    }
}

static int colParede(int deslocamento){
    if(!peca || !peca->posicoes){
        return 1;
    }

    for(int i=0;i<peca->length;i++){
        Posicao *posicao = peca->posicoes[i];
        if(posicao && posicao->valido &&
           (posicao->x + deslocamento < 0 || posicao->x + deslocamento > 9)){
            return 1;
        }
    }
    return 0;
}

void direita(){
    if(!peca){return;}

    if(colParede(1)){return;}

    for(int i=0;i<9;i++){
        peca->posicoes[i]->x++;
    }

    action = ACTION_NONE;
}
void esquerda(){
    if(!peca){return;}
    if(colParede(-1)){return;}
    for(int i=0;i<9;i++){
        peca->posicoes[i]->x--;
    }

    action = ACTION_NONE;
}

void rotacao(){

    if(!peca || !peca->posicoes){
        printf("não é possivel girar peça nula\n");
        return;
    }

    int p[9];

    p[0] = peca->posicoes[6]->valido;   p[1] = peca->posicoes[3]->valido;   p[2] = peca->posicoes[0]->valido;
    p[3] = peca->posicoes[7]->valido;   p[4] = peca->posicoes[4]->valido;   p[5] = peca->posicoes[1]->valido;
    p[6] = peca->posicoes[8]->valido;   p[7] = peca->posicoes[5]->valido;   p[8] = peca->posicoes[2]->valido;

    for(int i=0;i<9;i++){
       peca->posicoes[i]->valido = p[i];
    }

    action = ACTION_NONE;
}