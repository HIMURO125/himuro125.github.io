#include "header.h"

// FMODシステムとサウンド
FMOD::System* soundSystem = nullptr;
FMOD::Sound* Titlebgm = nullptr;
FMOD::Sound* Playbgm = nullptr;
FMOD::Sound* Resultbgm = nullptr;
FMOD::Sound* FootSE = nullptr;
FMOD::Sound* KeySE = nullptr;
FMOD::Sound* GateSE = nullptr;
FMOD::Channel* bgmchannel = nullptr;
FMOD::Channel* footchannel = nullptr;
FMOD::Channel* keychannel = nullptr;
FMOD::Channel* gatechannel = nullptr;
FMOD::ChannelGroup* bgmgroup = nullptr;
FMOD::ChannelGroup* segroup = nullptr;

void initFMOD() {
    // FMODシステムの初期化
    FMOD::System_Create(&soundSystem);
    soundSystem->init(32, FMOD_INIT_NORMAL, nullptr);

    // サウンドの読み込み
    soundSystem->createSound("bgm.mp3", FMOD_DEFAULT, nullptr, &Titlebgm);
    soundSystem->createSound("bgm2.mp3", FMOD_DEFAULT, nullptr, &Playbgm);
    soundSystem->createSound("bgm3.mp3", FMOD_DEFAULT, nullptr, &Resultbgm);
    soundSystem->createSound("foot.mp3", FMOD_DEFAULT, nullptr, &FootSE);
    soundSystem->createSound("key.mp3", FMOD_DEFAULT, nullptr, &KeySE);
    soundSystem->createSound("gate.mp3", FMOD_DEFAULT, nullptr, &GateSE);
    soundSystem->createChannelGroup("BGM", &bgmgroup);
    soundSystem->createChannelGroup("SE", &segroup);

    // ループ再生に設定
    Titlebgm->setMode(FMOD_LOOP_NORMAL);
    Playbgm->setMode(FMOD_LOOP_NORMAL);
    Resultbgm->setMode(FMOD_LOOP_NORMAL);
    FootSE->setMode(FMOD_LOOP_NORMAL);
    bgmgroup->setVolume(0.25f);
}

//BGMの再生
void playBGM(int i) {
    if (i == 0) {
        bgmchannel->stop();
        soundSystem->playSound(Titlebgm, bgmgroup, false, &bgmchannel);
    }
    else if (i == 1) {
        bgmchannel->stop();
        soundSystem->playSound(Playbgm, bgmgroup, false, &bgmchannel);
    }
    else if (i == 2) {
        bgmchannel->stop();
        soundSystem->playSound(Resultbgm, bgmgroup, false, &bgmchannel);
    }
}

//SEの再生
void playSE(int i) {
    if (i == 0) {
        soundSystem->playSound(FootSE, segroup, false, &footchannel);
    }
    else if (i == 1) {
        soundSystem->playSound(KeySE, segroup, false, &keychannel);
    }
    else if (i == 2) {
        soundSystem->playSound(GateSE, segroup, false, &gatechannel);
    }
}

//SEの停止
void stopSE(int i) {
    if (i == 0) {
        footchannel->stop();
    }
    else if (i == 1) {
        keychannel->stop();
    }
    else if (i == 2) {
        gatechannel->stop();
    }
}

//クリーンアップ
void cleanupFMOD() {
    Titlebgm->release();
    Playbgm->release();
    Resultbgm->release();
    FootSE->release();
    KeySE->release();
    GateSE->release();
    soundSystem->close();
    soundSystem->release();
}

//更新
void UpdateFMOD() {
    bool isPlaying = false;
    if (keychannel) {
        keychannel->isPlaying(&isPlaying);  // 再生中かどうか確認
        if (!isPlaying) {
            stopSE(1);  // 再生終了時に停止
            keychannel = nullptr;
        }
    }
    if (gatechannel) {
        gatechannel->isPlaying(&isPlaying);
        if (!isPlaying) {
            stopSE(2);
            gatechannel = nullptr;
        }
    }
    soundSystem->update();
}