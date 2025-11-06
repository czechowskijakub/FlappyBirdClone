#include "../Headers/pipe.h"
#include "../Headers/game.h"
#include "../Headers/renderer.h"

#define WINDOW_TITLE    "C Project"
#define SCREEN_WIDTH    1920
#define SCREEN_HEIGHT   1080
#define IMAGE_FLAGS     IMG_INIT_PNG
#define TEXT_SIZE       50
#define PIPE_WIDTH      200
#define PIPE_HEIGHT     800

struct pipePair {
    SDL_Rect rectUp;
    SDL_Rect rectDown;
    
    SDL_Texture* pipeUp;
    SDL_Texture* pipeDown;
};

int scaleHeight(int image_x, int image_y) {
    return image_y * 100 / image_x;
}

void buildPipes(struct Game* game, struct pipePair* obstacles, int count) {

    for (struct pipePair* it = obstacles; it < obstacles + count; it++) {
        it->pipeDown = IMG_LoadTexture(game->renderer, "images/obstacles/Pipe_Up_2.png");
        it->pipeUp = IMG_LoadTexture(game->renderer, "images/obstacles/Pipe_Down_2.png");

        if (!it->pipeUp || !it->pipeDown) {
            fprintf(stderr, "<< TEXTURE NOT LOADED: %s >>", IMG_GetError());
            break;
        }
    }
    
    int spriteOffset = 120;
    obstacles[0].rectUp = (SDL_Rect){(SCREEN_WIDTH * 5/4), (SCREEN_HEIGHT - (SCREEN_HEIGHT - PIPE_HEIGHT - spriteOffset)), PIPE_WIDTH, PIPE_HEIGHT};      // by subtracting from PIPE_HEIGHT, we push the pipe from the top upwards, so we just offset it up
    obstacles[0].rectDown = (SDL_Rect){(SCREEN_WIDTH * 5/4), -spriteOffset, PIPE_WIDTH, PIPE_HEIGHT};                                                     // by reversing, we push the pipe from the top downwards, so we just offset it down

    obstacles[1].rectUp = (SDL_Rect){(SCREEN_WIDTH * 7/4), (SCREEN_HEIGHT - (SCREEN_HEIGHT - PIPE_HEIGHT + 400 - spriteOffset)), PIPE_WIDTH, PIPE_HEIGHT};
    obstacles[1].rectDown = (SDL_Rect){(SCREEN_WIDTH * 7/4), -400 - spriteOffset, PIPE_WIDTH, PIPE_HEIGHT};

    obstacles[2].rectUp = (SDL_Rect){(SCREEN_WIDTH * 9/4), (SCREEN_HEIGHT - (SCREEN_HEIGHT - PIPE_HEIGHT + 200 - spriteOffset)), PIPE_WIDTH, PIPE_HEIGHT};
    obstacles[2].rectDown = (SDL_Rect){(SCREEN_WIDTH * 9/4), -200 - spriteOffset, PIPE_WIDTH, PIPE_HEIGHT};

}