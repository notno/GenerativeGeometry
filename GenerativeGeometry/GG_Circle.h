#pragma once
#include "GG_Geometry.h"

namespace GenerativeGeometry {

class Circle : public Geometry {

	int NumEdges;

	float Radius;

public:
	Circle() :NumEdges(16), Radius(10) {};

	Circle(vec3 center, float radius, int edges) : Geometry(center), Radius(radius), NumEdges(edges) {};

	void Draw() { MakeTriangles(); };

	int GetTriangleAt(int i) { return Triangles[i]; }
	vec3 GetVertexAt(int i) { return Vertices[i]; }
	vec3 GetNormalAt(int i) { return Normals[i]; }

protected:
	std::vector<int> Triangles;
	std::vector<vec3> Vertices;
	std::vector<vec3> Normals;

	float GetEdgeWidthUnit() const {
		return 2.0 * pi / NumEdges;
	};
	float GetThetaAtIthSpoke(int i) const {
		return i * GetEdgeWidthUnit();
	};

	/**
	* @param: index of vertex at neighboring spoke ccw,
	* @param: index of vertex at i'th spoke,
	* @param: index of vertex at shared center
	*/
	virtual void AddTri(int a, int b, int c) {
		Triangles.push_back(a);
		Triangles.push_back(b);
		Triangles.push_back(c);
	}

	virtual void MakeTriangles() {
		auto c = GetCenter();
		Vertices.push_back(c);
		Normals.push_back(vec3{ 1, 0, 0 });

		// Iterate through all spokes (numTeeth*2)
		for (int i = 1; i <= NumEdges; i++) {
			float theta = GetThetaAtIthSpoke(i - 1);
			float cT = cos(theta);
			float sT = sin(theta);

			// Create vertices for front of circle
			Vertices.push_back(vec3{ 0 + c.x, Radius * cT + c.y, Radius * sT + c.z });

			if (i < NumEdges) {
				// Make a face triangle 
				AddTri(i + 1, i, 0);
			}
			else if (i == NumEdges)
			{
				// Last triangle face, clockwise
				AddTri(1, i, 0);
			}

			Normals.push_back(vec3{ 1, 0, 0 });

		}
	};
};


}  // namespace GenerativeGeometry
