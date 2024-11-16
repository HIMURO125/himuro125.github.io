/*******************************************************
* ファイル名：Game.cpp
* 概要　　　：main関数を持ち、freeglutの処理を主に実行
* 　　　　　　freeglutを使用
********************************************************/
#pragma once
#include "header.h"

float cameraX = 0.0f;               //カメラのx座標
float cameraY = 1.0f;               //カメラのy座標
float cameraZ = 0.0f;               //カメラのz座標
float cameraAngle = 0.0f;           //カメラの角度
float cameraDirX;                   //カメラのx軸方向の向き
float cameraDirZ;                   //カメラのz軸方向の向き
int size;                           //迷路のサイズ
const int Path = 0;                 //道を0とする
const int Wall = 1;                 //壁を1とする
const int Key = 2;                  //鍵を2とする
const int Gate = 3;                 //扉を3とする
std::vector<std::vector<int>> maze; //迷路の二次元配列
bool keyflag = false;               //鍵を取得しているかのフラグ
bool gateflag = false;              //扉が開いているかのフラグ
bool support = true;                //足跡機能のフラグ(デフォルトでON)
bool TitleSound = false;            //タイトル画面のBGMがなっているかのフラグ
bool PlaySound = false;             //ゲーム画面のBGMがなっているかのフラグ
bool ResultSound = false;           //リザルト画面のBGMがなっているかのフラグ
bool move = false;                  //移動しているかのフラグ
bool goForward = false;             //前に進んでいるかのフラグ
bool goBack = false;                //後ろに進んでいるかのフラグ
bool flag = false;                  //扉のSEを一度だけ再生するためのフラグ
int scene = 0;                      //現在のゲーム状態
const int title = 0;                //タイトル画面を0とする
const int play = 1;                 //ゲーム画面を1とする
const int result = 2;               //リザルト画面を2とする
const int option = 3;               //オプション画面を3とする
const int pause = 4;                //ポーズ画面を4とする
int WindowW = 0;                    //ウィンドウの幅
int WindowH = 0;                    //ウィンドウの高さ
int currentItem = 0;                //タイトル画面の選択項目
int currentOpItem = 0;              //オプション画面の選択項目
int currentPaItem = 0;              //ポーズ画面の選択項目
std::chrono::time_point<std::chrono::steady_clock> start_time;        //ステージを始めた時間
std::chrono::time_point<std::chrono::steady_clock> pause_start_time;  //ポーズ画面を開き始めた時間
std::chrono::time_point<std::chrono::steady_clock> pause_end_time;    //ポーズ画面を閉じた時間
std::chrono::nanoseconds pause_time;                                  //ポーズ画面を開いていた累計時間
char Goal_char[50];                                //クリアタイムを記述する文字配列
float line_diffuse[] = { 1.0f,1.0f,1.0f,1.0f };    //床、足跡、壁、鍵、扉の
float line_specular[] = { 1.0f,1.0f,1.0f,1.0f };   //環境光、拡散光、鏡面光、鏡面係数の設定
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

AABB cameraBox;              //カメラのAABB
AABB KEY;                    //鍵のAABB
AABB GATE;                   //扉のAABB
AABB GOAL;                   //ゴールのAABB
std::vector<AABB> cubes;     //全ての壁のAABBを格納する配列
std::vector<Square> squares; //全ての足跡の座標を格納する配列

/*******************************************************
* 一般キーが押された時に呼び出される関数
* 引数
* key:押されたキーのASCIIコード
* x,y:キーを押したときのマウスの座標値
********************************************************/
void myKeyboard(unsigned char key, int x, int y) {
	//タイトル画面
	if (scene == title) {
		//Enterキー
		if (key == 13) {
			//レベル１
			if (currentItem == 0) {
				currentPaItem = 0;
				size = 9;
				maze = InitMaze(size);                        //サイズを指定して迷路作成
				start_time = std::chrono::steady_clock::now();//開始時刻の記録
				keyflag = false;                              //フラグ等のリセット
				gateflag = false;
				flag = false;
				scene = play;
				cameraX = -34.0f;
				cameraZ = -34.0f;
			}
			//レベル２
			else if (currentItem == 1) {
				currentPaItem = 0;
				size = 15;
				maze = InitMaze(size);                        //サイズを指定して迷路作成
				start_time = std::chrono::steady_clock::now();//開始時刻の記録
				keyflag = false;                              //フラグ等のリセット
				gateflag = false;
				flag = false;
				scene = play;
				cameraX = -34.0f;
				cameraZ = -34.0f;
			}
			//レベル３
			else if (currentItem == 2) {
				currentPaItem = 0;
				size = 21;
				maze = InitMaze(size);                        //サイズを指定して迷路作成
				start_time = std::chrono::steady_clock::now();//開始時刻の記録
				keyflag = false;                              //フラグ等のリセット
				gateflag = false;
				flag = false;
				scene = play;
				cameraX = -34.0f;
				cameraZ = -34.0f;
			}
			//オプション画面に遷移
			else if (currentItem == 3) {
				scene = option;
			}
		}
	}
	//リザルト画面
	else if (scene == result) {
		//Enterキー
		if (key == 13) {
			scene = title;  //タイトル画面に遷移
		}
	}
	//オプション画面
	else if (scene == option) {
		//Enterキー
		if (key == 13) {
			//足跡機能ON
			if (currentOpItem == 0) {
				support = true;
			}
			//足跡機能OFF
			else if (currentOpItem == 1) {
				support = false;
			}
			scene = title;  //タイトル画面に遷移
		}
	}
	//ゲーム画面
	else if (scene == play) {
		//Pキー
		if (key == 'p') {
			scene = pause;                                       //ポーズ画面に遷移
			pause_start_time = std::chrono::steady_clock::now(); //ポーズ開始時刻の記録
		}
	}
	//ポーズ画面
	else if (scene == pause) {
		//Enterキー
		if (key == 13) {
			//Yes
			if (currentPaItem == 0) {
				pause_end_time = std::chrono::steady_clock::now();             //ポーズ終了時刻の記録
				pause_time = pause_time + (pause_end_time - pause_start_time); //ポーズ累計時間の記録
				scene = play;  //ゲーム画面に遷移
			}
			//No
			else if (currentPaItem == 1) {
				scene = title;  //タイトル画面に遷移
			}
		}
	}
	//Escキー
	if (key == 27)
		exit(0);  //終了
}

/*******************************************************
* 特殊キーが押された時に呼び出される関数
* 引数
* key:押された特殊キーのコード
* x,y:キーを押したときのマウスの座標値
********************************************************/
void mySpecialKeys(int key, int x, int y) {
	//タイトル画面
	if (scene == title) {
		switch (key) {
		case GLUT_KEY_UP:   //上矢印キーで項目を上に移動
			currentItem = (currentItem + 3) % 4;
			break;
		case GLUT_KEY_DOWN: //上矢印キーで項目を下に移動
			currentItem = (currentItem + 1) % 4;
			break;
		}
	}
	//オプション画面
	else if (scene == option) {
		switch (key) {
		case GLUT_KEY_LEFT:  //左矢印キーで項目を左に移動
			currentOpItem = (currentOpItem + 1) % 2; 
			break;
		case GLUT_KEY_RIGHT: //右矢印キーで項目を右に移動
			currentOpItem = (currentOpItem + 1) % 2;
			break;
		}
	}
	//ゲーム画面
	else if (scene == play) {
		switch (key) {
		case GLUT_KEY_UP:    //上矢印キーで前進
			goForward = true;
			break;
		case GLUT_KEY_DOWN:  //下矢印キーで後退
			goBack = true;
			break;
		case GLUT_KEY_LEFT:  //左矢印キーで左を向く
			cameraAngle -= M_PI / 2;
			break;
		case GLUT_KEY_RIGHT: //右矢印キーで右を向く
			cameraAngle += M_PI / 2;
			break;
		}
	}
	//ポーズ画面
	else if (scene == pause) {
		switch (key) {
		case GLUT_KEY_LEFT:  //左矢印キーで項目を左に移動
			currentPaItem = (currentPaItem + 1) % 2;
			break;
		case GLUT_KEY_RIGHT: //右矢印キーで項目を右に移動
			currentPaItem = (currentPaItem + 1) % 2;
			break;
		}
	}
}

/*******************************************************
* 特殊キーを押すのを止めた時に呼び出される関数
* 引数
* key:押されていた特殊キーのコード
* x,y:キーを押したときのマウスの座標値
********************************************************/
void mySpecialKeysUp(int key, int x, int y) {
	//上矢印キーまたは下矢印キーを離したとき
	if (key == GLUT_KEY_UP || key == GLUT_KEY_DOWN) {
		goForward = false;
		goBack = false;
		//移動時のSE停止
		if (move) {
			StopSE(0);
			move = false;
		}
	}
}

/*******************************************************
* 光源の各種設定を行う関数
* 設定を行った後、光源を有効にする
********************************************************/
void SetLight() {
	float light0_pos[] = { 1.0f ,0.0f, 1.0f ,0.0f };     //平行光源の方向ベクトルの数値
	float light1_pos[] = { -1.0f ,0.0f, -1.0f ,0.0f };
	float light0_ambient[] = { 0.25f,0.25f,0.25f,1.0f }; //光源の環境光、拡散光、鏡面光の数値
	float light1_ambient[] = { 0.1f,0.1f,0.1f,1.0f };
	float light0_diffuse[] = { 0.5f,0.5f,0.5f,1.0f };
	float light1_diffuse[] = { 0.1f,0.1f,0.1f,1.0f };
	float light_specular[] = { 1.0f,1.0f,1.0f,1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);       //光源の各種設定
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glEnable(GL_LIGHT0);  //光源の有効化
	glEnable(GL_LIGHT1);
}

/*******************************************************
* freeglutによる描画を行う時に呼び出す関数
* ゲーム状態に応じて描画を変更
********************************************************/
void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //グラフィックス用のフレームバッファ、zバッファの初期化
	//タイトル画面
	if (scene == title) {
		squares.clear(); //足跡消去
		PlaySound = false;
		ResultSound = false;
		//BGM再生
		if (!TitleSound) {
			PlayBGM(0);
			TitleSound = true;
		}

		glPushMatrix();                    //現在の変換行列状態を保存 これにより他の行列処理の影響を受け無くなる
		glMatrixMode(GL_PROJECTION);       //投影変換行列スタックを選択

		glPushMatrix();
		glLoadIdentity();                  //単位行列を格納
		gluOrtho2D(0, WindowW, 0, WindowH);//直交投影を定義
		glMatrixMode(GL_MODELVIEW);        //モデルビュー行列スタックを選択
		glLoadIdentity();
		char Titletext[17] = "3D Maze Explorer";  //文字列配列
		char Level1[7] = "Level1";
		char Level2[7] = "Level2";
		char Level3[7] = "Level3";
		char Option[7] = "Option";
		char* p;
		int textWidth = 0;

		glColor3d(1.0, 1.0, 1.0);          //文字の色設定
		//文字数カウント
		for (p = Titletext; *p; p++) {
			textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		int xPos = (WindowW - textWidth) / 2; //画面中央座標を設定
		int yPos = WindowH / 2;
		glRasterPos2i(xPos, yPos + 100);      //文字の位置を設定
		//文字描画
		for (p = Titletext; *p; p++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		}
		textWidth = 0;
		//選択中は文字の色を変える
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
		glPopMatrix();  //保存した変換行列を復帰

		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
	//ゲーム画面
	else if (scene == play) {
		TitleSound = false;
		ResultSound = false;
		//BGM再生
		if (!PlaySound) {
			PlayBGM(1);
			PlaySound = true;
		}
		glEnable(GL_DEPTH_TEST);       //陰面処理、光源の有効化
		glEnable(GL_LIGHTING);

		glPushMatrix();
		cameraDirX = cos(cameraAngle); //x軸方向の向きを設定
		cameraDirZ = sin(cameraAngle); //z軸方向の向きを設定
		gluLookAt(cameraX, cameraY, cameraZ, cameraX + cameraDirX, 1, cameraZ + cameraDirZ, 0, 1, 0); //視点
		SetLight();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, line_diffuse); //マテリアルの各種設定
		glMaterialfv(GL_FRONT, GL_SPECULAR, line_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mtrl_shininess);

		//床描画
		glBegin(GL_LINES);
		for (int i = -35; i < 7; i += 2) {
			glVertex3i(i, 0, -35);
			glVertex3i(i, 0, 35);
			glVertex3i(-50, 0, i);
			glVertex3i(50, 0, i);
		}
		glEnd();

		//足跡描画
		if (support) {
			for (const auto& square : squares) {
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, point_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, point_specular);
				glMaterialfv(GL_FRONT, GL_SHININESS, mtrl_shininess);
				drawSquare(square.x, square.z);
			}
		}

		Vector3 center; //中心座標
		cubes.clear();  //壁のAABBを全て消去

		//壁、鍵、ゴール描画
		for (int x = 0; x < size; x++) {
			for (int z = 0; z < size; z++) {
				//壁
				if (maze[x][z] == Wall) {
					glPushMatrix();
					glTranslated(2 * x - 36, 7.5, 2 * z - 36);           //移動
					glScaled(2.0, 15.0, 2.0);                            //大きさ変更
					center = { 2.0f * x - 36, 2.0f, 2.0f * z - 36 };
					cubes.push_back(GetCubeAABB(center, 2.0));           //壁のAABBを追加
					glMaterialfv(GL_FRONT, GL_AMBIENT, cube_ambient);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_diffuse);
					glMaterialfv(GL_FRONT, GL_SPECULAR, cube_specular);
					glMaterialfv(GL_FRONT, GL_SHININESS, cube_shininess);
					glutSolidCube(1.0);                                  //ソリッドの立方体を描画
					glPopMatrix();
				}
				//鍵を取っていない場合描画
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
				//扉を開けていない場合描画
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
				//扉を開けたらゴールの当たり判定を作成
				else if (maze[x][z] == Gate && gateflag) {
					glPushMatrix();
					center = { 2.0f * x - 34, 1.0, 2.0f * z - 36 };
					GOAL = GetCubeAABB(center, 2.0);
					glPopMatrix();
				}
			}
		}
		glPopMatrix();

		glDisable(GL_DEPTH_TEST);  //陰面処理の無効化
	}
	//リザルト画面
	else if (scene == result) {
		squares.clear();
		StopSE(2);  //扉のSE停止
		TitleSound = false;
		PlaySound = false;
		//BGM再生
		if (!ResultSound) {
			PlayBGM(2);
			ResultSound = true;
		}
		glDisable(GL_LIGHTING);  //光源の無効化

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
	//ポーズ画面
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
	glutSwapBuffers();  //描画実行
}

/*******************************************************
* ウィンドウの初期化を行う関数
********************************************************/
void myInit() {
	WindowW = 640;
	WindowH = 480;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //ダブルバッファモード、RGBAモード、zバッファの使用を宣言
	glutInitWindowSize(WindowW, WindowH);                      //ウィンドウサイズの指定 引数は共にピクセル値
	glutInitWindowPosition(0, 0);                              //ウィンドウの左上の位置の指定 引数は共にピクセル値
	glutCreateWindow("Maze");                                  //ウィンドウ生成 引数はウィンドウ名
	glClearColor(0.0, 0.0, 0.0, 1.0);                          //カラーバッファのクリア
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (double)WindowW / (double)WindowH, 0.1, 20.0); //透視投影を定義
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	glLoadIdentity();
}

/*******************************************************
* ユーザーがマウスなどを用いてウィンドウのサイズ、位置を変更した時に呼び出される関数
* 引数
* width,height:新しいウィンドウの横幅と縦幅 共にピクセル数
********************************************************/
void myReshape(int width, int height) {
	glViewport(0, 0, width, height);  //ビューポートの設定
	WindowW = width;
	WindowH = height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)width / (double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*******************************************************
* 足跡の描画を行う関数
* 引数
* value:この関数に付与された番号 今回は使用しない
********************************************************/
void onTimer(int value) {
	if (support) {
		//新しい足跡を足元の位置に追加
		squares.push_back(Square{ cameraX, cameraZ });
		//0.5秒間隔
		glutTimerFunc(500, onTimer, 0);
	}
}

/*******************************************************
* 描画の更新を行う関数
* 引数
* value:この関数に付与された番号 今回は使用しない
********************************************************/
void Update(int value) {
	Vector3 preCameraPos = { cameraX, cameraY, cameraZ }; //移動前のカメラ座標
	float speed = 0.1f; // カメラの移動速度
	//ゲーム画面
	if (scene == play) {
		//前進
		if (goForward) {
			cameraX += cameraDirX * speed;
			cameraZ += cameraDirZ * speed;
			if (!move) {
				PlaySE(0);
				move = true;
			}
		}
		//後退
		else if (goBack) {
			cameraX -= cameraDirX * speed;
			cameraZ -= cameraDirZ * speed;
			if (!move) {
				PlaySE(0);
				move = true;
			}
		}
		Vector3 cameraPosition = { cameraX, cameraY, cameraZ }; //移動後のカメラ座標
		cameraBox = GetCameraAABB(cameraPosition);
		//壁の衝突検知
		for (int i = 0; i < cubes.size(); i++) {
			if (CheckCollision(cameraBox, cubes[i])) {
				cameraX = preCameraPos.x;
				cameraZ = preCameraPos.z;
				break;
			}
		}
		//鍵の衝突判定
		if (CheckCollision(cameraBox, KEY)) {
			if (!keyflag) {
				keyflag = true;
				PlaySE(1);
			}
				
		}
		//扉の衝突判定
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
		//ゴールの衝突判定
		if (CheckCollision(cameraBox, GOAL) && gateflag) {
			//クリアタイム計算
			auto current_time = std::chrono::steady_clock::now();
			auto Goalseconds = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time - pause_time).count();
			snprintf(Goal_char, sizeof(Goal_char), "Clear Time: %lld Seconds", Goalseconds);
			scene = result;
		}
	}
	glutPostRedisplay(); //再描画を指示する
	glutTimerFunc(16, Update, 0);
}

/*******************************************************
* メイン関数
* 引数
* argc:コマンドライン引数の数
* argv:コマンドライン引数の文字列の配列
********************************************************/
int main(int argc, char** argv) {
	srand(time(NULL));                 //乱数生成のシード値を現在時刻で設定
	glutInit(&argc, argv);             //GLUTライブラリの初期化 引数はウィンドウ名
	myInit();
	glutKeyboardFunc(myKeyboard);      //一般キーが押された時に呼び出す関数の指定
	glutSpecialFunc(mySpecialKeys);    //特殊キーが押された時に呼び出す関数の指定
	glutSpecialUpFunc(mySpecialKeysUp);//特殊キーを押すのを止めた時に呼び出す関数の指定
	glutReshapeFunc(myReshape);        //ウィンドウのサイズ、位置を変更した時に呼び出す関数の指定
	glutDisplayFunc(myDisplay);        //freeglutによる描画を行う関数の指定
	glutTimerFunc(500, onTimer, 0);    //指定した時間(ミリ秒単位)毎に呼び出す関数の指定
	glutTimerFunc(16, Update, 0);      //引数は左から呼び出すまでの時間、呼び出す関数名、関数に付与する番号
	if (!initSDL()) {                  
		return -1;
	}
	LoadSound();
	glutMainLoop();                    //他イベント待ちになるイベント処理ループに入る
	closeSDL();
	return 0;
}