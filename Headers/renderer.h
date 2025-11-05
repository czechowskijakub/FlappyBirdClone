#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

struct Game {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* background;

    TTF_Font* textFont;
    SDL_Color text_color;
    SDL_Rect text_title;
    SDL_Texture* text_image;
    int text_xVel;
    int text_yVel;

    SDL_Rect rectBackground;
    SDL_Rect rectBackground2;
    SDL_Rect rectBackground3;
    SDL_Rect displayRect;

    SDL_Texture* pipeTextureUp;
    SDL_Texture* pipeTextureDown;
    SDL_Rect pipeRectUp;
    SDL_Rect pipeRectDown;

};

bool SDL_Initialize(struct Game* game);
SDL_Window* loadWindow(struct Game* game);
SDL_Renderer* loadRenderer(struct Game* game);
SDL_Texture* loadBackground(struct Game* game, const char* imageTitle);
bool loadFontAndText(struct Game* game, const char* text, SDL_Color color, int textSize);
void gameCleanup(struct Game* game, int exitStatus);

#endif