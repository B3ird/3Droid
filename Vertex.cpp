#include "Vertex.hpp"
#include <iostream>

Vertex::Vertex(void) {
	x= 0;
	y = 0;
	z = 0;
	u = 0;
	v = 0;
}

Vertex::Vertex(double x2, double y2, double z2) {
	x= x2;
	y = y2;
	z = z2;
	u = 0;
	v = 0;
}

Vertex::Vertex(double x2, double y2, double z2, double u2, double v2) {
	x= x2;
	y = y2;
	z = z2;
	u = u2;
	v = v2;
}

Vertex::~Vertex(void){}

void Vertex::toString() {
	std::cout << "(" << x << ", " << y << ", " << z << ")";
}