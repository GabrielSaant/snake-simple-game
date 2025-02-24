#include "snake.h"

int main() {
    if (!al_init()) {
        fprintf(stderr, "Falha ao inicializar Allegro.\n");
        return -1;
    }

    ALLEGRO_DISPLAY *display = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!display) {
        fprintf(stderr, "Falha ao criar display.\n");
        return -1;
    }

    al_init_primitives_addon();
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_FONT *fonte = al_create_builtin_font();

    Cobra cobra;
    Comida comida;
    int pontuacao = 0;
    bool game_over = false;

    inicializar_jogo(&cobra, &comida);

    ALLEGRO_EVENT_QUEUE *fila_eventos = al_create_event_queue();
    al_register_event_source(fila_eventos, al_get_display_event_source(display));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());

    while (!game_over) {
        processar_eventos(fila_eventos, &cobra, &game_over);
        atualizar_jogo(&cobra, &comida, &pontuacao, &game_over);
        desenhar_jogo(&cobra, &comida, pontuacao, fonte);
        al_rest(1.0 / VELOCIDADE); 
    }

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(fonte, al_map_rgb(255, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2, ALLEGRO_ALIGN_CENTER, "Game Over!");
    al_draw_textf(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, ALTURA_TELA / 2 + 30, ALLEGRO_ALIGN_CENTER, "Pontuação: %d", pontuacao);
    al_flip_display();
    al_rest(3); 

    al_destroy_display(display);
    al_destroy_event_queue(fila_eventos);
    al_destroy_font(fonte);

    return 0;
}
