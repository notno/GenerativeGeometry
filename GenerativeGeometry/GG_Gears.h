#pragma once
#include "GG_Circle.h"

namespace GenerativeGeometry {

class Gear2D : public Circle {
	int NumTeeth;
	double ToothWidthUnit;
	double GearWidth;

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
	double GetGearWidth() const {
		return GearWidth;
	};

protected:
	double SetToothWidthUnit(double) const {
		return 2.0 * pi / (NumTeeth * 2.0);
	};

	virtual void MakeTriangles() override {
		auto center = GetCenter();
		auto radius = GetRadius();
		auto outerRadius = radius + GetToothWidth();

		Vertices.PUSH(GetCenter());
		Normals.PUSH(V3(1, 0, 0));

		// Iterate through all spokes (NumTeeth*2)
		for (int i = 1; i <= NumTeeth * 2; i++) {
			double theta = GetThetaAtIthSpoke(i - 1);
			double cT = cos(theta);
			double sT = sin(theta);

			// Create vertices for front of gear
			Vertices.PUSH(V3(0 + center.X, radius * cT, radius * sT));
			Vertices.PUSH(V3(0 + center.X, outerRadius * cT, outerRadius * sT));
			
			// Create placeholder normals, 1 for each vert
			Normals.PUSH(V3(1, 0, 0));
			Normals.PUSH(V3(1, 0, 0));

			MakeGearTriangleVerts2D(i);

		//  TODO: Add support for UV coordinates, tangents, vert colors
		//	UV0.Add(uvAtI(i)); 
		//	UV0.Add(uvAtI(i));
		//	tangents.Add(FProcMeshTangent(0, 1, 0));
		//	tangents.Add(FProcMeshTangent(0, 1, 0));
		//	vertexColors.Add(FLinearColor(0.75, 0, 0, 1.0));
		//	vertexColors.Add(FLinearColor(0.75, 0, 0, 1.0));
		}
	};

	void MakeGearTriangleVerts2D(int i) {
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
			AddTri(0, 1, 2*i);
		}
	}
}; 

//class Gear3D : Gear2D {
//
//public:
//	//Gear3D(int NumTeeth) : Gear2D(NumTeeth) {};
//
//protected:
//virtual void MakeTriangles() override {
//	auto center = GetCenter();
//	auto radius = GetRadius();
//	auto outerRadius = radius + GetToothWidth();
//
//	Vertices.PUSH(GetCenter());
//	Normals.PUSH(V3{ 1, 0, 0 });
//
//	// Iterate through all spokes (NumTeeth*2)
//	for (int i = 1; i <= NumTeeth * 2; i++) {
//		double theta = GetThetaAtIthSpoke(i - 1);
//		double cT = cos(theta);
//		double sT = sin(theta);
//
//		// Create vertices for front of gear
//		Vertices.PUSH(V3{ 0 + center.X, radius * cT, radius * sT });
//		Vertices.PUSH(V3{ 0 + center.X, outerRadius * cT, outerRadius * sT });
//		// Create Vertices for back of gear
//		Vertices.PUSH(V3{ -GearWidth, outerRadius * cT, outerRadius * sT });
//		Vertices.PUSH(V3{ -GearWidth, radius * cT, radius * sT });
//
//		MakeGearTriangleVerts2D(i);
//
//		Normals.PUSH(V3{ 1, 0, 0 });
//		Normals.PUSH(V3{ 1, 0, 0 });
//		Normals.PUSH(V3{ 1, 0, 0 });
//		Normals.PUSH(V3{ 1, 0, 0 });
//		//	UV0.Add(uvAtI(i)); // TODO: Understand weird striping
//		//	UV0.Add(uvAtI(i));
//		//	UV0.Add(uvAtI(i));
//		//	UV0.Add(uvAtI(i));
//		//	tangents.Add(FProcMeshTangent(0, 1, 0));
//		//	tangents.Add(FProcMeshTangent(0, 1, 0));
//		//	tangents.Add(FProcMeshTangent(0, 1, 0));
//		//	tangents.Add(FProcMeshTangent(0, 1, 0));
//		//	vertexColors.Add(FLinearColor(0.75, 0, 0, 1.0));
//		//	vertexColors.Add(FLinearColor(0.75, 0, 0, 1.0));
//		//	vertexColors.Add(FLinearColor(0.75, 0, 0, 1.0));
//		//	vertexColors.Add(FLinearColor(0.75, 0, 0, 1.0));
//	}
//};

//	void MakeGearTriangleVerts3D(int i) {
//		// Storing indices of Vertices for easy use when making triangles
//		// Using "even" for even numbered spokes, "odd" for odd spokes
//		int even4 = 4 * i,
//			even3 = even4 - 1,
//			even2 = even4 - 2,
//			even1 = even4 - 3,
//			even8 = 4 * (i + 1),
//			even7 = even8 - 1,
//			even6 = even8 - 2,
//			even5 = even8 - 3,
//			odd1 = even1,
//			odd2 = even4,
//			odd3 = even5,
//			odd4 = even8;
//
//		if (i < NumTeeth * 2) {
//			if ((i & 1) == 1) { // Gear tooth
//				// Make gear face triangle for tooth
//				TriangleVerts.PUSH(even6); // Neighbor's outer vertex
//				TriangleVerts.PUSH(even2); // Outer vertex
//				TriangleVerts.PUSH(0);     // Triangles all sharing vertex 0, the center point
//				// Make 2 tris for outer face of tooth
//				TriangleVerts.PUSH(even6);
//				TriangleVerts.PUSH(even7);
//				TriangleVerts.PUSH(even3);
//				TriangleVerts.PUSH(even3);
//				TriangleVerts.PUSH(even2);
//				TriangleVerts.PUSH(even6);
//				// Make 2 tris for cw side of tooth
//				TriangleVerts.PUSH(even1);
//				TriangleVerts.PUSH(even2);
//				TriangleVerts.PUSH(even4);
//				TriangleVerts.PUSH(even2);
//				TriangleVerts.PUSH(even3);
//				TriangleVerts.PUSH(even4);
//				// Make 2 tris for ccw side of tooth
//				TriangleVerts.PUSH(even8);
//				TriangleVerts.PUSH(even7);
//				TriangleVerts.PUSH(even6);
//				TriangleVerts.PUSH(even5);
//				TriangleVerts.PUSH(even8);
//				TriangleVerts.PUSH(even6);
//			}
//			else // Gap between gear teeth
//			{
//				// Make gear face triangle
//				TriangleVerts.PUSH(0);
//				TriangleVerts.PUSH(odd3); // Inner vertex
//				TriangleVerts.PUSH(odd1); // Neighbor's inner vertex 
//				// Make 2 tris for outer face of gap
//				TriangleVerts.PUSH(odd3);
//				TriangleVerts.PUSH(odd4);
//				TriangleVerts.PUSH(odd1);
//				TriangleVerts.PUSH(odd1);
//				TriangleVerts.PUSH(odd4);
//				TriangleVerts.PUSH(odd2);
//			}
//		}
//		else if (i == NumTeeth * 2) {
//			// Last triangle face, clockwise, a gap
//			TriangleVerts.PUSH(0);
//			TriangleVerts.PUSH(1);
//			TriangleVerts.PUSH(odd1);
//			// Make 2 tris for outer face of gap
//			TriangleVerts.PUSH(1);
//			TriangleVerts.PUSH(4);
//			TriangleVerts.PUSH(odd1);
//			TriangleVerts.PUSH(odd1);
//			TriangleVerts.PUSH(4);
//			TriangleVerts.PUSH(odd2);
//		}
//	}

//};  

}; // namespace GenerativeGeometry