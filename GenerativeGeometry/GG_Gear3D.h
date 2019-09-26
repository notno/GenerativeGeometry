#pragma once
#include "GG_Gear.h"
#include <iostream>
#include <assert.h>
#include <exception>

//#define NDEBUG
namespace GenerativeGeometry {

	class Gear3D : public Gear {
		static Gear3D* LastLink;
		Gear3D* MyPreviousLink = nullptr;
		double GearWidth = 30.0;
		double DistanceFromPrevious = 500; // Mostly for testing
	public:
		Gear3D();
		Gear3D(V3 center);
		Gear3D(V3 center, double radius, int numTeeth, double width);
		void ThisIsFirstGear();
		void NewGearFromCenter(V3 center);
		double GetGearWidth() const { return GearWidth; };
		double GetDistanceFromPrevious() const { return DistanceFromPrevious; };
		double ComputeDistanceFromPrevious(V3 newCenter) const;
	protected:
		virtual void MakeVertices(int i) override;
		virtual void MakeNormals() override;
		virtual void MakeTriangleVertexIndices(int i) override;
	};

}; // namespace GenerativeGeometry

