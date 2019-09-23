#pragma once
#include "GG_Geometry.h"

namespace GenerativeGeometry {

using std::vector;

class Circle : public Geometry { 

	int NumSpokes;
	double Radius; 

public:
	Circle() : Geometry(V3(0,0,0)),NumSpokes(16), Radius(10) {};

	Circle(V3 center, double radius, int edges) : Geometry(center), Radius(radius), NumSpokes(edges) {};

	virtual void Draw() { MakeTriangles(); };

	double GetRadius() const { return Radius; }
	int GetTriangleAt(int i) const { return TriangleVerts[i]; }
	V3 GetVertexAt(int i) const { return Vertices[i]; }
	V3 GetNormalAt(int i) const { return Normals[i]; }
	int GetNumSpokes() const { return NumSpokes; };
	int GetNumVerts() const { return Vertices.NUM(); };
	int GetNumNormals() const { return Normals.NUM(); };
	int GetNumTriangleVerts() const { return TriangleVerts.NUM(); };

	VEC<int> GetTriangleVerts() const { return TriangleVerts; };
	VEC<V3> GetVertices() const { return Vertices; };
	VEC<V3> GetNormals() const { return Normals; };

protected:

	VEC<int> TriangleVerts;
	VEC<V3> Vertices;
	VEC<V3> Normals;

	double GetEdgeWidthUnit() const {
		return 2.0 * pi / NumSpokes;
	};
	double GetThetaAtIthSpoke(int i) const {
		return i * GetEdgeWidthUnit();
	};

	virtual void AddTri(int a, int b, int c) {
		TriangleVerts.PUSH(a);
		TriangleVerts.PUSH(b);
		TriangleVerts.PUSH(c);
	}

	virtual void MakeTriangles() override {
		auto c = GetCenter();
		Vertices.PUSH(c);
		Normals.PUSH(V3( 1, 0, 0 ));

		// Iterate through all spokes (numTeeth*2)
		for (int i = 1; i <= NumSpokes; i++) {
			double theta = GetThetaAtIthSpoke(i - 1);
			double cT = cos(theta);
			double sT = sin(theta);

			// Create vertices for front of circle
			Vertices.PUSH(V3( 0 + c.X, Radius * cT + c.Y, Radius * sT + c.Z ));

			if (i < NumSpokes) {
				// Make a face triangle 
				AddTri(i + 1, i, 0);
			}
			else if (i == NumSpokes)
			{
				// Last triangle face, clockwise
				AddTri(1, i, 0);
			}

			Normals.PUSH(V3( 1, 0, 0 ));
		}
	};
};


}  // namespace GenerativeGeometry
