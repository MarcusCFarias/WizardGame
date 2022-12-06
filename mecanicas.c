#include "mecanicas.h"

int podeMover(PERSONAGEM p, char mapa[][LarguraMapa], int movX, int movY){
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

int escolheDirecao (PERSONAGEM p, char mapa[][LarguraMapa]){
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

void colocaBomba(BOMBA *b, PERSONAGEM p, char mapa[][LarguraMapa], int *poebomba){
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

void coletaCriatura(PERSONAGEM c[], PERSONAGEM *p, int ncriaturas){
    int i;
    for (i=0;i<ncriaturas;i++)
        if (p->posX == c[i].posX && p->posY == c[i].posY && c[i].vida>0)
        {
            c[i].vida = 0;
            p->pontuacao+=10;
        }
}

int danoMonstro(PERSONAGEM p, PERSONAGEM m[],int nm){
    int dano = 0;
    for(int i=0;i<nm;i++)
        if (m[i].vida>0)
            if(p.posX == m[i].posX && p.posY == m[i].posY)
                dano = 1;
    return dano;
}

void explodeBombas(BOMBA b[], char mapa[][LarguraMapa], int *poebomba, PERSONAGEM *p){
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

void limpaBombas(char mapa[][LarguraMapa]){
    for (int j = 0; j < AlturaMapa; j++)
        for (int i = 0; i < LarguraMapa; i++)
        {
            if(mapa[j][i] == 'R')
            {
                mapa[j][i] = ' ';
            }
        }
}

void resetaP(PERSONAGEM *p, PERSONAGEM m[], PERSONAGEM c[], char mapa[][LarguraMapa], int nc, int nm){
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

void danoBombas(PERSONAGEM *p, PERSONAGEM m[], PERSONAGEM c[], char mapa[][LarguraMapa], int nc, int nm){
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
