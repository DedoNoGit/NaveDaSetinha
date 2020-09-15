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
#define ScreenHeight 25
#define ScreenWidgth 50

//Inicialização Global
Nave *jogo[ScreenHeight + 1][ScreenWidgth]; // a altura tem um endereço a mais pra guardar algumas definições
struct Nave jogador;
//

//prototypes
char GetKey(); //Get the latest pressed key without halting the program
void Update(); //All game related code should be here
void Start(); //All game initialization code should be here
void ScreenRender(); //Background ScreenRendering Routine
void Move(int x, int y, Nave *entity); //Moves Entity to x and y position on the game matrix
void Translate(int x, int y, Nave *entity); //Translates Entity in relation to it's current position
// Para mover entidades pela matrix do jogo use somente as funções acima, se elas não suportarem o que você planeja fazer, modifique-as de acordo
//

//temp 
short ClosingState = 0; //caso for 1 o jogo fechara no proximo loop
//

int main()
{
    struct Nave Empty; //define a entidade vazia
    struct Nave Wall; //define as paredes
    Empty.spriteNave = ' ';  
    Wall.spriteNave = '*';
    jogo[ScreenHeight][1] = &Wall; //Paredes são guardadas nos endereços extras
    jogo[ScreenHeight][0] = &Empty; //A entidade vazia tbm
    
    Start();
    while(!ClosingState)
    {
        Halt(166); //Periodo para uma frequencia de 60, ou seja o 'screen per second' maximo seria 60
        Update();
        ScreenRender();
    }
    return 0;
}

void Start()
{
    //Popula a matrix do jogo com as paredes e o espaço vazio
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 50; j++)
        {
            jogo[i][j] = (i==0 || i==24) ? (jogo[ScreenHeight][1]) : (jogo[ScreenHeight][0]);
        }
    }
    //Inicializa o jogador
    jogador.posicao.coordX=0;
    jogador.posicao.coordY=1;
    jogador.spriteNave = '>';
    jogo[1][0] = &jogador;
    //
}

void Update()
{
    //Movimentação do jogador
    char keypressed = GetKey();
    if(keypressed == 'w') Translate(0, -2, &jogador);//jogador->posicao.coordX -= 2;
    else if(keypressed == 's') Translate(0, 2, &jogador);//jogador->posicao.coordX += 2;
    else if(keypressed == 'e') ClosingState = 1;
    //
}

char GetKey()
{
    if(kbhit()) // Se alguma tecla foi pressionada
    {
        return getch(); //Retorne a tecla pressionada
    }
    return '\0';
}

void ScreenRender()
{
    int i,j;
    CLEARSCREEN(); //limpa a tela

    for(i = 0; i < 25; i++)
    {
        for(j = 0; j < 50; j++)
        {
            printf("%c", jogo[i][j]->spriteNave);
        }
        printf("\n");
    }
    //RENDER MATRIX
}


/*
void EnemyLogic()
{
    //ENEMY THONK
}
*/
void Move(int x, int y, Nave *entity) 
{
    //Check if the next movement will land the entity out of bounds ou inside a wall
    if((x > ScreenWidgth - 1 || x < 1) || (y > ScreenHeight - 1 || y < 1))
    {
        return;
    }
    //get current pos
    int _x, _y;
    _x = entity->posicao.coordX;
    _y = entity->posicao.coordY;
    //

    //update to new pos
    entity->posicao.coordX = x;
    entity->posicao.coordY = y;
    //

    //change position in matrix
    jogo[_y][_x] = jogo[25][0];
    jogo[y][x] = entity;
    //
}


void Translate(int x, int y, Nave *entity) 
{
    //get current pos
    int _x, _y;
    _x = entity->posicao.coordX;
    _y = entity->posicao.coordY;
    //

    //get local movement
    x += _x;
    y += _y;
    //
    
    Move(x, y, entity);
}