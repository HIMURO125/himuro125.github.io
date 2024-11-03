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

struct Vector3 {//���W�\����
	float x;
	float y;
	float z;
};

struct AABB {//AABB�\����
	Vector3 min;
	Vector3 max;
};

struct Square {
	float x, z; // �����̈ʒu
};

AABB GetCameraAABB(const Vector3& cameraPosition);//�J������AABB�擾
AABB GetCubeAABB(const Vector3& CubeCenter, float size);//�ǂ�AABB�擾
AABB GetKeyAABB(const Vector3& KeyCenter, float size);//����AABB�擾
bool CheckCollision(const AABB Camera, const AABB Cube);//�Փ˔���
bool CheckCollisionKey(const AABB Camera, const AABB Key);//���̎擾����
bool CheckCollisionGate(const AABB Camera, const AABB Gate);//���̏Փ˔���
std::vector<std::vector<int>> InitMaze(int size);//�_�|���@
void MakeArray(int size);//�z��̗v�f���ύX