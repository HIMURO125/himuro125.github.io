#include "header.h"

// FMOD�V�X�e���ƃT�E���h
FMOD::System* soundSystem = nullptr;
FMOD::Sound* Titlebgm = nullptr;
FMOD::Sound* Playbgm = nullptr;
FMOD::Sound* Resultbgm = nullptr;
FMOD::Sound* FootSE = nullptr;
FMOD::Channel* bgmchannel = nullptr;
FMOD::Channel* sechannel = nullptr;

void initFMOD() {
    // FMOD�V�X�e���̏�����
    FMOD::System_Create(&soundSystem);
    soundSystem->init(10, FMOD_INIT_NORMAL, nullptr);

    // BGM�T�E���h�̓ǂݍ���
    soundSystem->createSound("bgm.mp3", FMOD_DEFAULT, nullptr, &Titlebgm);
    soundSystem->createSound("bgm2.mp3", FMOD_DEFAULT, nullptr, &Playbgm);
    soundSystem->createSound("bgm3.mp3", FMOD_DEFAULT, nullptr, &Resultbgm);
    soundSystem->createSound("����1.mp3", FMOD_DEFAULT, nullptr, &FootSE);
    Titlebgm->setMode(FMOD_LOOP_NORMAL);  // ���[�v�Đ��ɐݒ�
    Playbgm->setMode(FMOD_LOOP_NORMAL);
    Resultbgm->setMode(FMOD_LOOP_NORMAL);
}

void playBGM(int i) {
    if (i == 0) {
        bgmchannel->stop();
        soundSystem->playSound(Titlebgm, nullptr, false, &bgmchannel);
    }
    else if (i == 1) {
        bgmchannel->stop();
        soundSystem->playSound(Playbgm, nullptr, false, &bgmchannel);
    }
    else if (i == 2) {
        bgmchannel->stop();
        soundSystem->playSound(Resultbgm, nullptr, false, &bgmchannel);
    }
}

void playSE(int i) {
    if (i == 0) {
        soundSystem->playSound(FootSE, 0, false, &sechannel);
    }
}

void stopSE(int i) {
    if (i == 0) {
        sechannel->stop();
    }
}

void cleanupFMOD() {
    Titlebgm->release();
    Playbgm->release();
    Resultbgm->release();
    soundSystem->close();
    soundSystem->release();
}

void UpdateFMOD() {
    soundSystem->update();
}