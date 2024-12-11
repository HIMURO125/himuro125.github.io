#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "header.h"

GLuint SetTexture(const char* filename) {
	GLuint TextureID;
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);

    if (!data) {
        exit(1);
    }
    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);

    // テクスチャの設定
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // テクスチャデータをOpenGLにアップロード
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
        (channels == 4 ? GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0); // テクスチャのバインドを解除
    stbi_image_free(data); // メモリを解放
    return TextureID;
}

void DrawTexture(GLuint TextureID) {
    glBindTexture(GL_TEXTURE_2D, TextureID);
    glBegin(GL_QUADS);

    //前面
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -7.5f, 1.0f);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(1.0f, -7.5f, 1.0f);
    glTexCoord2f(2.0f, 15.0f); glVertex3f(1.0f, 7.5f, 1.0f);
    glTexCoord2f(0.0f, 15.0f); glVertex3f(-1.0f, 7.5f, 1.0f);
    //後面
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -7.5f, -1.0f);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(1.0f, -7.5f, -1.0f);
    glTexCoord2f(2.0f, 15.0f); glVertex3f(1.0f, 7.5f, -1.0f);
    glTexCoord2f(0.0f, 15.0f); glVertex3f(-1.0f, 7.5f, -1.0f);
    //上部
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 7.5f, -1.0f);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(1.0f, 7.5f, -1.0f);
    glTexCoord2f(2.0f, 2.0f); glVertex3f(1.0f, 7.5f, 1.0f);
    glTexCoord2f(0.0f, 2.0f); glVertex3f(-1.0f, 7.5f, 1.0f);
    //下部
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -7.5f, -1.0f);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(1.0f, -7.5f, -1.0f);
    glTexCoord2f(2.0f, 2.0f); glVertex3f(1.0f, -7.5f, 1.0f);
    glTexCoord2f(0.0f, 2.0f); glVertex3f(-1.0f, -7.5f, 1.0f);
    //側面（右）
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -7.5f, -1.0f);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(1.0f, 7.5f, -1.0f);
    glTexCoord2f(2.0f, 2.0f); glVertex3f(1.0f, 7.5f, 1.0f);
    glTexCoord2f(0.0f, 2.0f); glVertex3f(1.0f, -7.5f, 1.0f);
    //側面（左）
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -7.5f, -1.0f);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(-1.0f, 7.5f, -1.0f);
    glTexCoord2f(2.0f, 2.0f); glVertex3f(-1.0f, 7.5f, 1.0f);
    glTexCoord2f(0.0f, 2.0f); glVertex3f(-1.0f, -7.5f, 1.0f);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}