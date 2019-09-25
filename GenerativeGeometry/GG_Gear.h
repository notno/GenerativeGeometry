#pragma once

#include "GG_Circle.h"

namespace GenerativeGeometry {

class Gear : public Circle {

public:
	Gear(V3 center, double radius, int numTeeth) :
		Circle(center, radius, numTeeth * 2),
		NumTeeth(numTeeth), ToothWidth_Unit(ComputeToothWidth_Unit()) {}
	void Generate() override { MakeTriangles(); }

	int GetNumTeeth() const { return NumTeeth; };
	void SetNumTeeth(int nT) { NumTeeth = nT; };
	
	double GetToothWidth_Unit() const { return ToothWidth_Unit; };
	void SetToothWidth_Unit(double tWU) { ToothWidth_Unit = tWU; };
	
	double GetToothWidth() const { return ToothWidth; }
	//GetToothWidth_Unit()* GetRadius();

	int GetRotationFactor() const { return RotationFactor; };
	void SetRotationFactor(int f) { RotationFactor = f; };

protected:
	int RotationFactor = 1;
	double ToothWidth_Unit = 2*pi/NumSpokes;
	double ToothWidth = 2*pi*Radius/NumSpokes;
	int NumTeeth = FIRST_GEAR_NUMTEETH;
	double OuterRadius= Radius + ToothWidth;

	double ComputeToothWidth_Unit() const {
		return 2.0 * pi / (NumTeeth * 2.0);
	};
};


}