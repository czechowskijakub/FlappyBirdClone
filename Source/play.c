#include "../Headers/play.h"
#include "../Headers/bird.h"
#include "../Headers/randomizer.h"
#define SCREEN_WIDTH    1920
#define SCREEN_HEIGHT   1080
#define PIPE_WIDTH      200
#define PIPE_HEIGHT     800

bool playGame(struct Game* game, struct GameMaps* maps, struct pipePair* obstacles, int count, struct Bird* bird, SDL_Event* event) {
    
    int scrollSpeed = 8;
    game->text_title.x = -game->text_title.w;

    SDL_RenderCopy(game->renderer, maps->gameStart, NULL, &game->rectBackground);
    SDL_RenderCopy(game->renderer, maps->gameLoop, NULL, &game->rectBackground2);
    SDL_RenderCopy(game->renderer, maps->gameLoop, NULL, &game->rectBackground3);

    for (struct pipePair* it = obstacles; it < obstacles + count; it++) {
        SDL_RenderCopy(game->renderer, it->pipeDown, NULL, &it->rectDown);
        SDL_RenderCopy(game->renderer, it->pipeUp, NULL, &it->rectUp);  
    }

    SDL_RenderCopy(game->renderer, bird->texture, NULL, &bird->canvas);
    birdFall(bird);
    
    if (bird->canvas.y + bird->canvas.h >= SCREEN_HEIGHT) { return false; }
    if (bird->canvas.y <= 0) { return false; }

    game->rectBackground2.x -= scrollSpeed / 2;
    game->rectBackground3.x -= scrollSpeed / 2;

    for (struct pipePair* it = obstacles; it < obstacles + count; it++) {
        it->rectDown.x -= scrollSpeed;
        it->rectUp.x -= scrollSpeed;
    }

    if (game->rectBackground.x + game->rectBackground.w >= 0) {
        game->rectBackground.x -= scrollSpeed / 2;
    } 

    if (game->rectBackground2.x + game->rectBackground2.w <= 0) {
        game->rectBackground2.x = game->rectBackground3.x + game->rectBackground3.w;
    }

    if (game->rectBackground3.x + game->rectBackground3.w <= 0) {
        game->rectBackground3.x = game->rectBackground2.x + game->rectBackground2.w;
    }

    for (struct pipePair* it = obstacles; it < obstacles + count; it++) {
        int spriteOffset = 120;
        if (it->rectDown.x + it->rectDown.w <= 0) {
            int randomHeight = randomNo(600);
            it->rectUp = (SDL_Rect){(SCREEN_WIDTH * 5) / 4, (SCREEN_HEIGHT - (SCREEN_HEIGHT - PIPE_HEIGHT + randomHeight - spriteOffset)), PIPE_WIDTH, PIPE_HEIGHT};      // by subtracting from PIPE_HEIGHT, we push the pipe from the top upwards, so we just offset it up
            it->rectDown = (SDL_Rect){(SCREEN_WIDTH * 5) / 4, -randomHeight -spriteOffset, PIPE_WIDTH, PIPE_HEIGHT};    
        }
    }
    /*
    if (obstacles[2].rectDown.x + obstacles[2].rectDown.w <= 0) {
        obstacles[2].rectDown.x = 5/4 * SCREEN_WIDTH;
        obstacles[2].rectUp.x = 5/4 * SCREEN_WIDTH;
    }

    if (obstacles[1].rectDown.x + obstacles[1].rectDown.w <= 0) {
        obstacles[1].rectDown.x = 5/4 * SCREEN_WIDTH;
        obstacles[1].rectUp.x = 5/4 * SCREEN_WIDTH;
    }
    */
    return true;
}


void resetGame(struct Game* game, struct pipePair* obstacles, int count, struct Bird* bird) {
    int xStart = 0, yStart = 0;
    game->rectBackground = (SDL_Rect){xStart, yStart, SCREEN_WIDTH, SCREEN_HEIGHT};
    game->rectBackground2 = (SDL_Rect){game->rectBackground.w, yStart, SCREEN_WIDTH, SCREEN_HEIGHT};
    game->rectBackground3 = (SDL_Rect){game->rectBackground.w + game->rectBackground2.w, yStart, SCREEN_WIDTH, SCREEN_HEIGHT};
    
    int spriteOffset = 120;
    obstacles[0].rectUp = (SDL_Rect){(SCREEN_WIDTH * 5/4), (SCREEN_HEIGHT - (SCREEN_HEIGHT - PIPE_HEIGHT - spriteOffset)), PIPE_WIDTH, PIPE_HEIGHT};      // by subtracting from PIPE_HEIGHT, we push the pipe from the top upwards, so we just offset it up
    obstacles[0].rectDown = (SDL_Rect){(SCREEN_WIDTH * 5/4), -spriteOffset, PIPE_WIDTH, PIPE_HEIGHT};                                                     // by reversing, we push the pipe from the top downwards, so we just offset it down

    obstacles[1].rectUp = (SDL_Rect){(SCREEN_WIDTH * 7/4), (SCREEN_HEIGHT - (SCREEN_HEIGHT - PIPE_HEIGHT + 400 - spriteOffset)), PIPE_WIDTH, PIPE_HEIGHT};
    obstacles[1].rectDown = (SDL_Rect){(SCREEN_WIDTH * 7/4), -400 - spriteOffset, PIPE_WIDTH, PIPE_HEIGHT};

    obstacles[2].rectUp = (SDL_Rect){(SCREEN_WIDTH * 9/4), (SCREEN_HEIGHT - (SCREEN_HEIGHT - PIPE_HEIGHT + 200 - spriteOffset)), PIPE_WIDTH, PIPE_HEIGHT};
    obstacles[2].rectDown = (SDL_Rect){(SCREEN_WIDTH * 9/4), -200 - spriteOffset, PIPE_WIDTH, PIPE_HEIGHT};

    int spriteWidth = 85;
    int spriteHeight = 60;
    bird->canvas.y = (SCREEN_HEIGHT / 2) - spriteHeight;
    bird->fallSpeed = 1.f;
}
