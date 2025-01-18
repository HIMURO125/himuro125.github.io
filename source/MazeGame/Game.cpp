/*******************************************************
* �t�@�C�����FGame.cpp
* �T�v�@�@�@�Fmain�֐��������Afreeglut�̏�������Ɏ��s
* �@�@�@�@�@�@freeglut���g�p
********************************************************/
#pragma once
#include "header.h"

int window = 0;
float cameraX = 0.0f;               //�J������x���W
float cameraY = 1.0f;               //�J������y���W
float cameraZ = 0.0f;               //�J������z���W
float cameraAngle = 0.0f;           //�J�����̊p�x
float cameraDirX = 0.0f; ;          //�J������x�������̌���
float cameraDirZ = 0.0f;            //�J������z�������̌���
int size = 0;                       //���H�̃T�C�Y
const int Path = 0;                 //����0�Ƃ���
const int Wall = 1;                 //�ǂ�1�Ƃ���
const int Key = 2;                  //����2�Ƃ���
const int Gate = 3;                 //����3�Ƃ���
vector<vector<int>> maze;           //���H�̓񎟌��z��
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
const int select = 5;               //�Z���N�g��ʂ�5�Ƃ���
const int explain = 6;              //������ʂ�6�Ƃ���
const int ranking = 7;				//�����L���O��ʂ�7�Ƃ���
int WindowW = 0;                    //�E�B���h�E�̕�
int WindowH = 0;                    //�E�B���h�E�̍���
int currentTiItem = 0;              //�^�C�g����ʂ̑I������
int currentOpItem1 = 0;             //�I�v�V������ʂ̑I������ �s�I��
int currentOpItem2 = 0;				//���Ս���
int currentOpItem3 = 4;				//BGM���ʍ���
int currentOpItem4 = 4;				//SE���ʍ���
int currentPaItem = 0;              //�|�[�Y��ʂ̑I������
int currentSeItem = 0;              //�Z���N�g��ʂ̑I������
chrono::time_point<chrono::steady_clock> start_time;        //�X�e�[�W���n�߂�����
chrono::time_point<chrono::steady_clock> pause_start_time;  //�|�[�Y��ʂ��J���n�߂�����
chrono::time_point<chrono::steady_clock> pause_end_time;    //�|�[�Y��ʂ��������
chrono::nanoseconds pause_time;                             //�|�[�Y��ʂ��J���Ă����݌v����
char Goal_char[50] = {};                                //�N���A�^�C�����L�q���镶���z��
float line_diffuse[] = { 1.0f,1.0f,1.0f,1.0f };    //���A���ՁA�ǁA���A����
float line_specular[] = { 1.0f,1.0f,1.0f,1.0f };   //�����A�g�U���A���ʌ��A���ʌW���̐ݒ�
float point_diffuse[] = { 0.75f,0.75f,0.0f,1.0f };
float point_specular[] = { 0.75f,0.75f,0.0f,1.0f };
float cube_ambient[] = { 0.5f,0.5f,0.5f,1.0f };
float cube_diffuse[] = { 0.75f,0.75f,0.75f,1.0f };
float cube_specular[] = { 0.9f,0.9f, 0.9f,1.0f };
float key_ambient[] = { 0.24725f,0.1995f,0.0745f,1.0f };
float key_diffuse[] = { 0.75164f,0.60648f,0.22648f,1.0f };
float key_specular[] = { 0.628281f,0.555802f,0.366065f,1.0f };
float key_shininess[] = { 0.4f };
float gate_ambient[] = { 0.19125f,0.0735f,0.0225f,1.0f };
float gate_diffuse[] = { 0.7038f,0.27048f,0.0828f,1.0f };
float gate_specular[] = { 0.256777f,0.137622f, 0.086014f, 1.0f };
float shininess[] = { 1.0f };

AABB cameraBox = {};     //�J������AABB
AABB KEY = {};           //����AABB
AABB GATE = {};          //����AABB
AABB GOAL = {};          //�S�[����AABB
vector<AABB> cubes;      //�S�Ă̕ǂ�AABB���i�[����z��
vector<Square> squares;  //�S�Ă̑��Ղ̍��W���i�[����z��
GLuint WallTextureID = 0;//�ǂ̃e�N�X�`��ID
GLuint GateTextureID = 0;//���̃e�N�X�`��ID

/*******************************************************
* ��ʃL�[�������ꂽ���ɌĂяo�����֐�
* ����
* key:�����ꂽ�L�[��ASCII�R�[�h
* x,y:�L�[���������Ƃ��̃}�E�X�̍��W�l
********************************************************/
static void myKeyboard(unsigned char key, int x, int y) {
	//�^�C�g�����
	if (scene == title) {
		//Enter�L�[
		if (key == 13) {
			PlaySE(4);
			//�Z���N�g��ʂɑJ��
			if (currentTiItem == 0) {
				scene = select;
			}
			//������ʂɑJ��
			else if (currentTiItem == 1) {
				scene = explain;
			}
			//�I�v�V������ʂɑJ��
			else if (currentTiItem == 2) {
				scene = option;
			}
			else if (currentTiItem == 3) {
				scene = ranking;
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
		//�ŏI�s���I������Ă���AEnter�L�[������
		if (currentOpItem1 == 3 && key == 13) {
			PlaySE(4);
			//���Ջ@�\ON
			if (currentOpItem2 == 0) {
				support = true;
			}
			//���Ջ@�\OFF
			else if (currentOpItem2 == 1) {
				support = false;
			}
			scene = title;		//�^�C�g����ʂɑJ��
			currentOpItem1 = 0; //�I���s���Z�b�g
		}
	}
	//�Q�[�����
	else if (scene == play) {
		//P�L�[
		if (key == 'p') {
			scene = pause;                                  //�|�[�Y��ʂɑJ��
			pause_start_time = chrono::steady_clock::now(); //�|�[�Y�J�n�����̋L�^
		}
	}
	//�|�[�Y���
	else if (scene == pause) {
		//Enter�L�[
		if (key == 13) {
			PlaySE(4);
			//Yes
			if (currentPaItem == 0) {
				pause_end_time = chrono::steady_clock::now();                  //�|�[�Y�I�������̋L�^
				pause_time = pause_time + (pause_end_time - pause_start_time); //�|�[�Y�݌v���Ԃ̋L�^
				scene = play;  //�Q�[����ʂɑJ��
			}
			//No
			else if (currentPaItem == 1) {
				scene = title;  //�^�C�g����ʂɑJ��
			}
		}
	}
	//�Z���N�g���
	else if (scene == select) {
		//Enter�L�[
		if (key == 13) {
			PlaySE(4);
			if (currentSeItem == 0 || currentSeItem == 1 || currentSeItem == 2) {
				//���x���P
				if (currentSeItem == 0) {
					::size = 9;
				}
				//���x���Q
				else if (currentSeItem == 1) {
					::size = 15;
				}
				//���x���R
				else if (currentSeItem == 2) {
					::size = 21;
				}
				currentPaItem = 0;
				maze = InitMaze(::size);                  //�T�C�Y���w�肵�Ė��H�쐬
				start_time = chrono::steady_clock::now(); //�J�n�����̋L�^
				keyflag = false;                          //�t���O���̃��Z�b�g
				gateflag = false;
				flag = false;
				cameraAngle = 0.0f;
				cameraX = -34.0f;
				cameraZ = -34.0f;
				scene = play;
				cubes.clear();
				cubes = InitWallAABB(::size, ::maze);
			}
			//�^�C�g����ʂɑJ��
			else if (currentSeItem == 3) {
				scene = title;
			}
			currentSeItem = 0;
		}
	}
	//������ʂƃ����L���O���
	else if (scene == explain || scene == ranking) {
		if (key == 13) {
			PlaySE(4);
			scene = title;
		}
	}
	//Esc�L�[
	if (key == 27) {
		glDeleteTextures(1, &WallTextureID);
		glDeleteTextures(1, &GateTextureID);
		glutDestroyWindow(window);
		closeSDL();
		exit(0);  //�I��
	}
}

/*******************************************************
* ����L�[�������ꂽ���ɌĂяo�����֐�
* ����
* key:�����ꂽ����L�[�̃R�[�h
* x,y:�L�[���������Ƃ��̃}�E�X�̍��W�l
********************************************************/
static void mySpecialKeys(int key, int x, int y) {
	//�^�C�g�����
	if (scene == title) {
		switch (key) {
		case GLUT_KEY_UP:   //����L�[�ō��ڂ���Ɉړ�
			currentTiItem = (currentTiItem + 3) % 4;
			PlaySE(3);
			break;
		case GLUT_KEY_DOWN: //����L�[�ō��ڂ����Ɉړ�
			currentTiItem = (currentTiItem + 1) % 4;
			PlaySE(3);
			break;
		}
	}
	//�I�v�V�������
	else if (scene == option) {
		switch (key) {
		case GLUT_KEY_LEFT:  //�����L�[�ō��ڂ����Ɉړ�
			//����
			if (currentOpItem1 == 0) {
				currentOpItem2 = (currentOpItem2 + 1) % 2;
			}
			//BGM
			else if (currentOpItem1 == 1) {
				currentOpItem3 = (currentOpItem3 + 4) % 5;
			}
			//SE
			else if (currentOpItem1 == 2) {
				currentOpItem4 = (currentOpItem4 + 4) % 5;
			}
			PlaySE(3);
			break;
		case GLUT_KEY_RIGHT: //�E���L�[�ō��ڂ��E�Ɉړ�
			//����
			if (currentOpItem1 == 0) {
				currentOpItem2 = (currentOpItem2 + 1) % 2;
			}
			//BGM
			else if (currentOpItem1 == 1) {
				currentOpItem3 = (currentOpItem3 + 1) % 5;
			}
			//SE
			else if (currentOpItem1 == 2) {
				currentOpItem4 = (currentOpItem4 + 1) % 5;
			}
			PlaySE(3);
			break;
		case GLUT_KEY_UP:   //����L�[�ōs����Ɉړ�
			currentOpItem1 = (currentOpItem1 + 3) % 4;
			PlaySE(3);
			break;
		case GLUT_KEY_DOWN: //�����L�[�ōs�����Ɉړ�
			currentOpItem1 = (currentOpItem1 + 1) % 4;
			PlaySE(3);
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
			cameraAngle -= (float)(M_PI / 2);
			break;
		case GLUT_KEY_RIGHT: //�E���L�[�ŉE������
			cameraAngle += (float)(M_PI / 2);
			break;
		}
	}
	//�|�[�Y���
	else if (scene == pause) {
		switch (key) {
		case GLUT_KEY_LEFT:  //�����L�[�ō��ڂ����Ɉړ�
			currentPaItem = (currentPaItem + 1) % 2;
			PlaySE(3);
			break;
		case GLUT_KEY_RIGHT: //�E���L�[�ō��ڂ��E�Ɉړ�
			currentPaItem = (currentPaItem + 1) % 2;
			PlaySE(3);
			break;
		}
	}
	//�Z���N�g���
	else if (scene == select) {
		switch (key) {
		case GLUT_KEY_UP:   //����L�[�ō��ڂ���Ɉړ�
			currentSeItem = (currentSeItem + 3) % 4;
			PlaySE(3);
			break;
		case GLUT_KEY_DOWN: //����L�[�ō��ڂ����Ɉړ�
			currentSeItem = (currentSeItem + 1) % 4;
			PlaySE(3);
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
static void mySpecialKeysUp(int key, int x, int y) {
	//����L�[�܂��͉����L�[�𗣂����Ƃ�
	if (key == GLUT_KEY_UP || key == GLUT_KEY_DOWN) {
		goForward = false;
		goBack = false;
		//�ړ�����SE��~
		if (::move) {
			StopSE(0);
			::move = false;
		}
	}
}

/*******************************************************
* �����̊e��ݒ���s���֐�
* �ݒ���s������A������L���ɂ���
********************************************************/
static void SetLight() {
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
static void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�O���t�B�b�N�X�p�̃t���[���o�b�t�@�Az�o�b�t�@�̏�����
	//�^�C�g�����
	if (scene == title) {
		PlaySound = false;
		ResultSound = false;
		//BGM�Đ�
		if (!TitleSound) {
			PlayBGM(0);
			TitleSound = true;
		}

		glMatrixMode(GL_PROJECTION);       //���e�ϊ��s��X�^�b�N��I��
		glLoadIdentity();                  //�P�ʍs����i�[
		gluOrtho2D(0, WindowW, 0, WindowH);//���𓊉e���`
		glMatrixMode(GL_MODELVIEW);        //���f���r���[�s��X�^�b�N��I��
		glLoadIdentity();
		glPushMatrix();                    //���݂̕ϊ��s���Ԃ�ۑ� ����ɂ�葼�̍s�񏈗��̉e�����󂯖����Ȃ�
		char Titletext[17] = "3D Maze Explorer";  //������z��
		char Select[13] = "Stage Select";
		char Explain[12] = "Explanation";
		char Option[7] = "Option";
		char Rank[8] = "Ranking";

		//�����̐F�ݒ�
		glColor3d(1.0, 1.0, 1.0);
		DrawChara(WindowW, WindowH, 0, 100, Titletext);
		//�I�𒆂͕����̐F��ς���
		if (currentTiItem == 0) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, 0, 0, Select);
		
		if (currentTiItem == 1) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, 0, -50, Explain);
		
		if (currentTiItem == 2) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, 0, -100, Option);

		if (currentTiItem == 3) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, 0, -150, Rank);
		
		glPopMatrix();  //�ۑ������ϊ��s��𕜋A
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
		glEnable(GL_DEPTH_TEST);       //�A�ʏ����A�����A�e�N�X�`���̗L����
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0, (double)WindowW / (double)WindowH, 0.1, 20.0); //�������e���`
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glPushMatrix();
		cameraDirX = cos(cameraAngle); //x�������̌�����ݒ�
		cameraDirZ = sin(cameraAngle); //z�������̌�����ݒ�
		gluLookAt(cameraX, cameraY, cameraZ, cameraX + cameraDirX, 1, cameraZ + cameraDirZ, 0, 1, 0); //���_
		SetLight();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, line_diffuse); //�}�e���A���̊e��ݒ�
		glMaterialfv(GL_FRONT, GL_SPECULAR, line_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

		//���`��
		glBegin(GL_LINES);
		for (int i = -35; i < 7; i += 2) {
			glVertex3i(i, 0, -35);
			glVertex3i(i, 0, 35);
			glVertex3i(-35, 0, i);
			glVertex3i(35, 0, i);
		}
		glEnd();

		glDisable(GL_LIGHTING);
		//���Օ`��
		if (support) {
			for (const auto& square : squares) {
				glColor3f(1, 1, 0);
				drawSquare(square.x, square.z);
			}
		}
		glEnable(GL_LIGHTING);
		
		Vector3 center; //���S���W

		//�ǁA���A�S�[���`��
		for (int x = 0; x < ::size; x++) {
			for (int z = 0; z < ::size; z++) {
				//��
				if (maze[x][z] == Wall) {
					glPushMatrix();
					glTranslated(2 * x - 36, 7.5, 2 * z - 36);           //�ړ�
					glScaled(2.0, 15.0, 2.0);                            //�傫���ύX
					glMaterialfv(GL_FRONT, GL_AMBIENT, cube_ambient);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_diffuse);
					glMaterialfv(GL_FRONT, GL_SPECULAR, cube_specular);
					glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
					DrawWallTexture(WallTextureID);                      //�e�N�X�`���̕`��
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
					glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
					DrawGateTexture(GateTextureID);
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

		glDisable(GL_DEPTH_TEST);  //�A�ʏ����A�e�N�X�`���A�����̖�����
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		//UI�̕`��
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, WindowW, 0, WindowH, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		if (support) {
			glPushMatrix();
			glTranslated(WindowW - 47.5, WindowH - 60, 0);
			glRotated(cameraAngle * 180 / M_PI, 0, 0, 1);
			glTranslated(-WindowW + 47.5, -WindowH + 60, 0);
			glColor3f(1, 0, 0);
			glBegin(GL_TRIANGLES);
			glVertex2d(WindowW - 65, WindowH - 60);
			glVertex2d(WindowW - 30, WindowH - 60);
			glVertex2d(WindowW - 47.5, WindowH - 30);
			glEnd();
			glColor3f(1, 1, 1);
			glBegin(GL_TRIANGLES);
			glVertex2d(WindowW - 65, WindowH - 60);
			glVertex2d(WindowW - 47.5, WindowH - 90);
			glVertex2d(WindowW - 30, WindowH - 60);
			glEnd();
			glPopMatrix();
		}
		glPushMatrix();
		auto current_time = chrono::steady_clock::now();
		auto seconds = chrono::duration_cast<chrono::seconds>(current_time - start_time - pause_time).count();
		char Time_Char[30] = {};
		snprintf(Time_Char, sizeof(Time_Char), "Time: %lld ", seconds);
		DrawChara(WindowW / 4, WindowH * 7 / 4, 0, 0, Time_Char);
		glPopMatrix();
	}
	//���U���g���
	else if (scene == result) {
		StopSE(2);  //����SE��~
		TitleSound = false;
		PlaySound = false;
		//BGM�Đ�
		if (!ResultSound) {
			PlayBGM(2);
			ResultSound = true;
		}
		glDisable(GL_LIGHTING);  //�����̖�����
		glColor3f(1, 1, 1);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, WindowW, 0, WindowH);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		char Resulttext[12] = "Game Clear!";
		char Backtext[12] = "Press Enter";

		DrawChara(WindowW, WindowH, 0, 50, Resulttext);
		DrawChara(WindowW, WindowH, 0, 0, Goal_char);
		DrawChara(WindowW, WindowH, 0, -50, Backtext);
		
		glPopMatrix();
	}
	//�I�v�V�������
	else if (scene == option) {
		glColor3f(1, 1, 1);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, WindowW, 0, WindowH);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		char Optiontext[7] = "Option";
		char Foot[8] = "Support";
		char On[3] = "ON";
		char Off[4] = "OFF";
		char BGM[4] = "BGM";
		char SE[3] = "SE";
		char One[2] = "1";
		char Two[2] = "2";
		char Three[2] = "3";
		char Max[4] = "MAX";
		char Ok[3] = "OK";

		//�����`��
		DrawChara(WindowW, WindowH, 0, 150, Optiontext);
		DrawChara(WindowW, WindowH, 0, 100, Foot);
		if (currentOpItem1 == 0 && currentOpItem2 == 0) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, -50, 50, On);
		if (currentOpItem1 == 0 && currentOpItem2 == 1) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, 50, 50, Off);
		glColor3d(1.0, 1.0, 1.0);
		DrawChara(WindowW, WindowH, 0, 0, BGM);
		if (currentOpItem1 == 1 && currentOpItem3 == 0) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, -150, -50, Off);
		if (currentOpItem1 == 1 && currentOpItem3 == 1) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, -75, -50, One);
		if (currentOpItem1 == 1 && currentOpItem3 == 2) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, 0, -50, Two);
		if (currentOpItem1 == 1 && currentOpItem3 == 3) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, 75, -50, Three);
		if (currentOpItem1 == 1 && currentOpItem3 == 4) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, 150, -50, Max);
		glColor3d(1.0, 1.0, 1.0);
		DrawChara(WindowW, WindowH, 0, -100, SE);
		if (currentOpItem1 == 2 && currentOpItem4 == 0) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, -150, -150, Off);
		if (currentOpItem1 == 2 && currentOpItem4 == 1) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, -75, -150, One);
		if (currentOpItem1 == 2 && currentOpItem4 == 2) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, 0, -150, Two);
		if (currentOpItem1 == 2 && currentOpItem4 == 3) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, 75, -150, Three);
		if (currentOpItem1 == 2 && currentOpItem4 == 4) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, 150, -150, Max);
		if (currentOpItem1 == 3) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, 0, -200, Ok);
		
		glPopMatrix();
	}
	//�|�[�Y���
	else if (scene == pause) {
		glDisable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, WindowW, 0, WindowH);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		char Pausetext[6] = "Pause";
		char Continue[10] = "Continue?";
		char Yes[4] = "Yes";
		char No[3] = "No";

		DrawChara(WindowW, WindowH, 0, 100, Pausetext);
		DrawChara(WindowW, WindowH, 0, 0, Continue);
		if (currentPaItem == 0) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, -50, -50, Yes);
		if (currentPaItem == 1) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, 50, -50, No);
		
		glPopMatrix();
	}
	//�Z���N�g���
	else if (scene == select) {
		squares.clear(); //���Տ���
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, WindowW, 0, WindowH);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		char Selecttext[13] = "Stage Select";
		char Level1[7] = "Level1";
		char Level2[7] = "Level2";
		char Level3[7] = "Level3";
		char Back[5] = "Back";

		//�����̐F�ݒ�
		glColor3d(1.0, 1.0, 1.0);
		DrawChara(WindowW, WindowH, 0, 100, Selecttext);
		//�I�𒆂͕����̐F��ς���
		if (currentSeItem == 0) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, 0, 0, Level1);

		if (currentSeItem == 1) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, 0, -50, Level2);

		if (currentSeItem == 2) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, 0, -100, Level3);

		if (currentSeItem == 3) {
			glColor3d(1.0, 0.0, 0.0);
		}
		else {
			glColor3d(1.0, 1.0, 1.0);
		}
		DrawChara(WindowW, WindowH, 0, -150, Back);

		glPopMatrix();
	}
	//�������
	else if (scene == explain) {
		glColor3f(1, 1, 1);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, WindowW, 0, WindowH);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		char Extext[12] = "Explanation";
		char Ex1[17] = "Arrows:Move,Turn";
		char Ex2[8] = "P:Pause";
		char Ex3[10] = "Esc:Exit";
		char Back[5] = "Back";

		glColor3d(1.0, 1.0, 1.0);
		DrawChara(WindowW, WindowH, 0, 100, Extext);
		DrawChara(WindowW, WindowH, 0, 0, Ex1);
		DrawChara(WindowW, WindowH, 0, -50, Ex2);
		DrawChara(WindowW, WindowH, 0, -100, Ex3);
		glColor3d(1.0, 0.0, 0.0);
		DrawChara(WindowW, WindowH, 0, -200, Back);

		glPopMatrix();
	}
	//�����L���O���
	else if (scene == ranking) {
		glColor3f(1, 1, 1);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, WindowW, 0, WindowH);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		char Rank[8] = "Ranking";
		char Level1[7] = "Level1";
		char Level2[7] = "Level2";
		char Level3[7] = "Level3";
		char Back[5] = "Back";
		vector<int> Lev1 = ReadFile("Rank1.txt");//�t�@�C���̓ǂݍ���
		vector<int> Lev2 = ReadFile("Rank2.txt");
		vector<int> Lev3 = ReadFile("Rank3.txt");

		char fir1[20], sec1[20], thir1[20];
		char fir2[20], sec2[20], thir2[20];
		char fir3[20], sec3[20], thir3[20];

		snprintf(fir1, sizeof(fir1), "1# %d sec", Lev1[0]);  //int�^��char�^�ɕϊ�
		snprintf(sec1, sizeof(sec1), "2# %d sec", Lev1[1]);
		snprintf(thir1, sizeof(thir1), "3# %d sec", Lev1[2]);
		snprintf(fir2, sizeof(fir2), "1# %d sec", Lev2[0]);
		snprintf(sec2, sizeof(sec2), "2# %d sec", Lev2[1]);
		snprintf(thir2, sizeof(thir2), "3# %d sec", Lev2[2]);
		snprintf(fir3, sizeof(fir2), "1# %d sec", Lev3[0]);
		snprintf(sec3, sizeof(sec2), "2# %d sec", Lev3[1]);
		snprintf(thir3, sizeof(thir2), "3# %d sec", Lev3[2]);

		DrawChara(WindowW, WindowH, 0, 100, Rank);
		DrawChara(WindowW, WindowH, -150, 50, Level1);
		DrawChara(WindowW, WindowH, -150, 0, fir1);
		DrawChara(WindowW, WindowH, -150, -50, sec1);
		DrawChara(WindowW, WindowH, -150, -100, thir1);
		DrawChara(WindowW, WindowH, 0, 50, Level2);
		DrawChara(WindowW, WindowH, 0, 0, fir2);
		DrawChara(WindowW, WindowH, 0, -50, sec2);
		DrawChara(WindowW, WindowH, 0, -100, thir2);
		DrawChara(WindowW, WindowH, 150, 50, Level3);
		DrawChara(WindowW, WindowH, 150, 0, fir3);
		DrawChara(WindowW, WindowH, 150, -50, sec3);
		DrawChara(WindowW, WindowH, 150, -100, thir3);
		glColor3f(1, 0, 0);
		DrawChara(WindowW, WindowH, 0, -150, Back);

	}
	glutSwapBuffers();  //�`����s
}

/*******************************************************
* �E�B���h�E�̏��������s���֐�
********************************************************/
static void myInit() {
	WindowW = 640;
	WindowH = 480;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //�_�u���o�b�t�@���[�h�ARGBA���[�h�Az�o�b�t�@�̎g�p��錾
	glutInitWindowSize(WindowW, WindowH);                      //�E�B���h�E�T�C�Y�̎w�� �����͋��Ƀs�N�Z���l
	glutInitWindowPosition(0, 0);                              //�E�B���h�E�̍���̈ʒu�̎w�� �����͋��Ƀs�N�Z���l
	window = glutCreateWindow("Maze");                         //�E�B���h�E���� �����̓E�B���h�E��
	glClearColor(0.0, 0.0, 0.0, 1.0);                          //�J���[�o�b�t�@�̃N���A
	glShadeModel(GL_SMOOTH);
	glLoadIdentity();
}

/*******************************************************
* ���[�U�[���}�E�X�Ȃǂ�p���ăE�B���h�E�̃T�C�Y�A�ʒu��ύX�������ɌĂяo�����֐�
* ����
* width,height:�V�����E�B���h�E�̉����Əc�� ���Ƀs�N�Z����
********************************************************/
static void myReshape(int width, int height) {
	glViewport(0, 0, width, height);  //�r���[�|�[�g�̐ݒ�
	WindowW = width;
	WindowH = height;
}

/*******************************************************
* ���Ղ̕`����s���֐�
* ����
* value:���̊֐��ɕt�^���ꂽ�ԍ� ����͎g�p���Ȃ�
********************************************************/
static void onTimer(int value) {
	if (support) {
		//�V�������Ղ𑫌��̈ʒu�ɒǉ�
		squares.push_back(Square{ cameraX, cameraZ });
	}
	//0.5�b�Ԋu
	glutTimerFunc(500, onTimer, 0);
}

/*******************************************************
* �`��̍X�V���s���֐�
* ����
* value:���̊֐��ɕt�^���ꂽ�ԍ� ����͎g�p���Ȃ�
********************************************************/
static void Update(int value) {
	Vector3 preCameraPos = { cameraX, cameraY, cameraZ }; //�ړ��O�̃J�������W
	float speed = 0.1f; // �J�����̈ړ����x
	//�Q�[�����
	if (scene == play) {
		//�O�i
		if (goForward) {
			cameraX += cameraDirX * speed;
			cameraZ += cameraDirZ * speed;
			if (!::move) {
				PlaySE(0);
				::move = true;
			}
		}
		//���
		else if (goBack) {
			cameraX -= cameraDirX * speed;
			cameraZ -= cameraDirZ * speed;
			if (!::move) {
				PlaySE(0);
				::move = true;
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
		if (!keyflag && CheckCollision(cameraBox, KEY)) {
			keyflag = true;
			PlaySE(1);
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
		if (gateflag && CheckCollision(cameraBox, GOAL)) {
			//�N���A�^�C���v�Z
			auto current_time = chrono::steady_clock::now();
			auto Goalseconds = chrono::duration_cast<chrono::seconds>(current_time - start_time - pause_time).count();
			snprintf(Goal_char, sizeof(Goal_char), "Clear Time: %lld Seconds", Goalseconds);
			//�N���A�^�C���̏�������
			switch(::size) {
			case 9:
				WriteFile(Goalseconds, "Rank1.txt");
				break;
			case 15:
				WriteFile(Goalseconds, "Rank2.txt");
				break;
			case 21:
				WriteFile(Goalseconds, "Rank3.txt");
				break;
			}
			scene = result;
		}
	}
	//�I�v�V�������
	else if (scene == option) {
		SetBGMVolume(currentOpItem3);//BGM���ʐݒ�
		SetSEVolume(currentOpItem4); //SE���ʐݒ�
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
	srand((unsigned int)(time(NULL)));                 //���������̃V�[�h�l�����ݎ����Őݒ�
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
	CheckFile("Rank1.txt");
	CheckFile("Rank2.txt");
	CheckFile("Rank3.txt");
	WallTextureID = SetTexture("wall.jpg");
	GateTextureID = SetTexture("gate.jpg");
	glutMainLoop();                    //���C�x���g�҂��ɂȂ�C�x���g�������[�v�ɓ���
	return 0;
}