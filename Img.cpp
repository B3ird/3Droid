#include "Img.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Img::~Img() {}

bool Img::LoadImg(char* FileName) {	
	int width;
	int height;
	int channels;
	
	unsigned char* data = stbi_load(FileName, &width, &height, &channels, 0);
	mWidth = width;
	mHeight = height;
	mImage = data;

	return 0;
}