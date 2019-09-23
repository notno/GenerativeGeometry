#pragma once
#include "GG_Circle.h"

namespace GenerativeGeometry {

class Gear2D : public Circle {
	int NumTeeth;
	double ToothWidthUnit;
	double GearWidth;

public:
	Gear2D(vec3 center, double radius, int numTeeth, double width = 30.0) : 
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

		Vertices.push_back(GetCenter());
		Normals.push_back(vec3(1, 0, 0));

		// Iterate through all spokes (NumTeeth*2)
		for (int i = 1; i <= NumTeeth * 2; i++) {
			double theta = GetThetaAtIthSpoke(i - 1);
			double cT = cos(theta);
			double sT = sin(theta);

			// Create vertices for front of gear
			Vertices.push_back(vec3(0 + center.X, radius * cT, radius * sT));
			Vertices.push_back(vec3(0 + center.X, outerRadius * cT, outerRadius * sT));
			
			// Create placeholder normals, 1 for each vert
			Normals.push_back(vec3(1, 0, 0));
			Normals.push_back(vec3(1, 0, 0));

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
//	Vertices.push_back(GetCenter());
//	Normals.push_back(V3{ 1, 0, 0 });
//
//	// Iterate through all spokes (NumTeeth*2)
//	for (int i = 1; i <= NumTeeth * 2; i++) {
//		double theta = GetThetaAtIthSpoke(i - 1);
//		double cT = cos(theta);
//		double sT = sin(theta);
//
//		// Create vertices for front of gear
//		Vertices.push_back(V3{ 0 + center.X, radius * cT, radius * sT });
//		Vertices.push_back(V3{ 0 + center.X, outerRadius * cT, outerRadius * sT });
//		// Create Vertices for back of gear
//		Vertices.push_back(V3{ -GearWidth, outerRadius * cT, outerRadius * sT });
//		Vertices.push_back(V3{ -GearWidth, radius * cT, radius * sT });
//
//		MakeGearTriangleVerts2D(i);
//
//		Normals.push_back(V3{ 1, 0, 0 });
//		Normals.push_back(V3{ 1, 0, 0 });
//		Normals.push_back(V3{ 1, 0, 0 });
//		Normals.push_back(V3{ 1, 0, 0 });
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
//				TriangleVerts.push_back(even6); // Neighbor's outer vertex
//				TriangleVerts.push_back(even2); // Outer vertex
//				TriangleVerts.push_back(0);     // Triangles all sharing vertex 0, the center point
//				// Make 2 tris for outer face of tooth
//				TriangleVerts.push_back(even6);
//				TriangleVerts.push_back(even7);
//				TriangleVerts.push_back(even3);
//				TriangleVerts.push_back(even3);
//				TriangleVerts.push_back(even2);
//				TriangleVerts.push_back(even6);
//				// Make 2 tris for cw side of tooth
//				TriangleVerts.push_back(even1);
//				TriangleVerts.push_back(even2);
//				TriangleVerts.push_back(even4);
//				TriangleVerts.push_back(even2);
//				TriangleVerts.push_back(even3);
//				TriangleVerts.push_back(even4);
//				// Make 2 tris for ccw side of tooth
//				TriangleVerts.push_back(even8);
//				TriangleVerts.push_back(even7);
//				TriangleVerts.push_back(even6);
//				TriangleVerts.push_back(even5);
//				TriangleVerts.push_back(even8);
//				TriangleVerts.push_back(even6);
//			}
//			else // Gap between gear teeth
//			{
//				// Make gear face triangle
//				TriangleVerts.push_back(0);
//				TriangleVerts.push_back(odd3); // Inner vertex
//				TriangleVerts.push_back(odd1); // Neighbor's inner vertex 
//				// Make 2 tris for outer face of gap
//				TriangleVerts.push_back(odd3);
//				TriangleVerts.push_back(odd4);
//				TriangleVerts.push_back(odd1);
//				TriangleVerts.push_back(odd1);
//				TriangleVerts.push_back(odd4);
//				TriangleVerts.push_back(odd2);
//			}
//		}
//		else if (i == NumTeeth * 2) {
//			// Last triangle face, clockwise, a gap
//			TriangleVerts.push_back(0);
//			TriangleVerts.push_back(1);
//			TriangleVerts.push_back(odd1);
//			// Make 2 tris for outer face of gap
//			TriangleVerts.push_back(1);
//			TriangleVerts.push_back(4);
//			TriangleVerts.push_back(odd1);
//			TriangleVerts.push_back(odd1);
//			TriangleVerts.push_back(4);
//			TriangleVerts.push_back(odd2);
//		}
//	}

//};  

}; // namespace GenerativeGeometry