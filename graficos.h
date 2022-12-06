#ifndef GRAFICOS_H_INCLUDED
#define GRAFICOS_H_INCLUDED

#include "elementos.h"
#include "raylib.h"
#include <stdio.h>

void desenharMapa(int larguraMapa, int alturaMapa, int larguraElemento, int alturaElemento, char mapa[][LarguraMapa]);

void colorirMapa(char text, int posX, int posY, int alturaElemento, int larguraElemento);

void desenharMenu(int *estadoJogoAtual);

void desenharIndicadoresJogador(int vidas, int pontuacao, int numBombas, int nivelAtual);

inicializarJogo(char mapa[][LarguraMapa], PERSONAGEM *player, PERSONAGEM inimigos[], PERSONAGEM criaturas[], int *nInimigos, int *nCriaturas);

int carregarMapa(char mapa[][LarguraMapa], char *nomeArq);

void SalvarJogo(char mapa[AlturaElemento][LarguraMapa], PERSONAGEM *player, PERSONAGEM inimigos[], PERSONAGEM criaturas[], int nInimigos, int nCriaturas);

void CarregarJogoSalvo(char mapa[][LarguraMapa], PERSONAGEM *player, PERSONAGEM inimigos[], PERSONAGEM criaturas[], int *nInimigos, int *nCriaturas);

#endif // GRAFICOS_H_INCLUDED
