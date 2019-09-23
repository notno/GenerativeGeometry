#include "pch.h"

#include <iostream>
#include <cmath>

#include "../GenerativeGeometry/GG_Math.h"
#include "../GenerativeGeometry/GG_Geometry.h"
#include "../GenerativeGeometry/GG_Circle.h"
#include "../GenerativeGeometry/GG_Gears.h"

using GenerativeGeometry::vec3;

TEST(RandRangeInt, ProbablyDoesntProduceBadResults) {
  EXPECT_LT(GenerativeGeometry::Math::RandRangeInt(20,30), 31);
  EXPECT_GT(GenerativeGeometry::Math::RandRangeInt(1, 2), 0);
  EXPECT_EQ(GenerativeGeometry::Math::RandRangeInt(1, 1), 1);
}

TEST(Circle, ShouldInitializeToZeros) {
	auto circle = GenerativeGeometry::Circle();
	EXPECT_EQ(circle.GetCenter().x, 0.0);
}

TEST(Circle, ShouldMakeGoodVertices) {
	auto circle = GenerativeGeometry::Circle(vec3{ 0.0,0.0,0.0 }, 10.0, 16);
	circle.Draw();
	EXPECT_EQ(circle.GetVertexAt(0).x, 0.0);
	EXPECT_FLOAT_EQ(circle.GetVertexAt(1).y, 10.0);
	auto w = floor(circle.GetVertexAt(16).y);
	EXPECT_EQ( w, 9);
	EXPECT_EQ(circle.GetCenter().x, 0.0);
}
TEST(Circle, ShouldMakeGoodTriangles) {
	auto circle = GenerativeGeometry::Circle(vec3{ 0.0,0.0,0.0 }, 10.0, 16);
	circle.Draw();
	EXPECT_EQ(circle.GetTriangleAt(0),2);
	EXPECT_EQ(circle.GetTriangleAt(1),1);
	EXPECT_EQ(circle.GetTriangleAt(2),0);
	EXPECT_EQ(circle.GetTriangleAt(16*3-2),16);
}
TEST(Circle, ShouldMakePredictableNormals) {
	auto circle = GenerativeGeometry::Circle(vec3{ 1.0,9.0,3.0 }, 1320.0, 32);
	circle.Draw();
	EXPECT_EQ(circle.GetNormalAt(0).x, 1);
	EXPECT_EQ(circle.GetNormalAt(0).y, 0);
	EXPECT_EQ(circle.GetNormalAt(0).z, 0);
}




TEST(Gears2D, ShouldHaveRightNumberOfTeeth) {
	auto gear = GenerativeGeometry::Gear2D(vec3{ 0.0,0.0,0.0 }, 10, 16);
	gear.Draw();
	EXPECT_EQ(gear.GetNumTeeth(), 16);
}

//TEST(Gears, ShouldHaveProperToothWidth){}

TEST(Gears2D, ShouldHaveRightNumberOfSpokes) {
	auto gear = GenerativeGeometry::Gear2D(vec3{ 0.0,0.0,0.0 }, 10, 16);
	gear.Draw();
	EXPECT_EQ(gear.GetNumSpokes(), 32);
}

TEST(Gears2D, ShouldHaveRightNumberOfVertices) {
	auto gear = GenerativeGeometry::Gear2D(vec3{ 0.0,0.0,0.0 }, 10, 16);
	gear.Draw();
	// 1 vert for center + 2*numSpokes, where numSpokes = 2*numTeeth  
	EXPECT_EQ(gear.GetNumVerts(), 1 + gear.GetNumTeeth() * 4);
}

TEST(Gears2D, ShouldHaveRightNumberOfNormals) {
	auto gear = GenerativeGeometry::Gear2D(vec3{ 0.0,0.0,0.0 }, 10, 16);
	gear.Draw();
	EXPECT_EQ(gear.GetNumNormals(), gear.GetNumVerts());
}

TEST(Gears2D, ShouldHaveRightNumberOfTriangles) {
	auto gear = GenerativeGeometry::Gear2D(vec3{ 0.0,0.0,0.0 }, 10, 16);
	gear.Draw();
	// Each tooth zone = 3 vert indices for 1 triangles
	// Each gap zone = 3 vert indices for 1 triangles
	// Therefor: numSpokes * 3
	EXPECT_EQ(gear.GetNumTriangleVerts(), 96);
}

//TEST(Gears3D, ShouldHaveRightNumberOfTriangles) {
//	auto gear = GenerativeGeometry::Gear2D(vec3{ 0.0,0.0,0.0 }, 10, 16);
//	gear.Draw();
//	// Tooth zone = 7 triangles
//	// Gap zone = 3 triangles
//	EXPECT_EQ(gear.GetNumTriangleVerts(), 7*16 + 3*16);
//}