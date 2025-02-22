/*******************************************************
* ファイル名　　　：header.h
* 概要　　　　　　：プログラムの構造体、関数を定義
* 外部ライブラリ　：freeglut-3.6.0		glut.h
* 　　　　　　　　　SDL2-2.30.9		　　SDL.h
* 　　　　　　　　　SDL2_mixer-2.8.0	SDL_mixer.h
*                   stb_image           stb_image.h
********************************************************/
#pragma once
#include <GL/glut.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <stb_image.h>
#include <cmath>
#include <ctime>
#include <vector>
#include <random>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
using namespace std;

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
vector<vector<int>> InitMaze(int size);                       //迷路の自動生成
void drawSquare(float x, float z);                            //足跡描画
bool initSDL();                                               //SDLの初期化
void closeSDL();                                              //SDLの終了
void LoadSound();                                             //音データのロード
void PlayBGM(int i);                                          //BGMの再生、停止
void PlaySE(int i);                                           //SEの再生
void StopSE(int i);                                           //SEの停止
void DrawChara(int WindowW, int WindowH, int posx, int posy, char* text);//文字の描画
void SetBGMVolume(int i);                                     //BGM音量設定
void SetSEVolume(int i);                                      //SE音量設定
GLuint SetTexture(const char* filename);                      //テクスチャデータの読み込み
void DrawWallTexture(GLuint TextureID);                       //壁のテクスチャの描画
void DrawGateTexture(GLuint TextureID);                       //扉のテクスチャの描画
vector<AABB> InitWallAABB(int size, vector<vector<int>> maze);//壁のAABB設定
vector<int> ReadFile(string filename);						  //ファイルの読み込み
void WriteFile(long long data, string filename);			  //ファイルの書き込み
void CheckFile(string filename);							  //ファイルの存在確認
void ChangeData1(char* str, int data, size_t size);			  //データの変換
void ChangeData2(char* str, int data, size_t size);
void ChangeData3(char* str, int data, size_t size);