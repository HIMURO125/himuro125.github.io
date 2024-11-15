/*******************************************************
* ファイル名　　　：header.h
* 概要　　　　　　：プログラムの構造体、関数を定義
* 外部ライブラリ　：freeglut-3.6.0		glut.h
* 　　　　　　　　　SDL2-2.30.9		　　SDL.h
* 　　　　　　　　　SDL2_mixer-2.8.0	SDL_mixer.h
********************************************************/
#pragma once
#include <stdlib.h>
#include <GL/glut.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <random>
#include <chrono>
#include <string>
#include <cstring>

//座標構造体を定義
struct Vector3 {
	float x;    //x座標
	float y;    //y座標
	float z;    //z座標
};

//AABB(Axis-Aligned Bounding Box)構造体を定義
struct AABB {
	Vector3 min;    //最小座標
	Vector3 max;    //最大座標
};

//足跡座標構造体を定義
struct Square {
	float x;    //x座標
	float z;    //z座標
};

AABB GetCameraAABB(const Vector3& cameraPosition);            //カメラのAABB設定
AABB GetCubeAABB(const Vector3& CubeCenter, float size);      //壁のAABB設定
AABB GetKeyAABB(const Vector3& KeyCenter, float size);        //鍵のAABB設定
bool CheckCollision(const AABB Camera, const AABB Obj);       //衝突判定
std::vector<std::vector<int>> InitMaze(int size);             //迷路の自動生成
void drawSquare(float x, float z);                            //足跡描画
bool initSDL();                                               //SDLの初期化
void closeSDL();                                              //SDLの終了
void LoadSound();                                             //音データのロード
void PlayBGM(int i);                                          //BGMの再生、停止
void PlaySE(int i);                                           //SEの再生
void StopSE(int i);                                           //SEの停止