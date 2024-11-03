#pragma once
#include <stdlib.h>
#include <GL/glut.h>
#include <SDL.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <random>
#include <chrono>
#include <string>
#include <cstring>
#define M_PI 3.1415926535897932384626433832795

struct Vector3 {//座標構造体
	float x;
	float y;
	float z;
};

struct AABB {//AABB構造体
	Vector3 min;
	Vector3 max;
};

struct Square {
	float x, z; // 足元の位置
};

AABB GetCameraAABB(const Vector3& cameraPosition);//カメラのAABB取得
AABB GetCubeAABB(const Vector3& CubeCenter, float size);//壁のAABB取得
AABB GetKeyAABB(const Vector3& KeyCenter, float size);//鍵のAABB取得
bool CheckCollision(const AABB Camera, const AABB Cube);//衝突判定
bool CheckCollisionKey(const AABB Camera, const AABB Key);//鍵の取得判定
bool CheckCollisionGate(const AABB Camera, const AABB Gate);//扉の衝突判定
std::vector<std::vector<int>> InitMaze(int size);//棒倒し法
void MakeArray(int size);//配列の要素数変更