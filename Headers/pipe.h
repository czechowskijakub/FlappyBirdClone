#include <SDL2/SDL.h>

struct Game;

struct pipePair {
    SDL_Rect rectUp;
    SDL_Rect rectDown;
    
    SDL_Texture* pipeUp;
    SDL_Texture* pipeDown;

    bool isPassed;
};


void buildPipes(struct Game* game, struct pipePair* obstacles, int count);
int scaleHeight(int image_x, int image_y);