typedef struct posicaoNave
{
    int coordX;
    int coordY;
} posicaoNave;

typedef struct Nave
{//fuck u
    posicaoNave posicao;
    char spriteNave;
    int hpNave;
    void (*Translate)(int x, int y, struct Nave *entity);
} Nave;


