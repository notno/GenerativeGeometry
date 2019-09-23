#pragma once

#include <vector>

namespace GenerativeGeometry {

const double pi = 3.14159265358979323846;

struct vec2 { 
	double X, Y; 
	vec2(double X, double Y) : X(X), Y(Y) {};
};
struct vec3 { 
	double X, Y, Z; 
	vec3(double X, double Y, double Z) : X(X), Y(Y), Z(Z) {};
	vec3() : X(0), Y(0), Z(0) {};
};
struct vec4 { 
	double r, g, b, a; 
	vec4(double r, double g, double b, double a) : r(r), g(g), b(b), a(a) {};
};

class Geometry {

	vec3 Center;

public:
	virtual void MakeTriangles() = 0;

	Geometry() : Center(vec3(0.0,0.0,0.0)) {};

	Geometry(vec3 center) : Center(center) {};

	vec3 GetCenter() {
		return Center;
	}
};

} // namespace GenerativeGeometry
