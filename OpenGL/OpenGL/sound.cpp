#include "header.h"

// FMOD�V�X�e���ƃT�E���h
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
    // FMOD�V�X�e���̏�����
    FMOD::System_Create(&soundSystem);
    soundSystem->init(32, FMOD_INIT_NORMAL, nullptr);

    // �T�E���h�̓ǂݍ���
    soundSystem->createSound("bgm.mp3", FMOD_DEFAULT, nullptr, &Titlebgm);
    soundSystem->createSound("bgm2.mp3", FMOD_DEFAULT, nullptr, &Playbgm);
    soundSystem->createSound("bgm3.mp3", FMOD_DEFAULT, nullptr, &Resultbgm);
    soundSystem->createSound("foot.mp3", FMOD_DEFAULT, nullptr, &FootSE);
    soundSystem->createSound("key.mp3", FMOD_DEFAULT, nullptr, &KeySE);
    soundSystem->createSound("gate.mp3", FMOD_DEFAULT, nullptr, &GateSE);
    soundSystem->createChannelGroup("BGM", &bgmgroup);
    soundSystem->createChannelGroup("SE", &segroup);

    // ���[�v�Đ��ɐݒ�
    Titlebgm->setMode(FMOD_LOOP_NORMAL);
    Playbgm->setMode(FMOD_LOOP_NORMAL);
    Resultbgm->setMode(FMOD_LOOP_NORMAL);
    FootSE->setMode(FMOD_LOOP_NORMAL);
    bgmgroup->setVolume(0.25f);
}

//BGM�̍Đ�
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

//SE�̍Đ�
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

//SE�̒�~
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

//�N���[���A�b�v
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

//�X�V
void UpdateFMOD() {
    bool isPlaying = false;
    if (keychannel) {
        keychannel->isPlaying(&isPlaying);  // �Đ������ǂ����m�F
        if (!isPlaying) {
            stopSE(1);  // �Đ��I�����ɒ�~
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