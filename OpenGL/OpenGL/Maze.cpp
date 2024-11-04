#include "header.h"

const int Path = 0;
const int Wall = 1;
const int Key = 2;
const int Gate = 3;
std::vector<std::vector<int>> matrix;

//�z��̗v�f���ύX
void MakeArray(int size) {
	matrix.resize(size);
	for (int i = 0; i < size; ++i) {
		matrix[i].resize(size);
	}
}

//�_�|���@
std::vector<std::vector<int>> InitMaze(int size) {
	//�ϐ��A�z��̏�����
	MakeArray(size);
	for (int x = 0; x < size; x++) {
		for (int z = 0; z < size; z++) {
			matrix[x][z] = Path;
		}
	}
	//���H����
	for (int x = 0; x < size; x++) {
		for (int z = 0; z < size; z++) {
			if (x == 0 || z == 0 || x == size - 1 || z == size - 1) {
				matrix[x][z] = Wall;// �O���͂��ׂĕ�
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
				// 1�s�ڂ̂ݏ�ɓ|����
				int direction;
				if (z == 2)
					direction = rand() % 4;
				else
					direction = rand() % 3;

				// �_��|�����������߂�
				int wallX = x;
				int wallZ = z;
				switch (direction)
				{
				case 0: // �E
					wallX++;
					break;
				case 1: // ��
					wallZ++;
					break;
				case 2: // ��
					wallX--;
					break;
				case 3: // ��
					wallZ--;
					break;
				}
				// �ǂ���Ȃ��ꍇ�̂ݓ|���ďI��
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

void drawSquare(float x, float z) {//���Օ`��
	glBegin(GL_QUADS);
	glVertex3f(x - 0.1f, 0.0f, z - 0.1f);
	glVertex3f(x + 0.1f, 0.0f, z - 0.1f);
	glVertex3f(x + 0.1f, 0.0f, z + 0.1f);
	glVertex3f(x - 0.1f, 0.0f, z + 0.1f);
	glEnd();
}