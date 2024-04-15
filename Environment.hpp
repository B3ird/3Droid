#pragma once

#include "Texture.hpp"
#include "Mesh.hpp"
#include "Audio.hpp"

class Environment {
public:

	Environment(void);
	~Environment(void);
	
	// 2D Textures
	Texture tLogo;
	Texture tFloor;
	Texture tSky;
	Texture tStory;
	Texture tFalcon;

	// 3D objects
	Mesh floor;
	Mesh gizmo;
	Mesh logo;
	Mesh sky;
	Mesh story;
	Mesh falcon;

	// Methods
	void createMeshes();
	void loadTextures();
	void display();

	// Flag
	bool showMenu = true;

	// Audio
	Audio audio = Audio();
};

