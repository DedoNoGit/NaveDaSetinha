#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "nave.h"

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}




char jogo[25][50];


int main()
{
    int i,j;
    struct Nave jogador;
    jogador.posicao.coordX=1;
    jogador.posicao.coordY=0;
    jogador.spriteNave = '>';

    char keypressed = 'x';

    while(keypressed != 'e'){
        system("clear");

        if(keypressed == 'w') jogador.posicao.coordX -= 2;
        else if(keypressed == 's') jogador.posicao.coordX += 2;


        for(i = 0; i < 25; i++)
            for(j = 0; j < 50; j++){
                jogo[i][j] = (i==0 || i==24) ? '*' : ' ';
                if(i == jogador.posicao.coordX && j == jogador.posicao.coordY) jogo[i][j] = jogador.spriteNave;
            }

        for(i = 0; i < 25; i++){
            for(j = 0; j < 50; j++)
                printf("%c", jogo[i][j]);
            printf("\n");
        }
        keypressed = getch();
    }


    return 0;
}
