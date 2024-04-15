#pragma once

class Vertex {
	public:

		double x, y, z;
		double u, v;

		Vertex(void);
		Vertex(double x2, double y2, double z2);
		Vertex(double x2, double y2, double z2, double u2, double v2);
		
		~Vertex(void);

		void toString();
};

