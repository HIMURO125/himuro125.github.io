#include "header.h"

const int Path = 0;
const int Wall = 1;
const int Key = 2;
const int Gate = 3;
std::vector<std::vector<int>> matrix;

//”z—ñ‚Ì—v‘f”•ÏX
void MakeArray(int size) {
	matrix.resize(size);
	for (int i = 0; i < size; ++i) {
		matrix[i].resize(size);
	}
}

//–_“|‚µ–@
std::vector<std::vector<int>> InitMaze(int size) {
	//•Ï”A”z—ñ‚Ì‰Šú‰»
	MakeArray(size);
	for (int x = 0; x < size; x++) {
		for (int z = 0; z < size; z++) {
			matrix[x][z] = Path;
		}
	}
	//–À˜H¶¬
	for (int x = 0; x < size; x++) {
		for (int z = 0; z < size; z++) {
			if (x == 0 || z == 0 || x == size - 1 || z == size - 1) {
				matrix[x][z] = Wall;// ŠOü‚Í‚·‚×‚Ä•Ç
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
				// 1s–Ú‚Ì‚İã‚É“|‚¹‚é
				int direction;
				if (z == 2)
					direction = rand() % 4;
				else
					direction = rand() % 3;

				// –_‚ğ“|‚·•ûŒü‚ğŒˆ‚ß‚é
				int wallX = x;
				int wallZ = z;
				switch (direction)
				{
				case 0: // ‰E
					wallX++;
					break;
				case 1: // ‰º
					wallZ++;
					break;
				case 2: // ¶
					wallX--;
					break;
				case 3: // ã
					wallZ--;
					break;
				}
				// •Ç‚¶‚á‚È‚¢ê‡‚Ì‚İ“|‚µ‚ÄI—¹
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

void drawSquare(float x, float z) {//‘«Õ•`‰æ
	glBegin(GL_QUADS);
	glVertex3f(x - 0.1f, 0.0f, z - 0.1f);
	glVertex3f(x + 0.1f, 0.0f, z - 0.1f);
	glVertex3f(x + 0.1f, 0.0f, z + 0.1f);
	glVertex3f(x - 0.1f, 0.0f, z + 0.1f);
	glEnd();
}