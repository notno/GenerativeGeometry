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

}; // namespace GenerativeGeometry