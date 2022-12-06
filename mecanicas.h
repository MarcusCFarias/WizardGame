#ifndef MECANICAS_H_INCLUDED
#define MECANICAS_H_INCLUDED

#include "elementos.h"

int podeMover(PERSONAGEM p, char mapa[][LarguraMapa], int movX, int movY);

int escolheDirecao (PERSONAGEM p, char mapa[][LarguraMapa]);

void move(char mapa[][LarguraMapa], PERSONAGEM *p);

void colocaBomba(BOMBA *b, PERSONAGEM p, char mapa[][LarguraMapa], int *poebomba);

void coletaCriatura(PERSONAGEM c[], PERSONAGEM *p, int ncriaturas);

int danoMonstro(PERSONAGEM p, PERSONAGEM m[],int nm);

void explodeBombas(BOMBA b[], char mapa[][LarguraMapa], int *poebomba, PERSONAGEM *p);

void limpaBombas(char mapa[][LarguraMapa]);

void resetaP(PERSONAGEM *p, PERSONAGEM m[], PERSONAGEM c[], char mapa[][LarguraMapa], int nc, int nm);

void danoBombas(PERSONAGEM *p, PERSONAGEM m[], PERSONAGEM c[], char mapa[][LarguraMapa], int nc, int nm);
#endif // MECANICAS_H_INCLUDED
