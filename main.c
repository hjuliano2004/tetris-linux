#include "janela/Janela.h"
#include "janela/wayland/cbk.h"
#include "cenario/Cenario.h"
#include "renderir/Render.h"
#include "cenario/modelos/Modelos.h"
#include <stdlib.h>
#include <time.h>
#include "tempo/Setts.h"
#include <stdio.h>
#include <stddef.h>

int tamanho = 15;
int QA= 10 * 20;//quantidade de quandrados em tela(quantidade calculada manualmente)

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

int main(){

    /*primeiro abre a janela*/
    Janela *janela = new_Janela("Tetris");

    padrao = ((janela->novoHeight / 20)); //* 3) / 10; //calcula o tamanho do padrão

    sWayland *wayland = new_Wayland(); 
    new_Nos(janela, wayland);



    srand((unsigned)time(NULL));//cria semente baseada no tempo atual

    torre = new_ListaPosicao(QA);
    peca  = new_Peca();

    branco(janela);

    setInterval(gravidade, janela, 0.5);

    while(janela->aberto){
        wl_display_dispatch(wayland->display);
        //branco(janela);

        if (janela->buffer && janela->buffer_liberado && janela->frame_pronto) {
            janela->redraw_requested = 1;
            attJanela(janela->nos);
        }

        rodar();

    }

    delJanela(janela);
    deslWayland(wayland);

    
    return 0;
}