/*******************************************************
* ファイル名：Maze.cpp
* 概要　　　：二次元配列の迷路の自動生成、サイズ変更、足跡の描画を実行
* 　　　　　　freeglutを使用
********************************************************/
#pragma once
#include "header.h"

const int Path = 0;                    //道を0とする
const int Wall = 1;                    //壁を1とする
const int Key = 2;                     //鍵を2とする
const int Gate = 3;                    //扉を3とする
std::vector<std::vector<int>> matrix;  //迷路の二次元配列

/*******************************************************
* 引数で指定した大きさの迷路を自動生成する関数
* アルゴリズムとして棒倒し法を使用
* 返り値として生成した迷路である二次元配列を返す
* 引数
* size:迷路のサイズ
********************************************************/
std::vector<std::vector<int>> InitMaze(int size) {
	//迷路のサイズ変更
	matrix.resize(size);
	for (int i = 0; i < size; ++i) {
		matrix[i].resize(size);
	}

	//迷路の初期化
	for (int x = 0; x < size; x++) {
		for (int z = 0; z < size; z++) {
			matrix[x][z] = Path;
		}
	}

	//外周を全て壁にする
	for (int x = 0; x < size; x++) {
		for (int z = 0; z < size; z++) {
			if (x == 0 || z == 0 || x == size - 1 || z == size - 1) {
				matrix[x][z] = Wall;
			}
			else {
				matrix[x][z] = Path;
			}
		}
	}

	//棒倒し法
	for (int x = 2; x < size - 1; x += 2) {
		for (int z = 2; z < size - 1; z += 2) {
			matrix[x][z] = 1;      //最初の棒
			while (true)
			{
				int direction;     //棒を倒す方向

				// 1行目のみ上に倒せる
				if (z == 2)
					direction = rand() % 4;
				else
					direction = rand() % 3;

				int wallX = x;     //x座標
				int wallZ = z;     //z座標

				// 棒を倒す方向を決める
				switch (direction)
				{
				case 0: //右
					wallX++;
					break;
				case 1: //下
					wallZ++;
					break;
				case 2: //左
					wallX--;
					break;
				case 3: //上
					wallZ--;
					break;
				}

				//壁じゃない場合のみ棒を倒して終了
				if (matrix[wallX][wallZ] != Wall)
				{
					matrix[wallX][wallZ] = Wall;
					break;
				}
			}
		}
	}
	matrix[size - 1][size - 2] = Gate; //右上を扉とする

	//迷路の中央部分の道のどこかに鍵を設置
	while (true) {
		int MinRamge = size / 3;                                   //迷路のサイズの3分の1の範囲
		int MaxRange = 2 * size / 3 - 1;
		std::random_device rd;                                     //ハードウェア乱数生成器を初期化
		std::mt19937 gen(rd());                                    //擬似乱数生成器を初期化
		std::uniform_int_distribution<int> dis(MinRamge, MaxRange);//MinRamge、MaxRangeの範囲で乱数生成するための分布オブジェクトを作成
		int x = dis(gen);                                          //乱数生成
		int z = dis(gen);

		//選ばれた場所が道の場合鍵を設置
		if (matrix[x][z] == Path) {
			matrix[x][z] = Key;
			break;
		}
	}
	return matrix;
}

/*******************************************************
* 足跡を描画する関数
* 引数
* x,y:描画する座標
********************************************************/
void drawSquare(float x, float z) {
	//四角形のポリゴンを描画
	glBegin(GL_QUADS);
	glVertex3f(x - 0.1f, 0.0f, z - 0.1f);
	glVertex3f(x + 0.1f, 0.0f, z - 0.1f);
	glVertex3f(x + 0.1f, 0.0f, z + 0.1f);
	glVertex3f(x - 0.1f, 0.0f, z + 0.1f);
	glEnd();
}