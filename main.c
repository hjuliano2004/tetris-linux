#include "janela/Janela.h"
#include "janela/wayland/cbk.h"
#include "cenario/Cenario.h"
#include "renderir/Render.h"
#include <stdlib.h>
#include <time.h>
#include "tempo/Setts.h"
#include <stddef.h>
#include <stdbool.h>
#include "cenario/modelos/Modelos.h"

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

    SetTimer *timer = setInterval(gravidade, 0, 0.5);

    bool pause = false;

    

    while(janela->aberto){
        wl_display_dispatch(wayland->display);
        //branco(janela);
        if (janela->buffer && janela->buffer_liberado && janela->frame_pronto) {
            janela->redraw_requested = 1;
            attJanela(janela->nos);
        }

        switch (action){
        case ACTION_PAUSE:
            pause = !pause;
            action = ACTION_NONE;
            

            if(pause){
                c1 = c1 + c1 * 2;
            }else{
                c2 = c1 / 2;
            }

            break;
        case OUT:
            janela->aberto = false;
        break;
        
        default:
            break;
        }

        if(pause){
            continue;
        }

        switch (action){
        case ACTION_NONE:
            break;
        case ACTION_MOVE_RIGHT:
            direita();
            break;
        case ACTION_MOVE_LEFT:
            esquerda();
            break;
        case ACTION_FAST:
            rapido(timer);
            break;
        case ACTION_NORMAL:
            vNormal(timer);
            break;
        case ACTION_ROTATE:
            rotacaoPeca();
            break;
        
        case ACTION_PAUSE:
        case OUT:
        break;
        }


        rodar();
    }

    delJanela(janela);
    deslWayland(wayland);

    
    return 0;
}


