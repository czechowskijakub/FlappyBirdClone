#pragma once
#include <SDL2/SDL.h>

struct Game;

struct Bird {
    SDL_Rect canvas;
    SDL_Texture* texture;
    float fallSpeed;
};

void buildBird(struct Game* game, struct Bird* bird);
void birdJump(struct Bird* bird);
void birdFall(struct Bird* bird);
