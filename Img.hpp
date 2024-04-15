#pragma once
#include <string>

class Img {
	public:

		Img() : mWidth(0), mHeight(0), mImage(0) { }

		~Img();

		bool LoadImg(char* FileName);

		int GetWidth() const { return mWidth; }
		int GetHeight() const { return mHeight; }
		unsigned char* GetPixels() const { return mImage; }

	private:
		int mWidth, mHeight;
		unsigned char* mImage;
};