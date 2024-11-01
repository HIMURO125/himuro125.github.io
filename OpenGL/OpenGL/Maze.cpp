#include "header.h"

const int Path = 0;
const int Wall = 1;
const int Key = 2;
const int Gate = 3;
std::vector<std::vector<int>> matrix;

//配列の要素数変更
void MakeArray(int size) {
	matrix.resize(size);
	for (int i = 0; i < size; ++i) {
		matrix[i].resize(size);
	}
}

//棒倒し法
std::vector<std::vector<int>> InitMaze(int size) {
	//変数、配列の初期化
	MakeArray(size);
	for (int x = 0; x < size; x++) {
		for (int z = 0; z < size; z++) {
			matrix[x][z] = Path;
		}
	}
	//迷路生成
	for (int x = 0; x < size; x++) {
		for (int z = 0; z < size; z++) {
			if (x == 0 || z == 0 || x == size - 1 || z == size - 1) {
				matrix[x][z] = Wall;// 外周はすべて壁
			}
			else {
				matrix[x][z] = Path;
			}
		}
	}
	for (int x = 2; x < size - 1; x += 2) {
		for (int z = 2; z < size - 1; z += 2) {
			matrix[x][z] = 1;
			while (true)
			{
				// 1行目のみ上に倒せる
				int direction;
				if (z == 2)
					direction = rand() % 4;
				else
					direction = rand() % 3;

				// 棒を倒す方向を決める
				int wallX = x;
				int wallZ = z;
				switch (direction)
				{
				case 0: // 右
					wallX++;
					break;
				case 1: // 下
					wallZ++;
					break;
				case 2: // 左
					wallX--;
					break;
				case 3: // 上
					wallZ--;
					break;
				}
				// 壁じゃない場合のみ倒して終了
				if (matrix[wallX][wallZ] != Wall)
				{
					matrix[wallX][wallZ] = Wall;
					break;
				}
			}
		}
	}
	matrix[size - 1][size - 2] = Gate;
	while (true) {
		int MinRamge = size / 3;
		int MaxRange = 2 * size / 3 - 1;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(MinRamge, MaxRange);
		int x = dis(gen);
		int z = dis(gen);
		if (matrix[x][z] == Path) {
			matrix[x][z] = Key;
			break;
		}
	}
	return matrix;
}