/*******************************************************
* ファイル名：sound.cpp
* 概要　　　：ゲームのBGM、SEの読み込み、再生、停止を実行
* 　　　　　　SDL2、SDL2_mixerを使用
********************************************************/
#pragma once
#include "header.h"

Mix_Music* bgm1 = nullptr;  //一つ目のBGMを保持
Mix_Music* bgm2 = nullptr;  //二つ目のBGMを保持
Mix_Music* bgm3 = nullptr;  //三つ目のBGMを保持
Mix_Chunk* foot = nullptr;  //足跡のSEを保持
Mix_Chunk* key = nullptr;   //鍵のSEを保持
Mix_Chunk* gate = nullptr;  //扉のSEを保持

/*******************************************************
* SDL、SDL_mixerの初期化を行う関数
* 初期化に成功した場合trueを返し、失敗した場合falseを返す
********************************************************/
bool initSDL() {
    //SDLの初期化
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        return false;
    }
    //SDL_mixerの初期化
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        return false;
    }
    return true;
}

/*******************************************************
* SDL、SDL_mixerの終了を行う関数
* 読み込んだ音を全て開放し、終了する
********************************************************/
void closeSDL() {
    Mix_FreeMusic(bgm1);  //BGMの開放
    Mix_FreeMusic(bgm2);
    Mix_FreeMusic(bgm3);
    Mix_FreeChunk(foot);  //SEの開放
    Mix_FreeChunk(key);
    Mix_FreeChunk(gate);
    Mix_CloseAudio();     //SDL_mixerの終了
    SDL_Quit();           //SDLの終了
}

/*******************************************************
* BGM、SEの読み込みを行う関数
* プロジェクトフォルダの指定した音ファイルを読み込み変数に格納する
* どれか一つでも読み込みに失敗した場合プログラムを終了させる
********************************************************/
void LoadSound() {
    bgm1 = Mix_LoadMUS("bgm1.mp3");  //BGMの読み込み
    bgm2 = Mix_LoadMUS("bgm2.mp3");
    bgm3 = Mix_LoadMUS("bgm3.mp3");
    foot = Mix_LoadWAV("foot.wav");  //SEの読み込み
    key = Mix_LoadWAV("key.wav");
    gate = Mix_LoadWAV("gate.wav");
    //読み込み失敗
    if (!bgm1 || !bgm2 || !bgm3 || !foot || !key || !gate) {
        closeSDL();
        exit(0);
    }
}

/*******************************************************
* BGMの再生、停止を行う関数
* BGMを全て停止させた後、引数で指定したBGMを再生する
* BGM音量は25%に設定
* 引数
* i:BGMを指定する値
********************************************************/
void PlayBGM(int i) {
    Mix_VolumeMusic(32);          //BGM音量調整
    Mix_HaltMusic();              //全てのBGMの停止
    if (i == 0) {
        Mix_PlayMusic(bgm1, -1);  //bgm1を無限ループで再生
    }
    else if (i == 1) {
        Mix_PlayMusic(bgm2, -1);  //bgm2を無限ループで再生
    }
    else if (i == 2) {
        Mix_PlayMusic(bgm3, 1);   //bgm3を一度だけ再生
    }
}

/*******************************************************
* SEの再生を行う関数
* SE音量は100%に設定
* 引数
* i:SEを指定する値
********************************************************/
void PlaySE(int i) {
    Mix_VolumeChunk(foot, 128);        //SE音量調整
    Mix_VolumeChunk(key, 128);
    Mix_VolumeChunk(gate, 128);
    if (i == 0) {
        Mix_PlayChannel(0, foot, -1);  //footを無限ループで再生
    }
    else if (i == 1) {
        Mix_PlayChannel(1, key, 0);    //keyを一度だけ再生
    }
    else if (i == 2) {
        Mix_PlayChannel(2, gate, 0);   //gateを一度だけ再生
    }
}

/*******************************************************
* SEの停止を行う関数
* 引数
* i:SEを指定する値
********************************************************/
void StopSE(int i) {
    if (i == 0) {
        Mix_HaltChannel(0);    //チャンネル0番(foot)を停止
    }
    else if (i == 1) {
        Mix_HaltChannel(1);    //チャンネル1番(key)を停止
    }
    else if (i == 2) {
        Mix_HaltChannel(2);    //チャンネル2番(gate)を停止
    }
}