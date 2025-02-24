#ifndef SNAKE.H
#define SNAKE.H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <stdio.h>

#define LARGURA_TELA 800
#define ALTURA_TELA 600
#define TAMANHO_CELULA 20
#define VELOCIDADE 5


typedef enum {
    CIMA, BAIXO, ESQUERDA, DIREITA
} Direcao;

typedef struct {
    int x, y;
} Segmento;

typedef struct {
    Segmento corpo[100]; // Lista de segmentos
    int tamanho;         // Tamanho da cobra
    Direcao direcao;     // Direção atual
} Cobra;

typedef struct {
    int x, y;
} Comida;

void gerar_comida(Comida *comida, Cobra *cobra);
bool colisao(Cobra *cobra);
void inicializar_jogo(Cobra *cobra, Comida *comida);
void processar_eventos(ALLEGRO_EVENT_QUEUE *fila_eventos, Cobra *cobra, bool *game_over);
void atualizar_jogo(Cobra *cobra, Comida *comida, int *pontuacao, bool *game_over);
void desenhar_jogo(Cobra *cobra, Comida *comida, int pontuacao, ALLEGRO_FONT *fonte);

#endif
