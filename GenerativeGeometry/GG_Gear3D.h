#pragma once
#include "GG_Gear2D.h"

namespace GenerativeGeometry {

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
			Vertices.PUSH(V3(0 + center.X, radius * cT, radius * sT));
			Vertices.PUSH(V3(0 + center.X, outerRadius * cT, outerRadius * sT));
			// Create Vertices for back of gear
			Vertices.PUSH(V3(-GearWidth, outerRadius * cT, outerRadius * sT));
			Vertices.PUSH(V3(-GearWidth, radius * cT, radius * sT));
		}

		virtual void MakeNormals() override
		{
			Normals.PUSH(V3(1, 0, 0));
			Normals.PUSH(V3(1, 0, 0));
			Normals.PUSH(V3(1, 0, 0));
			Normals.PUSH(V3(1, 0, 0));
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

	};

}; // namespace GenerativeGeometry