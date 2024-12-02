/*******************************************************
* ファイル名：Character.cpp
* 概要　　　：渡された文字列を指定した位置に描画する
********************************************************/
#pragma once
#include "header.h"

/*******************************************************
* 文字の描画を行う関数
* 引数
* WindowW:ウィンドウの幅
* WindowH:ウィンドウの高さ
* posx,posy:文字の位置
* text:描画する文字配列
********************************************************/
void DrawChara(int WindowW, int WindowH, int posx, int posy, char* text) {
	char* p;
	int textWidth = 0;
	//文字数カウント
	for (p = text; *p; p++) {
		textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *p);
	}
	int xPos = (WindowW - textWidth) / 2;     //画面中央座標を設定
	int yPos = WindowH / 2;
	glRasterPos2i(xPos + posx, yPos + posy);  //文字の位置を設定
	//文字描画
	for (p = text; *p; p++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
	}
}