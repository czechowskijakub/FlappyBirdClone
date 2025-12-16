#include "../Headers/sfx.h"

static Sounds sounds;

bool initAudio() {
    SDL_Init(SDL_INIT_AUDIO);
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_Log("Mix_OpenAudio error: %s", Mix_GetError());
        return true;
    }

    Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
    sounds.coinSFX = Mix_LoadWAV("sound/mario_coin.mp3");
    if (!sounds.coinSFX) {
        printf("<<< SOUND LOAD ERROR: %s >>>", Mix_GetError());
    } 

    sounds.bgMusic = Mix_LoadMUS("sound/cipher.mp3");
    if (!sounds.bgMusic) {
        printf("<<< SOUND LOAD ERROR: %s >>>", Mix_GetError());
    } 

    return false;
}

void playScoreSFX() {
    int channel = Mix_PlayChannel(-1, sounds.coinSFX, 0);
    if (channel != -1) {
        Mix_Volume(channel, MIX_MAX_VOLUME / 8);
    }
}

void playBGMusic() {
    Mix_PlayMusic(sounds.bgMusic, -1);
}

void quitAudio() {
    Mix_FreeChunk(sounds.coinSFX);
    Mix_FreeMusic(sounds.bgMusic);
    Mix_CloseAudio();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}