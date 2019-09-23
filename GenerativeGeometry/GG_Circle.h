#pragma once
#include "GG_Geometry.h"

namespace GenerativeGeometry {

using std::vector;

class Circle : public Geometry { 

	int NumSpokes;
	double Radius;

public:
	Circle() : Geometry(vec3(0,0,0)),NumSpokes(16), Radius(10) {};

	Circle(vec3 center, double radius, int edges) : Geometry(center), Radius(radius), NumSpokes(edges) {};

	virtual void Draw() { MakeTriangles(); };

	double GetRadius() const { return Radius; }
	int GetTriangleAt(int i) const { return TriangleVerts[i]; }
	vec3 GetVertexAt(int i) const { return Vertices[i]; }
	vec3 GetNormalAt(int i) const { return Normals[i]; }
	int GetNumSpokes() const { return NumSpokes; };
	int GetNumVerts() const { return Vertices.size(); };
	int GetNumNormals() const { return Normals.size(); };
	int GetNumTriangleVerts() const { return TriangleVerts.size(); };

	vector<int> GetTriangleVerts() const { return TriangleVerts; };
	vector<vec3> GetVertices() const { return Vertices; };
	vector<vec3> GetNormals() const { return Normals; };

protected:

	vector<int> TriangleVerts;
	vector<vec3> Vertices;
	vector<vec3> Normals;

	double GetEdgeWidthUnit() const {
		return 2.0 * pi / NumSpokes;
	};
	double GetThetaAtIthSpoke(int i) const {
		return i * GetEdgeWidthUnit();
	};

	virtual void AddTri(int a, int b, int c) {
		TriangleVerts.push_back(a);
		TriangleVerts.push_back(b);
		TriangleVerts.push_back(c);
	}

	virtual void MakeTriangles() override {
		auto c = GetCenter();
		Vertices.push_back(c);
		Normals.push_back(vec3( 1, 0, 0 ));

		// Iterate through all spokes (numTeeth*2)
		for (int i = 1; i <= NumSpokes; i++) {
			double theta = GetThetaAtIthSpoke(i - 1);
			double cT = cos(theta);
			double sT = sin(theta);

			// Create vertices for front of circle
			Vertices.push_back(vec3( 0 + c.X, Radius * cT + c.y, Radius * sT + c.z ));

			if (i < NumSpokes) {
				// Make a face triangle 
				AddTri(i + 1, i, 0);
			}
			else if (i == NumSpokes)
			{
				// Last triangle face, clockwise
				AddTri(1, i, 0);
			}

			Normals.push_back(vec3( 1, 0, 0 ));
		}
	};
};


}  // namespace GenerativeGeometry
