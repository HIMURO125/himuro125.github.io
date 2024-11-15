/*******************************************************
* �t�@�C�����@�@�@�Fheader.h
* �T�v�@�@�@�@�@�@�F�v���O�����̍\���́A�֐����`
* �O�����C�u�����@�Ffreeglut-3.6.0		glut.h
* �@�@�@�@�@�@�@�@�@SDL2-2.30.9		�@�@SDL.h
* �@�@�@�@�@�@�@�@�@SDL2_mixer-2.8.0	SDL_mixer.h
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

//���W�\���̂��`
struct Vector3 {
	float x;    //x���W
	float y;    //y���W
	float z;    //z���W
};

//AABB(Axis-Aligned Bounding Box)�\���̂��`
struct AABB {
	Vector3 min;    //�ŏ����W
	Vector3 max;    //�ő���W
};

//���Ս��W�\���̂��`
struct Square {
	float x;    //x���W
	float z;    //z���W
};

AABB GetCameraAABB(const Vector3& cameraPosition);            //�J������AABB�ݒ�
AABB GetCubeAABB(const Vector3& CubeCenter, float size);      //�ǂ�AABB�ݒ�
AABB GetKeyAABB(const Vector3& KeyCenter, float size);        //����AABB�ݒ�
bool CheckCollision(const AABB Camera, const AABB Obj);       //�Փ˔���
std::vector<std::vector<int>> InitMaze(int size);             //���H�̎�������
void drawSquare(float x, float z);                            //���Օ`��
bool initSDL();                                               //SDL�̏�����
void closeSDL();                                              //SDL�̏I��
void LoadSound();                                             //���f�[�^�̃��[�h
void PlayBGM(int i);                                          //BGM�̍Đ��A��~
void PlaySE(int i);                                           //SE�̍Đ�
void StopSE(int i);                                           //SE�̒�~