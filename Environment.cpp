#include "Environment.hpp"
#include "GL/freeglut.h"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "Event.hpp"
#include <math.h>

Environment::Environment(void) {}

Environment::~Environment(void) {}

void Environment::createMeshes() {
	floor.createPlane(30, 30, 1);
	logo.createPlane(51.2, 21.5, 1);
	story.createPlane(51.2, 12.8, 1);
	sky.createBox(1000, 500, 1000);
	//menu.createPlane(50.0, 50.0, 1);
	falcon.createPlane(30.0, 30.0, 1);
}

void Environment::loadTextures() {
	tLogo.load("textures/author.jpg");
	tStory.load("textures/story.png");
	tFloor.load("textures/floor.png");
	tSky.load("textures/sky.jpg");
	//tMenu.load("textures/menu.png");
	tFalcon.load("textures/falcon.png");
}

bool falconRun = false;
bool falconSoundApplied = false;
float falconPosX = 100.0;
float falconPosZ = 0.0;
float falconSpeed = 2.0;
float falconPathLenght = 1000.0;

void Environment::display() {

	// Skybox
	glPushMatrix();
		glCullFace(GL_FRONT);
		glColor3f(1.0, 1.0, 1.0);
		tSky.bind();
		sky.drawBox();
	glPopMatrix();

	// Falcon
	if (falconRun) {
		if (falconPosZ > 400 && !falconSoundApplied) { //before mid, aprox. to the top of player
			audio.playThreadAudio("falcon", "mp3");
			falconSoundApplied = true;
		}
		if (falconPosZ >= falconPathLenght -falconSpeed) { // animation finished
			falconRun = false;
			falconSoundApplied = false;
		}
		falconPosZ = fmod(falconPosZ + falconSpeed, falconPathLenght);
		
		//std::cout << "Current falconPosZ : " << falconPosZ << "\n";
		//falconPosZ = 1025.0;
		glPushMatrix();
			glTranslated(falconPosX, 100, falconPathLenght / 2 - falconPosZ + 25); //added half size of sprite
			glRotated(180, 0, 0, 1);
			glColor3f(1.0, 1.0, 1.0);
			glEnable(GL_TEXTURE_2D);
			glCullFace(GL_BACK);
			tFalcon.bindAlpha();
			falcon.drawQuads();
		glPopMatrix();

	} else {
		int dice = rand() % 10000;
		//std::cout << "dice : " << dice << "\n";
		if (dice <= 1) { // proba 0.01% per try (scene draw)
			//define new random x location starter
			falconPosX = -500 + rand() % 1000; // -500 to +500
			std::cout << "New falconPosX : " << falconPosX << "\n";
			//flag run
			falconRun = true;
		}
	}

	glPushMatrix();
		glCullFace(GL_BACK);
		glRotated(90, 1, 0, 0);
		glTranslated(0, -24, -10);
		glRotated(180, 0, 0, 1);
		glRotated(-60, 1, 0, 0);
		glColor3f(1.0, 1.0, 1.0);

		// Menu
		/*if (showMenu) {
			tMenu.bindAlpha();
			menu.drawQuads();
		}*/
		glTranslated(0, 0, -40);

		// Logo
		glPushMatrix();
			glTranslated(0, -50, -60);
			tLogo.bind();
			logo.drawQuads();
		glPopMatrix();
	glPopMatrix();

	// Floor
	glPushMatrix();
		glCullFace(GL_BACK);
		glColor3f(1.0, 1.0, 1.0);
		tFloor.bindAlpha();
		glTranslated(0, -0.01, 0);
		floor.drawQuads();
		//glRotated(180, 0, 0, 1);
		//glCullFace(GL_FRONT);
		//floor.drawQuads();
		//glCullFace(GL_BACK);
	glPopMatrix();

	// Gizmo X Y Z
	/*glPushMatrix();
		glTranslatef(0, -0.2, 0);
		gizmo.displayAxe();
	glPopMatrix();*/

	// Story
	glPushMatrix();
		glRotated(180, 0, 1, 0);
		glRotated(90, 1, 0, 0);
		glTranslated(0, 100, -50);
		glRotated(180, 0, 0, 1);
		glColor3f(1.0, 1.0, 1.0);
		tStory.bindAlpha();
		story.drawQuads();
	glPopMatrix();
}