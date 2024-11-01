#include <iostream>
#include <chrono>
#include <random>
#include <time.h>

/*int size = 15;
const int Path = 0;
const int Wall = 1;
const int Key = 2;
std::vector<std::vector<int>> maze;
bool keyflag = false;

void MakeArray(int size) {
	maze.resize(size);
	for (int i = 0; i < size; ++i) {
		maze[i].resize(size);
	}
}

void InitMaze() {
	MakeArray(size);
	for (int x = 0; x < size; x++) {
		for (int z = 0; z < size; z++) {
			maze[x][z] = Path;
		}
	}
	for (int x = 0; x < size; x++) {
		for (int z = 0; z < size; z++) {
			if (x == 0 || z == 0 || x == size - 1 || z == size - 1) {
				maze[x][z] = Wall;// 外周はすべて壁
			}
			else {
				maze[x][z] = Path;

			}
		}
	}
	for (int x = 2; x < size - 1; x += 2) {
		for (int z = 2; z < size - 1; z += 2) {
			maze[x][z] = 1;
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
				if (maze[wallX][wallZ] != Wall)
				{
					maze[wallX][wallZ] = Wall;
					break;
				}
			}
		}
	}
	maze[size - 1][size - 2] = Path;
	while (true) {
		int MinRamge = size / 3;
		int MaxRange = 2 * size / 3 - 1;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(MinRamge, MaxRange);
		int x = dis(gen);
		int y = dis(gen);
		if (maze[x][y] == Path) {
			maze[x][y] = Key;
			break;
		}
	}
	
	for (int i = size - 1; i >= 0; i--) {
		for (int j = 0; j < size; j++) {
			printf("%d", maze[i][j]);
		}
		printf("\n");
	}
}
int main() {
	srand(time(NULL));
	int num[] = { 9,15,21,27 };
	int i = 0;
	char choice;
	do {
		size = num[i];
		InitMaze();
		if (i == sizeof(num) / sizeof(int) - 1) {
			i = 0;
		}
		else {
			i++;
		}
		std::cout << "別の配列サイズを定義しますか？ (y/n): ";
		std::cin >> choice;
	} while (choice == 'y' || choice == 'Y');
	
	return 0;
}*/
std::chrono::time_point<std::chrono::steady_clock> start_time = std::chrono::steady_clock::now();
int main() {
	
	char choice;
	do {
		// 現在時刻を取得
		auto current_time = std::chrono::steady_clock::now();
		// 経過時間を秒単位で計算
		std::chrono::duration<double> elapsed_seconds = current_time - start_time;

		// 経過時間を表示（デバッグ用）
		std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
		std::cout << "別の配列サイズを定義しますか？ (y/n): ";
		std::cin >> choice;
	} while (choice == 'y' || choice == 'Y');
	return 0;
}