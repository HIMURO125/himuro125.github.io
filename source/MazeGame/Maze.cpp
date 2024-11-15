/*******************************************************
* �t�@�C�����FMaze.cpp
* �T�v�@�@�@�F�񎟌��z��̖��H�̎��������A�T�C�Y�ύX�A���Ղ̕`������s
* �@�@�@�@�@�@freeglut���g�p
********************************************************/
#pragma once
#include "header.h"

const int Path = 0;                    //����0�Ƃ���
const int Wall = 1;                    //�ǂ�1�Ƃ���
const int Key = 2;                     //����2�Ƃ���
const int Gate = 3;                    //����3�Ƃ���
std::vector<std::vector<int>> matrix;  //���H�̓񎟌��z��

/*******************************************************
* �����Ŏw�肵���傫���̖��H��������������֐�
* �A���S���Y���Ƃ��Ė_�|���@���g�p
* �Ԃ�l�Ƃ��Đ����������H�ł���񎟌��z���Ԃ�
* ����
* size:���H�̃T�C�Y
********************************************************/
std::vector<std::vector<int>> InitMaze(int size) {
	//���H�̃T�C�Y�ύX
	matrix.resize(size);
	for (int i = 0; i < size; ++i) {
		matrix[i].resize(size);
	}

	//���H�̏�����
	for (int x = 0; x < size; x++) {
		for (int z = 0; z < size; z++) {
			matrix[x][z] = Path;
		}
	}

	//�O����S�ĕǂɂ���
	for (int x = 0; x < size; x++) {
		for (int z = 0; z < size; z++) {
			if (x == 0 || z == 0 || x == size - 1 || z == size - 1) {
				matrix[x][z] = Wall;
			}
			else {
				matrix[x][z] = Path;
			}
		}
	}

	//�_�|���@
	for (int x = 2; x < size - 1; x += 2) {
		for (int z = 2; z < size - 1; z += 2) {
			matrix[x][z] = 1;      //�ŏ��̖_
			while (true)
			{
				int direction;     //�_��|������

				// 1�s�ڂ̂ݏ�ɓ|����
				if (z == 2)
					direction = rand() % 4;
				else
					direction = rand() % 3;

				int wallX = x;     //x���W
				int wallZ = z;     //z���W

				// �_��|�����������߂�
				switch (direction)
				{
				case 0: //�E
					wallX++;
					break;
				case 1: //��
					wallZ++;
					break;
				case 2: //��
					wallX--;
					break;
				case 3: //��
					wallZ--;
					break;
				}

				//�ǂ���Ȃ��ꍇ�̂ݖ_��|���ďI��
				if (matrix[wallX][wallZ] != Wall)
				{
					matrix[wallX][wallZ] = Wall;
					break;
				}
			}
		}
	}
	matrix[size - 1][size - 2] = Gate; //�E�����Ƃ���

	//���H�̒��������̓��̂ǂ����Ɍ���ݒu
	while (true) {
		int MinRamge = size / 3;                                   //���H�̃T�C�Y��3����1�͈̔�
		int MaxRange = 2 * size / 3 - 1;
		std::random_device rd;                                     //�n�[�h�E�F�A�����������������
		std::mt19937 gen(rd());                                    //�[�������������������
		std::uniform_int_distribution<int> dis(MinRamge, MaxRange);//MinRamge�AMaxRange�͈̔͂ŗ����������邽�߂̕��z�I�u�W�F�N�g���쐬
		int x = dis(gen);                                          //��������
		int z = dis(gen);

		//�I�΂ꂽ�ꏊ�����̏ꍇ����ݒu
		if (matrix[x][z] == Path) {
			matrix[x][z] = Key;
			break;
		}
	}
	return matrix;
}

/*******************************************************
* ���Ղ�`�悷��֐�
* ����
* x,y:�`�悷����W
********************************************************/
void drawSquare(float x, float z) {
	//�l�p�`�̃|���S����`��
	glBegin(GL_QUADS);
	glVertex3f(x - 0.1f, 0.0f, z - 0.1f);
	glVertex3f(x + 0.1f, 0.0f, z - 0.1f);
	glVertex3f(x + 0.1f, 0.0f, z + 0.1f);
	glVertex3f(x - 0.1f, 0.0f, z + 0.1f);
	glEnd();
}