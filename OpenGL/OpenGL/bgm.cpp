#include <GL/glut.h>  // OpenGL�̃w�b�_
#include <fmod.hpp>   // FMOD�̃w�b�_
#include <iostream>

// FMOD�V�X�e���ƃT�E���h
FMOD::System* soundSystem = nullptr;
FMOD::Sound* bgmSound = nullptr;
FMOD::Channel* channel = nullptr;

void initFMOD() {
    // FMOD�V�X�e���̏�����
    FMOD::System_Create(&soundSystem);
    soundSystem->init(512, FMOD_INIT_NORMAL, nullptr);

    // BGM�T�E���h�̓ǂݍ���
    soundSystem->createSound("bgm.mp3", FMOD_DEFAULT, nullptr, &bgmSound);
    bgmSound->setMode(FMOD_LOOP_NORMAL);  // ���[�v�Đ��ɐݒ�
}

void playBGM() {
    soundSystem->playSound(bgmSound, nullptr, false, &channel);
}

void cleanupFMOD() {
    bgmSound->release();
    soundSystem->close();
    soundSystem->release();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // OpenGL�̕`��R�[�h�i��F3D�I�u�W�F�N�g�̕`��j
    // ...

    // FMOD�̍X�V
    soundSystem->update();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'p') {  // 'p'�L�[��BGM���Đ�
        playBGM();
    }
    else if (key == 'q') {  // 'q'�L�[�ŏI��
        cleanupFMOD();
        exit(0);
    }
}

int main(int argc, char** argv) {
    // OpenGL�̏�����
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("OpenGL + FMOD Example");

    // FMOD�̏�����
    initFMOD();

    // OpenGL�̃R�[���o�b�N�֐��̐ݒ�
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    // ���C�����[�v
    glutMainLoop();

    // �I������
    cleanupFMOD();
    return 0;
}