#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define LARGURA 50
#define ALTURA 20

typedef struct {
    int x;
    int y;
} Posicao;

typedef struct SegmentoCobra {
    Posicao pos;
    struct SegmentoCobra *proximo;
} SegmentoCobra;

typedef struct {
    SegmentoCobra *cabeca;
    SegmentoCobra *rabo;
    int comprimento;
} Cobra;

typedef struct {
    Cobra cobra;
    Posicao comida;
    int pontuacao;
    int fimDeJogo;
} EstadoJogo;

void maca(int mx, int my) {
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(mx, my);
    printf("@");
}

void pontuacao(int pontos) {
    screenSetColor(WHITE, BLACK);
    screenGotoxy(LARGURA - 13, 1);
    printf("Pontos: %d", pontos);
}

void render(EstadoJogo *jogo) {
    screenClear();

    for (int y = 0; y < ALTURA; y++) {
        for (int x = 0; x < LARGURA; x++) {
            if (x == 0 || x == LARGURA - 1 || y == 0 || y == ALTURA - 1)
                printf("#");
            else if (x == jogo->comida.x && y == jogo->comida.y)
                maca(x, y);
            else {
                SegmentoCobra *segmento = jogo->cobra.cabeca;
                int segmentoPrintado = 0;
                while (segmento != NULL) {
                    if (segmento->pos.x == x && segmento->pos.y == y) {
                        printf("O");
                        segmentoPrintado = 1;
                        break;
                    }
                    segmento = segmento->proximo;
                }
                if (!segmentoPrintado)
                    printf(" ");
            }
        }
        printf("\n");
    }

    pontuacao(jogo->pontuacao);
    screenUpdate();
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
}

void entrada(int *dx, int *dy) {
    if (keyhit()) {
        int tecla = readch();
        switch (tecla) {
            case 'w':
                *dx = 0;
                *dy = -1;
                break;
            case 's':
                *dx = 0;
                *dy = 1;
                break;
            case 'a':
                *dx = -1;
                *dy = 0;
                break;
            case 'd':
                *dx = 1;
                *dy = 0;
                break;
        }
    }
}

void atualizaCobra(EstadoJogo *jogo, int dx, int dy) {
    SegmentoCobra *novoSegmento = (SegmentoCobra *)malloc(sizeof(SegmentoCobra));
    novoSegmento->pos.x = jogo->cobra.cabeca->pos.x + dx;
    novoSegmento->pos.y = jogo->cobra.cabeca->pos.y + dy;
    novoSegmento->proximo = jogo->cobra.cabeca;

    jogo->cobra.cabeca = novoSegmento;

    if (novoSegmento->pos.x == jogo->comida.x && novoSegmento->pos.y == jogo->comida.y) {
        jogo->pontuacao++;
        jogo->comida.x = rand() % (LARGURA - 2) + 1;
        jogo->comida.y = rand() % (ALTURA - 2) + 1;
        jogo->cobra.comprimento++;
    } else {
        SegmentoCobra *temp = jogo->cobra.cabeca;
        while (temp->proximo != jogo->cobra.rabo) {
            temp = temp->proximo;
        }
        free(jogo->cobra.rabo);
        jogo->cobra.rabo = temp;
        jogo->cobra.rabo->proximo = NULL;
    }
}

int verificaColisao(EstadoJogo *jogo) {
    SegmentoCobra *temp = jogo->cobra.cabeca->proximo;
    while (temp != NULL) {
        if (jogo->cobra.cabeca->pos.x == temp->pos.x && jogo->cobra.cabeca->pos.y == temp->pos.y) {
            return 1;
        }
        temp = temp->proximo;
    }

    if (jogo->cobra.cabeca->pos.x <= 0 || jogo->cobra.cabeca->pos.x >= LARGURA - 1 ||
        jogo->cobra.cabeca->pos.y <= 0 || jogo->cobra.cabeca->pos.y >= ALTURA - 1) {
        return 1;
    }

    return 0;
}

void endGame(EstadoJogo *jogo) {
    screenClear();
    printf("Game Over!\n");
    printf("Pontuacao final: %d\n", jogo->pontuacao);
    screenUpdate(); //serve para atualizar a tela do console após terem sido feitas todas as operações de renderização
}

void espera(int milissegundos) {
    timerUpdateTimer(milissegundos); //serve para atualizar o temporizador utilizado em um programa.
    while (!timerTimeOver()) { //espera até que o temporizador expire(enquanto nao expirar continuar rolando)
    }
}

int main() {
    EstadoJogo jogo;
    inicializaJogo(&jogo);

    int dx = 1, dy = 0;

    screenInit(0); //é usada para inicializar a tela do console com determinadas configurações.
    keyboardInit(); //é usada para inicializar o sistema de entrada de teclado
    timerInit(100); //inicializa o temporizador com um intervalo de 100 milissegundos

    while (!jogo.fimDeJogo) {
        entrada(&dx, &dy);
        atualizaCobra(&jogo, dx, dy);
        render(&jogo);
        espera(100);
        jogo.fimDeJogo = verificaColisao(&jogo);
    }

    endGame(&jogo);

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}