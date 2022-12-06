#include "graficos.h"

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

void desenharIndicadoresJogador(int vidas, int pontuacao, int numBombas, int nivelAtual){

    DrawText(TextFormat("Vidas: %02i", vidas), 10, AlturaTela - 50, 20, RED);
    DrawText(TextFormat("Bombas: %02i", numBombas), 10, AlturaTela - 20, 20, RED);
    DrawText(TextFormat("Pontuacao: %i", pontuacao), 150, AlturaTela - 20, 20, RED);
    DrawText(TextFormat("Nivel: %02i", nivelAtual), 150, AlturaTela - 50, 20, RED);
}

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
    carregarMapa(mapa, "Salvamento//MapaSalvo.txt");

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
}
