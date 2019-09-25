#pragma once

#include <vector>
#include <memory>

/**
 * HACK ALERT: This macro business makes me uncomfortable, 
 * but makes it easy to test code in Unreal without 
 * depending on Unreal's containers in non-Unreal contexts
 * (e.g. OpenFrameworks, TouchDesigner)
 * 
 * @TODO: find a better solution
 *
 * For this to work in Unreal, add this line to your MyGame.Build.cs file:
 *     Definitions.Add("_THIS_IS_UNREAL_=1");
 */
#ifdef _THIS_IS_UNREAL_
#define V3 FVector
#define VEC TArray
#define NUM Num
#define PUSH Add
#else
#define V3 vec3
#define VEC std::vector
#define NUM size
#define PUSH push_back
#endif


namespace GenerativeGeometry {

	using std::cout;
	using std::endl;
const double pi = 3.14159265358979323846;

struct vec2 {  
	double X, Y; 
	vec2(double X, double Y) : X(X), Y(Y) {};
};
struct vec3 { 
	double X, Y, Z; 
	vec3(double X, double Y, double Z) : X(X), Y(Y), Z(Z) {};
	vec3() : vec3(0.0, 0.0, 0.0) {};
	vec3(double val) : vec3(val, val, val) {};
};
struct vec4 { 
	double r, g, b, a; 
	vec4(double r, double g, double b, double a) : r(r), g(g), b(b), a(a) {};
};

class Geometry {


public:
	virtual void MakeTriangles() = 0;
	virtual void Generate() = 0;

	Geometry() : Center(V3(0.0,0.0,0.0)) {};
	Geometry(V3 center) : Center(center) {};

	V3 GetCenter() const {
		return Center;
	}
protected:
	V3 Center;
};


} // namespace GenerativeGeometry
