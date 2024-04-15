#include "Texture.hpp"
#include "GL/freeglut.h"
#include "Img.hpp"
#include <string>

Texture::Texture(void) {
}


Texture::~Texture(void) {
	 glDeleteTextures(1, &id);
}

void Texture::load(std::string s) {
	const char* str = s.c_str();
	image.LoadImg((char*)str);
	glEnable(GL_TEXTURE_2D);
	loaded = true;
}

void Texture::bind() {
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGB,
		image.GetWidth(),
		image.GetHeight(),
		0, 
		GL_RGB,
		GL_UNSIGNED_BYTE,
		image.GetPixels()
	);
}

void Texture::bindAlpha() {
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		image.GetWidth(),
		image.GetHeight(),
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		image.GetPixels()
	);
}