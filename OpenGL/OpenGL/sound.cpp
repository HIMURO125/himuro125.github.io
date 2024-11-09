#include "header.h"

Mix_Music* bgm1 = nullptr;
Mix_Music* bgm2 = nullptr;
Mix_Music* bgm3 = nullptr;
Mix_Chunk* foot = nullptr;
Mix_Chunk* key = nullptr;
Mix_Chunk* gate = nullptr;

bool initSDL() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        return false;
    }
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        return false;
    }
    return true;
}

void closeSDL() {
    Mix_FreeMusic(bgm1);
    Mix_FreeMusic(bgm2);
    Mix_FreeMusic(bgm3);
    Mix_FreeChunk(foot);
    Mix_FreeChunk(key);
    Mix_FreeChunk(gate);
    Mix_CloseAudio();
    SDL_Quit();
}


void LoadSound() {
    bgm1 = Mix_LoadMUS("bgm.mp3");
    bgm2 = Mix_LoadMUS("bgm2.mp3");
    bgm3 = Mix_LoadMUS("bgm3.mp3");
    foot = Mix_LoadWAV("foot.wav");
    key = Mix_LoadWAV("key.wav");
    gate = Mix_LoadWAV("gate.wav");
    if (!bgm1 || !bgm2 || !bgm3 || !foot || !key || !gate) {
        closeSDL();
        exit(0);
    }
}

void PlayBGM(int i) {
    Mix_VolumeMusic(32);
    if (i == 0) {
        Mix_HaltMusic();
        Mix_PlayMusic(bgm1, -1);
    }
    else if (i == 1) {
        Mix_HaltMusic();
        Mix_PlayMusic(bgm2, -1);
    }
    else if (i == 2) {
        Mix_HaltMusic();
        Mix_PlayMusic(bgm3, -1);
    }
}

void PlaySE(int i) {
    if (i == 0) {
        Mix_PlayChannel(0, foot, -1);
    }
    else if (i == 1) {
        Mix_PlayChannel(1, key, 0);
    }
    else if (i == 2) {
        Mix_PlayChannel(2, gate, 0);
    }
    Mix_VolumeChunk(foot, 128);
    Mix_VolumeChunk(key, 128);
    Mix_VolumeChunk(gate, 128);
}

void StopSE(int i) {
    if (i == 0) {
        Mix_HaltChannel(0);
    }
    else if (i == 1) {
        Mix_HaltChannel(1);
    }
    else if (i == 2) {
        Mix_HaltChannel(2);
    }
}