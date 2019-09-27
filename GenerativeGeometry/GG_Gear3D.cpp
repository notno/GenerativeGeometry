#include "GG_Gear3D.h"

GenerativeGeometry::Gear3D::Gear3D(V3 center, double radius, int numTeeth, Gear3D* previous, double width = 30.0)
	: Gear(center, radius, numTeeth), GearWidth(width), MyPreviousLink(previous)
{
	assert(radius > 0);

	if (MyPreviousLink == nullptr) {

		cout << "FIRST" << endl;
		ThisIsFirstGear();
	}
	else {

		cout << "NOT FIRST" << endl;
		NewGearFromCenter(center);
	}
};

// Use placeholder values // TODO: fix 
GenerativeGeometry::Gear3D::Gear3D(V3 center, Gear3D* previous) : Gear3D(center, FIRST_GEAR_RADIUS, FIRST_GEAR_NUMTEETH, previous)
{};

// Default initializer with no args just for Google Test
GenerativeGeometry::Gear3D::Gear3D() : Gear3D( V3(0), nullptr ) {};

void GenerativeGeometry::Gear3D::ThisIsFirstGear()
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
}

void GenerativeGeometry::Gear3D::NewGearFromCenter(V3 center)
{
	DistanceFromPrevious = ComputeDistanceFromPrevious(center);
	if (abs(DistanceFromPrevious - 0) < 0.0001) { // Safeguard
		Radius = FIRST_GEAR_RADIUS;
		ToothWidth = MyPreviousLink->ToothWidth;
		OuterRadius = Radius + ToothWidth;
	}
	else
	{
		OuterRadius = DistanceFromPrevious - MyPreviousLink->Radius;
		ToothWidth = MyPreviousLink->ToothWidth; // Copy tooth width from last Gear
		Radius = OuterRadius - ToothWidth;
	}
	NumSpokes = 2.0 * pi * Radius / ToothWidth;
	NumTeeth = NumSpokes / 2;
	RotationFactor = -MyPreviousLink->RotationFactor;

	assert(Radius > 0);
	assert(ToothWidth > 0);
	assert(OuterRadius >= Radius);
}

double GenerativeGeometry::Gear3D::ComputeDistanceFromPrevious(V3 newCenter) const {
	V3 oldCenter = MyPreviousLink->Center;

	double aSquared = pow(oldCenter.X - newCenter.X, 2.0);
	double bSquared = pow(oldCenter.Y - newCenter.Y, 2.0);
	double cSquared = pow(oldCenter.Z - newCenter.Z, 2.0);

	return sqrt(aSquared + bSquared + cSquared);
};

void GenerativeGeometry::Gear3D::MakeVertices(int i)
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

void GenerativeGeometry::Gear3D::MakeNormals()
{
	Normals.PUSH(V3(1, 0, 0));
	Normals.PUSH(V3(1, 0, 0));
	Normals.PUSH(V3(1, 0, 0));
	Normals.PUSH(V3(1, 0, 0));
}

void GenerativeGeometry::Gear3D::MakeTriangleVertexIndices(int i)
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