#pragma once
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <random>
#include <chrono>
#include <string>
#include <cstring>
#define M_PI 3.1415926535897932384626433832795

struct Vector3 {//ÀW\¢Ì
	float x;
	float y;
	float z;
};

struct AABB {//AABB\¢Ì
	Vector3 min;
	Vector3 max;
};

AABB GetCameraAABB(const Vector3& cameraPosition);//JÌAABBæ¾
AABB GetCubeAABB(const Vector3& CubeCenter, float size);//ÇÌAABBæ¾
AABB GetKeyAABB(const Vector3& KeyCenter, float size);//®ÌAABBæ¾
bool CheckCollision(const AABB Camera, const AABB Cube);//ÕË»è
bool CheckCollisionKey(const AABB Camera, const AABB Key);//®Ìæ¾»è
bool CheckCollisionGate(const AABB Camera, const AABB Gate);//àÌÕË»è
std::vector<std::vector<int>> InitMaze(int size);//_|µ@
void MakeArray(int size);//zñÌvfÏX