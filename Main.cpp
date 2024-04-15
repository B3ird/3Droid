#include "GL/freeglut.h"
#include "Img.hpp"
#include "Event.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "Robot.hpp"
#include "Environment.hpp"
#include <string>
#include <chrono>
#include <iostream>
#include "Audio.hpp"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


using namespace std;

//hide terminal & log prints
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

/* Evenements */
Event ev;

/* Models 3D */
Robot robot;
Environment environment;

/* Animation */
const float maxSpeed = 1.0;
float speed;
bool accelerate;
int currentDirection;

// Rotation
float rotationSpeed;
const float maxRotationSpeed = 3.0;

void manageKeyboardUp(unsigned char key, int x, int y);
void manageKeyboard(unsigned char key, int x, int y);
void manageSpecialKeyboard(int key, int x, int y);
void manageMouse(int button, int etat, int x, int y);
void manageMouseMove(int x, int y);
void manageMouseWheel(int wheel, int dir, int x, int y);

void display();
void reshape(int l, int h);

// Meshes
Mesh menu;
Mesh floorBack;

// Textures
Texture tMenu;
Texture tFloorBack;

// Audio
Audio audio = Audio();
bool musicPlaying = true;

void init() {
	speed = 0.0;
	accelerate = false;
	currentDirection = 0;
	rotationSpeed = 0.0;
	robot.init();
	//Music
	if (ev.enableMusic) {
		audio.playMusic();
	}
}

void initGraphics(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	glShadeModel(GL_SMOOTH);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_shininess = 50.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	// Set up lighting
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_position[] = { 0.0f, 1.0f, 0.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_COLOR_MATERIAL);
	
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glEnable(GL_NORMALIZE);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/* Model creation */
	robot.createMeshes();
	environment.createMeshes();

	/* Textures loading */
	robot.loadTextures();
	environment.loadTextures();

	menu.createPlane(50.0, 50.0, 1);
	floorBack.createPlane(30, 30, 1);
	tMenu.load("textures/menu.jpg");
	tFloorBack.load("textures/floor.png");
}

bool debug = false;
int frame = 0;
int currenttime = 0;
int timebase = 0;
char title[] = "OpenGL project by Julien MERLE";

void timerCB(int millisec) {
	glutTimerFunc(millisec, timerCB, millisec);
	glutPostRedisplay();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// Window
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(200, 200);
	glutCreateWindow(title);
	cout << title << "\n";

	// Keyboard
	glutKeyboardUpFunc(manageKeyboardUp);
	glutKeyboardFunc(manageKeyboard);
	glutSpecialFunc(manageSpecialKeyboard);
	
	// Mouse
	glutMouseFunc(manageMouse);
	glutMouseWheelFunc(manageMouseWheel);
	glutMotionFunc(manageMouseMove);
	
	initGraphics();

	init();

	//fps limiter by drawing each 15ms (66 fps max)
	glutTimerFunc(15, timerCB, 15);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}

void manageKeyboardUp(unsigned char key, int x, int y) {
	ev.KeyboardKeysUp(key, x, y);
}

void manageKeyboard(unsigned char key, int x, int y) {
	ev.KeyboardKeys(key, x, y);
}

void manageSpecialKeyboard(int key, int x, int y) {
	ev.arrowKeys(key, x, y);
}

void manageMouse(int button, int etat, int x, int y) {
	ev.mouse(button, etat, x, y);
}

void manageMouseMove(int x, int y) {
	ev.mouseMove(x, y);
}

void manageMouseWheel(int wheel, int dir, int x, int y) {
	ev.mouseWheel(wheel, dir, x, y);
}

void display(void) {

	// Music
	if(ev.enableMusic && !musicPlaying) {
		audio.playMusic();
		musicPlaying = true;
	} else if (!ev.enableMusic && musicPlaying) {
		audio.stopMusic();
		musicPlaying = false;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//calculate the frames per second
	frame++;

	//get the current time
	currenttime = glutGet(GLUT_ELAPSED_TIME);

	//check if a second has passed
	if (currenttime - timebase > 1000) {
		char buffer[100];
		sprintf(buffer, "%s : %4.0f fps", title, frame * 1000.0 / (currenttime - timebase));
		glutSetWindowTitle(buffer);
		timebase = currenttime;
		frame = 0;
	}

	glEnable(GL_CULL_FACE);

	if (ev.enableDebug && !debug) {
		debug = true;
		robot.loadDebugTextures();
		cout << "DEBUG ENABLED\n";
	} else if (!ev.enableDebug && debug) {
		debug = false;
		robot.loadTextures();
		ev.enableDebug = false;
		cout << "DEBUG DISABLED\n";
	}

	int zoom = ev.getZoomValue() * 3;
	//std:cout << zoom << "\n";

	if (ev.resetRobot) {
		init();
		ev.resetRobot = false;
		cout << "ROBOT RESETED\n";
	}

	// Menu
	if (ev.showMenu) {
		glPushMatrix();
			glRotated(90, 1, 0, 0);
			float scale = -zoom / 70.0;
			glTranslatef(0.0, -80, 0.0);
			glEnable(GL_TEXTURE_2D);
			glColor3f(1, 1, 1);
			tMenu.bind();
			menu.drawQuads();
		glPopMatrix();
	} else {
		glPushMatrix();
		
			if (ev.cameraMode == 1) { //back view
				float distance = zoom;  // distance from the object
				float angle = (ev.droidAngle / 180) * M_PI;  // convert rotation to radians

				ev.cameraX = ev.droidX + distance * sin(angle);
				ev.cameraY = ev.droidY + 20;// distance;
				ev.cameraZ = ev.droidZ + distance * cos(angle);

				glLoadIdentity();
				gluLookAt(
					ev.cameraX, ev.cameraY, ev.cameraZ, // position of the camera
					ev.droidX, ev.droidY + 4, ev.droidZ,// where the camera is looking at
					0.0f, 1.0f, 0.0f);

			} else if (ev.cameraMode == 2) { //tracking view
				float distance = zoom;
				ev.cameraX = 0;
				ev.cameraY = 0 + 20;// distance;
				ev.cameraZ = -zoom;
				gluLookAt(
					ev.cameraX, ev.cameraY, ev.cameraZ, // position of the camera
					ev.droidX, ev.droidY + 4, ev.droidZ,// where the camera is looking at
					0.0f, 1.0f, 0.0f);
			} else { // static view
				glTranslatef(0.0, -4.0, -zoom);
				glRotatef(ev.getAngley(), 1.0, 0.0, 0.0);
				glRotatef(ev.getAnglex(), 0.0, 1.0, 0.0);
			}

			switch (ev.moveDirection) {
				case 1: //forward
					if (speed < maxSpeed) {
						speed += 0.04; //acceleration
					}
					if (currentDirection == -1) { //reverse
						speed = 0; //brake
					}
					currentDirection = 1;
					break;
				case -1: //backward
					if (speed < maxSpeed) {
						speed += 0.02; //acceleration
					}
					if (currentDirection == 1) { //reverse
						speed = 0; //brake
					}
					currentDirection = -1;
					break;
				default:
					if (speed > 0) {
						speed -= 0.02; //friction
					}
					break;
			}

			if (speed > 0) { //inertie speed
				ev.droidZ -= currentDirection * speed * 0.5 * cos((ev.droidAngle / 180) * M_PI);
				ev.droidX -= currentDirection * speed * 0.5 * sin((ev.droidAngle / 180) * M_PI);
			}

			switch (ev.rotateDirection) {
				case 0:
					rotationSpeed = 0.0;
					break;
				case 1:
					if (rotationSpeed < maxRotationSpeed) {
						rotationSpeed += 0.2;
					}
					ev.droidAngle -= rotationSpeed;
					
					break;
				case -1:
					if (rotationSpeed < maxRotationSpeed) {
						rotationSpeed += 0.2;
					}
					ev.droidAngle += rotationSpeed;
					break;
				default: break;
			}

			environment.showMenu = ev.showMenu;
			environment.display();

			//!Important : draw transparent elements at the end
			glPushMatrix();
				glTranslated(ev.droidX, ev.droidY, ev.droidZ);
				glRotated(ev.droidAngle, ev.rotatex, ev.rotatey, ev.rotatez);
				robot.rotateHeadDirection = ev.rotateHeadDirection;
				robot.headAutoRotation = ev.headAutoRotation;
				robot.showHologram = ev.showHologram;
				robot.display();
			glPopMatrix();

			glPushMatrix();
				glTranslated(0, -0.1, 0);
				glRotated(180, 0, 0, 1);
				glEnable(GL_TEXTURE_2D);
				glColor3f(1.0, 1.0, 1.0);
				tFloorBack.bindAlpha();
				floorBack.drawQuads();
			glPopMatrix();

		glPopMatrix();

	}

	//glutPostRedisplay();
	glFlush();
	glutSwapBuffers();
}

void reshape(int w,int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0, w, h);
	gluPerspective(45.0, (double)w/(double)h, 1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}
