#include "Mesh.hpp"
#include "GL/freeglut.h"
#include <iostream>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef NULL
#define NULL 0
#endif
#include <iostream>
#include <math.h>

Mesh::Mesh(void) {}

Mesh::~Mesh(void) {}

void Mesh::displayAxe() {

	vertices.clear();

	vertices.push_back(Vertex(0, 0, 0));
	vertices.push_back(Vertex(1, 0, 0));
	vertices.push_back(Vertex(0, 1, 0));
	vertices.push_back(Vertex(0, 0, 1));

	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glLineWidth(4);
		glVertex3f (vertices[0].x, vertices[0].y, vertices[0].z);
		glVertex3f (vertices[1].x, vertices[1].y, vertices[1].z);
	glEnd();
	glBegin(GL_LINES);
		glColor3f(0,1,0);
		glLineWidth(4);
		glVertex3f (vertices[0].x, vertices[0].y, vertices[0].z);
		glVertex3f (vertices[2].x, vertices[2].y, vertices[2].z);
	glEnd();
	glBegin(GL_LINES);
		glColor3f(0,0,1);
		glLineWidth(4);
		glVertex3f (vertices[0].x, vertices[0].y, vertices[0].z);
		glVertex3f (vertices[3].x, vertices[3].y, vertices[3].z);
	glEnd();
	
}

void Mesh::createPlane(double largeur, double longueur, int n) {
	vertices.clear();
	vertices.push_back(Vertex(-largeur/2, 0, longueur/2, 0, n));
	vertices.push_back(Vertex(largeur/2, 0, longueur/2, n, n));
	vertices.push_back(Vertex(largeur/2, 0, -longueur/2, n, 0));
	vertices.push_back(Vertex(-largeur/2, 0, -longueur/2, 0, 0));
}

void Mesh::createCylinder(double r, double h, double n, double m) {
	vertices.clear();
	for (int i = 0; i < n; i++) {
		vertices.push_back(Vertex(r*cos((i+1)*2* M_PI /n), -h/2, r*sin((i+1)*2* M_PI /n), (i+1)/n*m, 1.0*m));
		vertices.push_back(Vertex(r*cos(i*2* M_PI /n), -h/2, r*sin(i*2* M_PI /n), i/n*m, 1.0*m));
		vertices.push_back(Vertex(r*cos(i*2* M_PI /n), h/2, r*sin(i*2* M_PI /n), i/n*m, 0.0*m));
		vertices.push_back(Vertex(r*cos((i+1)*2* M_PI /n), h/2, r*sin((i+1)*2* M_PI /n), (i+1)/n*m, 0.0*m));
	}	
}

void Mesh::createCone(double r1, double r2, double h, double n, double m) {
	vertices.clear();
	for (int i = 0; i < n; i++)	{
		vertices.push_back(Vertex(r1*cos((i+1)*2* M_PI /n), -h/2, r1*sin((i+1)*2* M_PI /n), (i+1)/n*m, 1.0*m));
		vertices.push_back(Vertex(r1*cos(i*2* M_PI /n), -h/2, r1*sin(i*2* M_PI /n), i/n*m, 1.0*m));
		vertices.push_back(Vertex(r2*cos(i*2* M_PI /n), h/2, r2*sin(i*2* M_PI /n), i/n*m, 0.0*m));
		vertices.push_back(Vertex(r2*cos((i+1)*2* M_PI /n), h/2, r2*sin((i+1)*2* M_PI /n), (i+1)/n*m, 0.0*m));
	}	
}

void Mesh::createHalfSphere(double R) {
	const int espace = 10;
	double a;
	double b;
	vertices.clear();
	for( b = 0; b <= 90 - espace; b+=espace) {
		for( a = 0; a <= 360 - espace; a+=espace) {
			vertices.push_back(Vertex(R * sin((a) / 180 * M_PI) * sin((b) / 180 * M_PI), R * cos((a) / 180 * M_PI) * sin((b) / 180 * M_PI), R * cos((b) / 180 * M_PI),  (a) / 360, (2 * b) / 360));
			vertices.push_back(Vertex(R * sin((a) / 180 * M_PI) * sin((b + espace) / 180 * M_PI), R * cos((a) / 180 * M_PI) * sin((b + espace) / 180 * M_PI), R * cos((b + espace) / 180 * M_PI), (a) / 360, (2 * (b + espace)) / 360));
			vertices.push_back(Vertex(R * sin((a + espace) / 180 * M_PI) * sin((b) / 180 * M_PI), R * cos((a + espace) / 180 * M_PI) * sin((b) / 180 * M_PI), R * cos((b) / 180 * M_PI), (a + espace) / 360, (2 * b) / 360));
			vertices.push_back(Vertex(R * sin((a + espace) / 180 * M_PI) * sin((b + espace) /180 * M_PI), R * cos((a + espace) / 180 * M_PI) * sin((b + espace) / 180 * M_PI), R * cos((b + espace) / 180 * M_PI), (a + espace) / 360, (2 * (b + espace)) / 360));
		}
	}
}

void Mesh::createTrapeze(double x, double y, double z, double n) {
	x = x/2;
	y = y/2;
	z = z/2;
	vertices.clear();

	vertices.push_back(Vertex(-x*n, -y*n, z));
	vertices.push_back(Vertex(x*n, -y*n, z));
	vertices.push_back(Vertex(x*n, y*n, z));
	vertices.push_back(Vertex(-x*n, y*n, z));
	
	vertices.push_back(Vertex(-x, -y, -z));
	vertices.push_back(Vertex(x, -y, -z));
	vertices.push_back(Vertex(x, y, -z));
	vertices.push_back(Vertex(-x, y, -z));
}

void Mesh::createBox(double x, double y, double z) {
	x = x/2;
	y = y/2;
	z = z/2;
	
	vertices.clear();

	vertices.push_back(Vertex(-x, -y, z));
	vertices.push_back(Vertex(x, -y, z));
	vertices.push_back(Vertex(x, y, z));
	vertices.push_back(Vertex(-x, y, z));

	vertices.push_back(Vertex(-x, -y, -z));
	vertices.push_back(Vertex(x, -y, -z));
	vertices.push_back(Vertex(x, y, -z));
	vertices.push_back(Vertex(-x, y, -z));
}

void Mesh::drawBox() {
	//TOP
	glBegin(GL_QUADS);
	//glColor3f(1.0, 0.0, 1.0);//purple
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glEnd();

	//BOTTOM
	glBegin(GL_QUADS);
	//glColor3f(0.0, 1.0, 0.0);//green
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	glEnd();

	//FRONT
	glBegin(GL_QUADS);
	//glColor3f(0.0, 0.0, 1.0);//blue
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glEnd();

	//BACK
	glBegin(GL_QUADS);
	//glColor3f(0.0, 1.0, 1.0);//cyan
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
	glEnd();

	//RIGHT
	glBegin(GL_QUADS);
	//glColor3f(1.0, 0.0, 0.0);//red
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
	glEnd();

	//LEFT
	glBegin(GL_QUADS);
	//glColor3f(1.0, 1.0, 0.0);//yellow
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
	glEnd();
}

void Mesh::drawTrapeze(double x1, double y1, double z1, double n, bool lids) {
	
	const float x = x1 / 2;
	const float y = y1 / 2;
	const float z = z1 / 2;

	vertices.clear();

	vertices.push_back(Vertex(-x * n, -y * n, z));
	vertices.push_back(Vertex(x * n, -y * n, z));
	vertices.push_back(Vertex(x * n, y * n, z));
	vertices.push_back(Vertex(-x * n, y * n, z));

	vertices.push_back(Vertex(-x, -y, -z));
	vertices.push_back(Vertex(x, -y, -z));
	vertices.push_back(Vertex(x, y, -z));
	vertices.push_back(Vertex(-x, y, -z));

	const float trap_wide = x1*y1*z1;
	const float trap_narrow = x1*y1*z1*n;
	/* Fix trapezoid texture application
	Source : https://stackoverflow.com/questions/15242507/perspective-correct-texturing-of-trapezoid-in-opengl-es-2-0
	But streched texture on height of trapezoid...
	*/

	if (lids) {
		//TOP
		glBegin(GL_QUADS);
			//glColor3f(1.0, 0.0, 1.0);//purple
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
		glEnd();

		//BOTTOM
		glBegin(GL_QUADS);
			//glColor3f(0.0, 1.0, 0.0);//green
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
		glEnd();
	}

	//FRONT
	glBegin(GL_QUADS);
		//glColor3f(0.0, 0.0, 1.0);//blue
		glColor3f(1.0, 1.0, 1.0);
		glNormal3f(1.0f, 0.0f, 0.0f);

		//glTexCoord2f(0.0f, 0.0f);
		glTexCoord4f(0, 0, 0, trap_narrow);
		glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	
		//glTexCoord2f(1.0f, 0.0f);
		glTexCoord4f(trap_narrow, 0, 0, trap_narrow);
		glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z); 
	
		//glTexCoord2f(1.0f, 1.0f); 
		glTexCoord4f(trap_wide, trap_wide, 0, trap_wide);
		glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);

		//glTexCoord2f(0.0f, 1.0f);
		glTexCoord4f(0, trap_wide, 0, trap_wide);
		glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	
	glEnd();
	
	//BACK
	glBegin(GL_QUADS);
		//glColor3f(0.0, 1.0, 1.0);//cyan
		glNormal3f(-1.0f, 0.0f, 0.0f);
	
		//glTexCoord2f(0.0f, 0.0f); 
		glTexCoord4f(0, 0, 0, trap_narrow);
		glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	
		//glTexCoord2f(1.0f, 0.0f); 
		glTexCoord4f(trap_narrow, 0, 0, trap_narrow);
		glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	
		//glTexCoord2f(1.0f, 1.0f); 
		glTexCoord4f(trap_wide, trap_wide, 0, trap_wide);
		glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
	
		//glTexCoord2f(0.0f, 1.0f); 
		glTexCoord4f(0, trap_wide, 0, trap_wide);
		glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
	glEnd();

	//RIGHT
	glBegin(GL_QUADS);
		//glColor3f(1.0, 0.0, 0.0);//red
		glNormal3f(0.0f, 1.0f, 0.0f);
		//glTexCoord2f(0.0f, 0.0f); 
		glTexCoord4f(0, 0, 0, trap_narrow);
		glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);

		//glTexCoord2f(1.0f, 0.0f); 
		glTexCoord4f(trap_narrow, 0, 0, trap_narrow);
		glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);

		//glTexCoord2f(1.0f, 1.0f); 
		glTexCoord4f(trap_wide, trap_wide, 0, trap_wide);
		glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);

		//glTexCoord2f(0.0f, 1.0f); 
		glTexCoord4f(0, trap_wide, 0, trap_wide);
		glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
	glEnd();

	
	//LEFT
	glBegin(GL_QUADS);
		//glColor3f(1.0, 1.0, 0.0);//yellow
		glNormal3f(0.0f, -1.0f, 0.0f);

		//glTexCoord2f(0.0f, 0.0f); 
		glTexCoord4f(0, 0, 0, trap_narrow);
		glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);

		//glTexCoord2f(1.0f, 0.0f); 
		glTexCoord4f(trap_narrow, 0, 0, trap_narrow);
		glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);

		//glTexCoord2f(1.0f, 1.0f); 
		glTexCoord4f(trap_wide, trap_wide, 0, trap_wide);
		glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);

		//glTexCoord2f(0.0f, 1.0f); 
		glTexCoord4f(0, trap_wide, 0, trap_wide);
		glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
	glEnd();
}

void Mesh::drawSphere(double r, int lats, int longs) {
	int i, j;
	for (i = 0; i <= lats; i++) {
		double lat0 = M_PI * (-0.5 + (double)(i - 1) / lats);
		double z0 = sin(lat0);
		double zr0 = cos(lat0);

		double lat1 = M_PI * (-0.5 + (double)i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= longs; j++) {
			double lng = 2 * M_PI * (double)(j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);

			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(r * x * zr0, r * y * zr0, r * z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(r * x * zr1, r * y * zr1, r * z1);
		}
		glEnd();
	}
}

void Mesh::drawHalfSphere(double r, int lats, int longs) {
	int i, j;
	for (i = 1; i <= lats/2; i++) {
		double lat0 = M_PI * (-0.5 + (double)(i - 1) / lats);
		double z0 = sin(lat0);
		double zr0 = cos(lat0);

		double lat1 = M_PI * (-0.5 + (double)i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		glBegin(GL_TRIANGLE_STRIP);
	
		for (j = 0; j <= longs; j++) {
			double lng = 2 * M_PI * (double)(j - 1) / longs;
			double x = -cos(lng);
			double y = sin(lng);

			glNormal3f(x * zr0, y * zr0, z0);
			glTexCoord2f((double)j / longs, (double)(i - 1) / lats);
			glVertex3f(r * x * zr0, r * y * zr0, r * z0);

			glNormal3f(x * zr1, y * zr1, z1);
			glTexCoord2f((double)j / longs, (double)i / lats);
			glVertex3f(r * x * zr1, r * y * zr1, r * z1);
		}
		glEnd();
	}
}

void Mesh::drawCylinder(int numMajor, int numMinor, float height, float radius, bool lids, Texture pipeTexture, Texture lidTexture) {
	double majorStep = height / numMajor;
	double minorStep = 2.0 * M_PI / numMinor;

	if (pipeTexture.loaded) {
		pipeTexture.bind();
	}

	for (int i = 0; i < numMajor; ++i) {
		GLfloat z0 = 0.5 * height - i * majorStep;
		GLfloat z1 = z0 - majorStep;

		glBegin(GL_TRIANGLE_STRIP);

		for (int j = 0; j <= numMinor; ++j) {
			double a = j * minorStep;
			GLfloat x = radius * cos(a);
			GLfloat y = radius * sin(a);
			glNormal3f(x / radius, y / radius, 0.0);
			glTexCoord2f(j / (GLfloat)numMinor, i / (GLfloat)numMajor);
			glVertex3f(x, y, z0);

			glNormal3f(x / radius, y / radius, 0.0);
			glTexCoord2f(j / (GLfloat)numMinor, (i + 1) / (GLfloat)numMajor);
			glVertex3f(x, y, z1);
		}
		glEnd();
	}

	if (lids) {
		if (lidTexture.loaded) {
			lidTexture.bind();
		}

		// Draw top lid
		glBegin(GL_TRIANGLE_FAN);

		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(0.0, 0.0, 0.5 * height);
		for (int j = 0; j <= numMinor; j++) {
			double a = j * minorStep;
			GLfloat x = radius * cos(a);
			GLfloat y = radius * sin(a);
			GLfloat s = 0.5 * (1.0 + cos(a));
			GLfloat t = 0.5 * (1.0 + sin(a));
			glTexCoord2f(s, t);
			glVertex3f(x, y, 0.5 * height);
		}
		glEnd();

		// Draw bottom lid
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.5, 0.5);
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(0.0, 0.0, -0.5 * height);
		for (int j = numMinor; j >= 0 ; j--) {
			double a = j * minorStep;
			GLfloat x = radius * cos(a);
			GLfloat y = radius * sin(a);
			GLfloat s = 0.5 * (1.0 + cos(a));
			GLfloat t = 0.5 * (1.0 + sin(a));
			glTexCoord2f(s, t);
			glVertex3f(x, y, -0.5 * height);
		}
		glEnd();
	}
}

void Mesh::drawHalfCylinder(int numMajor, int numMinor, float height, float radius, bool lids, Texture pipeTexture, Texture lidTexture) {
	double majorStep = height / numMajor;
	double minorStep = 2.0 * M_PI / numMinor;

	if (pipeTexture.loaded) {
		pipeTexture.bind();
	}

	for (int i = 0; i < numMajor; ++i) {
		GLfloat z0 = 0.5 * height - i * majorStep;
		GLfloat z1 = z0 - majorStep;

		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j <= numMinor/2; ++j) {
			double a = j * minorStep;
			GLfloat x = radius * cos(a);
			GLfloat y = radius * sin(a);
			glNormal3f(x / radius, y / radius, 0.0);
			//glTexCoord2f(j / (GLfloat)numMinor, i / (GLfloat)numMajor);
			glTexCoord2f(j / (GLfloat)numMinor*2, i);
			glVertex3f(x, y, z0);

			glNormal3f(x / radius, y / radius, 0.0);
			//glTexCoord2f(j / (GLfloat)numMinor, (i + 1) / (GLfloat)numMajor);
			glTexCoord2f(j / (GLfloat)numMinor*2, (i + 1));
			glVertex3f(x, y, z1);
		}
		glEnd();
	}
	if (lids) {

		if (lidTexture.loaded) {
			lidTexture.bind();
		}

		// Draw top lid
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.5, 0.5);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.5 * height);
		for (int j = 0; j <= numMinor/2; j++) {
			double a = j * minorStep;
			GLfloat x = radius * cos(a);
			GLfloat y = radius * sin(a);
			GLfloat s = 0.5 * (1.0 + cos(a));
			GLfloat t = 0.5 * (1.0 + sin(a));
			glTexCoord2f(s, t);
			glVertex3f(x, y, 0.5 * height);
		}
		glEnd();

		// Draw bottom lid
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.5, 0.5);
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(0.0, 0.0, -0.5 * height);
		for (int j = numMinor/2; j >= 0; j--) {
			double a = j * minorStep;
			GLfloat x = radius * cos(a);
			GLfloat y = radius * sin(a);
			GLfloat s = 0.5 * (1.0 + cos(a));
			GLfloat t = 0.5 * (1.0 + sin(a));
			glTexCoord2f(s, t);
			glVertex3f(x, y, -0.5 * height);
		}
		glEnd();
	}
}

void Mesh::drawCone(int numMajor, int numMinor, float height, float radiusTop, float radiusBottom, bool lids, Texture pipeTexture, Texture lidTexture) {
	double majorStep = height / numMajor;
	double minorStep = 2.0 * M_PI / numMinor;
	int i, j;
	
	if (pipeTexture.loaded) {
		pipeTexture.bind();
	}

	for (i = 0; i < numMajor; ++i) {
		GLfloat z0 = 0.5 * height - i * majorStep;
		GLfloat z1 = z0 - majorStep;

		glBegin(GL_TRIANGLE_STRIP);
		for (j = 0; j <= numMinor; ++j) {
			double a = j * minorStep;

			GLfloat x = radiusTop * cos(a);
			GLfloat y = radiusTop * sin(a);
			glNormal3f(x / radiusTop, y / radiusTop, 0.0);
			glTexCoord2f(j / (GLfloat)numMinor, i / (GLfloat)numMajor);
			glVertex3f(x, y, z0);

			GLfloat x2 = radiusBottom * cos(a);
			GLfloat y2 = radiusBottom * sin(a);
			glNormal3f(x2 / radiusBottom, y2 / radiusBottom, 0.0);
			glTexCoord2f(j / (GLfloat)numMinor, (i + 1) / (GLfloat)numMajor);
			glVertex3f(x2, y2, z1);
		}
		glEnd();
	}
	if (lids) {

		if (lidTexture.loaded) {
			lidTexture.bind();
		}

		// Draw top lid
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.5, 0.5);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.5 * height);
		for (j = 0; j <= numMinor; j++) {
			double a = j * minorStep;
			GLfloat x = radiusTop * cos(a);
			GLfloat y = radiusTop * sin(a);
			GLfloat s = 0.5 * (1.0 + cos(a));
			GLfloat t = 0.5 * (1.0 + sin(a));
			glTexCoord2f(s, t);
			glVertex3f(x, y, 0.5 * height);
		}
		glEnd();

		// Draw bottom lid
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.5, 0.5);
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(0.0, 0.0, -0.5 * height);
		for (j = numMinor; j >= 0; j--) {
			double a = j * minorStep;
			GLfloat x = radiusBottom * cos(a);
			GLfloat y = radiusBottom * sin(a);
			GLfloat s = 0.5 * (1.0 + cos(a));
			GLfloat t = 0.5 * (1.0 + sin(a));
			glTexCoord2f(s, t);
			glVertex3f(x, y, -0.5 * height);
		}
		glEnd();
	}
}

void Mesh::drawTriangles() {	
	for(int nb = 0; nb < vertices.size()/3 ; ++nb) {
		glBegin(GL_TRIANGLES);
		for(int i = 0; i < 3; ++i) {
			glTexCoord2f(vertices[nb*3+i].u, vertices[nb*3+i].v);   
			glVertex3f(vertices[nb*3+i].x,vertices[nb*3+i].y, vertices[nb*3+i].z);
		}
		glEnd();
	}
}

void Mesh::drawTriangleStrip() {
	glBegin(GL_TRIANGLE_STRIP);
	for(int nb = 0; nb < vertices.size()/3 ; ++nb) {
		for(int i = 0; i < 3; ++i) {
			glTexCoord2f(vertices[nb*3+i].u, vertices[nb*3+i].v);   
			glVertex3f(vertices[nb*3+i].x,vertices[nb*3+i].y, vertices[nb*3+i].z);
		}
	}
	glEnd();
}

void Mesh::drawQuads(){
	for(int nb = 0; nb < vertices.size()/4 ; ++nb) {
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			for(int i = 0; i < 4; ++i) {
				glTexCoord2f(vertices[nb*4+i].u, vertices[nb*4+i].v);
				glVertex3f(vertices[nb*4+i].x,vertices[nb*4+i].y, vertices[nb*4+i].z);
			}
		glEnd();
	}
}

void Mesh::drawQuadStrip() {
	glBegin(GL_QUAD_STRIP);
	for(int nb = 0; nb < vertices.size() ; ++nb) {
		glTexCoord2f(vertices[nb].u, vertices[nb].v);   
		glVertex3f(vertices[nb].x,vertices[nb].y, vertices[nb].z);
	}
	glEnd();
}

void Mesh::drawLineStrip() {
	glBegin(GL_LINE_STRIP);
	for(int nb = 0; nb < vertices.size()/2; ++nb) {
		for(int i = 0; i < 2; ++i) {
			glTexCoord2f(vertices[nb*2+i].u, vertices[nb*2+i].v);   
			glVertex3f(vertices[nb*2+i].x,vertices[nb*2+i].y, vertices[nb*2+i].z);
		}
	}
	glEnd();
}

void Mesh::drawPolygons() {
	glBegin(GL_POLYGON);
	for(int i = 0; i < vertices.size(); i++) {
		glTexCoord2f(vertices[i].u, vertices[i].v);
		glVertex3f(vertices[i].x,vertices[i].y, vertices[i].z);
	}
	glEnd();
}

