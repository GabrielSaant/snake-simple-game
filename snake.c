#include "snake.h"
#include <stdlib.h>
#include <time.h>

void gerar_comida(Comida *comida, Cobra *cobra) {
    bool sobrepoe;
    do {
        sobrepoe = false;
        comida->x = (rand() % (LARGURA_TELA / TAMANHO_CELULA)) * TAMANHO_CELULA;
        comida->y = (rand() % (ALTURA_TELA / TAMANHO_CELULA)) * TAMANHO_CELULA;

        for (int i = 0; i < cobra->tamanho; i++) {
            if (comida->x == cobra->corpo[i].x && comida->y == cobra->corpo[i].y) {
                sobrepoe = true;
                break;
            }
        }
    } while (sobrepoe);
}

bool colisao(Cobra *cobra) {
    if (cobra->corpo[0].x < 0 || cobra->corpo[0].x >= LARGURA_TELA ||
        cobra->corpo[0].y < 0 || cobra->corpo[0].y >= ALTURA_TELA) {
        return true;
    }

    for (int i = 1; i < cobra->tamanho; i++) {
        if (cobra->corpo[0].x == cobra->corpo[i].x && cobra->corpo[0].y == cobra->corpo[i].y) {
            return true;
        }
    }

    return false;
}

void inicializar_jogo(Cobra *cobra, Comida *comida) {
    cobra->tamanho = 1;
    cobra->corpo[0].x = LARGURA_TELA / 2;
    cobra->corpo[0].y = ALTURA_TELA / 2;
    cobra->direcao = DIREITA;

    srand(time(NULL));
    gerar_comida(comida, cobra);
}

void processar_eventos(ALLEGRO_EVENT_QUEUE *fila_eventos, Cobra *cobra, bool *game_over) {
    ALLEGRO_EVENT evento;
    while (al_get_next_event(fila_eventos, &evento)) {
        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            *game_over = true;
        } else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (evento.keyboard.keycode) {
                case ALLEGRO_KEY_UP:    if (cobra->direcao != BAIXO) cobra->direcao = CIMA; break;
                case ALLEGRO_KEY_DOWN:  if (cobra->direcao != CIMA) cobra->direcao = BAIXO; break;
                case ALLEGRO_KEY_LEFT:  if (cobra->direcao != DIREITA) cobra->direcao = ESQUERDA; break;
                case ALLEGRO_KEY_RIGHT: if (cobra->direcao != ESQUERDA) cobra->direcao = DIREITA; break;
            }
        }
    }
}

void atualizar_jogo(Cobra *cobra, Comida *comida, int *pontuacao, bool *game_over) {
    Segmento nova_cabeca = cobra->corpo[0];
    switch (cobra->direcao) {
        case CIMA:    nova_cabeca.y -= TAMANHO_CELULA; break;
        case BAIXO:   nova_cabeca.y += TAMANHO_CELULA; break;
        case ESQUERDA: nova_cabeca.x -= TAMANHO_CELULA; break;
        case DIREITA: nova_cabeca.x += TAMANHO_CELULA; break;
    }

    for (int i = cobra->tamanho - 1; i > 0; i--) {
        cobra->corpo[i] = cobra->corpo[i - 1];
    }
    cobra->corpo[0] = nova_cabeca;

    if (cobra->corpo[0].x == comida->x && cobra->corpo[0].y == comida->y) {
        cobra->tamanho++;
        (*pontuacao)++;
        gerar_comida(comida, cobra);
    }

    if (colisao(cobra)) {
        *game_over = true;
    }
}

void desenhar_jogo(Cobra *cobra, Comida *comida, int pontuacao, ALLEGRO_FONT *fonte) {
    al_clear_to_color(al_map_rgb(0, 0, 0)); 
    for (int i = 0; i < cobra->tamanho; i++) {
        al_draw_filled_rectangle(cobra->corpo[i].x, cobra->corpo[i].y,
                                cobra->corpo[i].x + TAMANHO_CELULA, cobra->corpo[i].y + TAMANHO_CELULA,
                                al_map_rgb(0, 255, 0)); 
    }
    al_draw_filled_rectangle(comida->x, comida->y, comida->x + TAMANHO_CELULA, comida->y + TAMANHO_CELULA, al_map_rgb(255, 0, 0)); 
    al_draw_textf(fonte, al_map_rgb(255, 255, 255), 10, 10, 0, "Pontuação: %d", pontuacao); 
    al_flip_display();
}
