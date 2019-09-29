#pragma once

#include "GG_Circle.h"

namespace GenerativeGeometry {

class Gear : public Circle {

public:
	Gear(V3 center, double radius, int numTeeth) :
		Circle(center, radius, numTeeth * 2),
		ToothWidth(2.0 * pi * radius / (numTeeth * 2.0)) 
	{
		OuterRadius = radius + ToothWidth;
	}

	Gear(V3 center, double radius, double oR, int nT, double tW,int rF) :
		Circle(center, radius, nT * 2),
		ToothWidth(tW),
		OuterRadius(oR),
		RotationFactor(rF)
	{}

	void Generate() override { MakeTriangles(); }

	int GetNumTeeth() const { 
		return NumSpokes/2; 
	};
	void SetNumTeeth(int nT) { NumSpokes = nT*2; };
	
	double GetToothWidth() const { return ToothWidth; }

	int GetRotationFactor() const { return RotationFactor; };
	void SetRotationFactor(int f) { RotationFactor = f; };

protected:
	int RotationFactor = 1;
	double ToothWidth; // = 2 * pi * Radius / NumSpokes;
	double OuterRadius;// = Radius + ToothWidth;
};


}