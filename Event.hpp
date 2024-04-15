#pragma once

#include "Audio.hpp"

using namespace std;

class Event{
	public:

		Event(void);
		~Event(void);

		void init();

		// camera
		int anglex;
		int angley;
		int xold;
		int yold;
		int zoom;

		float cameraX;
		float cameraY;
		float cameraZ;
		int cameraMode;
	
		// animation
		int rotateHeadDirection;
		bool headAutoRotation;
		double droidX, droidY, droidZ;
		double droidAngle;
		int rotatex, rotatey, rotatez;
		bool showHologram;

		// music
		Audio audio = Audio();
		bool enableMusic = true;

		// movement
		int moveDirection;
		int rotateDirection;		

		// settings
		bool enableDebug;
		bool showMenu;
		int displayMode;
		bool lowQuality;
		bool resetRobot = false;

		// methods
		void KeyboardKeysUp(unsigned char key, int x, int y);
		void KeyboardKeys(unsigned char touche,int x,int y);
		void arrowKeys(int key, int x, int y);
		void mouse(int bouton, int etat,int x,int y);
		void mouseMove(int x,int y);
		void mouseWheel(int wheel, int dir, int x, int y);
	
		// getters
		int getAnglex();
		int getAngley();
		int getZoomValue();

		// setter
		void setZoomValue(int val);		
};

