#pragma once
#include "GG_Gear.h"
#include "GG_Math.h"
#include <iostream>
#include <vector>
#include <assert.h>
#include <exception>

using std::vector;

namespace GenerativeGeometry { 

class Gear3D : public Gear {
	double Depth;
public:
	Gear3D(V3 center, double radius, int numTeeth, double depth);
	Gear3D(V3 center, double radius, int numTeeth, double depth, int rotation);
	Gear3D(V3 center, double radius, double outerRadius, int numTeeth, double toothWidth, int rotationFactor, double depth);
	Gear3D(); // Only for Google Test
	double GetDepth() const { 
		return Depth; 
	};

protected:
	void MakeVertices(int i) override;
	void MakeNormals() override;
	void MakeTriangleVertexIndices(int i) override;

private:
	class Gear3DFactory {
	public:
		static Gear3D GearFromPrevious(V3 center, const Gear3D& previous);
	};
public: 
	static Gear3DFactory Factory;
};

}; // namespace GenerativeGeometry

