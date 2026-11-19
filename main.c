#include "janela/Janela.h"
#include "janela/wayland/cbk.h"
#include "cenario/Cenario.h"
#include "renderir/Render.h"
//#include "cenario/modelos/Modelos.h"
#include <stdlib.h>
#include <time.h>
#include "tempo/Setts.h"
//#include <stdio.h>
#include <stddef.h>

int tamanho = 15;
int QA= 10 * 20;//quantidade de quandrados em tela(quantidade calculada manualmente)




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

        switch (action){
        case ACTION_MOVE_RIGHT:
            direita();
            break;
        case ACTION_MOVE_LEFT:
            esquerda();
            break;
        case ACTION_FAST:

            break;
        case ACTION_ROTATE:
            rotacao();
            break;
        case OUT:
            janela->aberto = false;
        break;
        }


        rodar();
    }

    delJanela(janela);
    deslWayland(wayland);

    
    return 0;
}