#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>

enum GameState {
    STATE_MAIN_MENU,
    STATE_PLAYING,
    STATE_GAME_OVER
};

void gameLoop();