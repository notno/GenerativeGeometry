#pragma once
#include "GG_Gear.h"
#include <iostream>
#include <vector>
#include <assert.h>
#include <exception>

using std::vector;

namespace GenerativeGeometry {

class Gear3D : public Gear {
	double GearWidth = 30.0;
	double DistanceFromPrevious = 500; // Mostly for testing
public:
	Gear3D(V3 center, double radius, int numTeeth, Gear3D* previous , double width);
	Gear3D(V3 center, Gear3D* previous);
	Gear3D(); // Only for Google Test
	void ThisIsFirstGear();
	void NewGearFromCenter(V3 center);
	double GetGearWidth() const { return GearWidth; };
	double GetDistanceFromPrevious() const { return DistanceFromPrevious; };
	double ComputeDistanceFromPrevious(V3 newCenter) const;

protected:
	Gear3D* MyPreviousLink = nullptr;
	virtual void MakeVertices(int i) override;
	virtual void MakeNormals() override;
	virtual void MakeTriangleVertexIndices(int i) override;
};

}; // namespace GenerativeGeometry

