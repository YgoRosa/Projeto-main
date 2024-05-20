#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define LARGURA 20
#define ALTURA 20

typedef struct {
    int x;
    int y;
} Posicao;

typedef struct SegmentoCobra {
    Posicao pos;
    struct SegmentoCobra *proximo; //ponteiro que aponta para o próximo segmento da cobra.
} SegmentoCobra;

typedef struct {
    SegmentoCobra *cabeca; //ponteiro para o primeiro segmento da cobra, ou seja, a cabeça da cobra.
    SegmentoCobra *rabo; //ponteiro para o primeiro segmento da cobra, ou seja, o rabo da cobra.
    int comprimento;
} Cobra;

typedef struct {
    Cobra cobra; 
    Posicao comida;
    int pontuacao; 
    int fimDeJogo; //indica se o jogo terminou (0 para não, 1 para sim).
} EstadoJogo;

void posicao(int x, int y) {
    COORD coord; /*COORD é uma estrutura definida em windows.h
    que contém dois membros: X e Y, que representam as coordenadas horizontais e verticais no console, respectivamente.*/
    coord.X = x; //atribui valor de x para o membro X de coord
    coord.Y = y; //atribui valor de y para o membro Y de coord
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); //a função SetConsoleCursorPosition da API do Windows.
    /*GetStdHandle(STD_OUTPUT_HANDLE): Esta função obtém um identificador para o buffer de saída padrão do console (geralmente a tela do console). STD_OUTPUT_HANDLE é uma constante que representa a saída padrão.
    coord: Este é o segundo argumento, que é a estrutura coord contendo as coordenadas x e y onde o cursor deve ser posicionado.*/
}

void maca(int mx, int my) {
    posicao(mx, my); //chama a função posicao com os parâmetros mx e my
    printf("%c", '@');  //desenha a comida (maçã) na posição (mx, my)
}

void pontuacao(int pontos) {
    posicao(LARGURA - 13, 1); 
    printf("Pontos: %d", pontos);  //exibe a pontuação na posição especificada
}

void render() {
    system("cls");  //limpa a tela no Windows

    for (int x = 0; x < LARGURA; x++) {  //borda superior
        printf("#");
    }
    printf("\n");

    for (int y = 1; y < ALTURA - 1; y++) {  //bordas laterais e o interior da tela
        printf("#");  //borda esquerda
        for (int x = 1; x < LARGURA - 1; x++) {
            printf(" ");  //espaço vazio
        }
        printf("#\n");  //borda direita
    }

    for (int x = 0; x < LARGURA; x++) {  //borda inferior
        printf("#");
    }
    printf("\n");
}

void inicializaJogo(EstadoJogo *jogo) {
    SegmentoCobra *segmentoInicial = (SegmentoCobra *)malloc(sizeof(SegmentoCobra));
    segmentoInicial->pos.x = LARGURA / 2;
    segmentoInicial->pos.y = ALTURA / 2;
    segmentoInicial->proximo = NULL;

    jogo->cobra.cabeca = segmentoInicial;
    jogo->cobra.rabo = segmentoInicial;
    jogo->cobra.comprimento = 1;

    srand(time(0));
    jogo->comida.x = rand() % (LARGURA - 2) + 1;
    jogo->comida.y = rand() % (ALTURA - 2) + 1;

    jogo->pontuacao = 0;
    jogo->fimDeJogo = 0;
} //essa funcao nao foi eu (kze) que fez, foi o chatgpt. ainda to vendo se vamos usar mesmo pq nao entendi legal nao

//tem que ver legal, bora ver como funciona depois, e qualquer coisa a gente adapta essa e faz uma nossa, mas bora ir vendo - ygor


int main(){
    int cobra[300][2]; //matriz do corpinho da cobra
    int maca[2]; //matriz da maçã
    int pontos = 1; //pontuação do player
    int cx = 2, cy = 2; //coordenadas x e y

//return x;
}