#include "header.h"

float cameraX = 0.0f;
float cameraY = 1.0f;
float cameraZ = 0.0f;
float cameraAngle = 0.0f;
float cameraDirX;
float cameraDirZ;
int size;
const int Path = 0;
const int Wall = 1;
const int Key = 2;
const int Gate = 3;
std::vector<std::vector<int>> maze;
bool keyflag = false;
bool gateflag = false;
bool support = true;
int scene = 0;
const int title = 0;
const int play = 1;
const int result = 2;
const int option = 3;
int WindowW = 0;
int WindowH = 0;
int currentItem = 0;
int currentOpItem = 0;
std::chrono::time_point<std::chrono::steady_clock> start_time;
char Goal_char[50];

AABB cameraBox;
std::vector<AABB> cubes;
AABB KEY;
AABB GATE;
AABB GOAL;

std::vector<Square> squares;

//開始(Enter)と終了(Esc)
void myKeyboard(unsigned char key, int x, int y) {
	if (scene == title) {//タイトル画面
		if (key == 13) {
			if (currentItem == 0) {//レベル１
				size = 9;
				maze = InitMaze(size);//サイズを指定して迷路作成
				start_time = std::chrono::steady_clock::now();
				keyflag = false;//フラグ等のリセット
				gateflag = false;
				scene = play;
				cameraX = -34.0f;
				cameraZ = -34.0f;
			}
			else if (currentItem == 1) {//レベル２
				size = 15;
				maze = InitMaze(size);//サイズを指定して迷路作成
				start_time = std::chrono::steady_clock::now();
				keyflag = false;//フラグ等のリセット
				gateflag = false;
				scene = play;
				cameraX = -34.0f;
				cameraZ = -34.0f;
			}
			else if (currentItem == 2) {//レベル３
				size = 21;
				maze = InitMaze(size);//サイズを指定して迷路作成
				start_time = std::chrono::steady_clock::now();
				keyflag = false;//フラグ等のリセット
				gateflag = false;
				scene = play;
				cameraX = -34.0f;
				cameraZ = -34.0f;
			}
			else if (currentItem == 3) {
				scene = option;
			}
			glutPostRedisplay();
		}
	}
	else if (scene == result) {//リザルト画面
		if (key == 13) {
			scene = title;
			glutPostRedisplay();
		}
	}
	else if (scene == option) {
		if (key == 13) {
			if (currentOpItem == 0) {
				support = true;
			}
			else if (currentOpItem == 1) {
				support = false;
			}
			scene = title;
			glutPostRedisplay();
		}
	}
	if (key == 27)
		exit(0);
	if (key == 'p') {  // 'p'キーでBGMを再生
		if (scene == title || scene == option) {
			initFMODTitle();
		}
		else if (scene == play) {
			initFMODPlay();
		}
		else if (scene == result) {
			initFMODResult();
		}
		playBGM();
	}
	else if (key == 'q') {  // 'q'キーで終了
		cleanupFMOD();
	}
}

//自機、項目操作
void mySpecialKeys(int key, int x, int y) {
	if (scene == title) {
		switch (key) {
		case GLUT_KEY_UP:
			currentItem = (currentItem + 3) % 4; // 項目を上に移動
			break;
		case GLUT_KEY_DOWN:
			currentItem = (currentItem + 1) % 4; // 項目を下に移動
			break;
		}
		glutPostRedisplay(); // 再描画を指示
	}
	else if (scene == option) {
		switch (key) {
		case GLUT_KEY_LEFT:
			currentOpItem = (currentOpItem + 1) % 2; // 項目を左に移動
			break;
		case GLUT_KEY_RIGHT:
			currentOpItem = (currentOpItem + 1) % 2; // 項目を右に移動
			break;
		}
		glutPostRedisplay(); // 再描画を指示
	}
	else if (scene == play) {
		float speed = 0.1f; // カメラの移動速度
		Vector3 preCameraPos = { cameraX, cameraY, cameraZ };

		switch (key) {
		case GLUT_KEY_UP: // 上矢印キーで前進
			cameraX += cameraDirX * speed;
			cameraZ += cameraDirZ * speed;
			break;
		case GLUT_KEY_DOWN: // 下矢印キーで後退
			cameraX -= cameraDirX * speed;
			cameraZ -= cameraDirZ * speed;
			break;
		case GLUT_KEY_LEFT: //左矢印キーで左を向く
			cameraAngle -= M_PI / 2;
			break;
		case GLUT_KEY_RIGHT: //右矢印キーで右を向く
			cameraAngle += M_PI / 2;
			break;
		}

		Vector3 cameraPosition = { cameraX, cameraY, cameraZ };
		cameraBox = GetCameraAABB(cameraPosition);//壁の当たり判定
		for (int i = 0; i < cubes.size(); i++) {
			if (CheckCollision(cameraBox, cubes[i])) {
				cameraX = preCameraPos.x;
				cameraZ = preCameraPos.z;
				break;
			}
		}
		if (CheckCollisionKey(cameraBox, KEY)) {//鍵の当たり判定
			if (!keyflag)
				keyflag = true;
		}
		if (CheckCollisionGate(cameraBox, GATE)) {//扉の当たり判定
			if (!keyflag) {
				cameraX = preCameraPos.x;
				cameraZ = preCameraPos.z;
			}
			else if (keyflag) {
				gateflag = true;
			}
		}
		if (CheckCollision(cameraBox, GOAL) && gateflag) {//ゴールの当たり判定
			auto current_time = std::chrono::steady_clock::now();
			auto Goalseconds = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();
			snprintf(Goal_char, sizeof(Goal_char), "CLEAR TIME: %lld SECONDS", Goalseconds);
			scene = result;
		}
		glutPostRedisplay(); // 再描画を指示
	}
}

void drawSquare(float x, float z) {
	glBegin(GL_QUADS);
	glVertex3f(x - 0.1f, 0.0f, z - 0.1f);
	glVertex3f(x + 0.1f, 0.0f, z - 0.1f);
	glVertex3f(x + 0.1f, 0.0f, z + 0.1f);
	glVertex3f(x - 0.1f, 0.0f, z + 0.1f);
	glEnd();
}

//描画処理
void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//タイトル画面
	if (scene == title) {
		glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, WindowW, 0, WindowH);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		char Titletext[10] = "MAZE GAME";
		char Level1[7] = "LEVEL1";
		char Level2[7] = "LEVEL2";
		char Level3[7] = "LEVEL3";
		char Option[7] = "OPTION";
		char* p;
		int textWidth = 0;
		glColor3d(1.0, 1.0, 1.0);
		for (p = Titletext; *p; p++) {
			textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		int xPos = (WindowW - textWidth) / 2;
		int yPos = WindowH / 2;
		glRasterPos2i(xPos, yPos + 100);
		for (p = Titletext; *p; p++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		textWidth = 0;
		if (currentItem == 0) {//選択中は文字の色を変える
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
		if (currentItem == 1) {//選択中は文字の色を変える
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
		if (currentItem == 2) {//選択中は文字の色を変える
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
		if (currentItem == 3) {//選択中は文字の色を変える
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
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
	//ゲーム画面
	else if (scene == play) {
		glEnable(GL_DEPTH_TEST);
		glPushMatrix();
		glLoadIdentity();
		float light_pos[] = { -34 ,5,-34 ,0 };
		float light_ambient[] = { 1.0,1.0,1.0,1.0 };
		float light_diffuse[] = { 1.0,1.0,1.0,1.0 };
		float light_specular[] = { 1.0,1.0,1.0,1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
		glPopMatrix();
		float line_diffuse[] = { 1.0,1.0,1.0,1.0 };
		float line_specular[] = { 1.0,1.0,1.0,1.0 };
		float point_diffuse[] = { 0.75,0.75,0.0,1.0 };
		float point_specular[] = { 0.75,0.75,0.0,1.0 };
		float cube_ambient[] = { 0.5,0.5,0.5,1.0 };
		float cube_diffuse[] = { 0.5,0.5,0.5,1.0 };
		float cube_specular[] = { 0.5,0.5, 0.5, 1.0 };
		float cube_shininess[] = { 0.6 };
		float key_ambient[] = { 0.24725,0.1995,0.0745,1.0 };
		float key_diffuse[] = { 0.75164,0.60648,0.22648,1.0 };
		float key_specular[] = { 0.628281,0.555802,0.366065,1.0 };
		float key_shininess[] = { 0.6 };
		float gate_ambient[] = { 0.19125,0.0735,0.0225,1.0 };
		float gate_diffuse[] = { 0.7038,0.27048,0.0828,1.0 };
		float gate_specular[] = { 0.256777,0.137622, 0.086014, 1.0 };
		float gate_shininess[] = { 0.4 };
		float mtrl_shininess[] = { 100.0 };
		glPushMatrix();
		cameraDirX = cos(cameraAngle);
		cameraDirZ = sin(cameraAngle);
		gluLookAt(cameraX, cameraY, cameraZ, cameraX + cameraDirX, 1, cameraZ + cameraDirZ, 0, 1, 0);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, line_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, line_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mtrl_shininess);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glBegin(GL_LINES);
		for (int i = -35; i < 36; i += 2) {//床描画
			glVertex3i(i, 0, -35);
			glVertex3i(i, 0, 35);
			glVertex3i(-50, 0, i);
			glVertex3i(50, 0, i);
		}
		glEnd();
		if (support) {
			for (const auto& square : squares) {
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, point_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, point_specular);
				glMaterialfv(GL_FRONT, GL_SHININESS, mtrl_shininess);
				drawSquare(square.x, square.z);
			}
		}
		Vector3 center;
		cubes.clear();
		for (int x = 0; x < size; x++) {//壁、鍵、ゴール描画
			for (int z = 0; z < size; z++) {
				if (maze[x][z] == Wall) {//壁
					glPushMatrix();
					glTranslated(2 * x - 36, 7.5, 2 * z - 36);
					glScaled(2.0, 15.0, 2.0);
					center = { 2.0f * x - 36, 2.0f, 2.0f * z - 36 };
					cubes.push_back(GetCubeAABB(center, 2.0));
					glMaterialfv(GL_FRONT, GL_AMBIENT, cube_ambient);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_diffuse);
					glMaterialfv(GL_FRONT, GL_SPECULAR, cube_specular);
					glMaterialfv(GL_FRONT, GL_SHININESS, cube_shininess);
					glutSolidCube(1.0);
					glPopMatrix();
				}
				else if (maze[x][z] == Key && !keyflag) {//鍵
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
				else if (maze[x][z] == Gate && !gateflag) {//扉
					glPushMatrix();
					glTranslated(2 * x - 36, 1.0, 2 * z - 36);
					center = { 2.0f * x - 36, 1.0, 2.0f * z - 36 };
					GATE = GetCubeAABB(center, 2.0);
					glScaled(2.0, 2.0, 2.0);
					glMaterialfv(GL_FRONT, GL_AMBIENT, gate_ambient);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, gate_diffuse);
					glMaterialfv(GL_FRONT, GL_SPECULAR, gate_specular);
					glMaterialfv(GL_FRONT, GL_SHININESS, gate_shininess);
					glutSolidCube(1.0);
					glPopMatrix();
				}
				else if (maze[x][z] == Gate && gateflag) {//ゴール
					glPushMatrix();
					center = { 2.0f * x - 34, 1.0, 2.0f * z - 36 };
					GOAL = GetCubeAABB(center, 2.0);
					glPopMatrix();
				}
			}
		}
		glPopMatrix();
		glDisable(GL_DEPTH_TEST);
	}
	//リザルト画面
	else if (scene == result) {
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
		glPushMatrix();
		glColor3f(1, 1, 1);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, WindowW, 0, WindowH);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		char Titletext[12] = "GAME CLEAR!";
		char Starttext[12] = "PRESS ENTER";
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
	//オプション画面
	else if (scene == option) {
		glPushMatrix();
		glColor3f(1, 1, 1);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, WindowW, 0, WindowH);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		char Optiontext[7] = "OPTION";
		char Foot[11] = "FOOTPRINTS";
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
		glRasterPos2i(xPos, yPos + 50);
		for (p = Foot; *p; p++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		textWidth = 0;
		if (currentOpItem == 0) {//選択中は文字の色を変える
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
		if (currentOpItem == 1) {//選択中は文字の色を変える
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
	glutSwapBuffers();
}

//初期化
void myInit(char* progname) {
	int width = 640, height = 480;
	WindowW = width;
	WindowH = height;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Maze");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (double)width / (double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	glLoadIdentity();
}

//ウィンドウサイズ変更
void myReshape(int width, int height) {//新しいウィンドウの横幅と縦幅　ピクセル数で表す
	glViewport(0, 0, width, height);
	WindowW = width;
	WindowH = height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//単位行列格納
	gluPerspective(60.0, (double)width / (double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void onTimer(int value) {
	if (support) {
		// 新しい四角形を足元の位置に追加
		squares.push_back(Square{ cameraX, cameraZ });
		//0.5秒間隔
		glutTimerFunc(500, onTimer, 0);
	}
}

//メイン関数
int main(int argc, char** argv) {
	srand(time(NULL));
	glutInit(&argc, argv);
	myInit(argv[0]);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeys);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutTimerFunc(1000, onTimer, 0);
	glutMainLoop();
	cleanupFMOD();
	return 0;
}