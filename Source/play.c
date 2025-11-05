#include "../Headers/play.h"
#define SCREEN_WIDTH    1920


void playGame(struct Game* game, struct GameMaps* maps, struct pipePair* obstacles) {
    
    int scrollSpeed = 5;
    game->text_title.x = -game->text_title.w;

    SDL_RenderCopy(game->renderer, maps->gameStart, NULL, &game->rectBackground);
    SDL_RenderCopy(game->renderer, maps->gameLoop, NULL, &game->rectBackground2);
    SDL_RenderCopy(game->renderer, maps->gameLoop, NULL, &game->rectBackground3);

    SDL_RenderCopy(game->renderer, obstacles[0].pipeDown, NULL, &obstacles[0].rectDown);
    SDL_RenderCopy(game->renderer, obstacles[0].pipeUp, NULL, &obstacles[0].rectUp);

    SDL_RenderCopy(game->renderer, obstacles[1].pipeDown, NULL, &obstacles[1].rectDown);
    SDL_RenderCopy(game->renderer, obstacles[1].pipeUp, NULL, &obstacles[1].rectUp);

    SDL_RenderCopy(game->renderer, obstacles[2].pipeDown, NULL, &obstacles[2].rectDown);
    SDL_RenderCopy(game->renderer, obstacles[2].pipeUp, NULL, &obstacles[2].rectUp);
    
    game->rectBackground2.x -= scrollSpeed;
    game->rectBackground3.x -= scrollSpeed;

    obstacles[0].rectDown.x -= scrollSpeed;
    obstacles[0].rectUp.x -= scrollSpeed;

    obstacles[1].rectDown.x -= scrollSpeed;
    obstacles[1].rectUp.x -= scrollSpeed;

    obstacles[2].rectDown.x -= scrollSpeed;
    obstacles[2].rectUp.x -= scrollSpeed;

    if (game->rectBackground.x + game->rectBackground.w >= 0) {
        game->rectBackground.x -= scrollSpeed;
    } 

    if (game->rectBackground2.x + game->rectBackground2.w <= 0) {
        game->rectBackground2.x = game->rectBackground3.x + game->rectBackground3.w;
    }

    if (game->rectBackground3.x + game->rectBackground3.w <= 0) {
        game->rectBackground3.x = game->rectBackground2.x + game->rectBackground2.w;
    }

    if (obstacles[2].rectDown.x + obstacles[0].rectDown.w <= 0) {
        obstacles[2].rectDown.x = 5/4 * SCREEN_WIDTH;
        obstacles[2].rectUp.x = 5/4 * SCREEN_WIDTH;
        
    }

    if (obstacles[1].rectDown.x + obstacles[1].rectDown.w <= 0) {
        obstacles[1].rectDown.x = 5/4 * SCREEN_WIDTH;
        obstacles[1].rectUp.x = 5/4 * SCREEN_WIDTH;
    }

    /*
    To do:
    make substitute pipepairs for each obstacle's expiration. After obstacle's disapearance, pick random obstacle from
    certain pipepair position and place it there.
    */ 
}
