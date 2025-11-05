#include "../Headers/play.h"
#define SCREEN_WIDTH    1920


void playGame(struct Game* game, struct GameMaps* maps, struct pipePair* obstacles, int count) {
    
    int scrollSpeed = 5;
    game->text_title.x = -game->text_title.w;

    SDL_RenderCopy(game->renderer, maps->gameStart, NULL, &game->rectBackground);
    SDL_RenderCopy(game->renderer, maps->gameLoop, NULL, &game->rectBackground2);
    SDL_RenderCopy(game->renderer, maps->gameLoop, NULL, &game->rectBackground3);

    for (struct pipePair* it = obstacles; it < obstacles + count; it++) {
        SDL_RenderCopy(game->renderer, it->pipeDown, NULL, &it->rectDown);
        SDL_RenderCopy(game->renderer, it->pipeUp, NULL, &it->rectUp);  
    }
    
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
}
