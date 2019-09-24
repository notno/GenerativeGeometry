#include "pch.h"

#include <iostream>
#include <cmath>

#include "../GenerativeGeometry/GG_Math.h"
#include "../GenerativeGeometry/GG_Geometry.h"
#include "../GenerativeGeometry/GG_Circle.h"
#include "../GenerativeGeometry/GG_Gear2D.h"
#include "../GenerativeGeometry/GG_Gear3D.h"
#include "../GenerativeGeometry/GG_Chain.h"

using GenerativeGeometry::vec3;
using std::vector;

TEST(Chain, ShouldRevealCorrectNumberOfGears) {
	auto chain = GenerativeGeometry::Chain::Chain();
	auto gear1 = GenerativeGeometry::Gear3D(vec3(0.0, 0.0, 0.0), 10, 16);
	chain.AddGear3D(&gear1);
	auto gear2 = GenerativeGeometry::Gear3D(vec3(0.0, 0.0, 0.0), 10, 16);
	chain.AddGear3D(&gear2);
	auto gear3 = GenerativeGeometry::Gear3D(vec3(0.0, 0.0, 0.0), 10, 16);
	chain.AddGear3D(&gear3);
	EXPECT_EQ(chain.GetChainLength(), 3);
}

TEST(Chain, ShouldAlternateRotationFactor) {
	auto chain = GenerativeGeometry::Chain::Chain();
	auto gear1 = GenerativeGeometry::Gear3D(vec3(0.0, 0.0, 0.0), 10, 16);
	chain.AddGear3D(&gear1);
	auto gear2 = GenerativeGeometry::Gear3D(vec3(0.0, 0.0, 0.0), 10, 16);
	chain.AddGear3D(&gear2);
	auto gear3 = GenerativeGeometry::Gear3D(vec3(0.0, 0.0, 0.0), 10, 16);
	chain.AddGear3D(&gear3);
	EXPECT_EQ(gear1.GetRotFactor(), 1);
	EXPECT_EQ(gear2.GetRotFactor(), -1);
	EXPECT_EQ(gear3.GetRotFactor(), 1);
}

TEST(RandRangeInt, ProbablyDoesntProduceBadResults) {
  EXPECT_LT(GenerativeGeometry::Math::RandRangeInt(20,30), 31);
  EXPECT_GT(GenerativeGeometry::Math::RandRangeInt(1, 2), 0);
  EXPECT_EQ(GenerativeGeometry::Math::RandRangeInt(1, 1), 1);
}

TEST(Circle, ShouldInitializeToZeros) {
	auto circle = GenerativeGeometry::Circle();
	EXPECT_EQ(circle.GetCenter().X, 0.0);
}

TEST(Circle, ShouldMakeGoodVertices) {
	auto circle = GenerativeGeometry::Circle(vec3( 0.0,0.0,0.0 ), 10.0, 16);
	circle.Generate();
	EXPECT_EQ(circle.GetVertexAt(0).X, 0.0);
	EXPECT_FLOAT_EQ(circle.GetVertexAt(1).Y, 10.0);
	auto w = floor(circle.GetVertexAt(16).Y);
	EXPECT_EQ( w, 9);
	EXPECT_EQ(circle.GetCenter().X, 0.0);
}
TEST(Circle, ShouldMakeGoodTriangles) {
	auto circle = GenerativeGeometry::Circle(vec3( 0.0,0.0,0.0 ), 10.0, 16);
	circle.Generate();
	EXPECT_EQ(circle.GetTriangleAt(0),2);
	EXPECT_EQ(circle.GetTriangleAt(1),1);
	EXPECT_EQ(circle.GetTriangleAt(2),0);
	EXPECT_EQ(circle.GetTriangleAt(16*3-2),16);
}
TEST(Circle, ShouldMakePredictableNormals) {
	auto circle = GenerativeGeometry::Circle(vec3( 1.0,9.0,3.0 ), 1320.0, 32);
	circle.Generate();
	EXPECT_EQ(circle.GetNormalAt(0).X, 1);
	EXPECT_EQ(circle.GetNormalAt(0).Y, 0);
	EXPECT_EQ(circle.GetNormalAt(0).Z, 0);
}
TEST(Circle, ShouldHaveRightNumberOfVerts) {
	auto circle = GenerativeGeometry::Circle(vec3( 1.0,9.0,3.0 ), 1320.0, 32);
	circle.Generate();
	EXPECT_EQ(circle.GetNumVerts(), 33);
}




TEST(Gear2D, ShouldHaveRightNumberOfTeeth) {
	auto gear = GenerativeGeometry::Gear2D(vec3( 0.0,0.0,0.0 ), 10, 16);
	gear.Generate();
	EXPECT_EQ(gear.GetNumTeeth(), 16);
}

//TEST(Gears, ShouldHaveProperToothWidthUnit){}
TEST(Gears, ShouldHaveProperToothWidth){
	GenerativeGeometry::Gear2D gear(vec3(), 55.0, 32);
	gear.Generate();
	EXPECT_FLOAT_EQ(gear.GetToothWidth(), 5.3996124);
	
}

TEST(Gear2D, ShouldHaveRightNumberOfSpokes) {
	auto gear = GenerativeGeometry::Gear2D(vec3( 0.0,0.0,0.0 ), 10, 16);
	gear.Generate();
	EXPECT_EQ(gear.GetNumSpokes(), 32);
}

TEST(Gear2D, ShouldHaveRightNumberOfVertices) {
	auto gear = GenerativeGeometry::Gear2D(vec3( 0.0,0.0,0.0 ), 10, 16);
	gear.Generate();
	// 1 vert for center + 2*numSpokes, where numSpokes = 2*numTeeth  
	EXPECT_EQ(gear.GetNumVerts(), 1 + gear.GetNumTeeth() * 4);
}

TEST(Gear2D, ShouldGetRightNumberOfVertsPublicly) {
	auto gear = GenerativeGeometry::Gear2D(vec3( 0.0,0.0,0.0 ), 10, 16);
	gear.Generate();
	EXPECT_EQ(gear.GetVertices().size(), 65);
}

TEST(Gear2D, ShouldHaveRightNumberOfNormals) {
	auto gear = GenerativeGeometry::Gear2D(vec3( 0.0,0.0,0.0 ), 10, 16);
	gear.Generate();
	EXPECT_EQ(gear.GetNumNormals(), gear.GetNumVerts());
}

TEST(Gear2D, ShouldHaveRightNumberOfTriangleVertices) {
	auto gear = GenerativeGeometry::Gear2D(vec3( 0.0,0.0,0.0 ), 10, 16);
	gear.Generate();
	// Each tooth zone = 3 vert indices for 1 triangles
	// Each gap zone = 3 vert indices for 1 triangles
	// Therefor: numSpokes * 3
	EXPECT_EQ(gear.GetNumTriangleVertIndices(), 96);
}

TEST(Gear3D, ShouldHaveRightNumberOfTriangleVertices) {
	auto gear = GenerativeGeometry::Gear3D(vec3( 0.0,0.0,0.0 ), 10, 16);
	gear.Generate();
	// Tooth zone = 7 triangles = 21 vertices
	// Gap zone = 3 triangles
	EXPECT_EQ(gear.GetNumTriangleVertIndices(), 21*16 + 9*16);
}

//Circle, ShouldHaveMoreThanTwoEdges
//Gear2D, ShouldHaveMoreThanOneTeeth
//Gear3D, ShouldHaveMoreThanOneTeeth