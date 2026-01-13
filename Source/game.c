#include "../Headers/game.h"
#define SCREEN_WIDTH    1920
#define SCREEN_HEIGHT   1080

void gameLoop() {
    struct Game game = {
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

        .pipeTextureUp = NULL,
        .pipeTextureDown = NULL,
        .pipeRectUp = {0, 0, 0, 0},
        .pipeRectDown = {0, 0, 0, 0},
    };

    if (SDL_Initialize(&game)) {
        gameCleanup(&game, EXIT_FAILURE);
    }
    
    // instantiate one window and renderer; so we can easily swap backgrounds
    loadWindow(&game);
    loadRenderer(&game);

    struct GameMaps maps = {
        maps.gameMenu = loadBackground(&game, "maps/BG_Flappy_Start.png"),
        maps.gameStart = loadBackground(&game, "maps/BG_Flappy_Start.png"),
        maps.gameLoop = loadBackground(&game, "maps/BG_Flappy_Loop.png"),
        maps.gameLoop2 = loadBackground(&game, "maps/BG_Flappy_Loop.png"),
    };
    int count = 3;
    struct pipePair obstacles[count];
    buildPipes(&game, obstacles, count);

    game.background = maps.gameMenu;
    game.displayRect = (SDL_Rect){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    int xStart = 0, yStart = 0;
    game.rectBackground = (SDL_Rect){xStart, yStart, SCREEN_WIDTH, SCREEN_HEIGHT};
    game.rectBackground2 = (SDL_Rect){game.rectBackground.w, yStart, SCREEN_WIDTH, SCREEN_HEIGHT};
    game.rectBackground3 = (SDL_Rect){game.rectBackground.w + game.rectBackground2.w, yStart, SCREEN_WIDTH, SCREEN_HEIGHT};

    if (loadFontAndText(&game, "Floppy Burd", game.text_color, 50)) {
        gameCleanup(&game, EXIT_FAILURE);
    }

    static enum GameState currentState = STATE_MAIN_MENU;

    while (true) {
        SDL_Event event;
        
        Uint8 r = randomNo();
        Uint8 g = randomNo();
        Uint8 b = randomNo();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                gameCleanup(&game, EXIT_SUCCESS);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_B:
                    currentState = STATE_PLAYING;
                    break;
                case SDL_SCANCODE_C:
                    currentState = STATE_MAIN_MENU;
                    game.rectBackground = (SDL_Rect){xStart, yStart, SCREEN_WIDTH, SCREEN_HEIGHT};
                    game.rectBackground2 = (SDL_Rect){game.rectBackground.w, yStart, SCREEN_WIDTH, SCREEN_HEIGHT};
                    game.rectBackground3 = (SDL_Rect){game.rectBackground.w + game.rectBackground2.w, yStart, SCREEN_WIDTH, SCREEN_HEIGHT};
                    break;
                case SDL_SCANCODE_ESCAPE:
                    gameCleanup(&game, EXIT_SUCCESS);
                    break;
                case SDL_SCANCODE_SPACE:
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
            game.text_title.x = (SCREEN_WIDTH - game.text_title.w) / 2;
            displayMainMenu(&game);
            
        }
        
        if (currentState == STATE_PLAYING) {
            playGame(&game, &maps, obstacles, count);
        }

        SDL_RenderCopy(game.renderer, game.text_image, NULL, &game.text_title);

        SDL_RenderPresent(game.renderer);

        SDL_Delay(16);
    }
}
