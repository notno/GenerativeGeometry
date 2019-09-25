#pragma once
#include "GG_Gear.h"
#include <iostream>
#include <assert.h>
#include <exception>

//#define NDEBUG
namespace GenerativeGeometry {

class Gear3D : public Gear {
	static Gear3D* LastLink;
	double GearWidth = 30.0;
	double DistanceFromPrevious = 500; // Mostly for testing
public:
	Gear3D() : Gear3D(V3(0)) {};
	Gear3D(V3 center, double radius, int numTeeth, double width);
	Gear3D(V3 center);
	void ThisIsFirstGear();
	void NewGearFromCenter(V3 center);
	double GetGearWidth() const { return GearWidth; };
	double GetDistanceFromPrevious() const { return DistanceFromPrevious; };
	double ComputeDistanceFromPrevious(V3 newCenter) const;
protected:
	virtual void MakeVertices(int i) override;
	virtual void MakeNormals() override;
	virtual void MakeTriangleVertexIndices(int i) override;
};

Gear3D::Gear3D(V3 center, double radius, int numTeeth, double width = 30.0)
	: Gear(center, radius, numTeeth), GearWidth(width)
{
	assert(radius > 0);

	if (LastLink == nullptr) {
		//cout << "FIRST GEAR" << endl;
		ThisIsFirstGear();
	}
	else 
	{
		//cout << "NOT FIRST GEAR. LastLink.Radius: " << LastLink->Radius << endl;
		NewGearFromCenter(center);
	}
};

Gear3D::Gear3D(V3 center) : Gear3D(center, FIRST_GEAR_RADIUS, FIRST_GEAR_NUMTEETH) // Use placeholder values // TODO: fix
{ };

Gear3D* Gear3D::LastLink = nullptr;

void Gear3D::ThisIsFirstGear()
{
	RotationFactor = 1;
	DistanceFromPrevious = 0;

	Radius = FIRST_GEAR_RADIUS;
	ToothWidth_Unit = 2 * pi / (2 * FIRST_GEAR_NUMTEETH);
	ToothWidth = ToothWidth_Unit * Radius;
	OuterRadius = Radius + ToothWidth;
	NumSpokes = 2.0 * pi * Radius / ToothWidth;
	NumTeeth = NumSpokes / 2;

	assert(OuterRadius >= Radius);
	assert(Radius > 0);
	assert(ToothWidth > 0);
	
	LastLink = this;
}

void Gear3D::NewGearFromCenter(V3 center)
{
	DistanceFromPrevious = ComputeDistanceFromPrevious(center);
	if (abs(DistanceFromPrevious - 0) < 0.0001) { // Safeguard
		//cout << "!!!!DistanceFromPrevious: " << DistanceFromPrevious << endl;
		Radius = FIRST_GEAR_RADIUS;
		ToothWidth = LastLink->ToothWidth;
		OuterRadius = Radius + ToothWidth;
	}
	else 
	{
		OuterRadius = DistanceFromPrevious - LastLink->Radius;
		ToothWidth = LastLink->ToothWidth; // Copy tooth width from last Gear
		Radius = OuterRadius - ToothWidth;
	}
	NumSpokes = 2.0 * pi * Radius / ToothWidth;
	NumTeeth = NumSpokes / 2;
	RotationFactor = -LastLink->RotationFactor;

	//cout << "DistanceFromPrevious: " << DistanceFromPrevious << " LastLink->Radius: " << LastLink->Radius << endl;
	//cout << "OuterRadius: " << OuterRadius << " Radius: " << Radius << endl;
	//cout << "ToothWidth: " << ToothWidth << "\n" << endl;
	assert(Radius > 0);
	assert(ToothWidth > 0);
	assert(OuterRadius >= Radius);
}

double Gear3D::ComputeDistanceFromPrevious(V3 newCenter) const {
	V3 oldCenter = LastLink->Center;
	//cout << "xNEW: " << newCenter.X << " yNEW: " << newCenter.Y << " zNEW: " << newCenter.Z << endl;
	//cout << "xOLD: " << oldCenter.X << " yOLD: " << oldCenter.Y << " zOLD: " << oldCenter.Z << endl;
	
	double aSquared = pow(oldCenter.X - newCenter.X, 2.0);
	double bSquared = pow(oldCenter.Y - newCenter.Y, 2.0);
	double cSquared = pow(oldCenter.Z - newCenter.Z, 2.0);
	//cout << "a2: " << aSquared << " b2: " << bSquared << " c2: " << cSquared << endl;
	return sqrt(aSquared + bSquared + cSquared);
};

void Gear3D::MakeVertices(int i)
{
	double theta = GetThetaAtIthSpoke(i - 1);
	double cT = cos(theta);
	double sT = sin(theta);

	// Create vertices for front of gear
	Vertices.PUSH(V3(0 + Center.X, Radius * cT, Radius * sT));
	Vertices.PUSH(V3(0 + Center.X, OuterRadius * cT, OuterRadius * sT));
	// Create Vertices for back of gear
	Vertices.PUSH(V3(-GearWidth, OuterRadius * cT, OuterRadius * sT));
	Vertices.PUSH(V3(-GearWidth, Radius * cT, Radius * sT));
}

void Gear3D::MakeNormals()
{
	Normals.PUSH(V3(1, 0, 0));
	Normals.PUSH(V3(1, 0, 0));
	Normals.PUSH(V3(1, 0, 0));
	Normals.PUSH(V3(1, 0, 0));
}

void Gear3D::MakeTriangleVertexIndices(int i)
{
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
			// Neighbor's outer vertex, Outer vertex
			// Triangles all sharing vertex 0, the center point
			AddTri(even6, even2, 0);
			// Make 2 tris for outer face of tooth
			AddTri(even6, even7, even3);
			AddTri(even3, even2, even6);
			// Make 2 tris for cw side of tooth
			AddTri(even1, even2, even4);
			AddTri(even2, even3, even4);
			// Make 2 tris for ccw side of tooth
			AddTri(even8, even7, even6);
			AddTri(even5, even8, even6);
		}
		else // Gap between gear teeth
		{
			// Make gear face triangle
			AddTri(0, odd3, odd1);
			// Make 2 tris for outer face of gap
			AddTri(odd3, odd4, odd1);
			AddTri(odd1, odd4, odd2);
		}
	}
	else if (i == NumTeeth * 2) {
		// Last triangle face, clockwise, a gap
		AddTri(0, 1, odd1);
		// Make 2 tris for outer face of gap
		AddTri(1, 4, odd1);
		AddTri(odd1, 4, odd2);
	}
}

}; // namespace GenerativeGeometry