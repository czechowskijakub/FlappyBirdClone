#include "../Headers/play.h"
#include "../Headers/bird.h"
#include "../Headers/randomizer.h"
#define SCREEN_WIDTH    1920
#define SCREEN_HEIGHT   1080
#define PIPE_WIDTH      200
#define PIPE_HEIGHT     800
#define START_POS       800

void updateScore(struct Game* game) {
    char buffer[32];
        sprintf(buffer, "%d", game->score);

        if (game->scoreTexture) {
            SDL_DestroyTexture(game->scoreTexture);
        }

        game->scoreTexture = renderText(game->renderer, game->textFont, buffer, (SDL_Color){255, 255, 255, 255}, &game->scoreRect);

        game->scoreRect.x = 40;
        game->scoreRect.y = 40;

        SDL_RenderCopy(game->renderer, game->scoreTexture, NULL, &game->scoreRect);
}

bool checkCollision(SDL_Rect a, SDL_Rect b) {
    return (a.x + a.w > b.x &&
            a.x < b.x + b.w &&
            a.y + a.h > b.y &&
            a.y < b.y + b.h
        );
}

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
    
    // "hitboxes"
    if (bird->canvas.y + bird->canvas.h >= SCREEN_HEIGHT) { return false; }
    if (bird->canvas.y <= 0) { return false; }
    for (short i = 0; i < count; i++) {
        if (checkCollision(bird->canvas, obstacles[i].rectDown) || checkCollision(bird->canvas, obstacles[i].rectUp)) {
            return false;
        }
    }

    for (short i = 0; i < count; i++) {
        if (bird->canvas.x + bird->canvas.w >= obstacles[i].rectDown.x + (obstacles[i].rectDown.w / 2) && !obstacles[i].isPassed) {
            game->score++;
            obstacles[i].isPassed = true;
        }
    }

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

    short spriteOffset = 120;
    short gap = 800;
    for (int i = 0; i < count; i++) {
        if (obstacles[i].rectDown.x + PIPE_WIDTH <= 0) {
            obstacles[i].isPassed = false;
            short nextIndex = (i - 1 + count) % count;
            short nextX = obstacles[nextIndex].rectDown.x + gap;

            short randomHeight = randomNo(600);
            obstacles[i].rectUp = (SDL_Rect){nextX, (SCREEN_HEIGHT - (SCREEN_HEIGHT - PIPE_HEIGHT + randomHeight - spriteOffset)), PIPE_WIDTH, PIPE_HEIGHT};
            obstacles[i].rectDown = (SDL_Rect){nextX, -randomHeight - spriteOffset, PIPE_WIDTH, PIPE_HEIGHT};
        }
    }

    return true;
}

void resetGame(struct Game* game, struct pipePair* obstacles, int count, struct Bird* bird) {
    unsigned xStart = 0, yStart = 0;
    game->rectBackground = (SDL_Rect){xStart, yStart, SCREEN_WIDTH, SCREEN_HEIGHT};
    game->rectBackground2 = (SDL_Rect){game->rectBackground.w, yStart, SCREEN_WIDTH, SCREEN_HEIGHT};
    game->rectBackground3 = (SDL_Rect){game->rectBackground.w + game->rectBackground2.w, yStart, SCREEN_WIDTH, SCREEN_HEIGHT};

    for (short i = 0; i < count; i++) {
        obstacles[i].isPassed = false;
    }
    
    short spriteOffset = 120;
    obstacles[0].rectUp = (SDL_Rect){(START_POS * 3), (SCREEN_HEIGHT - (SCREEN_HEIGHT - PIPE_HEIGHT - spriteOffset)), PIPE_WIDTH, PIPE_HEIGHT};      // by subtracting from PIPE_HEIGHT, we push the pipe from the top upwards, so we just offset it up
    obstacles[0].rectDown = (SDL_Rect){(START_POS * 3), -spriteOffset, PIPE_WIDTH, PIPE_HEIGHT};                                                     // by reversing, we push the pipe from the top downwards, so we just offset it down

    obstacles[1].rectUp = (SDL_Rect){(START_POS * 4), (SCREEN_HEIGHT - (SCREEN_HEIGHT - PIPE_HEIGHT + 400 - spriteOffset)), PIPE_WIDTH, PIPE_HEIGHT};
    obstacles[1].rectDown = (SDL_Rect){(START_POS * 4), -400 - spriteOffset, PIPE_WIDTH, PIPE_HEIGHT};

    obstacles[2].rectUp = (SDL_Rect){(START_POS * 5), (SCREEN_HEIGHT - (SCREEN_HEIGHT - PIPE_HEIGHT + 200 - spriteOffset)), PIPE_WIDTH, PIPE_HEIGHT};
    obstacles[2].rectDown = (SDL_Rect){(START_POS * 5), -200 - spriteOffset, PIPE_WIDTH, PIPE_HEIGHT};

    short spriteWidth = 85;
    short spriteHeight = 60;
    bird->canvas.y = (SCREEN_HEIGHT / 2) - spriteHeight;
    bird->fallSpeed = 1.f;
}