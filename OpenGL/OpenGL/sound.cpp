#include "header.h"

// FMOD�V�X�e���ƃT�E���h
FMOD::System* soundSystem = nullptr;
FMOD::Sound* bgmSound = nullptr;
FMOD::Channel* channel = nullptr;

void initFMODTitle() {
    // FMOD�V�X�e���̏�����
    FMOD::System_Create(&soundSystem);
    soundSystem->init(512, FMOD_INIT_NORMAL, nullptr);

    // BGM�T�E���h�̓ǂݍ���
    soundSystem->createSound("bgm.mp3", FMOD_DEFAULT, nullptr, &bgmSound);
    bgmSound->setMode(FMOD_LOOP_NORMAL);  // ���[�v�Đ��ɐݒ�
}

void initFMODPlay() {
    // FMOD�V�X�e���̏�����
    FMOD::System_Create(&soundSystem);
    soundSystem->init(512, FMOD_INIT_NORMAL, nullptr);

    // BGM�T�E���h�̓ǂݍ���
    soundSystem->createSound("bgm2.mp3", FMOD_DEFAULT, nullptr, &bgmSound);
    bgmSound->setMode(FMOD_LOOP_NORMAL);  // ���[�v�Đ��ɐݒ�
}
void initFMODResult() {
    // FMOD�V�X�e���̏�����
    FMOD::System_Create(&soundSystem);
    soundSystem->init(512, FMOD_INIT_NORMAL, nullptr);

    // BGM�T�E���h�̓ǂݍ���
    soundSystem->createSound("bgm3.mp3", FMOD_DEFAULT, nullptr, &bgmSound);
    bgmSound->setMode(FMOD_LOOP_NORMAL);  // ���[�v�Đ��ɐݒ�
}

void playBGM() {
    soundSystem->playSound(bgmSound, nullptr, false, &channel);
}

void cleanupFMOD() {
    bgmSound->release();
    soundSystem->close();
    soundSystem->release();
}