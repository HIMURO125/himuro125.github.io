#include "header.h"

// FMODシステムとサウンド
FMOD::System* soundSystem = nullptr;
FMOD::Sound* bgmSound = nullptr;
FMOD::Channel* channel = nullptr;

void initFMODTitle() {
    // FMODシステムの初期化
    FMOD::System_Create(&soundSystem);
    soundSystem->init(512, FMOD_INIT_NORMAL, nullptr);

    // BGMサウンドの読み込み
    soundSystem->createSound("bgm.mp3", FMOD_DEFAULT, nullptr, &bgmSound);
    bgmSound->setMode(FMOD_LOOP_NORMAL);  // ループ再生に設定
}

void initFMODPlay() {
    // FMODシステムの初期化
    FMOD::System_Create(&soundSystem);
    soundSystem->init(512, FMOD_INIT_NORMAL, nullptr);

    // BGMサウンドの読み込み
    soundSystem->createSound("bgm2.mp3", FMOD_DEFAULT, nullptr, &bgmSound);
    bgmSound->setMode(FMOD_LOOP_NORMAL);  // ループ再生に設定
}
void initFMODResult() {
    // FMODシステムの初期化
    FMOD::System_Create(&soundSystem);
    soundSystem->init(512, FMOD_INIT_NORMAL, nullptr);

    // BGMサウンドの読み込み
    soundSystem->createSound("bgm3.mp3", FMOD_DEFAULT, nullptr, &bgmSound);
    bgmSound->setMode(FMOD_LOOP_NORMAL);  // ループ再生に設定
}

void playBGM() {
    soundSystem->playSound(bgmSound, nullptr, false, &channel);
}

void cleanupFMOD() {
    bgmSound->release();
    soundSystem->close();
    soundSystem->release();
}