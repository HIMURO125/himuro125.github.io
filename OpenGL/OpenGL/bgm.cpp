#include <GL/glut.h>  // OpenGLのヘッダ
#include <fmod.hpp>   // FMODのヘッダ
#include <iostream>

// FMODシステムとサウンド
FMOD::System* soundSystem = nullptr;
FMOD::Sound* bgmSound = nullptr;
FMOD::Channel* channel = nullptr;

void initFMOD() {
    // FMODシステムの初期化
    FMOD::System_Create(&soundSystem);
    soundSystem->init(512, FMOD_INIT_NORMAL, nullptr);

    // BGMサウンドの読み込み
    soundSystem->createSound("bgm.mp3", FMOD_DEFAULT, nullptr, &bgmSound);
    bgmSound->setMode(FMOD_LOOP_NORMAL);  // ループ再生に設定
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
    // OpenGLの描画コード（例：3Dオブジェクトの描画）
    // ...

    // FMODの更新
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
    if (key == 'p') {  // 'p'キーでBGMを再生
        playBGM();
    }
    else if (key == 'q') {  // 'q'キーで終了
        cleanupFMOD();
        exit(0);
    }
}

int main(int argc, char** argv) {
    // OpenGLの初期化
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("OpenGL + FMOD Example");

    // FMODの初期化
    initFMOD();

    // OpenGLのコールバック関数の設定
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    // メインループ
    glutMainLoop();

    // 終了処理
    cleanupFMOD();
    return 0;
}