#pragma once
#include "GG_Circle.h"
#include <memory>
 
namespace GenerativeGeometry {

class Gear : public Circle {

	int RotationFactor = 1;
	int NumTeeth;
	double ToothWidthUnit;

public:
	Gear(V3 center, double radius, int numTeeth) :
		Circle(center, radius, numTeeth * 2),
		NumTeeth(numTeeth), ToothWidthUnit(ComputeToothWidth_Unit()) {}

	int GetNumTeeth() const { return NumTeeth; }; 
	void SetNumTeeth(int nT) { NumTeeth = nT; };
	double GetToothWidthUnit() const { return ToothWidthUnit; };
	void SetToothWidthUnit(double tWU) { ToothWidthUnit = tWU; };
	double GetToothWidth() const {
		return GetToothWidthUnit() * GetRadius();
	}

	int GetRotationFactor() const { return RotationFactor; };
	void SetRotationFactor(int f) { RotationFactor = f; };

protected:

	double ComputeToothWidth_Unit() const {
		return 2.0 * pi / (NumTeeth * 2.0);
	};
};




class Gear2D : public Gear {
public:
	Gear2D(V3 center, double radius, int numTeeth) : 
		Gear(center, radius, numTeeth) { };

	void Generate() override { MakeTriangles(); }

protected:

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
		if (i < GetNumTeeth() * 2) {
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
		else if (i == GetNumTeeth() * 2) {
			// Last triangle face, clockwise, a gap
			AddTri(0, 2, 2*i);
		}
	}
}; 


}; // namespace GenerativeGeometry