#pragma once
#include <vector>

namespace GenerativeGeometry {

const double pi = 3.14159265358979323846;
struct vec2 { float x, y; };
struct vec3 { float x, y, z; };
struct vec4 { float r, g, b, a; };

class Geometry {

	vec3 Center;

public:
	Geometry() : Center(vec3{ 0.0, 0.0, 0.0 }) {};

	Geometry(vec3 center) : Center(center) {};

	virtual void MakeTriangles() = 0;

public: 
	vec3 GetCenter() {
		return Center;
	}
};

} // namespace GenerativeGeometry
