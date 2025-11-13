#include "../Headers/main_menu.h"
#include <math.h>
#define SCREEN_WIDTH    1920
#define SCREEN_HEIGHT   1080

void textUpdate(struct Game* game) {
    float time = SDL_GetTicks() / 500.f;
    int timer = SDL_GetTicks() / 500.f;
    int baseY = 50;
    int baseX = (SCREEN_WIDTH - game->text_title.w) / 2;
    int amplitude = 15;
    game->text_title.y = baseY + (int)(sin(time) * amplitude);
    game->text_title.x = baseX;
}

void displayMainMenu(struct Game* game) {
    textUpdate(game);
    SDL_RenderCopy(game->renderer, game->background, NULL, &game->displayRect);
    SDL_RenderCopy(game->renderer, game->text_canvas, NULL, &game->text_enter);
}