#define STB_IMAGE_IMPLEMENTATION
#include "header.h"

GLuint LoadTexture(const char* filename) {
	int width;
	int height;
	int channel;
	GLuint Texture;
	GLenum format{};
	unsigned char* Texture_ID = stbi_load(filename, &width, &height, &channel, 0);
	if(Texture_ID == nullptr) {
		return 0;
	}
	else {
		glGenTextures(1, &Texture);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if (channel == 4) {
			format = GL_RGBA;
		}
		else {
			format = GL_RGB;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, Texture_ID);
		stbi_image_free(Texture_ID);
		return Texture;
	}
}

void DrawTexture(GLuint Texture) {
	glBindTexture(GL_TEXTURE_2D, Texture);

	glMaterialf(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, 0.0f);
	glMaterialf(GL_FRONT, GL_SPECULAR, 0.0f);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);

	glBegin(GL_QUADS);
	//ëO
	glTexCoord2d(0.0, 0.0); glVertex3d(-1.0,-7.5,-1.0);
	glTexCoord2d(1.0, 0.0); glVertex3d(1.0, -7.5, -1.0);
	glTexCoord2d(1.0, 1.0); glVertex3d(1.0, 7.5, -1.0);
	glTexCoord2d(0.0, 1.0); glVertex3d(-1.0, 7.5, -1.0);
	
	//å„ÇÎ
	glTexCoord2d(0.0, 0.0); glVertex3d(-1.0, -7.5, 1.0);
	glTexCoord2d(1.0, 0.0); glVertex3d(1.0, -7.5, 1.0);
	glTexCoord2d(1.0, 1.0); glVertex3d(1.0, 7.5, 1.0);
	glTexCoord2d(0.0, 1.0); glVertex3d(-1.0, 7.5, 1.0);
	
	//âE
	glTexCoord2d(0.0, 0.0); glVertex3d(1.0, -7.5, -1.0);
	glTexCoord2d(1.0, 0.0); glVertex3d(1.0, -7.5, 1.0);
	glTexCoord2d(1.0, 1.0); glVertex3d(1.0, 7.5, 1.0);
	glTexCoord2d(0.0, 1.0); glVertex3d(1.0, 7.5, -1.0);
	
	//ç∂
	glTexCoord2d(0.0, 0.0); glVertex3d(-1.0, -7.5, -1.0);
	glTexCoord2d(1.0, 0.0); glVertex3d(-1.0, -7.5, 1.0);
	glTexCoord2d(1.0, 1.0); glVertex3d(-1.0, 7.5, 1.0);
	glTexCoord2d(0.0, 1.0); glVertex3d(-1.0, 7.5, -1.0);
	
	//è„
	glTexCoord2d(0.0, 0.0); glVertex3d(-1.0, 7.5, -1.0);
	glTexCoord2d(1.0, 0.0); glVertex3d(1.0, 7.5, -1.0);
	glTexCoord2d(1.0, 1.0); glVertex3d(1.0, 7.5, 1.0);
	glTexCoord2d(0.0, 1.0); glVertex3d(-1.0, 7.5, 1.0);
	
	//â∫
	glTexCoord2d(0.0, 0.0); glVertex3d(-1.0, -7.5, -1.0);
	glTexCoord2d(1.0, 0.0); glVertex3d(1.0, -7.5, -1.0);
	glTexCoord2d(1.0, 1.0); glVertex3d(1.0, -7.5, 1.0);
	glTexCoord2d(0.0, 1.0); glVertex3d(-1.0, -7.5, 1.0);

	glEnd();
}