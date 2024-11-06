#include "header.h"

// FMOD�V�X�e���ƃT�E���h
FMOD::System* soundSystem = nullptr;
FMOD::Sound* Titlebgm = nullptr;
FMOD::Sound* Playbgm = nullptr;
FMOD::Sound* Resultbgm = nullptr;
FMOD::Sound* FootSE = nullptr;
FMOD::Sound* KeySE = nullptr;
FMOD::Channel* bgmchannel = nullptr;
FMOD::Channel* footchannel = nullptr;
FMOD::Channel* keychannel = nullptr;
FMOD::ChannelGroup* bgmgroup = nullptr;
FMOD::ChannelGroup* segroup = nullptr;

void initFMOD() {
    // FMOD�V�X�e���̏�����
    FMOD::System_Create(&soundSystem);
    soundSystem->init(32, FMOD_INIT_NORMAL, nullptr);

    // BGM�T�E���h�̓ǂݍ���
    soundSystem->createSound("bgm.mp3", FMOD_DEFAULT, nullptr, &Titlebgm);
    soundSystem->createSound("bgm2.mp3", FMOD_DEFAULT, nullptr, &Playbgm);
    soundSystem->createSound("bgm3.mp3", FMOD_DEFAULT, nullptr, &Resultbgm);
    soundSystem->createSound("foot.mp3", FMOD_DEFAULT, nullptr, &FootSE);
    soundSystem->createSound("key.mp3", FMOD_DEFAULT, nullptr, &KeySE);
    soundSystem->createChannelGroup("BGM", &bgmgroup);
    soundSystem->createChannelGroup("SE", &segroup);
    Titlebgm->setMode(FMOD_LOOP_NORMAL);  // ���[�v�Đ��ɐݒ�
    Playbgm->setMode(FMOD_LOOP_NORMAL);
    Resultbgm->setMode(FMOD_LOOP_NORMAL);
    FootSE->setMode(FMOD_LOOP_NORMAL);
    bgmgroup->setVolume(0.25f);
}

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

void playSE(int i) {
    if (i == 0) {
        soundSystem->playSound(FootSE, segroup, false, &footchannel);
    }
    else if (i == 1) {
        soundSystem->playSound(KeySE, segroup, false, &keychannel);
    }
}

void stopSE(int i) {
    if (i == 0) {
        footchannel->stop();
    }
    else if (i == 1) {
        keychannel->stop();
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