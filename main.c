#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include <conio.h>
#include <time.h>
#include <ctype.h>

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

inicializarJogo(char mapa[][LarguraMapa], PERSONAGEM *player, PERSONAGEM inimigos[], PERSONAGEM criaturas[], int *nInimigos, int *nCriaturas){

    int ninimigos = 0;
    int ncriaturas = 0;

    for (int j = 0; j < AlturaMapa; j++)
        for (int i = 0; i < LarguraMapa; i++)
        {
            if (mapa[j][i]== 'J')
            {
                player -> pInicialX = i;
                player -> pInicialY = j;
                player -> posX = player->pInicialX;
                player -> posY = player->pInicialY;
                //player -> vida = 3;
                //player -> nivel = 1;
                //player -> pontuacao = 0;
            }
            else if (mapa[j][i]== 'M')
            {
                inimigos[ninimigos].pInicialX = i;
                inimigos[ninimigos]. pInicialY = j;
                inimigos[ninimigos].posX = inimigos[ninimigos].pInicialX;
                inimigos[ninimigos]. posY = inimigos[ninimigos].pInicialY;
                inimigos[ninimigos]. NPC = 1;
                inimigos[ninimigos]. monstro = 1;
                inimigos[ninimigos]. vida = 1;
                ninimigos++;
            }
            else if (mapa[j][i] == 'K')
            {
                criaturas[ncriaturas].pInicialX = i;
                criaturas[ncriaturas].pInicialY = j;
                criaturas[ncriaturas].posX = criaturas[ncriaturas].pInicialX;
                criaturas[ncriaturas].posY = criaturas[ncriaturas].pInicialY;
                criaturas[ncriaturas].NPC = 1;
                criaturas[ncriaturas].monstro = 0;
                criaturas[ncriaturas].vida = 1;
                ncriaturas++;
            }
        }

    *nCriaturas = ncriaturas;
    *nInimigos = ninimigos;
}

int carregarMapa(char mapa[][LarguraMapa], char *nomeArq){

    int sucesso = 1, i, j;

    char c;
    FILE *arq;

    arq = fopen(nomeArq, "r");

    if(arq != NULL){

        i = 0, j = 0;

        rewind(arq);
        while(!feof(arq)){

            c = getc(arq);
            //printf("Posicao[%d][%d]: ", i, j);
            //printf("%c\n", c);
            mapa[i][j] = c;

            if(c == '\n'){
                j = 0;
                i++;
            }else{
                j++;
            }
        }

        fclose(arq);
    }else{
        sucesso = 0;
        printf("ERRO AO ABRIR MAPA!\n\n");
    }

    return sucesso;
}

void SalvarJogo(char mapa[AlturaElemento][LarguraMapa], PERSONAGEM *player, PERSONAGEM inimigos[], PERSONAGEM criaturas[], int nInimigos, int nCriaturas){

    FILE *arqBin;
    FILE *arqTxt;
    char c;

    arqBin = fopen("Salvamento//EstadoJogoSalvo.bin", "wb");
    arqTxt = fopen("Salvamento//MapaSalvo.txt", "w");

    if(arqBin == NULL && arqTxt == NULL){
        printf("Erro ao abrir o arquivo\n");
    }else{

        for(int i = 0; i < AlturaMapa; i++){
            for(int j = 0; j < LarguraMapa; j++){
                c = mapa[i][j];
                //printf("%c", mapa[i][j]);
                fputc(c, arqTxt);
            }
            fputs("\n", arqTxt);
        }

        //erro ao salvar estado do jogo em binario

        if(fwrite(&player, sizeof(player),1, arqBin) != 1){
            printf("Erro ao salvar!\n");
        }

        for(int i = 0; i < nInimigos; i++){

            if(fwrite(inimigos, sizeof(inimigos),1,arqBin) != 1){
                printf("Erro ao salvar!\n");
            }

        }

        for(int i = 0; i < nInimigos; i++){

            if(fwrite(criaturas, sizeof(criaturas),1,arqBin) != 1){
                printf("Erro ao salvar!\n");
            }

        }

        fclose(arqBin);
        fclose(arqTxt);
    }
}

void CarregarJogoSalvo(char mapa[][LarguraMapa], PERSONAGEM *player, PERSONAGEM inimigos[], PERSONAGEM criaturas[], int *nInimigos, int *nCriaturas){

    ClearBackground(RAYWHITE);
    printf("TESTE\n");
    carregarMapa(mapa, "Salvamento//MapaSalvo.txt");
    printf("TESTE\n");





    int ninimigos = 0;
    int ncriaturas = 0;

    //funcionando somente as posicoes, precisa carregar o binario
    for (int j = 0; j < AlturaMapa; j++)
        for (int i = 0; i < LarguraMapa; i++)
        {
            if (mapa[j][i]== 'J')
            {
                player -> pInicialX = i;
                player -> pInicialY = j;
                player -> posX = player->pInicialX;
                player -> posY = player->pInicialY;
                player -> vida = 3;
                player -> nivel = 1;
                player -> pontuacao = 0;
            }
            else if (mapa[j][i]== 'M')
            {
                inimigos[ninimigos].pInicialX = i;
                inimigos[ninimigos]. pInicialY = j;
                inimigos[ninimigos].posX = inimigos[ninimigos].pInicialX;
                inimigos[ninimigos]. posY = inimigos[ninimigos].pInicialY;
                inimigos[ninimigos]. NPC = 1;
                inimigos[ninimigos]. monstro = 1;
                inimigos[ninimigos]. vida = 1;
                ninimigos++;
            }
            else if (mapa[j][i] == 'K')
            {
                criaturas[ncriaturas].pInicialX = i;
                criaturas[ncriaturas].pInicialY = j;
                criaturas[ncriaturas].posX = criaturas[ncriaturas].pInicialX;
                criaturas[ncriaturas].posY = criaturas[ncriaturas].pInicialY;
                criaturas[ncriaturas].NPC = 1;
                criaturas[ncriaturas].monstro = 0;
                criaturas[ncriaturas].vida = 1;
                ncriaturas++;
            }
        }

    *nCriaturas = ncriaturas;
    *nInimigos = ninimigos;

    //PERSONAGEM player;
    //PERSONAGEM inimigos[MAXINIMIGOS]
}

void desenharIndicadoresJogador(int vidas, int pontuacao, int numBombas, int nivelAtual){

    DrawText(TextFormat("Vidas: %02i", vidas), 10, AlturaTela - 50, 20, RED);
    DrawText(TextFormat("Bombas: %02i", numBombas), 10, AlturaTela - 20, 20, RED);
    DrawText(TextFormat("Pontuacao: %i", pontuacao), 150, AlturaTela - 20, 20, RED);
    DrawText(TextFormat("Nivel: %02i", nivelAtual), 150, AlturaTela - 50, 20, RED);
}

int podeMover(PERSONAGEM p, char mapa[][LarguraMapa], int movX, int movY)
{
    if(movX == 0 && movY == 0)
        return 1;
    else if (mapa[p.posY + movY][p.posX + movX] == ' ')
         return 1;
    else if (!p.NPC)
    {
        if (mapa[p.posY + movY][p.posX + movX] == 'P' || mapa[p.posY + movY][p.posX + movX] == 'K' || mapa[p.posY + movY][p.posX + movX] == 'R' || mapa[p.posY + movY][p.posX + movX] == 'M')
            return 1;
    }
    else if(p.monstro)
    {
        if (mapa[p.posY + movY][p.posX + movX] == 'J')
            return 1;
    }
    return 0;
}

void desenharMenu(int *estadoJogoAtual){

    ClearBackground(BLACK) ;

    Rectangle opcaoMenu[numOpcoesMenu];

    opcaoMenu[0] = (Rectangle){40, 50, 150, 30};
    opcaoMenu[1] = (Rectangle){40, 85, 150, 30};
    opcaoMenu[2] = (Rectangle){LarguraTela - 190, 50, 150, 30};
    opcaoMenu[3] = (Rectangle){LarguraTela - 190, 85, 150, 30};
    opcaoMenu[4] = (Rectangle){195, 150, 150, 30};
    DrawRectangleRec(opcaoMenu[0], RED);
    DrawRectangleRec(opcaoMenu[1], RED);
    DrawRectangleRec(opcaoMenu[2], RED);
    DrawRectangleRec(opcaoMenu[3], RED);
    DrawRectangleRec(opcaoMenu[4], RED);

    DrawText("Novo Jogo (N)", 45, 55, 20, GREEN);
    DrawText("Voltar (V)", 55, 90, 20, GREEN);
    DrawText("Salvar (S)", LarguraTela - 160, 55, 20, GREEN);
    DrawText("Carregar (C)", LarguraTela - 180, 90, 20, GREEN);
    DrawText("Quit (Q)", 230, 155, 20, GREEN);

    if(IsKeyPressed('N')){
        *estadoJogoAtual = NOVO_JOGO;
    }else if(IsKeyPressed('S')){
        *estadoJogoAtual = SALVAR;
    }else if(IsKeyPressed('C')){
        *estadoJogoAtual = CARREGAR;
    }else if(IsKeyPressed('Q')){
        *estadoJogoAtual = QUIT;
    }else if(IsKeyPressed('V')){
        *estadoJogoAtual = VOLTAR;
    }
}

int escolheDirecao (PERSONAGEM p, char mapa[][LarguraMapa])
{
    int novad;
    int movX, movY;
    int cont = 0;
    do{
        novad = GetRandomValue(0,3);
        switch (novad)
        {
        case 0:
            movX = 1;
            movY = 0;
            break;
        case 1:
            movX = -1;
            movY = 0;
            break;
        case 2:
            movX = 0;
            movY = -1;
            break;
        case 3:
            movX = 0;
            movY = 1;
            break;
        }
        cont++;
        if (cont >= 50)
        {
            movX = 0;
            movY = 0;
            novad = 4;
        }
    }while(!podeMover(p, mapa, movX, movY));

    return novad;
}
 void move(char mapa[][LarguraMapa], PERSONAGEM *p){

    mapa[p->posY][p->posX] = ' ';
    switch (p->direcao)
        {
        case 0:
            p->posX += 1;
            break;
        case 1:
            p->posX -= 1;
            break;
        case 2:
            p->posY -= 1;
            break;
        case 3:
            p->posY += 1;
            break;
        default:
            break;
        }
    if (!(p->NPC))
    {
        if (mapa[p->posY][p->posX] == 'P')
        {
            p->pontuacao+=50;
        }
        mapa[p->posY][p->posX] = 'J';
    }
    else
    {
        if (p->monstro)
            mapa[p->posY][p->posX] = 'M';
        else
            mapa[p->posY][p->posX] = 'K';
    }
}

void coletaCriatura(PERSONAGEM c[], PERSONAGEM *p, int ncriaturas)
{
    int i;
    for (i=0;i<ncriaturas;i++)
        if (p->posX == c[i].posX && p->posY == c[i].posY && c[i].vida>0)
        {
            c[i].vida = 0;
            p->pontuacao+=10;
        }
}

int danoMonstro(PERSONAGEM p, PERSONAGEM m[],int nm)
{
    int dano = 0;
    for(int i=0;i<nm;i++)
        if (m[i].vida>0)
            if(p.posX == m[i].posX && p.posY == m[i].posY)
                dano = 1;
    return dano;
}

void colocaBomba(BOMBA *b, PERSONAGEM p, char mapa[][LarguraMapa], int *poebomba)
{
    *poebomba +=1;
    switch(p.direcao)
    {
    case 0:
        if (mapa[p.posY][p.posX+1] == ' ')
        {
            b->posX = p.posX+1;
            b->posY = p.posY;
            b->tempo = clock();
        }
        break;
    case 1:
        if (mapa[p.posY][p.posX-1] == ' ')
        {
            b->posX = p.posX-1;
            b->posY = p.posY;
            b->tempo = clock();
        }
        break;
    case 2:
        if (mapa[p.posY-1][p.posX] == ' ')
        {
            b->posX = p.posX;
            b->posY = p.posY-1;
            b->tempo = clock();
        }
        break;
    case 3:
        if (mapa[p.posY+1][p.posX] == ' ')
        {
            b->posX = p.posX;
            b->posY = p.posY+1;
            b->tempo = clock();
        }
        break;
    }
    if (b->posX != 0 && b->posY != 0)
        mapa[b->posY][b->posX] = 'B';
}

void explodeBombas(BOMBA b[], char mapa[][LarguraMapa], int *poebomba, PERSONAGEM *p)
{
    for (int i=MAXBOMBAS-1;i>=0; i--)
    {
        if (b[i].tempo > 0 && clock() > b[i].tempo+3000)
        {
            //DIRECOES CARDEAIS
            mapa[b[i].posY][b[i].posX] = 'R';
            //esquerda:
            if (mapa[b[i].posY][b[i].posX-1] != 'W' && mapa[b[i].posY][b[i].posX-1] != 'B')
            {
                if (mapa[b[i].posY][b[i].posX-1] == 'D')
                {
                    p->pontuacao +=10;
                }
                mapa[b[i].posY][b[i].posX-1] = 'R';
                if (mapa[b[i].posY][b[i].posX-2] != 'W' && mapa[b[i].posY][b[i].posX-2] != 'B')
                {
                    if (mapa[b[i].posY][b[i].posX-2] == 'D')
                    {
                        p->pontuacao +=10;
                    }
                    mapa[b[i].posY][b[i].posX-2] = 'R';
                }
            }
            //direita:
            if (mapa[b[i].posY][b[i].posX+1] != 'W' && mapa[b[i].posY][b[i].posX+1] != 'B')
            {
                if (mapa[b[i].posY][b[i].posX+1] == 'D')
                {
                    p->pontuacao +=10;
                }
                mapa[b[i].posY][b[i].posX+1] = 'R';
                if (mapa[b[i].posY][b[i].posX+2] != 'W' && mapa[b[i].posY][b[i].posX+2] != 'B')
                {
                    if (mapa[b[i].posY][b[i].posX+2] == 'D')
                    {
                        p->pontuacao +=10;
                    }
                    mapa[b[i].posY][b[i].posX+2] = 'R';
                }
            }
            //baixo:
            if (mapa[b[i].posY+1][b[i].posX] != 'W' && mapa[b[i].posY+1][b[i].posX] != 'W')
            {
                mapa[b[i].posY+1][b[i].posX] = 'R';
                if (mapa[b[i].posY+2][b[i].posX] != 'W' && mapa[b[i].posY+2][b[i].posX] != 'B')
                    mapa[b[i].posY+2][b[i].posX] = 'R';
            }
            //cima
            if (mapa[b[i].posY-1][b[i].posX] != 'W' && mapa[b[i].posY-1][b[i].posX] != 'B')
            {
                if (mapa[b[i].posY-1][b[i].posX] == 'D')
                {
                    p->pontuacao +=10;
                }
                mapa[b[i].posY-1][b[i].posX] = 'R';
                if (mapa[b[i].posY-2][b[i].posX] != 'W' && mapa[b[i].posY-2][b[i].posX] != 'B')
                {
                    if (mapa[b[i].posY-2][b[i].posX] == 'D')
                    {
                        p->pontuacao +=10;
                    }
                    mapa[b[i].posY-2][b[i].posX] = 'R';
                }
            }

            //DIRECOES COLATERAIS
            //nordeste
            if (mapa[b[i].posY-1][b[i].posX+1]  != 'W' && mapa[b[i].posY-1][b[i].posX+1]  != 'B')
            {
                if (mapa[b[i].posY-1][b[i].posX+1] == 'D')
                {
                    p->pontuacao +=10;
                }
                mapa[b[i].posY-1][b[i].posX+1] = 'R';
                if (mapa[b[i].posY-2][b[i].posX+2] != 'W' && mapa[b[i].posY-2][b[i].posX+2] != 'B')
                {
                    if (mapa[b[i].posY-2][b[i].posX+2] == 'D')
                    {
                        p->pontuacao +=10;
                    }
                    mapa[b[i].posY-2][b[i].posX+2] = 'R';
                }
            }
            //noroeste
            if (mapa[b[i].posY-1][b[i].posX-1]  != 'W' && mapa[b[i].posY-1][b[i].posX-1]  != 'B')
            {
                if (mapa[b[i].posY-1][b[i].posX-1] == 'D')
                {
                    p->pontuacao +=10;
                }
                mapa[b[i].posY-1][b[i].posX-1] = 'R';
                if (mapa[b[i].posY-2][b[i].posX-2] != 'W' && mapa[b[i].posY-2][b[i].posX-2] != 'B')
                {
                    if (mapa[b[i].posY-2][b[i].posX-2] == 'D')
                    {
                        p->pontuacao +=10;
                    }
                    mapa[b[i].posY-2][b[i].posX-2] = 'R';
                }
            }
            //sudoeste
            if (mapa[b[i].posY+1][b[i].posX-1]  != 'W' && mapa[b[i].posY+1][b[i].posX-1]  != 'B')
            {
                if (mapa[b[i].posY+1][b[i].posX-1] == 'D')
                {
                    p->pontuacao +=10;
                }
                mapa[b[i].posY+1][b[i].posX-1] = 'R';
                if (mapa[b[i].posY+2][b[i].posX-2] != 'W' && mapa[b[i].posY+2][b[i].posX-2] != 'B')
                {
                    if (mapa[b[i].posY+2][b[i].posX-2] == 'D')
                    {
                        p->pontuacao +=10;
                    }
                    mapa[b[i].posY+2][b[i].posX-2] = 'R';
                }
            }
            //sudeste
            if (mapa[b[i].posY+1][b[i].posX+1]  != 'W' && mapa[b[i].posY+1][b[i].posX+1]  != 'B')
            {
                if (mapa[b[i].posY+1][b[i].posX+1] == 'D')
                {
                    p->pontuacao +=10;
                }
                mapa[b[i].posY+1][b[i].posX+1] = 'R';
                if (mapa[b[i].posY+2][b[i].posX+2] != 'W' && mapa[b[i].posY+2][b[i].posX+2] != 'B')
                {
                    if (mapa[b[i].posY+2][b[i].posX+2] == 'D')
                    {
                        p->pontuacao +=10;
                    }
                    mapa[b[i].posY+2][b[i].posX+2] = 'R';
                }
            }

            //DIRECOES SUBCOLATERAIS
            //nor-nordeste
            if ((mapa[b[i].posY-2][b[i].posX+1]  != 'W' && mapa[b[i].posY-2][b[i].posX+1]  != 'B') && (mapa[b[i].posY-1][b[i].posX] == 'R' && mapa[b[i].posY-1][b[i].posX+1] == 'R'))
            {
                if (mapa[b[i].posY-2][b[i].posX+1] == 'D')
                {
                    p->pontuacao +=10;
                }
                mapa[b[i].posY-2][b[i].posX+1]  = 'R';
            }
            //nor-noroeste
            if ((mapa[b[i].posY-2][b[i].posX-1]  != 'W' && mapa[b[i].posY-2][b[i].posX-1]  != 'B') && (mapa[b[i].posY-1][b[i].posX] == 'R' && mapa[b[i].posY-1][b[i].posX-1] == 'R'))
            {
                if (mapa[b[i].posY-2][b[i].posX-1] == 'D')
                {
                    p->pontuacao +=10;
                }
                mapa[b[i].posY-2][b[i].posX-1]  = 'R';
            }
            //oes-noroeste
            if ((mapa[b[i].posY-1][b[i].posX-2]  != 'W' && mapa[b[i].posY-1][b[i].posX-2]  != 'B') && (mapa[b[i].posY][b[i].posX-1] == 'R' && mapa[b[i].posY-1][b[i].posX-1] == 'R'))
            {
                if (mapa[b[i].posY-1][b[i].posX-2] == 'D')
                {
                    p->pontuacao +=10;
                }
                mapa[b[i].posY-1][b[i].posX-2]  = 'R';
            }
            //oes-sudoeste
            if ((mapa[b[i].posY+1][b[i].posX-2]  != 'W' && mapa[b[i].posY+1][b[i].posX-2]  != 'B') && (mapa[b[i].posY][b[i].posX-1] == 'R' && mapa[b[i].posY+1][b[i].posX-1] == 'R'))
            {
                if (mapa[b[i].posY+1][b[i].posX-2] == 'D')
                {
                    p->pontuacao +=10;
                }
                mapa[b[i].posY+1][b[i].posX-2]  = 'R';
            }
            //sul-sudoeste
            if ((mapa[b[i].posY+2][b[i].posX-1]  != 'W' && mapa[b[i].posY+2][b[i].posX-1]  != 'B') && (mapa[b[i].posY+1][b[i].posX] == 'R' && mapa[b[i].posY+1][b[i].posX-1] == 'R'))
            {
                if (mapa[b[i].posY+2][b[i].posX-1] == 'D')
                {
                    p->pontuacao +=10;
                }
                mapa[b[i].posY+2][b[i].posX-1]  = 'R';
            }
            //sul-sudeste
            if ((mapa[b[i].posY+2][b[i].posX+1]  != 'W' && mapa[b[i].posY+2][b[i].posX+1]  != 'B') && (mapa[b[i].posY+1][b[i].posX] == 'R' && mapa[b[i].posY+1][b[i].posX+1] == 'R'))
            {
                if (mapa[b[i].posY+2][b[i].posX+1] == 'D')
                {
                    p->pontuacao +=10;
                }
                mapa[b[i].posY+2][b[i].posX+1]  = 'R';
            }
            //les-sudeste
            if ((mapa[b[i].posY+1][b[i].posX+2]  != 'W' && mapa[b[i].posY+1][b[i].posX+2]  != 'B') && (mapa[b[i].posY][b[i].posX+1] == 'R' && mapa[b[i].posY+1][b[i].posX+1] == 'R'))
            {
                if (mapa[b[i].posY+1][b[i].posX+2] == 'D')
                {
                    p->pontuacao +=10;
                }
                mapa[b[i].posY+1][b[i].posX+2]  = 'R';
            }
            //les-nordeste
            if ((mapa[b[i].posY-1][b[i].posX+2]  != 'W' && mapa[b[i].posY-1][b[i].posX+2]  != 'B') && (mapa[b[i].posY][b[i].posX+1] == 'R' && mapa[b[i].posY-1][b[i].posX+1] == 'R'))
            {
                if (mapa[b[i].posY-1][b[i].posX+2] == 'D')
                {
                    p->pontuacao +=10;
                }
                mapa[b[i].posY-1][b[i].posX+2]  = 'R';
            }

            b[i].tempo = 0;
            b[i].texplosao = clock();
            *poebomba -=1;
        }
    }
}

void limpaBombas(char mapa[][LarguraMapa])
{
    for (int j = 0; j < AlturaMapa; j++)
        for (int i = 0; i < LarguraMapa; i++)
        {
            if(mapa[j][i] == 'R')
            {
                mapa[j][i] = ' ';
            }
        }
}

void resetaP(PERSONAGEM *p, PERSONAGEM m[], PERSONAGEM c[], char mapa[][LarguraMapa], int nc, int nm)
{
    p->vida--;
    if(p->pontuacao-100 < 00)
        p->pontuacao=0;
    else
        p->pontuacao-=100;
    if (mapa[p->posY][p->posY] != 'W')
        mapa[p->posY][p->posY] = ' ';
    p->posX = p->pInicialX;
    p->posY = p->pInicialY;
    if (p->vida > 0)
        mapa[p->posY][p->posX] = 'J';

    for(int i = 0; i<nc; i++)
    {
        if (c[i].vida > 0)
        {
            mapa[c[i].posY][c[i].posX] = ' ';
            c[i].posX = c[i].pInicialX;
            c[i].posY = c[i].pInicialY;
            mapa[c[i].posY][c[i].posX] = 'K';
        }
    }
    for(int i = 0; i<nm; i++)
    {
        if (m[i].vida > 0)
        {
            mapa[m[i].posY][m[i].posX] = ' ';
            m[i].posX = m[i].pInicialX;
            m[i].posY = m[i].pInicialY;
            mapa[m[i].pInicialY][m[i].pInicialX] = 'M';
        }
    }
    for(int i=0; i<LarguraMapa; i++)
        for (int j=0; j<AlturaMapa; j++)
            if (mapa[j][i] == 'B')
                mapa[j][i] = ' ';
}

void danoBombas(PERSONAGEM *p, PERSONAGEM m[], PERSONAGEM c[], char mapa[][LarguraMapa], int nc, int nm)
{
    if (mapa[p->posY][p->posX] == 'R')
    {
        resetaP(p, m, c, mapa, nc, nm);
    }

    for(int i = 0; i<nc; i++)
    {
        if (mapa[c[i].posY][c[i].posX] == 'R')
            c[i].vida = 0;
    }
    for(int i = 0; i<nm; i++)
    {
        if (mapa[m[i].posY][m[i].posX] == 'R' && m[i].vida>0)
        {
            m[i].vida = 0;
            p->pontuacao+=100;
        }
    }

}

void colorirMapa(char text, int posX, int posY, int alturaElemento, int larguraElemento){

    switch(text){
        case 'W':
            DrawRectangle(posX, posY, alturaElemento, larguraElemento, GRAY);
            break;
        case 'J':
            DrawRectangle(posX, posY, alturaElemento, larguraElemento, BLACK);
            break;
        case 'P':
            DrawRectangle(posX, posY, alturaElemento, larguraElemento, SKYBLUE);
            break;
        case 'M':
            DrawRectangle(posX, posY, alturaElemento, larguraElemento, DARKGREEN);
            break;
        case 'K':
            DrawRectangle(posX, posY, alturaElemento, larguraElemento, GOLD);
            break;
        case 'D':
            DrawRectangle(posX, posY, alturaElemento, larguraElemento, LIGHTGRAY);
            break;
        case 'B':
            DrawRectangle(posX+5, posY+5, alturaElemento/2, larguraElemento/2, GRAY);
            break;
        case 'R':
            DrawRectangle(posX, posY, alturaElemento, larguraElemento, ORANGE);
            break;
        default:
            DrawRectangle(posX, posY, alturaElemento, larguraElemento, BLANK);
            break;
    }
}

void desenharMapa(int larguraMapa, int alturaMapa, int larguraElemento, int alturaElemento, char mapa[][LarguraMapa]){

    int posicaoX = 0;
    int posicaoY = 0;
    char texto;

    ClearBackground(RAYWHITE);
    for(int i = 0; i < alturaMapa; i++){

        for(int j = 0; j < larguraMapa; j++){

            texto = toupper(mapa[i][j]);
            colorirMapa(texto, posicaoX, posicaoY, alturaElemento, larguraElemento);
            posicaoX = posicaoX + larguraElemento;
        }

        posicaoX = 0;
        posicaoY = posicaoY + larguraElemento;
    }
}

int main(){

    PERSONAGEM player;
    PERSONAGEM inimigos[MAXINIMIGOS];
    PERSONAGEM criaturas[MAXCRIATURAS];
    BOMBA bombas[MAXBOMBAS];

    char proxMapa[50] = "Mapas//nivel";
    char stringNivel[5];

    int vidaextra = 0;

    int Larg = 0, Alt = 0;

    int estadoJogoAtual = MENU;

    int ninimigos=0;
    int ncriaturas=0;
    int criaturasMortas = 0;

    char mapa[AlturaMapa][LarguraMapa];
    player.NPC = 0;
    player.nivel = 1;
    player.pontuacao = 0;
    player.vida=3;

    int poebomba = 0;
    for (int i=0;i<MAXBOMBAS; i++)
    {
        bombas[i].tempo = 0;
    }

    clock_t start_time = clock();

    InitWindow(LarguraTela, AlturaTela, "Jogo do Mago"); // Inicia a janela do jogo
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        if(estadoJogoAtual == MENU){
            desenharMenu(&estadoJogoAtual);

            if(estadoJogoAtual == NOVO_JOGO){
                if(carregarMapa(mapa, "Mapas//nivel1.txt") == 1){
                    inicializarJogo(mapa, &player, inimigos, criaturas, &ninimigos, &ncriaturas);
                    estadoJogoAtual = JOGANDO;
                }
            }else if(estadoJogoAtual == SALVAR){

                SalvarJogo(mapa, &player, inimigos, criaturas, ninimigos, ncriaturas);
                estadoJogoAtual = MENU;

            }else if(estadoJogoAtual == CARREGAR){

                CarregarJogoSalvo(mapa, &player, inimigos, criaturas, &ninimigos, &ncriaturas);

                estadoJogoAtual = JOGANDO;

            }else if(estadoJogoAtual == VOLTAR){
                estadoJogoAtual = JOGANDO;
            }else if(estadoJogoAtual == QUIT){
                CloseWindow();
            }
        }else if(estadoJogoAtual == JOGANDO){

            desenharMapa(LarguraMapa, AlturaMapa, LarguraElemento, AlturaElemento, mapa);
            desenharIndicadoresJogador(player.vida, player.pontuacao, MAXBOMBAS-poebomba, player.nivel);

            if (IsKeyPressed(KEY_RIGHT)) {player.direcao = 0; if (podeMover(player, mapa, 1, 0)) move(mapa, &player);} //Direita
            if (IsKeyPressed(KEY_LEFT)) {player.direcao = 1; if (podeMover(player, mapa, -1, 0)) move(mapa, &player);} //Esquerda
            if (IsKeyPressed(KEY_UP)) {player.direcao = 2; if (podeMover(player, mapa, 0, -1)) move(mapa, &player);}   //Cima
            if (IsKeyPressed(KEY_DOWN)) {player.direcao = 3; if (podeMover(player, mapa, 0, 1)) move(mapa, &player);}  //Baixo
            if(IsKeyPressed(KEY_TAB)) estadoJogoAtual = MENU;

            if (IsKeyPressed(KEY_B))
                if (poebomba<MAXBOMBAS)
                {
                    int podeBomba = 0;
                    switch(player.direcao)
                    {
                        case 0:
                            if (mapa[player.posY][player.posX+1] == ' ')
                                podeBomba = 1;
                            break;
                        case 1:
                            if (mapa[player.posY][player.posX-1] == ' ')
                                podeBomba = 1;
                            break;
                        case 2:
                            if (mapa[player.posY-1][player.posX] == ' ')
                                podeBomba = 1;
                            break;
                        case 3:
                            if (mapa[player.posY+1][player.posX] == ' ')
                                podeBomba = 1;
                            break;
                    }
                    if (podeBomba)
                        colocaBomba((bombas + (MAXBOMBAS-1) - poebomba), player, mapa, &poebomba);
                }

            coletaCriatura(criaturas, &player, ncriaturas);
            if (danoMonstro(player, inimigos, ninimigos) == 1)
                resetaP(&player, inimigos, criaturas, mapa, ncriaturas, ninimigos);

            if (player.pontuacao/1000 == vidaextra+1)
            {
                player.vida++;
                vidaextra++;
            }

            explodeBombas(bombas, mapa, &poebomba, &player);
            danoBombas(&player, inimigos, criaturas, mapa, ncriaturas, ninimigos);
            for (int i=0;i<MAXBOMBAS;i++)
            {
                if(bombas[i].texplosao > 0 && clock() > bombas[i].texplosao + 2000)
                {
                    limpaBombas(mapa);
                    bombas[i].texplosao = 0;
                }
            }
            if (clock() > start_time+1500)
            {
                for (int i=0; i<ninimigos ;i++)
                {
                    inimigos[i].direcao = escolheDirecao(inimigos[i], mapa);
                    if (inimigos[i].vida>0)
                        move(mapa,(inimigos + i));
                }
                for(int i=0; i<ncriaturas;i++)
                {
                    if (criaturas[i].vida>0)
                    {
                        criaturas[i].direcao = escolheDirecao(criaturas[i], mapa);
                        move(mapa, (criaturas + i));
                    }
                }
                start_time = clock();
            }

        if (player.vida<=0)
        {
            estadoJogoAtual = MENU;
        }
        criaturasMortas = 0;
        for (int i=0;i<ncriaturas;i++)
        {
            if (criaturas[i].vida == 0)
                criaturasMortas++;
        }
        if (criaturasMortas == ncriaturas && ncriaturas>0)
        {
            player.nivel+= 1;
            snprintf(proxMapa, 50, "Mapas//nivel%d.txt", player.nivel);
            if (carregarMapa(mapa, proxMapa) == 1)
            {
                inicializarJogo(mapa, &player, inimigos, criaturas, &ninimigos, &ncriaturas);
                estadoJogoAtual = JOGANDO;
            }
            else
            {
                estadoJogoAtual = MENU;
            }
        }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
