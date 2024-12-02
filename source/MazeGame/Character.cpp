/*******************************************************
* �t�@�C�����FCharacter.cpp
* �T�v�@�@�@�F�n���ꂽ��������w�肵���ʒu�ɕ`�悷��
********************************************************/
#pragma once
#include "header.h"

/*******************************************************
* �����̕`����s���֐�
* ����
* WindowW:�E�B���h�E�̕�
* WindowH:�E�B���h�E�̍���
* posx,posy:�����̈ʒu
* text:�`�悷�镶���z��
********************************************************/
void DrawChara(int WindowW, int WindowH, int posx, int posy, char* text) {
	char* p;
	int textWidth = 0;
	//�������J�E���g
	for (p = text; *p; p++) {
		textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *p);
	}
	int xPos = (WindowW - textWidth) / 2;     //��ʒ������W��ݒ�
	int yPos = WindowH / 2;
	glRasterPos2i(xPos + posx, yPos + posy);  //�����̈ʒu��ݒ�
	//�����`��
	for (p = text; *p; p++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
	}
}