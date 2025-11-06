#pragma once
#include <SDL2/SDL.h>

struct Bird {
    SDL_Rect canvas;
    SDL_Texture* texture;
    //float jumpStrength;
    float fallSpeed;
};

void buildBird(struct Game* game, struct Bird* bird);
void birdJump(struct Bird* bird);
