#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "../Headers/game.h"
#include "../Headers/bird.h"
#define SCREEN_WIDTH    1920
#define SCREEN_HEIGHT   1080

void buildBird(struct Game* game, struct Bird* bird) {
    bird->fallSpeed = 1.f;

    int spriteWidth = 85;
    int spriteHeight = 60;
    
    bird->canvas = (SDL_Rect){spriteWidth, (SCREEN_HEIGHT / 2) - spriteHeight, spriteWidth, spriteHeight};
    bird->texture = IMG_LoadTexture(game->renderer, "images/Bird/bird.png");
    if (!bird->texture) { 
        fprintf(stderr, "<< TEXTURE NOT LOADED: %s >>", IMG_GetError()); 
    }
}

void birdJump(struct Bird* bird) {
    bird->fallSpeed = -10.f;
}

void birdFall(struct Bird* bird) {
    float gravity = 0.5f;
    bird->fallSpeed += gravity;
    bird->canvas.y += bird->fallSpeed;
}