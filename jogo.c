#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
    #include <conio.h>
    #include <Windows.h>
    #define Halt(MILLISECONDS) Sleep(MILLISECONDS)
    #define CLEARSCREEN() system("cls")
#else
    #include "crossio.h"
    #define CLEARSCREEN() system("clear")
    #define Halt(MICROSECONDS) usleep(MICROSECONDS*1000)
#endif
#include "nave.h"

char jogo[25][50];

/*
Notas: Tudo isso tá uma bagunça por que temos que ficar passando jogador de um lado pro outro, então nenhuma função
consegue fazer somente o que deveriam, em vez disso elas tem de ficar repetindo as mesmas operações. Isso pode ser
melhorado transformando o array 'jogo' em um array de Naves em vez de um array de chars.
*/



//temp
short ClosingState = 0;
//

int main()
{
    
    struct Nave jogador;
    jogador.posicao.coordX=1;
    jogador.posicao.coordY=0;
    jogador.spriteNave = '>';

    
    Start();
    while(!ClosingState)
    {
        Halt(166); //Periodo para uma frequencia de 60, ou seja o 'screen per second' maximo seria 60
        Update(&jogador);
    }
    return 0;
}

void Start()
{
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 50; j++)
        {
            jogo[i][j] = (i==0 || i==24) ? '*' : ' ';
        }
    }
}

void Update(struct Nave *jogador)
{
    PlayerInput(jogador);

    //update player position in matrix, temporary shit 
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 50; j++)
        {
            jogo[i][j] = (i==0 || i==24) ? '*' : ' ';
            if(i == jogador->posicao.coordX && j == jogador->posicao.coordY) jogo[i][j] = jogador->spriteNave;
        }
    }
    //
    ScreenRender();
}

void PlayerInput(struct Nave *jogador)
{

    if(kbhit()) // Se alguma tecla foi pressionada
    {
        char keypressed = getch();

        if(keypressed == 'w') jogador->posicao.coordX -= 2;
        else if(keypressed == 's') jogador->posicao.coordX += 2;
        else if(keypressed == 'e') ClosingState = 1;
    }
}

void ScreenRender()
{
    int i,j;
    CLEARSCREEN();

    for(i = 0; i < 25; i++)
    {//luskas was here 
        for(j = 0; j < 50; j++)
            printf("%c", jogo[i][j]);
        printf("\n");
    }
    
    //RENDER MATRIX
    
}

/*

void EnemyLogic()
{
    //ENEMY THONK
}
void Move(int x, int y, struct NAVE *entity) 
{
    printf("LOl");
}

void Translate()
{

}
*/