#include "../Headers/pipe.h"
#include "../Headers/game.h"
#include "../Headers/renderer.h"

#define WINDOW_TITLE    "C Project"
#define SCREEN_WIDTH    1920
#define SCREEN_HEIGHT   1080
#define IMAGE_FLAGS     IMG_INIT_PNG
#define TEXT_SIZE       50
#define PIPE_WIDTH      100
#define PIPE_HEIGHT     200

struct pipePair {
    SDL_Rect rectUp;
    SDL_Rect rectDown;
    
    SDL_Texture* pipeUp;
    SDL_Texture* pipeDown;
};

int scaleHeight(int image_x, int image_y) {
    return image_y * 100 / image_x;
}

void buildPipes(struct Game* game, struct pipePair* obstacles) {

    int ob2_fill = 554;

    obstacles[0].pipeUp = IMG_LoadTexture(game->renderer, "images/obstacles/Pipe_Up.png");
    obstacles[0].pipeDown = IMG_LoadTexture(game->renderer, "images/obstacles/Pipe_Down.png");

    obstacles[1].pipeUp = IMG_LoadTexture(game->renderer, "images/obstacles/Pipe_Up_2.png");
    obstacles[1].pipeDown = IMG_LoadTexture(game->renderer, "images/obstacles/Pipe_Down_2.png");

    obstacles[2].pipeUp = IMG_LoadTexture(game->renderer, "images/obstacles/Pipe_Up_3.png");
    obstacles[2].pipeDown = IMG_LoadTexture(game->renderer, "images/obstacles/Pipe_Down_3.png");
    /*
    int i = 0;
    while (obstacles != NULL) {
        obstacles[i].pipeUp = IMG_LoadTexture(game->renderer, "images/obstacles/Pipe_Obstacle.png");
        obstacles[i].pipeDown = IMG_LoadTexture(game->renderer, "images/obstacles/Pipe_Obstacle_UpDown.png");
        i++;
    }*/
    if (!obstacles[0].pipeUp || !obstacles[0].pipeDown) {
        fprintf(stderr, "<< TEXTURE NOT LOADED: %s >>", IMG_GetError());
    }

    obstacles[0].rectUp = (SDL_Rect){(SCREEN_WIDTH * 5/4), (SCREEN_HEIGHT - PIPE_HEIGHT), PIPE_WIDTH, PIPE_HEIGHT};
    obstacles[0].rectDown = (SDL_Rect){(SCREEN_WIDTH * 5/4), 0, PIPE_WIDTH, scaleHeight(786, 2366)};

    obstacles[1].rectUp = (SDL_Rect){(SCREEN_WIDTH * 7/4), (SCREEN_HEIGHT - 554), PIPE_WIDTH, 554};
    obstacles[1].rectDown = (SDL_Rect){(SCREEN_WIDTH * 7/4), 0, PIPE_WIDTH, scaleHeight(786, 648)};

    obstacles[2].rectUp = (SDL_Rect){(SCREEN_WIDTH * 9/4), (SCREEN_HEIGHT - PIPE_HEIGHT), PIPE_WIDTH, PIPE_HEIGHT};
    obstacles[2].rectDown = (SDL_Rect){(SCREEN_WIDTH * 9/4), 0, PIPE_WIDTH, (854 - PIPE_HEIGHT)};

}

void movePipes(struct Game* game) {
    SDL_RenderCopy(game->renderer, game->pipeTextureDown, NULL, &game->pipeRectDown);
    SDL_RenderCopy(game->renderer, game->pipeTextureUp, NULL, &game->pipeRectUp);
    game->pipeRectDown.x -= 5;
    game->pipeRectUp.x -= 5;
}