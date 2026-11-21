#include "Render.h"
#include "../janela/Janela.h"
#include "../cenario/Cenario.h"
#include "../janela/teclado/Teclado.h"
#include <stdlib.h>
#include "../tempo/Setts.h"
#include <stdbool.h>
#include "../cenario/Cenario.h"

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

void destroiInvalido(){//libera memoria dos quadrados transparentes da peça
    for (int i = 0; i < peca->length; i++) {
        Posicao *posicao = peca->posicoes[i];
        if (posicao && !posicao->valido) {
            free(posicao);
        }
    }
}

void pilha(){
    for(int i =0;i<9;i++){
        for(int j=0;j<torre->length;j++){

            if((peca->posicoes[i]->x == torre->posicoes[j]->x) && 
            (peca->posicoes[i]->y + 1 == torre->posicoes[j]->y) && peca->posicoes[i]->valido){

                if(!addPeca(peca, torre)){
                    fprintf(stderr, "pilha: não foi possível guardar a peça na torre\n");
                }

                destroiInvalido();
                peca = new_Peca();

                if(!peca){
                    fprintf(stderr, "pilha: não foi possível criar nova peça\n");
                }
                linhaFechada();
                return;

            }
        }
    }
}


void gravidade(){
    if (!peca || !peca->posicoes ||
        peca->length <= 0 || peca->length > peca->size) {
        printf("a peça está nula, não é possível aplicar gravidade\n");
        return;
    }

    int chegou_ao_chao = 0;
    for (int i = 0; i < peca->length; i++) {
        Posicao *posicao = peca->posicoes[i];
        if (posicao && posicao->valido && posicao->y >= 19) {
            chegou_ao_chao = 1;
            break;
        }
    }

    if (chegou_ao_chao) {
        if (!addPeca(peca, torre)) {
            fprintf(stderr, "gravidade: não foi possível guardar a peça na torre\n");
            return;
        }else{
            linhaFechada();
        }

        destroiInvalido();

        peca = new_Peca();
        if (!peca) {
            fprintf(stderr, "gravidade: peça guardada, mas não foi possível criar a próxima\n");
        }
        return;
    }


    pilha();

    for (int i = 0; i < peca->length; i++) {
        if (peca->posicoes[i]) {
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

static  bool colisao(int n){//verifica colisão da peça com as posições da torre horizontalmente
    for(int i=0;i<9;i++){
        for(int j=0;j<torre->length;j++){
            if((peca->posicoes[i]->x + n == torre->posicoes[j]->x)&&(peca->posicoes[i]->y == torre->posicoes[j]->y)
             && peca->posicoes[i]->valido){
                return true;
            }
        }
    }

    return false;
}


void direita(){
    if(!peca){return;}

    if(colParede(1) || colisao(1)){return;}

    for(int i=0;i<9;i++){
        peca->posicoes[i]->x++;
    }

    action = ACTION_NONE;
}
void esquerda(){
    if(!peca){return;}

    if(colParede(-1) || colisao(-1)){return;}

    for(int i=0;i<9;i++){
        peca->posicoes[i]->x--;
    }

    action = ACTION_NONE;
}


void vNormal(SetTimer *time){
    printf("normal executado\n");
        clearInterval(time);

        time = setInterval(gravidade, 0, 0.5);
    
        action = ACTION_NONE;
    }


void rapido(SetTimer *time){
    printf("rapido executado\n");
        clearInterval(time);

        time = setInterval(gravidade, 0, 0.1);
        gravidade();
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

static void passar(int n)
{
    for (int i = torre->length - 1; i >= 0; i--) {
        if (torre->posicoes[i] &&
            torre->posicoes[i]->y == n) {
            removePosicao(torre->posicoes[i], torre);
        }
    }
}


static bool colideEspera(Posicao **posicoes, int length){

    for(int i=0;i<length;i++){
        for(int j=0; j<torre->length;j++){
            if(posicoes[i]->y + 1 == torre->posicoes[j]->y || posicoes[i]->y + 1 == 19){
                return true;
            }
        }
    }

    return false;
}



void linhaFechada(void)
{
    if (!torre || !torre->posicoes || torre->length <= 0) {
        return;
    }

    bool linhaRemovida[20] = { false };

    int vertical[20] = { 0 };

    for (int i = 0; i < torre->length; i++) {
        Posicao *posicao = torre->posicoes[i];

        if (posicao && posicao->y >= 0 && posicao->y < 20) {
            vertical[posicao->y]++;
        }
    }

    for (int y = 0; y < 20; y++) {
        if (vertical[y] == 10) {
            linhaRemovida[y] = true;
        }
    }

    for (int y = 0; y < 20; y++) {
        if (linhaRemovida[y]) {
            passar(y);
        }
    }

    for (int i = 0; i < torre->length; i++) {
        Posicao *posicao = torre->posicoes[i];

        if (!posicao) {
            continue;
        }

        int linhasRemovidasAbaixo = 0;

        for (int y = posicao->y + 1; y < 20; y++) {
            if (linhaRemovida[y]) {
                linhasRemovidasAbaixo++;
            }
        }

        posicao->y += linhasRemovidasAbaixo;
    }
}