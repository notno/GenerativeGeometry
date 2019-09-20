#pragma once
#include "GG_Geometry.h"

namespace GenerativeGeometry {

class Gear2D : Circle {
	int numTeeth;
public:
	Gear2D(int numTeeth) :numTeeth(numTeeth) {};
protected:
	virtual void Draw() override {};
	virtual void MakeTriangles() override {
		Vertices.push_back(GetCenter());
		Normals.push_back(vec3{ 1, 0, 0 });

		// Iterate through all spokes (numTeeth*2)
		//for (int i = 1; i <= numTeeth * 2; i++) {
		//	double theta = getTheta(i - 1);
		//	float cT = cos(theta);
		//	float sT = sin(theta);
		//	// TODO assure that this order is maintained
		//	// Create vertices for front of gear
		//	vertices.Add(FVector(0, innerRadius * cT, innerRadius * sT));
		//	vertices.Add(FVector(0, outerRadius * cT, outerRadius * sT));
		//	// Create vertices for back of gear
		//	vertices.Add(FVector(-gearWidth, outerRadius * cT, outerRadius * sT));
		//	vertices.Add(FVector(-gearWidth, innerRadius * cT, innerRadius * sT));

		//	// Storing indices of vertices for easy use when making triangles
		//	// Using "even" for even numbered spokes, "odd" for odd spokes
		//	int even4 = 4 * i,
		//		even3 = even4 - 1,
		//		even2 = even4 - 2,
		//		even1 = even4 - 3,
		//		even8 = 4 * (i + 1),
		//		even7 = even8 - 1,
		//		even6 = even8 - 2,
		//		even5 = even8 - 3,
		//		odd1 = even1,
		//		odd2 = even4,
		//		odd3 = even5,
		//		odd4 = even8;

		//	if (i < numTeeth * 2) {
		//		if ((i & 1) == 1) { // Gear tooth
		//			// Make gear face triangle for tooth
		//			trianglePoints.Add(even6); // Neighbor's outer vertex
		//			trianglePoints.Add(even2); // Outer vertex
		//			trianglePoints.Add(0);     // Triangles all sharing vertex 0, the center point
		//			// Make 2 tris for outer face of tooth
		//			trianglePoints.Add(even6);
		//			trianglePoints.Add(even7);
		//			trianglePoints.Add(even3);
		//			trianglePoints.Add(even3);
		//			trianglePoints.Add(even2);
		//			trianglePoints.Add(even6);
		//			// Make 2 tris for cw side of tooth
		//			trianglePoints.Add(even1);
		//			trianglePoints.Add(even2);
		//			trianglePoints.Add(even4);
		//			trianglePoints.Add(even2);
		//			trianglePoints.Add(even3);
		//			trianglePoints.Add(even4);
		//			// Make 2 tris for ccw side of tooth
		//			trianglePoints.Add(even8);
		//			trianglePoints.Add(even7);
		//			trianglePoints.Add(even6);
		//			trianglePoints.Add(even5);
		//			trianglePoints.Add(even8);
		//			trianglePoints.Add(even6);
		//		}
		//		else // Gap between gear teeth
		//		{
		//			// Make gear face triangle
		//			trianglePoints.Add(0);
		//			trianglePoints.Add(odd3); // Inner vertex
		//			trianglePoints.Add(odd1); // Neighbor's inner vertex 
		//			// Make 2 tris for outer face of gap
		//			trianglePoints.Add(odd3);
		//			trianglePoints.Add(odd4);
		//			trianglePoints.Add(odd1);
		//			trianglePoints.Add(odd1);
		//			trianglePoints.Add(odd4);
		//			trianglePoints.Add(odd2);
		//		}
		//	}
		//	else if (i == numTeeth * 2) {
		//		// Last triangle face, clockwise, a gap
		//		trianglePoints.Add(0);
		//		trianglePoints.Add(1);
		//		trianglePoints.Add(odd1);
		//		// Make 2 tris for outer face of gap
		//		trianglePoints.Add(1);
		//		trianglePoints.Add(4);
		//		trianglePoints.Add(odd1);
		//		trianglePoints.Add(odd1);
		//		trianglePoints.Add(4);
		//		trianglePoints.Add(odd2);
		//	}

		//	normals.Add(FVector(1, 0, 0));
		//	normals.Add(FVector(1, 0, 0));
		//	normals.Add(FVector(1, 0, 0));
		//	normals.Add(FVector(1, 0, 0));
		//	UV0.Add(uvAtI(i)); // TODO: Understand weird striping
		//	UV0.Add(uvAtI(i));
		//	UV0.Add(uvAtI(i));
		//	UV0.Add(uvAtI(i));
		//	tangents.Add(FProcMeshTangent(0, 1, 0));
		//	tangents.Add(FProcMeshTangent(0, 1, 0));
		//	tangents.Add(FProcMeshTangent(0, 1, 0));
		//	tangents.Add(FProcMeshTangent(0, 1, 0));
		//	vertexColors.Add(FLinearColor(0.75, 0, 0, 1.0));
		//	vertexColors.Add(FLinearColor(0.75, 0, 0, 1.0));
		//	vertexColors.Add(FLinearColor(0.75, 0, 0, 1.0));
		//	vertexColors.Add(FLinearColor(0.75, 0, 0, 1.0));
		//}
	};

	//int GetNumTeeth() const {
	//	return teeth.size();
	//};

	//double GetToothWidthUnit() const {
	//	return 2.0 * pi() / (numTeeth * 2.0);
	//};

	//double GetToothWidth() const {
	//	return GetToothWidthUnit() * innerRadius;
	//}

};

class Gear3D : Gear2D {

public:
	Gear3D(int numTeeth) : Gear2D(numTeeth) {};
protected:
	virtual void Draw() override {};
}; //What if it was the answer.

}