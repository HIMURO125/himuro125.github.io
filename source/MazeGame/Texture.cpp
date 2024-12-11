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

    // �e�N�X�`���̐ݒ�
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // �e�N�X�`���f�[�^��OpenGL�ɃA�b�v���[�h
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
        (channels == 4 ? GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0); // �e�N�X�`���̃o�C���h������
    stbi_image_free(data); // �����������
    return TextureID;
}

void DrawTexture(GLuint TextureID) {
    //glScaled(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, TextureID);
    glBegin(GL_QUADS);

    // �O��
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(2.0f, 15.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 15.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // ���
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(2.0f, 15.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 15.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    // ���ʁi�E�j
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(2.0f, 15.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 15.0f); glVertex3f(0.5f, 0.5f, -0.5f);

    // ���ʁi���j
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(2.0f, 15.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 15.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}