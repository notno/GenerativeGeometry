#pragma once
#include "GG_Circle.h"

namespace GenerativeGeometry {

class Gear2D : public Circle {
public:
	Gear2D(V3 center, double radius, int numTeeth, double width = 30.0) : 
		Circle(center, radius, numTeeth * 2), 
		NumTeeth(numTeeth), ToothWidthUnit(SetToothWidthUnit(radius)) { };

	void Draw() override { MakeTriangles(); }

	int GetNumTeeth() const { return NumTeeth; }; 
	double GetToothWidthUnit() const { return ToothWidthUnit; };
	double GetToothWidth() const {
		return GetToothWidthUnit() * GetRadius();
	}


protected:
	int NumTeeth;
	double ToothWidthUnit;

	double SetToothWidthUnit(double) const {
		return 2.0 * pi / (NumTeeth * 2.0);
	};

	virtual void MakeVertices(int i) override
	{
		auto center = GetCenter();
		auto radius = GetRadius();
		auto outerRadius = radius + GetToothWidth();

		double theta = GetThetaAtIthSpoke(i - 1);
		double cT = cos(theta);
		double sT = sin(theta);

		// Create vertices for front of gear
		Vertices.PUSH(V3(0 + center.X, radius * cT, radius * sT));
		Vertices.PUSH(V3(0 + center.X, outerRadius * cT, outerRadius * sT));
	}

	virtual void MakeNormals() override
	{
		// Create placeholder normals, 1 for each vert
		Normals.PUSH(V3(1, 0, 0));
		Normals.PUSH(V3(1, 0, 0));
	}

	virtual void MakeTriangleVertexIndices(int i) override 
	{
		if (i < NumTeeth * 2) {
			if ((i & 1) == 1) { // Gear tooth
				// Make gear face triangle for tooth
				AddTri(2*(i+1)-1, 2*i-1, 0); 
			}
			else // Gap between gear teeth
			{
				// Make gear face triangle
				AddTri(0, 2*(i+1), 2*i);
			}
		}
		else if (i == NumTeeth * 2) {
			// Last triangle face, clockwise, a gap
			AddTri(0, 2, 2*i);
		}
	}
}; 

class Gear3D : public Gear2D {

public:
	Gear3D(V3 center, double radius, int numTeeth, double width = 30.0) :
		Gear2D(center, radius, numTeeth), GearWidth(width) { };

	double GetGearWidth() const {
		return GearWidth;
	};

protected:
	double GearWidth;

	virtual void MakeVertices(int i) override 
	{
		auto center = GetCenter();
		auto radius = GetRadius();
		auto outerRadius = radius + GetToothWidth();

		double theta = GetThetaAtIthSpoke(i - 1);
		double cT = cos(theta);
		double sT = sin(theta);

		// Create vertices for front of gear
		Vertices.PUSH(V3( 0 + center.X, radius * cT, radius * sT ));
		Vertices.PUSH(V3( 0 + center.X, outerRadius * cT, outerRadius * sT ));
		// Create Vertices for back of gear
		Vertices.PUSH(V3( -GearWidth, outerRadius * cT, outerRadius * sT ));
		Vertices.PUSH(V3( -GearWidth, radius * cT, radius * sT ));
	}

	virtual void MakeNormals() override
	{ 
		Normals.PUSH(V3( 1, 0, 0 ));
		Normals.PUSH(V3( 1, 0, 0 ));
		Normals.PUSH(V3( 1, 0, 0 ));
		Normals.PUSH(V3( 1, 0, 0 ));
	}

	virtual void MakeTriangleVertexIndices(int i) override {
		// Storing indices of Vertices for easy use when making triangles
		// Using "even" for even numbered spokes, "odd" for odd spokes
		int even4 = 4 * i,
			even3 = even4 - 1,
			even2 = even4 - 2,
			even1 = even4 - 3,
			even8 = 4 * (i + 1),
			even7 = even8 - 1,
			even6 = even8 - 2,
			even5 = even8 - 3,
			odd1 = even1,
			odd2 = even4,
			odd3 = even5,
			odd4 = even8;

		if (i < NumTeeth * 2) {
			if ((i & 1) == 1) { // Gear tooth
				// Make gear face triangle for tooth
				TriangleVertIndices.PUSH(even6); // Neighbor's outer vertex
				TriangleVertIndices.PUSH(even2); // Outer vertex
				TriangleVertIndices.PUSH(0);     // Triangles all sharing vertex 0, the center point
				// Make 2 tris for outer face of tooth
				TriangleVertIndices.PUSH(even6);
				TriangleVertIndices.PUSH(even7);
				TriangleVertIndices.PUSH(even3);
				TriangleVertIndices.PUSH(even3);
				TriangleVertIndices.PUSH(even2);
				TriangleVertIndices.PUSH(even6);
				// Make 2 tris for cw side of tooth
				TriangleVertIndices.PUSH(even1);
				TriangleVertIndices.PUSH(even2);
				TriangleVertIndices.PUSH(even4);
				TriangleVertIndices.PUSH(even2);
				TriangleVertIndices.PUSH(even3);
				TriangleVertIndices.PUSH(even4);
				// Make 2 tris for ccw side of tooth
				TriangleVertIndices.PUSH(even8);
				TriangleVertIndices.PUSH(even7);
				TriangleVertIndices.PUSH(even6);
				TriangleVertIndices.PUSH(even5);
				TriangleVertIndices.PUSH(even8);
				TriangleVertIndices.PUSH(even6);
			}
			else // Gap between gear teeth
			{
				// Make gear face triangle
				TriangleVertIndices.PUSH(0);
				TriangleVertIndices.PUSH(odd3); // Inner vertex
				TriangleVertIndices.PUSH(odd1); // Neighbor's inner vertex 
				// Make 2 tris for outer face of gap
				TriangleVertIndices.PUSH(odd3);
				TriangleVertIndices.PUSH(odd4);
				TriangleVertIndices.PUSH(odd1);
				TriangleVertIndices.PUSH(odd1);
				TriangleVertIndices.PUSH(odd4);
				TriangleVertIndices.PUSH(odd2);
			}
		} 
		else if (i == NumTeeth * 2) {
			// Last triangle face, clockwise, a gap
			TriangleVertIndices.PUSH(0);
			TriangleVertIndices.PUSH(1);
			TriangleVertIndices.PUSH(odd1);
			// Make 2 tris for outer face of gap
			TriangleVertIndices.PUSH(1);
			TriangleVertIndices.PUSH(4);
			TriangleVertIndices.PUSH(odd1);
			TriangleVertIndices.PUSH(odd1);
			TriangleVertIndices.PUSH(4);
			TriangleVertIndices.PUSH(odd2);
		}
	}

};  

}; // namespace GenerativeGeometry