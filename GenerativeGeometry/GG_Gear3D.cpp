#include "GG_Gear3D.h"

GenerativeGeometry::Gear3D GenerativeGeometry::Gear3D::Gear3DFactory::GearFromPrevious(V3 center, const Gear3D& previous) {
	double distanceFromPrevious = Math::Distance<V3>(center, previous.Center);
	if (distanceFromPrevious < previous.Radius) { throw("too close"); }

	double outerRadius = distanceFromPrevious - previous.Radius;
	double toothWidth = previous.ToothWidth; // Copy tooth width from last Gear
	double radius = outerRadius - toothWidth;
	double diameter = 2.0 * pi * radius;
	int numSpokes = floor(diameter / toothWidth);
	radius = numSpokes * toothWidth / (2.0 * pi); 
	outerRadius = radius + toothWidth;
	int numTeeth = numSpokes / 2;
	int rotationFactor = -previous.RotationFactor;

	return Gear3D(center, radius, outerRadius, numTeeth, toothWidth, rotationFactor, previous.Depth);
}

GenerativeGeometry::Gear3D::Gear3D(V3 center, double radius, double oR, int nT, double tW, int rF, double depth) : 
	Gear(center,radius,oR,nT,tW,rF),
	Depth(depth) 
{
	assert(radius > 0);
	assert(OuterRadius >= Radius);
	assert(ToothWidth > 0);
}


GenerativeGeometry::Gear3D::Gear3D(V3 center, double radius, int numTeeth, double depth) :
	Gear(center, radius, numTeeth), 
	Depth(depth)
{
	assert(radius > 0);
	assert(OuterRadius >= Radius);
	assert(ToothWidth > 0);
};

GenerativeGeometry::Gear3D::Gear3D(V3 center, double radius, int numTeeth, double depth, int rotation) :
	Gear3D(center, radius, numTeeth, depth) 
{
	RotationFactor = rotation;
};

// Default initializer with no args just for Google Test
GenerativeGeometry::Gear3D::Gear3D() : Gear3D( V3(0), DEFAULT_RADIUS, DEFAULT_NUMSPOKES/2, 30, 1) {};

void GenerativeGeometry::Gear3D::MakeVertices(int i)
{
	double theta = GetThetaAtIthSpoke(i - 1);
	double cT = cos(theta);
	double sT = sin(theta);

	// Create vertices for front of gear
	Vertices.PUSH(V3(0 + Center.X, Radius * cT, Radius * sT));
	Vertices.PUSH(V3(0 + Center.X, OuterRadius * cT, OuterRadius * sT));
	// Create Vertices for back of gear
	Vertices.PUSH(V3(-Depth, OuterRadius * cT, OuterRadius * sT));
	Vertices.PUSH(V3(-Depth, Radius * cT, Radius * sT));
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

	if (i < NumSpokes) {
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
	else if (i == NumSpokes) {
		// Last triangle face, clockwise, a gap
		AddTri(0, 1, odd1);
		// Make 2 tris for outer face of gap
		AddTri(1, 4, odd1);
		AddTri(odd1, 4, odd2);
	}
}