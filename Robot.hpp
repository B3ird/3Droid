#pragma once

#include "Texture.hpp"
#include "Mesh.hpp"
#include "Audio.hpp"

using namespace std;

class Robot {
	public:

		Robot(void);
		~Robot(void);

		void init();

		// 2D Textures
		Texture tHead;
		Texture tBody;
		Texture tBodyLid;
		Texture tUnderbody;
		Texture tMisc;
		Texture tMetal;
		Texture tAxe;
		Texture tHoloLight;
		Texture tHologram;
		Texture tTint;
		Texture tJack;
		Texture tSquare;
		Texture tCircle;

		// 3D Objects
		//head
		Mesh head;
		Mesh eye;
		Mesh lens;

		//body
		Mesh body;
		Mesh underbody;
		
		//arm
		Mesh axeIn;
		Mesh axeOut;
		Mesh shoulderArc;
		Mesh shoulderBox;
		Mesh shoulderBottom;
		Mesh arm;
		Mesh forearm;
		Mesh armJack;

		//foot
		Mesh foot;
		Mesh ankle;
		Mesh underFoot;
		Mesh pipe;
		Mesh footBox;
		Mesh footBoxCylinder;

		//middle arm
		Mesh middleArm;
		Mesh middleForearm;

		//light
		Mesh holoLight;
		Mesh hologram;
		Mesh holoFlare;

		// Head animation
		float xRotation;
		bool reverseRotation;
		bool headAutoRotation = false;
		int rotateHeadDirection = 0;
		
		// Hologram
		bool showHologram = false;
		float flarePos;
		float flareSpeed;
		float flareHeight;
		float flarePathLenght;

		// Methods
		void createMeshes();		
		void loadTextures();
		void loadDebugTextures();
		void display();

		// Audio
		Audio audio = Audio();
};

