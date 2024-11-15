/*******************************************************
* �t�@�C�����Fsound.cpp
* �T�v�@�@�@�F�Q�[����BGM�ASE�̓ǂݍ��݁A�Đ��A��~�����s
* �@�@�@�@�@�@SDL2�ASDL2_mixer���g�p
********************************************************/
#pragma once
#include "header.h"

Mix_Music* bgm1 = nullptr;  //��ڂ�BGM��ێ�
Mix_Music* bgm2 = nullptr;  //��ڂ�BGM��ێ�
Mix_Music* bgm3 = nullptr;  //�O�ڂ�BGM��ێ�
Mix_Chunk* foot = nullptr;  //���Ղ�SE��ێ�
Mix_Chunk* key = nullptr;   //����SE��ێ�
Mix_Chunk* gate = nullptr;  //����SE��ێ�

/*******************************************************
* SDL�ASDL_mixer�̏��������s���֐�
* �������ɐ��������ꍇtrue��Ԃ��A���s�����ꍇfalse��Ԃ�
********************************************************/
bool initSDL() {
    //SDL�̏�����
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        return false;
    }
    //SDL_mixer�̏�����
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        return false;
    }
    return true;
}

/*******************************************************
* SDL�ASDL_mixer�̏I�����s���֐�
* �ǂݍ��񂾉���S�ĊJ�����A�I������
********************************************************/
void closeSDL() {
    Mix_FreeMusic(bgm1);  //BGM�̊J��
    Mix_FreeMusic(bgm2);
    Mix_FreeMusic(bgm3);
    Mix_FreeChunk(foot);  //SE�̊J��
    Mix_FreeChunk(key);
    Mix_FreeChunk(gate);
    Mix_CloseAudio();     //SDL_mixer�̏I��
    SDL_Quit();           //SDL�̏I��
}

/*******************************************************
* BGM�ASE�̓ǂݍ��݂��s���֐�
* �v���W�F�N�g�t�H���_�̎w�肵�����t�@�C����ǂݍ��ݕϐ��Ɋi�[����
* �ǂꂩ��ł��ǂݍ��݂Ɏ��s�����ꍇ�v���O�������I��������
********************************************************/
void LoadSound() {
    bgm1 = Mix_LoadMUS("bgm1.mp3");  //BGM�̓ǂݍ���
    bgm2 = Mix_LoadMUS("bgm2.mp3");
    bgm3 = Mix_LoadMUS("bgm3.mp3");
    foot = Mix_LoadWAV("foot.wav");  //SE�̓ǂݍ���
    key = Mix_LoadWAV("key.wav");
    gate = Mix_LoadWAV("gate.wav");
    //�ǂݍ��ݎ��s
    if (!bgm1 || !bgm2 || !bgm3 || !foot || !key || !gate) {
        closeSDL();
        exit(0);
    }
}

/*******************************************************
* BGM�̍Đ��A��~���s���֐�
* BGM��S�Ē�~��������A�����Ŏw�肵��BGM���Đ�����
* BGM���ʂ�25%�ɐݒ�
* ����
* i:BGM���w�肷��l
********************************************************/
void PlayBGM(int i) {
    Mix_VolumeMusic(32);          //BGM���ʒ���
    Mix_HaltMusic();              //�S�Ă�BGM�̒�~
    if (i == 0) {
        Mix_PlayMusic(bgm1, -1);  //bgm1�𖳌����[�v�ōĐ�
    }
    else if (i == 1) {
        Mix_PlayMusic(bgm2, -1);  //bgm2�𖳌����[�v�ōĐ�
    }
    else if (i == 2) {
        Mix_PlayMusic(bgm3, 1);   //bgm3����x�����Đ�
    }
}

/*******************************************************
* SE�̍Đ����s���֐�
* SE���ʂ�100%�ɐݒ�
* ����
* i:SE���w�肷��l
********************************************************/
void PlaySE(int i) {
    Mix_VolumeChunk(foot, 128);        //SE���ʒ���
    Mix_VolumeChunk(key, 128);
    Mix_VolumeChunk(gate, 128);
    if (i == 0) {
        Mix_PlayChannel(0, foot, -1);  //foot�𖳌����[�v�ōĐ�
    }
    else if (i == 1) {
        Mix_PlayChannel(1, key, 0);    //key����x�����Đ�
    }
    else if (i == 2) {
        Mix_PlayChannel(2, gate, 0);   //gate����x�����Đ�
    }
}

/*******************************************************
* SE�̒�~���s���֐�
* ����
* i:SE���w�肷��l
********************************************************/
void StopSE(int i) {
    if (i == 0) {
        Mix_HaltChannel(0);    //�`�����l��0��(foot)���~
    }
    else if (i == 1) {
        Mix_HaltChannel(1);    //�`�����l��1��(key)���~
    }
    else if (i == 2) {
        Mix_HaltChannel(2);    //�`�����l��2��(gate)���~
    }
}