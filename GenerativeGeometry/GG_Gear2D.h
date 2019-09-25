#pragma once
#include "GG_Gear.h"
#include <memory>
 
namespace GenerativeGeometry {

class Gear2D : public Gear {
public:
	Gear2D(V3 center, double radius, int numTeeth) : 
		Gear(center, radius, numTeeth) { };


protected:

	virtual void MakeVertices(int i) override
	{
		auto center = GetCenter();
		auto outerRadius = GetRadius() + GetToothWidth();

		double theta = GetThetaAtIthSpoke(i - 1);
		double cT = cos(theta);
		double sT = sin(theta);

		// Create vertices for front of gear
		Vertices.PUSH(V3(0 + center.X, Radius * cT, Radius * sT));
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