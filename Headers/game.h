#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>

#include "../Headers/main_menu.h"
#include "../Headers/pipe.h"
#include "../Headers/play.h"
#include "../Headers/renderer.h"
#include "../Headers/maps.h"
#include "../Headers/randomizer.h"
#include "../Headers/bird.h"

enum GameState {
    STATE_MAIN_MENU,
    STATE_PLAYING,
    STATE_GAME_OVER
};

void gameLoop();