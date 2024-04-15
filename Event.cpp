#include "Event.hpp"
#include "GL/freeglut.h"
#include <cstdlib>
#include <math.h>
#include "Audio.hpp"

Event::Event(void) {
	init();
}

Event::~Event(void) {
}

void Event::init() {
	cameraX = 0.0;
	cameraY = -4.0;
	cameraZ = 0.0;
	cameraMode = 0;
	droidX = 0;
	droidY = 0;
	droidZ = -5;
	droidAngle = 0;
	rotatex = 0;
	rotatey = 0;
	rotatez = 0;
	anglex = 180;
	angley = 20;
	zoom = 14;
	displayMode = 0;
	headAutoRotation = true;
	rotateHeadDirection = 0;
	showHologram = true;
	moveDirection = 0;
	rotateDirection = 0;
	enableDebug = false;
	showMenu = true;
	displayMode = 0;
	lowQuality = false;
}


void Event::KeyboardKeysUp(unsigned char key, int x, int y) {
	switch (key) {
		case 'z':
		case 'Z':
		case 's':
		case 'S':
			moveDirection = 0;
			break;
		case 'q':
		case 'Q':
		case 'd':
		case 'D':
			rotateDirection = 0;
			break;

		case 'a':
		case 'A':
		case 'e':
		case 'E':
			rotateHeadDirection = 0;
			break;
		default:
			break;
	}
}

void Event::KeyboardKeys(unsigned char touche,int x,int y) {
	switch(touche) {

		case 'a':
		case 'A':
			headAutoRotation = false;
			rotateHeadDirection = -1;
			break;
		case 'e':
		case 'E' :
			headAutoRotation = false;
			rotateHeadDirection = 1;
			break;
		case 'r':
		case 'R':
			headAutoRotation = !headAutoRotation;
			if (!headAutoRotation) {
				audio.playThreadAudio("head", "mp3");
			}
			break;

		case 'm':
		case 'M':
			enableMusic = !enableMusic;
			break;

		case 'f':
		case 'F':
			//Beep(523, 10); //turn on/off button sound
			showHologram = !showHologram;
			if (showHologram) {
				audio.playThreadAudio("whistle", "mp3");
			}
			break;

		case 'v':
		case 'V':
			audio.playThreadAudio("view", "mp3");
			cameraMode = (cameraMode+1)%3;
			break;

		case 13: //return
			audio.playThreadAudio("reset", "mp3");
			init();
			showMenu = false;
			resetRobot = true;
			break;
		
		case 32: //space
			showMenu = !showMenu;
			if (showMenu) {
				audio.playThreadAudio("menu", "mp3");
			}
			break;

		case 'y': 
		case 'Y':
			lowQuality = !lowQuality;
			if (lowQuality) {
				// Pixelated textures & flat meshes
				glShadeModel(GL_FLAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			} else {
				// Filtered textures & smooth meshes
				glShadeModel(GL_SMOOTH);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}
			break;

		case 'o':
		case 'O':
			enableDebug = !enableDebug;
			break;
		
		case 27: // ESCAPE to exit app
			exit(0);
			break;
		
		case 't': // Display mode
		case 'T':
			if (displayMode < 2) {
				displayMode++;
			} else {
				displayMode = 0;
			}
			switch (displayMode) {
				case 0: 
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
					break;
				case 1: 
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					break;
				case 2: 
					glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
					break;
				default: 
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					break;
			}
			break;
			
		case 'z': // Move forward
		case 'Z':
			moveDirection = 1;
			break;
		case 's': // Move backward
		case 'S':
			moveDirection = -1;
			break;
		case 'q': // Turn left
		case 'Q':
			rotateDirection = -1;
			rotatex = 0;
			rotatez=0;
			rotatey=1;
			break;
		case 'd': // Turn right
		case 'D':
			rotateDirection = 1;
			rotatex = 0;
			rotatez=0;
			rotatey=1;
			break;

		case '+': // Zoom in
			if (!showMenu) {
				zoom--;
			}
			break;
		case '-': // Zoom out
			if (!showMenu) {
				zoom++;
			}
			break;

		default:
			break;
	}
}

void Event::arrowKeys(int touche, int x, int y) {
	/*if (!showMenu) {
		switch (touche) {
			case GLUT_KEY_UP: // Top down camera
				anglex = 180;
				angley = 90;
				break;
			case GLUT_KEY_DOWN: // Bottom camera
				anglex = 0;
				angley = 270;
				break;
			case GLUT_KEY_LEFT: // Left camera
				anglex = 90;
				angley = 0;
				break;
			case GLUT_KEY_RIGHT: // Right camera
				anglex = 270;
				angley = 0;
				break;
			default:
				break;
		}
	}*/
}

char pressed;
void Event::mouse(int bouton, int etat,int x,int y) {
	if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN) {
		pressed = 1;
		xold = x; 
		yold = y;
	}
	if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_UP) {
		pressed=0; 
	}
}

void Event::mouseMove(int x,int y) {
	if (!showMenu) {
		if (pressed) {
			anglex = anglex + (x - xold);
			angley = angley + (y - yold);
		}
		xold = x;
		yold = y;
	}
}

void Event::mouseWheel(int wheel, int dir, int x, int y) {
	if (!showMenu) {
		if (dir > 0) {
			zoom--;
		}
		else {
			zoom++;
		}
	}
}

int Event::getAnglex() {
	return anglex;
}

int Event::getAngley() {
	return angley;
}

void Event::setZoomValue(int val) {
	zoom = val;
}

int Event::getZoomValue() {
	return zoom;
}