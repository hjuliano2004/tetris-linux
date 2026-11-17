#include "janela/Janela.h"
#include "janela/wayland/cbk.h"
#include "cenario/Cenario.h"
#include "renderir/Render.h"
#include "cenario/modelos/Modelos.h"
#include <stdlib.h>
#include <time.h>

int tamanho = 15;
int QA= 480;//quantidade de quandrados em tela(quantidade calculada manualmente)

int main(){

    /*primeiro abre a janela*/
    Janela *janela = new_Janela("Tetris");

    padrao = ((janela->novoWidth / 4) * 3) / 10; //calcula o tamanho do padrão

    janela->novoHeight = (int)janela->novoWidth * 1.2;

    sWayland *wayland = new_Wayland(); 
    new_Nos(janela, wayland);



    srand((unsigned)time(NULL));//cria semente baseada no tempo atual

    torre = new_ListaPosicao(QA);
    peca  = new_Peca();

    branco(janela);


    while(janela->aberto){
        wl_display_dispatch(wayland->display);
        //branco(janela);

        if (janela->buffer && janela->buffer_liberado && janela->frame_pronto) {
            janela->redraw_requested = 1;
            attJanela(janela->nos);
        }

    }

    delJanela(janela);
    deslWayland(wayland);

    
    return 0;
}