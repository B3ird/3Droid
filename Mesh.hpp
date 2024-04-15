#pragma once

#include <vector>
#include "Vertex.hpp"
#include "Texture.hpp"

class Mesh {
	public:

		std::vector<Vertex>vertices;

		Mesh(void);
		~Mesh(void);

		// Vertices creation methods
		void createPlane(double largeur, double longueur, int n);
		void createCylinder(double r, double h, double n, double m);
		void createCone(double r1, double r2, double h, double n, double m);
		void createHalfSphere (double R);
		void createBox(double x, double y, double z);
		void createTrapeze(double x, double y, double z, double n);

		/* Drawing methods */
		
		void displayAxe();

		// ..custom
		void drawBox();
		void drawTrapeze(double x, double y, double z, double n, bool lids = true);

		void drawCylinder(int numMajor, int numMinor, float height, float radius, bool lids, Texture pipeTexture = Texture(), Texture lidTexture = Texture());
		void drawHalfCylinder(int numMajor, int numMinor, float height, float radius, bool lids, Texture pipeTexture = Texture(), Texture lidTexture = Texture());
		void drawCone(int numMajor, int numMinor, float height, float radiusTop, float radiusBottom, bool lids, Texture pipeTexture = Texture(), Texture lidTexture = Texture());
		
		void drawSphere(double r, int lats, int longs);
		void drawHalfSphere(double r, int lats, int longs);
		
		// ..generic
		void drawTriangles();
		void drawTriangleStrip();
		void drawQuads();
		void drawQuadStrip();
		void drawPolygons();
		void drawLineStrip();
};

