#pragma once
#include "GG_Geometry.h"

namespace GenerativeGeometry {

const double FIRST_GEAR_RADIUS = 100.0;
const int FIRST_GEAR_NUMTEETH = 16;

class Circle : public Geometry { 
public:
	Circle() : Geometry(V3(0,0,0)),NumSpokes(0), Radius(0) {};
	Circle(V3 center, double radius, int edges) : Geometry(center), Radius(radius), NumSpokes(edges) {};

	virtual void Generate() override { MakeTriangles(); };

	// Getters & Setters mostly for testing
	int GetTriangleVertIndexAt(int i) const { return TriangleVertIndices[i]; }
	V3 GetVertexAt(int i) const { return Vertices[i]; }
	V3 GetNormalAt(int i) const { return Normals[i]; }
	int GetNumSpokes() const { return NumSpokes; };
	void SetNumSpokes(int nS) { NumSpokes = nS; };
	int GetNumVerts() const { return Vertices.NUM(); };
	int GetNumNormals() const { return Normals.NUM(); };
	int GetNumTriangleVertIndices() const { return TriangleVertIndices.NUM(); };
	double GetRadius() const { return Radius; }
	void SetRadius(double val) { Radius = val; }

	VEC<int> GetTriangleVertexIndices() const { return TriangleVertIndices; };
	VEC<V3> GetVertices() const { return Vertices; };
	VEC<V3> GetNormals() const { return Normals; };

protected:
	double Radius = FIRST_GEAR_RADIUS; 
	int NumSpokes = FIRST_GEAR_NUMTEETH*2;

	VEC<int> TriangleVertIndices;
	VEC<V3> Vertices;
	VEC<V3> Normals;

	double GetEdgeWidthUnit() const {
		return 2.0 * pi / NumSpokes;
	};
	double GetThetaAtIthSpoke(int i) const {
		return i * GetEdgeWidthUnit();
	};

	virtual void AddTri(int a, int b, int c) {
		TriangleVertIndices.PUSH(a);
		TriangleVertIndices.PUSH(b);
		TriangleVertIndices.PUSH(c);
	}


	void MakeTriangles() override {
		Vertices.PUSH(GetCenter());
		Normals.PUSH(V3(1, 0, 0));

		// Iterate through all spokes (NumTeeth*2)
		for (int i = 1; i <= NumSpokes; i++) {
			MakeVertices(i);
			MakeNormals();
			MakeTriangleVertexIndices(i);
		};
	};

	virtual void MakeTriangleVertexIndices(int i)
	{
		if (i < NumSpokes) {
			// Make a face triangle 
			AddTri(i + 1, i, 0);
		}
		else if (i == NumSpokes)
		{
			// Last triangle face, clockwise
			AddTri(1, i, 0);
		}
	}

	virtual void MakeNormals()
	{
		Normals.PUSH(V3(1, 0, 0));
	}

	virtual void MakeVertices(int i)
	{
		auto c = GetCenter();
		double theta = GetThetaAtIthSpoke(i - 1);
		double cT = cos(theta);
		double sT = sin(theta);
		// Create vertices for front of circle
		Vertices.PUSH(V3(0 + c.X, Radius * cT + c.Y, Radius * sT + c.Z));
	}

};


}  // namespace GenerativeGeometry
