#ifndef ELEMENTOS_H_INCLUDED
#define ELEMENTOS_H_INCLUDED
#include <time.h>

#define LarguraElemento 20
#define AlturaElemento 20
#define LarguraMapa 27
#define AlturaMapa 11

#define AlturaTela 270
#define LarguraTela 540
#define numOpcoesMenu 5

#define MAXINIMIGOS 50
#define MAXCRIATURAS 50
#define MAXBOMBAS 3

typedef enum {

    MENU = -1,
    NOVO_JOGO = 0,
    SALVAR = 1,
    CARREGAR = 2,
    QUIT = 3,
    VOLTAR = 4,
    JOGANDO = 5
} ESTADO_JOGO;

typedef struct Personagem
{
    int posX, posY, pInicialX,pInicialY;
    int vida;
    int pontuacao;
    int nivel;

    int NPC;
    int direcao;
    int monstro;
}PERSONAGEM;

typedef struct Bomba
{
    clock_t tempo;
    clock_t texplosao;

    int posX;
    int posY;

}BOMBA;


#endif // ELEMENTOS_H_INCLUDED
