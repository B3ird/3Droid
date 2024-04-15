#pragma once
#include <string>
#include "Img.hpp"
#include "GL/freeglut.h"

class Texture {
	public:

		GLuint id;
		Img image;
		bool loaded = false;

		Texture(void);
		~Texture(void);

		// Methods
		void load(std::string s);		
		void bind();
		void bindAlpha();
};

