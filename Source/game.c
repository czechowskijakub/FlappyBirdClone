#include "../Headers/game.h"
#include "../Headers/main_menu.h"
#include "../Headers/pipe.h"
#include "../Headers/play.h"
#include "../Headers/renderer.h"
#include "../Headers/maps.h"
#include "../Headers/randomizer.h"
#include "../Headers/bird.h"
#include "../Headers/sfx.h"
#define SCREEN_WIDTH    1920
#define SCREEN_HEIGHT   1080

void gameLoop() {
    struct Game game = {
        .file = NULL,
        .window = NULL,
        .renderer = NULL,
        .background = NULL,

        .rectBackground = {0, 0, 0, 0},
        .rectBackground2 = {0, 0, 0, 0},
        .rectBackground3 = {0, 0, 0, 0},
        .displayRect = {0, 0, 0, 0},
        
        .textFont = NULL,
        .text_color = {0, 255, 64, 255},
        .text_title = {0, 0, 0, 0},
        .text_image = NULL,
        .text_xVel = 3,
        .text_yVel = 3,

        .text_enter = {0, 0, 0, 0},
        .text_canvas = NULL,

        .pipeTextureUp = NULL,
        .pipeTextureDown = NULL,
        .pipeRectUp = {0, 0, 0, 0},
        .pipeRectDown = {0, 0, 0, 0},
        .best = 0,
        .score = 0,
        .scoreFont = NULL,
        .scoreTexture = NULL,
        .scoreRect = (SDL_Rect){20, 20, 0, 0},

        .overTexture = NULL,
        .overRect = (SDL_Rect){0, 0, 0, 0},

        .overCanvas = NULL,
        .overCanvasRect = (SDL_Rect){0, 0, 0, 0},

        .overScore = NULL,
        .overScoreRect = (SDL_Rect){0, 0, 0, 0},
        
        .highScore = NULL,
        .highScoreCanvas = (SDL_Rect){0, 0, 0, 0},
        
        .isInit = false
    };

    if (SDL_Initialize(&game)) {
        gameCleanup(&game, EXIT_FAILURE);
    }

    if (initAudio()) {
        quitAudio();
    }

    playBGMusic();

    loadHighScore(&game);
    Uint32 lastTick = SDL_GetTicks();
    float deltaTime;

    game.scoreFont = TTF_OpenFont("fonts/Returns.ttf", 50);
    
    loadWindow(&game);
    loadRenderer(&game);

    struct GameMaps maps = {
        maps.gameMenu = loadBackground(&game, "maps/BG_Flappy_Start.png"),
        maps.gameStart = loadBackground(&game, "maps/BG_Flappy_Start.png"),
        maps.gameLoop = loadBackground(&game, "maps/BG_Flappy_Loop.png"),
    };

    int count = 3;
    struct pipePair obstacles[count];
    buildPipes(&game, obstacles, count);

    game.background = maps.gameMenu;
    game.displayRect = (SDL_Rect){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    if (loadFontAndText(&game, "Flappy Burd", game.text_color, 50, (SCREEN_WIDTH / 2), 100)) {
        gameCleanup(&game, EXIT_FAILURE);
    }

    if (loadInstructions(&game, "press enter", game.text_color, 15, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT - 400))) {
        gameCleanup(&game, EXIT_FAILURE);
    }

    static enum GameState currentState = STATE_MAIN_MENU;
    struct Bird bird;
    buildBird(&game, &bird);

    resetGame(&game, obstacles, count, &bird);

    int xStart = 0, yStart = 0;
    while (true) {
        
        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTick) / 1000.0f;
        lastTick = currentTime;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                gameCleanup(&game, EXIT_SUCCESS);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_RETURN:
                    if (currentState == STATE_MAIN_MENU) {
                        currentState = STATE_PLAYING;
                    } else if (currentState == STATE_GAME_OVER) {
                        resetGame(&game, obstacles, count, &bird);
                        gameOver(&game);
                        currentState = STATE_PLAYING;
                    }
                    break;
                case SDL_SCANCODE_ESCAPE:
                    gameCleanup(&game, EXIT_SUCCESS);
                    break;
                case SDL_SCANCODE_SPACE:
                    birdJump(&bird);
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }

        SDL_RenderClear(game.renderer);
        SDL_RenderCopy(game.renderer, game.background, NULL, NULL);

        if (currentState == STATE_MAIN_MENU) {
            displayMainMenu(&game);
            resetGame(&game, obstacles, count, &bird);
        }
        
        if (currentState == STATE_PLAYING) {
            if (!playGame(&game, &maps, obstacles, count, &bird, &event)) {
                gameOver(&game);
                currentState = STATE_GAME_OVER;
            }
            updateScore(&game);
        }

        if (currentState == STATE_GAME_OVER) {
            overDown(&game);
        }

        SDL_RenderCopy(game.renderer, game.text_image, NULL, &game.text_title);

        SDL_RenderPresent(game.renderer);

        SDL_Delay(16);
    }
    quitAudio();
}
