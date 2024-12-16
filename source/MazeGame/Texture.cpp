/*******************************************************
* ファイル名：Texture.cpp
* 概要　　　：テクスチャの読み込み、描画を行う
********************************************************/
#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "header.h"

/*******************************************************
* テクスチャの読み込みを行う関数
* 返り値としてテクスチャデータのIDを返す
* 引数
* filename:テクスチャファイルの名前
********************************************************/
GLuint SetTexture(const char* filename) {
	GLuint TextureID;
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);//テクスチャの読み込み

    //失敗した場合終了
    if (!data) {
        exit(1);
    }
    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);//テクスチャのバインド

    // テクスチャの設定
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // テクスチャデータをOpenGLにアップロード
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
        (channels == 4 ? GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0); //テクスチャのバインドを解除
    stbi_image_free(data); //メモリを解放
    return TextureID;
}

/*******************************************************
* 壁のテクスチャの描画を行う関数
* 引数
* TextureID:テクスチャデータのID
********************************************************/
void DrawWallTexture(GLuint TextureID) {
    glBindTexture(GL_TEXTURE_2D, TextureID);
    glBegin(GL_QUADS);

    // 前面
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 15.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(2.0f, 15.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    // 後面
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 15.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(2.0f, 15.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);

    // 側面（右）
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 15.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(2.0f, 15.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // 側面（左）
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 15.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(2.0f, 15.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

/*******************************************************
* 扉のテクスチャの描画を行う関数
* 引数
* TextureID:テクスチャデータのID
********************************************************/
void DrawGateTexture(GLuint TextureID) {
    glBindTexture(GL_TEXTURE_2D, TextureID);
    glBegin(GL_QUADS);

    // 前面
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}