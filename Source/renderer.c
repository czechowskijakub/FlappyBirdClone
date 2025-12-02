#include "../Headers/renderer.h"

#define WINDOW_TITLE    "Flappy Bird"
#define SCREEN_WIDTH    1920
#define SCREEN_HEIGHT   1080
#define IMAGE_FLAGS     IMG_INIT_PNG
#define TEXT_SIZE       50

void gameCleanup(struct Game* game, int exitStatus) {
    SDL_DestroyTexture(game->text_image);
    TTF_CloseFont(game->textFont);
    SDL_DestroyTexture(game->background);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    exit(exitStatus);
}

bool SDL_Initialize(struct Game* game) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        fprintf(stderr, "<< SDL DID NOT INITIALIZE CORRECTLY: %s >>.\n", SDL_GetError());
        return true;
    }

    int imgInit = IMG_Init(IMAGE_FLAGS);
    if ((imgInit & IMAGE_FLAGS) != IMAGE_FLAGS) {
        fprintf(stderr, "<< SDL_IMAGE DID NOT INITIALIZE CORRECTLY: %s >>.\n", IMG_GetError());
        return true;
    }
    
    if (TTF_Init()) { 
        fprintf(stderr, "<< TTF WAS NOT CREATED: %s >>\n", SDL_GetError());
        return true;
    }

    return false;
}

SDL_Window* loadWindow(struct Game* game) {
    game->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!game->window) {
        fprintf(stderr, "<< WINDOW WAS NOT CREATED: %s >>\n", SDL_GetError());
    }
    return game->window;
}

SDL_Renderer* loadRenderer(struct Game* game) {
    game->renderer = SDL_CreateRenderer(game->window, -1, 0);
    if (!game->renderer) {
        fprintf(stderr, "<< RENDERER WAS NOT CREATED: %s >>\n", SDL_GetError());
    }
    return game->renderer;
}

SDL_Texture* loadBackground(struct Game* game, const char* imageTitle) {
    char path[64] = "images/";
    snprintf(path + 7, sizeof(path) - 7, "%s", imageTitle);
    
    SDL_Texture* background = IMG_LoadTexture(game->renderer, path);
    if (!background) {
        fprintf(stderr, "<< TEXTURE DID NOT LOAD PROPERLY: %s >>.\n", IMG_GetError());
        return NULL;
    }

    return background;
}

bool loadFontAndText(struct Game* game, const char* text, SDL_Color color, int textSize, int x, int y) {
    game->textFont = TTF_OpenFont("fonts/Returns.ttf", textSize);
    if (!game->textFont) {
        fprintf(stderr, "<< FONT DID NOT LOAD PROPERLY: %s >>\n", TTF_GetError());
        return true;
    }

    SDL_Surface* surface = TTF_RenderText_Blended(game->textFont, text, color);
    if (!surface) {
        fprintf(stderr, "<< SURFACE DID NOT LOAD PROPERLY: %s >>\n", SDL_GetError());
        return true;
    }

    game->text_title.w = surface->w;
    game->text_title.h = surface->h;
    game->text_image = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    game->text_title.x = x - game->text_title.w / 2;
    game->text_title.y = y;

    if (!game->text_image) {
        fprintf(stderr, "<< TEXT IMAGE DID NOT LOAD PROPERLY: %s >>.\n", SDL_GetError());
        return true;
    }

    return false;
}

bool loadInstructions(struct Game* game, const char* text, SDL_Color color, int textSize, int x, int y) {
    game->textFont = TTF_OpenFont("fonts/Returns.ttf", textSize);
    if (!game->textFont) {
        fprintf(stderr, "<< FONT DID NOT LOAD PROPERLY: %s >>\n", TTF_GetError());
        return true;
    }

    SDL_Surface* surface = TTF_RenderText_Blended(game->textFont, text, color);
    if (!surface) {
        fprintf(stderr, "<< SURFACE DID NOT LOAD PROPERLY: %s >>\n", SDL_GetError());
        return true;
    }

    game->text_enter.w = surface->w;
    game->text_enter.h = surface->h;
    game->text_canvas = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    game->text_enter.x = x - game->text_enter.w / 2;
    game->text_enter.y = y;

    if (!game->text_canvas) {
        fprintf(stderr, "<< TEXT IMAGE DID NOT LOAD PROPERLY: %s >>.\n", SDL_GetError());
        return true;
    }

    return false;
}

SDL_Texture* renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, SDL_Rect* rectOut) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
     if (!surface) {
        fprintf(stderr, "<< SURFACE ERROR: %s >>\n", TTF_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        fprintf(stderr, "<< TEXTURE ERROR: %s >>\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return NULL;
    }

    rectOut->w = surface->w;
    rectOut->h = surface->h;

    SDL_FreeSurface(surface);
    return texture;
}