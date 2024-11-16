/*******************************************************
* �t�@�C�����FGame.cpp
* �T�v�@�@�@�Fmain�֐��������Afreeglut�̏�������Ɏ��s
* �@�@�@�@�@�@freeglut���g�p
********************************************************/
#pragma once
#include "header.h"

float cameraX = 0.0f;               //�J������x���W
float cameraY = 1.0f;               //�J������y���W
float cameraZ = 0.0f;               //�J������z���W
float cameraAngle = 0.0f;           //�J�����̊p�x
float cameraDirX;                   //�J������x�������̌���
float cameraDirZ;                   //�J������z�������̌���
int size;                           //���H�̃T�C�Y
const int Path = 0;                 //����0�Ƃ���
const int Wall = 1;                 //�ǂ�1�Ƃ���
const int Key = 2;                  //����2�Ƃ���
const int Gate = 3;                 //����3�Ƃ���
std::vector<std::vector<int>> maze; //���H�̓񎟌��z��
bool keyflag = false;               //�����擾���Ă��邩�̃t���O
bool gateflag = false;              //�����J���Ă��邩�̃t���O
bool support = true;                //���Ջ@�\�̃t���O(�f�t�H���g��ON)
bool TitleSound = false;            //�^�C�g����ʂ�BGM���Ȃ��Ă��邩�̃t���O
bool PlaySound = false;             //�Q�[����ʂ�BGM���Ȃ��Ă��邩�̃t���O
bool ResultSound = false;           //���U���g��ʂ�BGM���Ȃ��Ă��邩�̃t���O
bool move = false;                  //�ړ����Ă��邩�̃t���O
bool goForward = false;             //�O�ɐi��ł��邩�̃t���O
bool goBack = false;                //���ɐi��ł��邩�̃t���O
bool flag = false;                  //����SE����x�����Đ����邽�߂̃t���O
int scene = 0;                      //���݂̃Q�[�����
const int title = 0;                //�^�C�g����ʂ�0�Ƃ���
const int play = 1;                 //�Q�[����ʂ�1�Ƃ���
const int result = 2;               //���U���g��ʂ�2�Ƃ���
const int option = 3;               //�I�v�V������ʂ�3�Ƃ���
const int pause = 4;                //�|�[�Y��ʂ�4�Ƃ���
int WindowW = 0;                    //�E�B���h�E�̕�
int WindowH = 0;                    //�E�B���h�E�̍���
int currentItem = 0;                //�^�C�g����ʂ̑I������
int currentOpItem = 0;              //�I�v�V������ʂ̑I������
int currentPaItem = 0;              //�|�[�Y��ʂ̑I������
std::chrono::time_point<std::chrono::steady_clock> start_time;        //�X�e�[�W���n�߂�����
std::chrono::time_point<std::chrono::steady_clock> pause_start_time;  //�|�[�Y��ʂ��J���n�߂�����
std::chrono::time_point<std::chrono::steady_clock> pause_end_time;    //�|�[�Y��ʂ��������
std::chrono::nanoseconds pause_time;                                  //�|�[�Y��ʂ��J���Ă����݌v����
char Goal_char[50];                                //�N���A�^�C�����L�q���镶���z��
float line_diffuse[] = { 1.0f,1.0f,1.0f,1.0f };    //���A���ՁA�ǁA���A����
float line_specular[] = { 1.0f,1.0f,1.0f,1.0f };   //�����A�g�U���A���ʌ��A���ʌW���̐ݒ�
float point_diffuse[] = { 0.75f,0.75f,0.0f,1.0f };
float point_specular[] = { 0.75f,0.75f,0.0f,1.0f };
float cube_ambient[] = { 0.5f,0.5f,0.5f,1.0f };
float cube_diffuse[] = { 0.75f,0.75f,0.75f,1.0f };
float cube_specular[] = { 0.9f,0.9f, 0.9f, 1.0f };
float cube_shininess[] = { 1.0f };
float key_ambient[] = { 0.24725f,0.1995f,0.0745f,1.0f };
float key_diffuse[] = { 0.75164f,0.60648f,0.22648f,1.0f };
float key_specular[] = { 0.628281f,0.555802f,0.366065f,1.0f };
float key_shininess[] = { 0.4f };
float gate_ambient[] = { 0.19125f,0.0735f,0.0225f,1.0f };
float gate_diffuse[] = { 0.7038f,0.27048f,0.0828f,1.0f };
float gate_specular[] = { 0.256777f,0.137622f, 0.086014f, 1.0f };
float gate_shininess[] = { 0.4f };
float mtrl_shininess[] = { 1.0f };

AABB cameraBox;              //�J������AABB
AABB KEY;                    //����AABB
AABB GATE;                   //����AABB
AABB GOAL;                   //�S�[����AABB
std::vector<AABB> cubes;     //�S�Ă̕ǂ�AABB���i�[����z��
std::vector<Square> squares; //�S�Ă̑��Ղ̍��W���i�[����z��

/*******************************************************
* ��ʃL�[�������ꂽ���ɌĂяo�����֐�
* ����
* key:�����ꂽ�L�[��ASCII�R�[�h
* x,y:�L�[���������Ƃ��̃}�E�X�̍��W�l
********************************************************/
void myKeyboard(unsigned char key, int x, int y) {
	//�^�C�g�����
	if (scene == title) {
		//Enter�L�[
		if (key == 13) {
			//���x���P
			if (currentItem == 0) {
				currentPaItem = 0;
				size = 9;
				maze = InitMaze(size);                        //�T�C�Y���w�肵�Ė��H�쐬
				start_time = std::chrono::steady_clock::now();//�J�n�����̋L�^
				keyflag = false;                              //�t���O���̃��Z�b�g
				gateflag = false;
				flag = false;
				scene = play;
				cameraX = -34.0f;
				cameraZ = -34.0f;
			}
			//���x���Q
			else if (currentItem == 1) {
				currentPaItem = 0;
				size = 15;
				maze = InitMaze(size);                        //�T�C�Y���w�肵�Ė��H�쐬
				start_time = std::chrono::steady_clock::now();//�J�n�����̋L�^
				keyflag = false;                              //�t���O���̃��Z�b�g
				gateflag = false;
				flag = false;
				scene = play;
				cameraX = -34.0f;
				cameraZ = -34.0f;
			}
			//���x���R
			else if (currentItem == 2) {
				currentPaItem = 0;
				size = 21;
				maze = InitMaze(size);                        //�T�C�Y���w�肵�Ė��H�쐬
				start_time = std::chrono::steady_clock::now();//�J�n�����̋L�^
				keyflag = false;                              //�t���O���̃��Z�b�g
				gateflag = false;
				flag = false;
				scene = play;
				cameraX = -34.0f;
				cameraZ = -34.0f;
			}
			//�I�v�V������ʂɑJ��
			else if (currentItem == 3) {
				scene = option;
			}
		}
	}
	//���U���g���
	else if (scene == result) {
		//Enter�L�[
		if (key == 13) {
			scene = title;  //�^�C�g����ʂɑJ��
		}
	}
	//�I�v�V�������
	else if (scene == option) {
		//Enter�L�[
		if (key == 13) {
			//���Ջ@�\ON
			if (currentOpItem == 0) {
				support = true;
			}
			//���Ջ@�\OFF
			else if (currentOpItem == 1) {
				support = false;
			}
			scene = title;  //�^�C�g����ʂɑJ��
		}
	}
	//�Q�[�����
	else if (scene == play) {
		//P�L�[
		if (key == 'p') {
			scene = pause;                                       //�|�[�Y��ʂɑJ��
			pause_start_time = std::chrono::steady_clock::now(); //�|�[�Y�J�n�����̋L�^
		}
	}
	//�|�[�Y���
	else if (scene == pause) {
		//Enter�L�[
		if (key == 13) {
			//Yes
			if (currentPaItem == 0) {
				pause_end_time = std::chrono::steady_clock::now();             //�|�[�Y�I�������̋L�^
				pause_time = pause_time + (pause_end_time - pause_start_time); //�|�[�Y�݌v���Ԃ̋L�^
				scene = play;  //�Q�[����ʂɑJ��
			}
			//No
			else if (currentPaItem == 1) {
				scene = title;  //�^�C�g����ʂɑJ��
			}
		}
	}
	//Esc�L�[
	if (key == 27)
		exit(0);  //�I��
}

/*******************************************************
* ����L�[�������ꂽ���ɌĂяo�����֐�
* ����
* key:�����ꂽ����L�[�̃R�[�h
* x,y:�L�[���������Ƃ��̃}�E�X�̍��W�l
********************************************************/
void mySpecialKeys(int key, int x, int y) {
	//�^�C�g�����
	if (scene == title) {
		switch (key) {
		case GLUT_KEY_UP:   //����L�[�ō��ڂ���Ɉړ�
			currentItem = (currentItem + 3) % 4;
			break;
		case GLUT_KEY_DOWN: //����L�[�ō��ڂ����Ɉړ�
			currentItem = (currentItem + 1) % 4;
			break;
		}
	}
	//�I�v�V�������
	else if (scene == option) {
		switch (key) {
		case GLUT_KEY_LEFT:  //�����L�[�ō��ڂ����Ɉړ�
			currentOpItem = (currentOpItem + 1) % 2; 
			break;
		case GLUT_KEY_RIGHT: //�E���L�[�ō��ڂ��E�Ɉړ�
			currentOpItem = (currentOpItem + 1) % 2;
			break;
		}
	}
	//�Q�[�����
	else if (scene == play) {
		switch (key) {
		case GLUT_KEY_UP:    //����L�[�őO�i
			goForward = true;
			break;
		case GLUT_KEY_DOWN:  //�����L�[�Ō��
			goBack = true;
			break;
		case GLUT_KEY_LEFT:  //�����L�[�ō�������
			cameraAngle -= M_PI / 2;
			break;
		case GLUT_KEY_RIGHT: //�E���L�[�ŉE������
			cameraAngle += M_PI / 2;
			break;
		}
	}
	//�|�[�Y���
	else if (scene == pause) {
		switch (key) {
		case GLUT_KEY_LEFT:  //�����L�[�ō��ڂ����Ɉړ�
			currentPaItem = (currentPaItem + 1) % 2;
			break;
		case GLUT_KEY_RIGHT: //�E���L�[�ō��ڂ��E�Ɉړ�
			currentPaItem = (currentPaItem + 1) % 2;
			break;
		}
	}
}

/*******************************************************
* ����L�[�������̂��~�߂����ɌĂяo�����֐�
* ����
* key:������Ă�������L�[�̃R�[�h
* x,y:�L�[���������Ƃ��̃}�E�X�̍��W�l
********************************************************/
void mySpecialKeysUp(int key, int x, int y) {
	//����L�[�܂��͉����L�[�𗣂����Ƃ�
	if (key == GLUT_KEY_UP || key == GLUT_KEY_DOWN) {
		goForward = false;
		goBack = false;
		//�ړ�����SE��~
		if (move) {
			StopSE(0);
			move = false;
		}
	}
}

/*******************************************************
* �����̊e��ݒ���s���֐�
* �ݒ���s������A������L���ɂ���
********************************************************/
void SetLight() {
	float light0_pos[] = { 1.0f ,0.0f, 1.0f ,0.0f };     //���s�����̕����x�N�g���̐��l
	float light1_pos[] = { -1.0f ,0.0f, -1.0f ,0.0f };
	float light0_ambient[] = { 0.25f,0.25f,0.25f,1.0f }; //�����̊����A�g�U���A���ʌ��̐��l
	float light1_ambient[] = { 0.1f,0.1f,0.1f,1.0f };
	float light0_diffuse[] = { 0.5f,0.5f,0.5f,1.0f };
	float light1_diffuse[] = { 0.1f,0.1f,0.1f,1.0f };
	float light_specular[] = { 1.0f,1.0f,1.0f,1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);       //�����̊e��ݒ�
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glEnable(GL_LIGHT0);  //�����̗L����
	glEnable(GL_LIGHT1);
}

/*******************************************************
* freeglut�ɂ��`����s�����ɌĂяo���֐�
* �Q�[����Ԃɉ����ĕ`���ύX
********************************************************/
void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�O���t�B�b�N�X�p�̃t���[���o�b�t�@�Az�o�b�t�@�̏�����
	//�^�C�g�����
	if (scene == title) {
		squares.clear(); //���Տ���
		PlaySound = false;
		ResultSound = false;
		//BGM�Đ�
		if (!TitleSound) {
			PlayBGM(0);
			TitleSound = true;
		}

		glPushMatrix();                    //���݂̕ϊ��s���Ԃ�ۑ� ����ɂ�葼�̍s�񏈗��̉e�����󂯖����Ȃ�
		glMatrixMode(GL_PROJECTION);       //���e�ϊ��s��X�^�b�N��I��

		glPushMatrix();
		glLoadIdentity();                  //�P�ʍs����i�[
		gluOrtho2D(0, WindowW, 0, WindowH);//���𓊉e���`
		glMatrixMode(GL_MODELVIEW);        //���f���r���[�s��X�^�b�N��I��
		glLoadIdentity();
		char Titletext[17] = "3D Maze Explorer";  //������z��
		char Level1[7] = "Level1";
		char Level2[7] = "Level2";
		char Level3[7] = "Level3";
		char Option[7] = "Option";
		char* p;
		int textWidth = 0;

		glColor3d(1.0, 1.0, 1.0);          //�����̐F�ݒ�
		//�������J�E���g
		for (p = Titletext; *p; p++) {
			textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		int xPos = (WindowW - textWidth) / 2; //��ʒ������W��ݒ�
		int yPos = WindowH / 2;
		glRasterPos2i(xPos, yPos + 100);      //�����̈ʒu��ݒ�
		//�����`��
		for (p = Titletext; *p; p++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		textWidth = 0;
		//�I�𒆂͕����̐F��ς���
		if (currentItem == 0) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}

		for (p = Level1; *p; p++) {
			textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		xPos = (WindowW - textWidth) / 2;
		glRasterPos2i(xPos, yPos);
		for (p = Level1; *p; p++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}

		textWidth = 0;
		if (currentItem == 1) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		for (p = Level2; *p; p++) {
			textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		xPos = (WindowW - textWidth) / 2;
		glRasterPos2i(xPos, yPos - 50);
		for (p = Level2; *p; p++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}

		textWidth = 0;
		if (currentItem == 2) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		for (p = Level3; *p; p++) {
			textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		xPos = (WindowW - textWidth) / 2;
		glRasterPos2i(xPos, yPos - 100);
		for (p = Level3; *p; p++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}

		textWidth = 0;
		if (currentItem == 3) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		for (p = Option; *p; p++) {
			textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		xPos = (WindowW - textWidth) / 2;
		glRasterPos2i(xPos, yPos - 150);
		for (p = Option; *p; p++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();  //�ۑ������ϊ��s��𕜋A

		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
	//�Q�[�����
	else if (scene == play) {
		TitleSound = false;
		ResultSound = false;
		//BGM�Đ�
		if (!PlaySound) {
			PlayBGM(1);
			PlaySound = true;
		}
		glEnable(GL_DEPTH_TEST);       //�A�ʏ����A�����̗L����
		glEnable(GL_LIGHTING);

		glPushMatrix();
		cameraDirX = cos(cameraAngle); //x�������̌�����ݒ�
		cameraDirZ = sin(cameraAngle); //z�������̌�����ݒ�
		gluLookAt(cameraX, cameraY, cameraZ, cameraX + cameraDirX, 1, cameraZ + cameraDirZ, 0, 1, 0); //���_
		SetLight();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, line_diffuse); //�}�e���A���̊e��ݒ�
		glMaterialfv(GL_FRONT, GL_SPECULAR, line_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mtrl_shininess);

		//���`��
		glBegin(GL_LINES);
		for (int i = -35; i < 7; i += 2) {
			glVertex3i(i, 0, -35);
			glVertex3i(i, 0, 35);
			glVertex3i(-50, 0, i);
			glVertex3i(50, 0, i);
		}
		glEnd();

		//���Օ`��
		if (support) {
			for (const auto& square : squares) {
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, point_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, point_specular);
				glMaterialfv(GL_FRONT, GL_SHININESS, mtrl_shininess);
				drawSquare(square.x, square.z);
			}
		}

		Vector3 center; //���S���W
		cubes.clear();  //�ǂ�AABB��S�ď���

		//�ǁA���A�S�[���`��
		for (int x = 0; x < size; x++) {
			for (int z = 0; z < size; z++) {
				//��
				if (maze[x][z] == Wall) {
					glPushMatrix();
					glTranslated(2 * x - 36, 7.5, 2 * z - 36);           //�ړ�
					glScaled(2.0, 15.0, 2.0);                            //�傫���ύX
					center = { 2.0f * x - 36, 2.0f, 2.0f * z - 36 };
					cubes.push_back(GetCubeAABB(center, 2.0));           //�ǂ�AABB��ǉ�
					glMaterialfv(GL_FRONT, GL_AMBIENT, cube_ambient);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_diffuse);
					glMaterialfv(GL_FRONT, GL_SPECULAR, cube_specular);
					glMaterialfv(GL_FRONT, GL_SHININESS, cube_shininess);
					glutSolidCube(1.0);                                  //�\���b�h�̗����̂�`��
					glPopMatrix();
				}
				//��������Ă��Ȃ��ꍇ�`��
				else if (maze[x][z] == Key && !keyflag) {
					glPushMatrix();
					glTranslated(2 * x - 36, 1.0, 2 * z - 36);
					center = { 2.0f * x - 36, 1.0, 2.0f * z - 36 };
					KEY = GetKeyAABB(center, 0.5);
					glScaled(1.0, 1.0, 1.0);
					glMaterialfv(GL_FRONT, GL_AMBIENT, key_ambient);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, key_diffuse);
					glMaterialfv(GL_FRONT, GL_SPECULAR, key_specular);
					glMaterialfv(GL_FRONT, GL_SHININESS, key_shininess);
					glutSolidSphere(0.2, 10, 10);
					for (int i = 0; i < 4; i++) {
						glTranslated(0, -0.125, 0);
						glutSolidCube(0.125);
						if (i == 1 || i == 3) {
							glTranslated(0.125, 0, 0);
							glutSolidCube(0.125);
							glTranslated(-0.125, 0, 0.125);
							glutSolidCube(0.125);
							glTranslated(0, 0, -0.125);
						}
					}
					glPopMatrix();
				}
				//�����J���Ă��Ȃ��ꍇ�`��
				else if (maze[x][z] == Gate && !gateflag) {
					glPushMatrix();
					glTranslated(2 * x - 35, 1.0, 2 * z - 36);
					center = { 2.0f * x - 35, 1.0, 2.0f * z - 36 };
					GATE = GetCubeAABB(center, 2.0);
					glScaled(2.0, 2.0, 2.0);
					glMaterialfv(GL_FRONT, GL_AMBIENT, gate_ambient);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, gate_diffuse);
					glMaterialfv(GL_FRONT, GL_SPECULAR, gate_specular);
					glMaterialfv(GL_FRONT, GL_SHININESS, gate_shininess);
					glutSolidCube(1.0);
					glPopMatrix();
				}
				//�����J������S�[���̓����蔻����쐬
				else if (maze[x][z] == Gate && gateflag) {
					glPushMatrix();
					center = { 2.0f * x - 34, 1.0, 2.0f * z - 36 };
					GOAL = GetCubeAABB(center, 2.0);
					glPopMatrix();
				}
			}
		}
		glPopMatrix();

		glDisable(GL_DEPTH_TEST);  //�A�ʏ����̖�����
	}
	//���U���g���
	else if (scene == result) {
		squares.clear();
		StopSE(2);  //����SE��~
		TitleSound = false;
		PlaySound = false;
		//BGM�Đ�
		if (!ResultSound) {
			PlayBGM(2);
			ResultSound = true;
		}
		glDisable(GL_LIGHTING);  //�����̖�����

		glPushMatrix();
		glColor3f(1, 1, 1);
		glMatrixMode(GL_PROJECTION);

		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, WindowW, 0, WindowH);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		char Titletext[12] = "Game Clear!";
		char Starttext[12] = "Press Enter";
		char* p;
		int textWidth = 0;

		for (p = Titletext; *p; p++) {
			textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		int xPos = (WindowW - textWidth) / 2;
		int yPos = WindowH / 2;
		glRasterPos2i(xPos, yPos + 50);
		for (p = Titletext; *p; p++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}

		textWidth = 0;
		for (p = Goal_char; *p; p++) {
			textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		xPos = (WindowW - textWidth) / 2;
		yPos = WindowH / 2;
		glRasterPos2i(xPos, yPos);
		for (p = Goal_char; *p; p++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}

		textWidth = 0;
		for (p = Starttext; *p; p++) {
			textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		xPos = (WindowW - textWidth) / 2;
		yPos = WindowH / 2;
		glRasterPos2i(xPos, yPos - 50);
		for (p = Starttext; *p; p++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
	//�I�v�V�������
	else if (scene == option) {
		glPushMatrix();
		glColor3f(1, 1, 1);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, WindowW, 0, WindowH);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		char Optiontext[7] = "Option";
		char Foot[11] = "Footprints";
		char On[3] = "ON";
		char Off[4] = "OFF";
		char* p;
		int textWidth = 0;

		for (p = Optiontext; *p; p++) {
			textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		int xPos = (WindowW - textWidth) / 2;
		int yPos = WindowH / 2;
		glRasterPos2i(xPos, yPos + 100);
		for (p = Optiontext; *p; p++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}

		textWidth = 0;
		for (p = Foot; *p; p++) {
			textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		xPos = (WindowW - textWidth) / 2;
		yPos = WindowH / 2;
		glRasterPos2i(xPos, yPos);
		for (p = Foot; *p; p++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}

		textWidth = 0;
		if (currentOpItem == 0) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		for (p = On; *p; p++) {
			textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		xPos = (WindowW - textWidth) / 2;
		yPos = WindowH / 2;
		glRasterPos2i(xPos - 50, yPos - 50);
		for (p = On; *p; p++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}

		textWidth = 0;
		if (currentOpItem == 1) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		for (p = Off; *p; p++) {
			textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		xPos = (WindowW - textWidth) / 2;
		yPos = WindowH / 2;
		glRasterPos2i(xPos + 50, yPos - 50);
		for (p = Off; *p; p++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
	//�|�[�Y���
	else if (scene == pause) {
		glDisable(GL_LIGHTING);
		glPushMatrix();
		glColor3f(1, 1, 1);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, WindowW, 0, WindowH);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		char Pausetext[6] = "Pause";
		char Continue[10] = "Continue?";
		char Yes[4] = "Yes";
		char No[3] = "No";
		char* p;

		int textWidth = 0;
		for (p = Pausetext; *p; p++) {
			textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		int xPos = (WindowW - textWidth) / 2;
		int yPos = WindowH / 2;
		glRasterPos2i(xPos, yPos + 100);
		for (p = Pausetext; *p; p++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}

		textWidth = 0;
		for (p = Continue; *p; p++) {
			textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		xPos = (WindowW - textWidth) / 2;
		yPos = WindowH / 2;
		glRasterPos2i(xPos, yPos);
		for (p = Continue; *p; p++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}

		textWidth = 0;
		if (currentPaItem == 0) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		for (p = Yes; *p; p++) {
			textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		xPos = (WindowW - textWidth) / 2;
		yPos = WindowH / 2;
		glRasterPos2i(xPos - 50, yPos - 50);
		for (p = Yes; *p; p++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}

		textWidth = 0;
		if (currentPaItem == 1) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		for (p = No; *p; p++) {
			textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		xPos = (WindowW - textWidth) / 2;
		yPos = WindowH / 2;
		glRasterPos2i(xPos + 50, yPos - 50);
		for (p = No; *p; p++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
	glutSwapBuffers();  //�`����s
}

/*******************************************************
* �E�B���h�E�̏��������s���֐�
********************************************************/
void myInit() {
	WindowW = 640;
	WindowH = 480;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //�_�u���o�b�t�@���[�h�ARGBA���[�h�Az�o�b�t�@�̎g�p��錾
	glutInitWindowSize(WindowW, WindowH);                      //�E�B���h�E�T�C�Y�̎w�� �����͋��Ƀs�N�Z���l
	glutInitWindowPosition(0, 0);                              //�E�B���h�E�̍���̈ʒu�̎w�� �����͋��Ƀs�N�Z���l
	glutCreateWindow("Maze");                                  //�E�B���h�E���� �����̓E�B���h�E��
	glClearColor(0.0, 0.0, 0.0, 1.0);                          //�J���[�o�b�t�@�̃N���A
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (double)WindowW / (double)WindowH, 0.1, 20.0); //�������e���`
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	glLoadIdentity();
}

/*******************************************************
* ���[�U�[���}�E�X�Ȃǂ�p���ăE�B���h�E�̃T�C�Y�A�ʒu��ύX�������ɌĂяo�����֐�
* ����
* width,height:�V�����E�B���h�E�̉����Əc�� ���Ƀs�N�Z����
********************************************************/
void myReshape(int width, int height) {
	glViewport(0, 0, width, height);  //�r���[�|�[�g�̐ݒ�
	WindowW = width;
	WindowH = height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)width / (double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*******************************************************
* ���Ղ̕`����s���֐�
* ����
* value:���̊֐��ɕt�^���ꂽ�ԍ� ����͎g�p���Ȃ�
********************************************************/
void onTimer(int value) {
	if (support) {
		//�V�������Ղ𑫌��̈ʒu�ɒǉ�
		squares.push_back(Square{ cameraX, cameraZ });
		//0.5�b�Ԋu
		glutTimerFunc(500, onTimer, 0);
	}
}

/*******************************************************
* �`��̍X�V���s���֐�
* ����
* value:���̊֐��ɕt�^���ꂽ�ԍ� ����͎g�p���Ȃ�
********************************************************/
void Update(int value) {
	Vector3 preCameraPos = { cameraX, cameraY, cameraZ }; //�ړ��O�̃J�������W
	float speed = 0.1f; // �J�����̈ړ����x
	//�Q�[�����
	if (scene == play) {
		//�O�i
		if (goForward) {
			cameraX += cameraDirX * speed;
			cameraZ += cameraDirZ * speed;
			if (!move) {
				PlaySE(0);
				move = true;
			}
		}
		//���
		else if (goBack) {
			cameraX -= cameraDirX * speed;
			cameraZ -= cameraDirZ * speed;
			if (!move) {
				PlaySE(0);
				move = true;
			}
		}
		Vector3 cameraPosition = { cameraX, cameraY, cameraZ }; //�ړ���̃J�������W
		cameraBox = GetCameraAABB(cameraPosition);
		//�ǂ̏Փˌ��m
		for (int i = 0; i < cubes.size(); i++) {
			if (CheckCollision(cameraBox, cubes[i])) {
				cameraX = preCameraPos.x;
				cameraZ = preCameraPos.z;
				break;
			}
		}
		//���̏Փ˔���
		if (CheckCollision(cameraBox, KEY)) {
			if (!keyflag) {
				keyflag = true;
				PlaySE(1);
			}
				
		}
		//���̏Փ˔���
		if (CheckCollision(cameraBox, GATE)) {
			if (!keyflag) {
				cameraX = preCameraPos.x;
				cameraZ = preCameraPos.z;
			}
			else if (keyflag) {
				gateflag = true;
				if (!flag) {
					PlaySE(2);
					flag = true;
				}
			}
		}
		//�S�[���̏Փ˔���
		if (CheckCollision(cameraBox, GOAL) && gateflag) {
			//�N���A�^�C���v�Z
			auto current_time = std::chrono::steady_clock::now();
			auto Goalseconds = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time - pause_time).count();
			snprintf(Goal_char, sizeof(Goal_char), "Clear Time: %lld Seconds", Goalseconds);
			scene = result;
		}
	}
	glutPostRedisplay(); //�ĕ`����w������
	glutTimerFunc(16, Update, 0);
}

/*******************************************************
* ���C���֐�
* ����
* argc:�R�}���h���C�������̐�
* argv:�R�}���h���C�������̕�����̔z��
********************************************************/
int main(int argc, char** argv) {
	srand(time(NULL));                 //���������̃V�[�h�l�����ݎ����Őݒ�
	glutInit(&argc, argv);             //GLUT���C�u�����̏����� �����̓E�B���h�E��
	myInit();
	glutKeyboardFunc(myKeyboard);      //��ʃL�[�������ꂽ���ɌĂяo���֐��̎w��
	glutSpecialFunc(mySpecialKeys);    //����L�[�������ꂽ���ɌĂяo���֐��̎w��
	glutSpecialUpFunc(mySpecialKeysUp);//����L�[�������̂��~�߂����ɌĂяo���֐��̎w��
	glutReshapeFunc(myReshape);        //�E�B���h�E�̃T�C�Y�A�ʒu��ύX�������ɌĂяo���֐��̎w��
	glutDisplayFunc(myDisplay);        //freeglut�ɂ��`����s���֐��̎w��
	glutTimerFunc(500, onTimer, 0);    //�w�肵������(�~���b�P��)���ɌĂяo���֐��̎w��
	glutTimerFunc(16, Update, 0);      //�����͍�����Ăяo���܂ł̎��ԁA�Ăяo���֐����A�֐��ɕt�^����ԍ�
	if (!initSDL()) {                  
		return -1;
	}
	LoadSound();
	glutMainLoop();                    //���C�x���g�҂��ɂȂ�C�x���g�������[�v�ɓ���
	closeSDL();
	return 0;
}