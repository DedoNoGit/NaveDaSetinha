#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
    #include <conio.h>
    #define CLEARSCREEN() system("cls")
#else
    #include "crossio.h"
    #define CLEARSCREEN() system("clear")
#endif
#include "nave.h"

char jogo[25][50];


int main()
{
    int i,j;
    struct Nave jogador;
    jogador.posicao.coordX=1;
    jogador.posicao.coordY=0;
    jogador.spriteNave = '>';

    char keypressed = 'x';

    while(keypressed != 'e')
    {//no braces will be left untouched
        CLEARSCREEN();

        if(keypressed == 'w') jogador.posicao.coordX -= 2;
        else if(keypressed == 's') jogador.posicao.coordX += 2;


        for(i = 0; i < 25; i++)
        {//YOU FUCKING PSYCHOPATH
            for(j = 0; j < 50; j++)
            {//why?? do i have to do this??
                jogo[i][j] = (i==0 || i==24) ? '*' : ' ';
                if(i == jogador.posicao.coordX && j == jogador.posicao.coordY) jogo[i][j] = jogador.spriteNave;
            }
        }
        for(i = 0; i < 25; i++)
        {//luskas was here 
            for(j = 0; j < 50; j++)
                printf("%c", jogo[i][j]);
            printf("\n");
        }
        keypressed = getch();
    }
    return 0;
}

void Update()
{
    ScreenRender();
}

void PlayerInput()
{
    
}

void ScreenRender()
{
    //RENDER MATRIX
    
}

void EnemyLogic()
{
    //ENEMY THONK
}
void Move(int x, int y, struct NAVE *entity) 
{
    printf("LOl");
}
