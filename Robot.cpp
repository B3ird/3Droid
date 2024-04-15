#include "Robot.hpp"
#include "GL/freeglut.h"
#include "Texture.hpp"
#include "Mesh.hpp"
#include <iostream>
#include "Audio.hpp"
#include <math.h>

using namespace std;

Robot::Robot(void) {
	init();
}

Robot::~Robot(void) {
}

void Robot::createMeshes() {
	shoulderBox.createBox(1.7, 1.5, 0.8);
	arm.createBox(0.5, 3.0, 1);
	forearm.createBox(0.4, 4.5, 0.5);
	foot.createTrapeze(2.7, 1.75, 1.35, 0.6);
	underFoot.createTrapeze(2.7, 1.75, 0.35, 0.85);
	middleArm.createBox(0.5, 1.4, 1.0);
	middleForearm.createBox(1.0, 1.4, 0.5); 	
	hologram.createPlane(3.5, 8.0, 1);
}

void Robot::loadTextures() {
	tBody.load("textures/body.jpg");
	tBodyLid.load("textures/bodyLid.jpg");
	tHead.load("textures/head.jpg");
	tUnderbody.load("textures/underbody.jpg");
	tMisc.load("textures/misc.jpg");
	tHoloLight.load("textures/holoLight.png");
	tHologram.load("textures/hologram.png");
	tSquare.load("textures/square.jpg");
	tTint.load("textures/tint.jpg");
	tJack.load("textures/jack.jpg");
	tCircle.load("textures/circle.jpg");
	tMetal.load("textures/metal.jpg");
	tAxe.load("textures/axe.jpg");
}

void Robot::loadDebugTextures() {
	tBody.load("textures/grid.jpg");
	tBodyLid.load("textures/grid.jpg");
	tHead.load("textures/grid.jpg");
	tUnderbody.load("textures/grid.jpg");
	tMisc.load("textures/grid.jpg");
	tHoloLight.load("textures/grid.png");
	tHologram.load("textures/grid.png");
	tSquare.load("textures/grid.jpg");
	tTint.load("textures/grid.jpg");
	tJack.load("textures/grid.jpg");
	tCircle.load("textures/grid.jpg");
	tMetal.load("textures/grid.jpg");
	tAxe.load("textures/grid.jpg");
}

void Robot::init() {
	flarePos = 0.0;
	flareSpeed = 0.02;
	flareHeight = 2.0;
	flarePathLenght = 8.0; //8 is height of hologram

	xRotation = -15;
	reverseRotation = false;
	headAutoRotation = true;
	rotateHeadDirection = 0;
	showHologram = true;
}

void Robot::display() {

	flarePos = fmod((flarePos + flareSpeed), flareHeight- flarePathLenght);

	glPushMatrix();
		glRotated(-19, 1.0, 0.0, 0.0);
		glTranslated(0.0, -1.5, 4.1);

		//RIGHT ARM
		
		//right shoulder
		glPushMatrix();
			glTranslated(-3.0, 6.8, 0.05);
			glRotated(90, 0, 1, 0);
			glColor3f(1.0, 1.0, 1.0);
			glEnable(GL_TEXTURE_2D);
			shoulderArc.drawHalfCylinder(1, 24, 0.75, 0.85, true, tSquare, tCircle);

			glTranslated(0, -0.75, 0);
			glColor3f(1.0, 1.0, 1.0);
			glEnable(GL_TEXTURE_2D);
			tSquare.bind();
			shoulderBox.drawBox();

			glTranslated(0, -1.1, 0);
			glRotated(90, 1, 0, 0);
			glColor3f(1.0, 1.0, 1.0);
			glEnable(GL_TEXTURE_2D);
			tSquare.bind();
			shoulderBottom.drawTrapeze(1.7, 0.8, 0.75, 0.6);
		glPopMatrix();
		
		//right axe
		glPushMatrix();
			glTranslated(-2.5, 6.8, 0.05);
			glRotated(90, 0, 1, 0);
			glColor3f(0.5, 0.5, 0.5);
			glEnable(GL_TEXTURE_2D);
			axeIn.drawCylinder(1, 16, 0.5, 0.65, false, tMetal, tAxe);
			
			glTranslated(0, 0, -1);
			glEnable(GL_TEXTURE_2D);
			axeOut.drawCylinder(1, 16, 0.15, 0.35, true, tMetal, tAxe);
		glPopMatrix();
		
		//right arm
		glPushMatrix();
			glTranslated(-3.0, 3.1, 0.05);
			glColor3f(0.95, 0.95, 0.95);
			glEnable(GL_TEXTURE_2D);
			tSquare.bind();
			arm.drawBox();

			//jack
			glRotated(90, 0, 0, 1);
			glRotated(90, 0, 1, 0);
			glTranslated(0.0, 0.45, 0.45);
			glColor3f(1.0, 1.0, 1.0);
			glEnable(GL_TEXTURE_2D);
			tJack.bind();
			armJack.drawHalfCylinder(1, 16, 3.5, 0.15, true);
		glPopMatrix();

		//right forearm
		glPushMatrix();
			glTranslated(-3.25, 4.05, 0.05);
			glColor3f(0.15, 0.25, 0.40);
			glEnable(GL_TEXTURE_2D);
			tSquare.bind();
			forearm.drawBox();
		glPopMatrix();

		//LEFT ARM_
		glDisable(GL_TEXTURE_2D);

		//left shoulder
		glPushMatrix();
			glTranslated(3.0,6.8, 0.05);
			glRotated(90, 0, 1, 0);
			glColor3f(1.0, 1.0, 1.0);
			glEnable(GL_TEXTURE_2D);
			shoulderArc.drawHalfCylinder(1, 32, 0.75, 0.85, true, tSquare, tCircle);
			
			glTranslated(0, -0.75, 0);
			glColor3f(1.0, 1.0, 1.0);
			glEnable(GL_TEXTURE_2D);
			tSquare.bind();
			shoulderBox.drawBox();

			glTranslated(0, -1.1, 0);
			glRotated(90, 1, 0, 0);
			glColor3f(1.0, 1.0, 1.0);
			glEnable(GL_TEXTURE_2D);
			tSquare.bind();
			shoulderBottom.drawTrapeze(1.7, 0.8, 0.75, 0.6);
		glPopMatrix();

		//left axe
		glPushMatrix();
			glTranslated(2.5, 6.8, 0.05);
			glRotated(90, 0, 1, 0);
			glColor3f(0.5, 0.5, 0.5);
			axeIn.drawCylinder(1, 16, 0.5, 0.65, false, tMetal, tAxe);
			glTranslated(0, 0, 1);
			axeOut.drawCylinder(1, 16, 0.15, 0.35, true, tMetal, tAxe);
		glPopMatrix();
		
		//left arm
		glPushMatrix();
			glTranslated(3.0, 3.1, 0.05);
			glColor3f(1.0, 1.0, 1.0);
			glEnable(GL_TEXTURE_2D);
			tSquare.bind();
			arm.drawBox();

			//jack
			glRotated(270, 0, 0, 1);
			glRotated(270, 0, 1, 0);
			glTranslated(0.0, 0.45, 0.45);
			glColor3f(1.0, 1.0, 1.0);
			glEnable(GL_TEXTURE_2D);
			tJack.bind();
			armJack.drawHalfCylinder(1, 16, 3.5, 0.15, true);
		glPopMatrix();

		//left forearm
		glPushMatrix();
			glTranslated(3.25,4.05,0.05);
			glColor3f(0.15,0.25,0.40);
			glEnable(GL_TEXTURE_2D);
			tSquare.bind();
			forearm.drawBox();
		glPopMatrix();

	glPopMatrix();

	glPushMatrix();

		glTranslated(0.0, 0.0, 3.85);
		//RIGHT FOOT
		glPushMatrix();
			glTranslated(-3.20,1.025,0);
			glRotated(270, 1, 0, 0);
			glRotated(90, 0, 0, 1);
			glColor3f(1.0, 1.0, 1.0);
			glEnable(GL_TEXTURE_2D);
			tSquare.bind();
			foot.drawTrapeze(2.7, 1.75, 1.35, 0.6);

			//foot box
			glPushMatrix();
				glTranslated(0.0, -0.92, 0.18);

				glPushMatrix();
					glRotated(90, 0, 0, 1);
					glEnable(GL_TEXTURE_2D);
					glColor3f(1.0, 1.0, 1.0);
					tSquare.bind();
					footBox.createBox(0.6, 1.5, 1.0);
					footBox.drawBox();
				glPopMatrix();

				glRotated(90, 1, 0, 0);
				glRotated(90, 0, 1, 0);
				glTranslated(0.0, 0.5, 0.0);
				glColor3f(1.0, 1.0, 1.0);
				glEnable(GL_TEXTURE_2D);
				glColor3f(1.0, 1.0, 1.0);
				footBoxCylinder.drawHalfCylinder(1, 16, 1.5, 0.3, true, tSquare, tCircle);
				
				glRotated(180, 1, 0, 0);
				glColor3f(1.0, 1.0, 1.0);
				glTranslated(0.0, 1.0, 0.0);
				glEnable(GL_TEXTURE_2D);
				glColor3f(1.0, 1.0, 1.0);
				footBoxCylinder.drawHalfCylinder(1, 16, 1.5, 0.3, true, tSquare, tCircle);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslated(-3.20,0.175,0);
			glRotated(90, 1, 0, 0);
			glRotated(90, 0, 0, 1);
			glColor3f(1.0, 1.0, 1.0);
			glEnable(GL_TEXTURE_2D);
			tSquare.bind();
			underFoot.drawTrapeze(2.7, 1.75, 0.35, 0.85);
		glPopMatrix();
		
		glPushMatrix();
			glTranslated(-4.0, 0.35, 0.0);
			glRotated(90, 0, 1, 0);
			glColor3f(1.0, 1.0, 1.0);
			glEnable(GL_TEXTURE_2D);
			ankle.drawHalfCylinder(1, 32, 0.2, 0.85, true, tSquare, tCircle);
		glPopMatrix();

		//LEFT FOOT
		glPushMatrix();
			glTranslated(3.20,1.025,0);
			glRotated(270, 1, 0, 0);
			glRotated(90, 0, 0, 1);
			glEnable(GL_TEXTURE_2D);
			glColor3f(1.0, 1.0, 1.0);
			tSquare.bind();
			foot.drawTrapeze(2.7, 1.75, 1.35, 0.6);
			
			//foot box
			glPushMatrix();
				glTranslated(0.0, 0.92, 0.18);
				
				glPushMatrix();
					glRotated(90, 0, 0, 1);
					glEnable(GL_TEXTURE_2D);
					glColor3f(1.0, 1.0, 1.0);
					tSquare.bind();
					footBox.createBox(0.6, 1.5, 1.0);
					footBox.drawBox();
				glPopMatrix();

				glRotated(90, 1, 0, 0);
				glRotated(90, 0, 1, 0);
				glTranslated(0.0, 0.5, 0.0);
				glEnable(GL_TEXTURE_2D);
				glColor3f(1.0, 1.0, 1.0);
				footBoxCylinder.drawHalfCylinder(1, 16, 1.5, 0.3, true, tSquare, tCircle);
				
				glRotated(180, 1, 0, 0);
				glTranslated(0.0, 1.0, 0.0);
				glEnable(GL_TEXTURE_2D);
				glColor3f(1.0, 1.0, 1.0);
				footBoxCylinder.drawHalfCylinder(1, 16, 1.5, 0.3, true, tSquare, tCircle);

			glPopMatrix();

		glPopMatrix();

		glPushMatrix();
			glTranslated(3.20, 0.175, 0);
			glRotated(90, 1, 0, 0);
			glRotated(90, 0, 0, 1);
			glColor3f(1.0, 1.0, 1.0);
			glEnable(GL_TEXTURE_2D);
			tSquare.bind();
			underFoot.drawTrapeze(2.7, 1.75, 0.35, 0.85);
		glPopMatrix();

		glPushMatrix();
			glTranslated(4.0, 0.35, 0.0);
			glRotated(90, 0, 1, 0);
			glColor3f(1.0, 1.0, 1.0);
			glEnable(GL_TEXTURE_2D);
			ankle.drawHalfCylinder(1, 32, 0.2, 0.85, true, tSquare, tCircle);
		glPopMatrix();

	glPopMatrix();

	glPushMatrix();

		glTranslated(0.0, 0.0, 0.45);
		glScaled(1.0, 0.8, 0.8);

		//MIDDLE FOOT
		glPushMatrix();
			glTranslated(0,1.025,0);
			glRotated(270, 1, 0, 0);
			glRotated(90, 0, 0, 1);
			glColor3f(0.92,0.92,0.92);
			glEnable(GL_TEXTURE_2D);
			tSquare.bind();
			foot.drawTrapeze(2.7, 1.75, 1.35, 0.6);
		glPopMatrix();

		glPushMatrix();
			glTranslated(0,0.175,0);
			glRotated(90, 1, 0, 0);
			glRotated(90, 0, 0, 1);
			glColor3f(0.95,0.95,0.95);
			glEnable(GL_TEXTURE_2D);
			tSquare.bind();
			underFoot.drawTrapeze(2.7, 1.75, 0.35, 0.85);
		glPopMatrix();

		glPushMatrix();
			glTranslated(0,0.35,0);
			glRotated(90, 0, 1, 0);
			glColor3f(1.0, 1.0, 1.0);
			glEnable(GL_TEXTURE_2D);
			ankle.drawHalfCylinder(1, 32, 1.75, 0.85, true, tSquare, tCircle);
		glPopMatrix();

	glPopMatrix();

	glPushMatrix();

		glRotated(19, 1.0, 0.0, 0.0);

		//BODY
		glPushMatrix();
			glTranslated(0, 5.1, 0);
			glRotated(180, 0, 0, 1);
			glRotated(270, 0, 1, 0);
			glRotated(90, 1, 0, 0);
			glEnable(GL_TEXTURE_2D);
			glCullFace(GL_BACK);
			body.drawCylinder(1, 64, 5.2, 2.5, true, tBody, tBodyLid);
		glPopMatrix();

		//UNDERBODY
		glPushMatrix();
			glTranslated(0, 2.25, 0);
			glRotated(270, 1, 0, 0);
			//tUnderbody.bind();
			underbody.drawCone(1, 64, 0.5, 1.9, 1.6, true, tUnderbody, tBodyLid);
		glPopMatrix();

		//MIDDLE ARM
		glPushMatrix();
			glTranslated(0, 1.3, 0);
			glColor3f(0.95, 0.95, 0.95);
			glEnable(GL_TEXTURE_2D);
			tSquare.bind();
			middleArm.drawBox();
		glPopMatrix();

		glPushMatrix();
			glTranslated(0, 1.3, 0);
			glColor3f(0.15, 0.25, 0.40);
			glEnable(GL_TEXTURE_2D);
			tSquare.bind();
			middleForearm.drawBox();
		glPopMatrix();

		//HEAD
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);

			if (headAutoRotation) {
				//cout << "rotate x " << xRotation << " and reverseRotation " << reverseRotation << "\n";
				if (reverseRotation) {
					xRotation -= 0.3;
					//cout << "rotate x - 0.3 = " << xRotation << "\n";
				} else {
					xRotation += 0.3;
					//cout << "rotate x + 0.3 = " << xRotation << "\n";
				}

				if (xRotation > 60.0) {
					reverseRotation = true;
					audio.playThreadAudio("beep", "mp3");
				}
				else if (xRotation < -60.0) {
					reverseRotation = false;
					audio.playThreadAudio("beep", "mp3");
				}
			}
			else {
				switch (rotateHeadDirection) {
					case 1:
						xRotation += 1.0;
						break;
					case -1:
						xRotation -= 1.0;
						break;
					default: break;
				}
			}
			glRotated(xRotation, 0, 1, 0);

			glTranslated(0, 7.7, 0);
			glRotated(90, 0, 1, 0);
			glRotated(90, 1, 0, 0);
			glEnable(GL_TEXTURE_2D);
			tHead.bind();
			glColor3f(1.0, 1.0, 1.0);
			head.drawHalfSphere(2.5, 24, 32);

			//black lens
			glPushMatrix();
				glRotated(-45, 0, 1, 0);
				glDisable(GL_TEXTURE_2D);
				glCullFace(GL_BACK);
				glColor4f(0.0, 0.0, 0.0, 0.7);
				glTranslated(0.19, 0.43, -1.98);
				lens.drawHalfSphere(0.62, 24, 32);
			glPopMatrix();

			//red lens
			glPushMatrix();
				glRotated(270, 0, 1, 0);
				glTranslated(-0.6, 0.4, -2.3);
				glDisable(GL_TEXTURE_2D);
				glCullFace(GL_BACK);
				glColor4f(0.5, 0.0, 0.0, 0.8);
				lens.drawHalfSphere(0.22, 12, 12);
			glPopMatrix();

			glPushMatrix();
				glRotated(90, 0, 1, 0);
				glRotated(15, 1, 0, 0);
				glRotated(15, 0, 1, 0);
				glTranslated(0.12, 0.08, 2.5);
				glColor3f(0.5, 0.5, 0.5);
				glCullFace(GL_BACK);
				glEnable(GL_TEXTURE_2D);
				eye.drawCylinder(1, 16, 0.3, 0.2, false, tMetal, tAxe);

				glDisable(GL_TEXTURE_2D);
				glCullFace(GL_BACK);
				glColor4f(0.14, 0.17, 0.22, 0.9);
				glTranslated(0.0, 0.0, 0.05);
				glRotated(180, 0, 1, 0);
				lens.drawHalfSphere(0.19, 12, 12);
			glPopMatrix();

			//HOLOGRAM
			if (showHologram) {
				glPushMatrix();

					glTranslated(7.1, -1.7, -2.3);
					glRotated(18, 0, 1, 0);
					glRotated(-13, 0, 0, 1);
					glRotated(90, 1, 0, 0);
					glRotated(270, 0, 1, 0);

					//character from back
					glPushMatrix();
						glRotated(180, 0, 1, 0);
						glRotated(270, 1, 0, 0);
						glTranslated(0, -5.0, 0);
						glCullFace(GL_BACK);
						glEnable(GL_TEXTURE_2D);
						glColor4f(1, 1, 1, 0.8);
						tHologram.bindAlpha();
						hologram.drawQuads();

						//flare from back
						glEnable(GL_TEXTURE_2D);
						glColor4f(1, 1, 1, 0.3);
						glTranslated(0, 0.1, 0);
						glTranslated(0, 0, flarePos - (flarePathLenght - flareHeight) / 2);
						tHoloLight.bindAlpha();
						holoFlare.createPlane(3.5, flareHeight, 1);
						holoFlare.drawQuads();
					glPopMatrix();

					//lightrays
					tHoloLight.bindAlpha();
					holoLight.drawTrapeze(3.5, 8.0, 10, 0.05, false);

					//character from front
					glRotated(270, 1, 0, 0);
					glTranslated(0, 5.0, 0);
					glColor3f(1.0, 1.0, 1.0);
					glEnable(GL_TEXTURE_2D);
					tHologram.bindAlpha();
					hologram.drawQuads();

					//flare
					glEnable(GL_TEXTURE_2D);
					glColor4f(1,1,1,0.4);
					glTranslated(0, 0.1, 0);
					glTranslated(0, 0, flarePos - (flarePathLenght-flareHeight)/2);
					tHoloLight.bindAlpha();
					holoFlare.createPlane(3.5, flareHeight, 1);
					holoFlare.drawQuads();

				glPopMatrix();
			}

		glPopMatrix();

	glPopMatrix();
}