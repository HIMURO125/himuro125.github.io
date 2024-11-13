#define STB_IMAGE_IMPLEMENTATION
#include <GL/glut.h>
#include <stb_image.h>

// テクスチャIDをグローバル変数として宣言
GLuint textureID;

GLuint loadTexture(const char* filename) {
	int width, height, channels;
	unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
	if (data == nullptr) {
		return 0;
	}

	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	// テクスチャのパラメータ設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// OpenGLテクスチャとして画像データを設定
	GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	// メモリを解放
	stbi_image_free(data);
	return texID;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// テクスチャを描画
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.5f, 0.5f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Texture Example with FreeGLUT");

	// 画像を読み込んでテクスチャに設定
	textureID = loadTexture("image.png");

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}