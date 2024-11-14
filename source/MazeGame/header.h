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

struct Vector3 {//���W�\����
	float x;
	float y;
	float z;
};

struct AABB {//AABB�\����
	Vector3 min;
	Vector3 max;
};

struct Square {//���Ս\����
	float x, z;
};

AABB GetCameraAABB(const Vector3& cameraPosition);//�J������AABB�擾
AABB GetCubeAABB(const Vector3& CubeCenter, float size);//�ǂ�AABB�擾
AABB GetKeyAABB(const Vector3& KeyCenter, float size);//����AABB�擾
bool CheckCollision(const AABB Camera, const AABB Cube);//�Փ˔���
bool CheckCollisionKey(const AABB Camera, const AABB Key);//���̎擾����
bool CheckCollisionGate(const AABB Camera, const AABB Gate);//���̏Փ˔���
std::vector<std::vector<int>> InitMaze(int size);//�_�|���@
void drawSquare(float x, float z);//���Օ`��
void MakeArray(int size);//�z��̗v�f���ύX
bool initSDL();//SDL�̏�����
void closeSDL();//SDL�̏I��
void LoadSound();//���f�[�^�̃��[�h
void PlayBGM(int i);//BGM�̍Đ�
void PlaySE(int i);//SE�i�T�E���h�G�t�F�N�g�j�̍Đ�
void StopSE(int i);//SE�̒�~
//GLuint LoadTexture(const char* filename);
//void DrawTexture(GLuint Texture);