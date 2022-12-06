#include "elementos.h"
#include "graficos.h"
#include "mecanicas.h"

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
