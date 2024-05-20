#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define LARGURA 20
#define ALTURA 20

//funcoes aqui:
void render() { // render = desenhar a tela do jogo
    printf("\033[H"); // limpa a tela 
/*
Escape ANSI: \033 eh o caractere de escape ANSI. Ele indica o início de uma sequência de controle;
Cursor Home: [H eh o comando para mover o cursor para a posição (1,1) na tela. A sequência completa é \033[H.
*/

for (int x = 0; x < LARGURA; x++) { //borda superior
        printf("#");
    }
        printf("\n");

    for (int y = 1; y < ALTURA - 1; y++) { //bordas laterais e o interior da tela
        printf("#"); //borda esquerda
        for (int x = 1; x < LARGURA - 1; x++) {
            printf(" "); //espaço vazio
        }
        printf("#\n"); //borda direita
    }
        for (int x = 0; x < LARGURA; x++) { //borda inferior
        printf("#");
    }
    printf("\n");
}



int main(){
    int cobra[300][2]; //matriz do corpinho da cobra
    int maca[2]; //matriz da maçã
    int pontos = 1; //pontuação do player
    int cx = 2, cy = 2; //coordenadas x e y
//return x;
}