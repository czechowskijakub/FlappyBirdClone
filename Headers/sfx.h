#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

typedef struct {
    Mix_Chunk* coinSFX;
    Mix_Music* bgMusic;
} Sounds;

bool initAudio();
void playScoreSFX();
void playBGMusic();
void quitAudio();

#pragma end