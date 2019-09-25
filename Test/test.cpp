#include "pch.h"

#include <iostream>
#include <cmath>

#include "../GenerativeGeometry/GG_Math.h"
#include "../GenerativeGeometry/GG_Geometry.h"
#include "../GenerativeGeometry/GG_Circle.h"
#include "../GenerativeGeometry/GG_Gear2D.h"
#include "../GenerativeGeometry/GG_Gear3D.h"
//#include "../GenerativeGeometry/GG_Chain.h"

using GenerativeGeometry::vec3;
using std::vector;
using std::cout;
using std::endl;
const double pi = 3.14159265358979323846;


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

TEST(Gear2D, ShouldHaveProperToothWidth){
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
	auto gear = GenerativeGeometry::Gear2D(vec3( 0.0,.0,0.0 ), 10, 16);
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

class Gear3DTest : public ::testing::Test, public GenerativeGeometry::Gear3D {
protected:
	Gear3DTest() {};
	void SetUp() override{
		gear0 = GenerativeGeometry::Gear3D(vec3());
		gear1 = GenerativeGeometry::Gear3D(vec3(0.0, 1000.0, 10.0));
		gear2 = GenerativeGeometry::Gear3D(vec3(0.0, 2200.0, 20.0));
		gear2.Generate();
		gear3 = GenerativeGeometry::Gear3D(vec3(0.0, 2700.0, 20.0));
		gear4 = GenerativeGeometry::Gear3D(vec3(0.0, 3000.0, 30.0));
		gear5 = GenerativeGeometry::Gear3D(vec3(0.0, 4000.0, 40.0));
		gear6 = GenerativeGeometry::Gear3D(vec3(0.0, 5500.0, 50.0));
	}
	GenerativeGeometry::Gear3D gear0; 
	GenerativeGeometry::Gear3D gear1; 
	GenerativeGeometry::Gear3D gear2; 
	GenerativeGeometry::Gear3D gear3;
	GenerativeGeometry::Gear3D gear4;
	GenerativeGeometry::Gear3D gear5;
	GenerativeGeometry::Gear3D gear6;
};


TEST_F(Gear3DTest, ShouldSetFirstGearRadiusAutomatically) {
	EXPECT_EQ(gear0.GetRadius(), 100.0);
}

TEST_F(Gear3DTest, ShouldHaveRightNumberOfTriangleVertices) {
	// Tooth zone = 7 triangles = 21 vertices
	// Gap zone = 3 triangles
	EXPECT_EQ(gear2.GetNumTriangleVertIndices(), 21 * 16 + 9 * 16);
}

TEST_F(Gear3DTest, ShouldComputeDistanceFromPrevious) {	
	EXPECT_FLOAT_EQ(gear2.GetDistanceFromPrevious(), 1000.0005);
	EXPECT_FLOAT_EQ(gear3.GetDistanceFromPrevious(), 2000.001);
}

TEST_F(Gear3DTest, ShouldComputeParamsFromDistanceToPrevious) {
	double tW = (2 * pi * 100 / 32);
	cout << tW << endl;
	double outerRadius2 = sqrt(101) - 10;
	cout << outerRadius2 << endl;
	double radius2 = outerRadius2 - tW;
	cout << radius2 << endl;
	EXPECT_EQ(gear2.GetToothWidth(), tW);
	EXPECT_EQ(gear2.GetRadius(), radius2);
}

TEST_F(Gear3DTest, ShouldAlternateRotationFactor) {
	int a = gear1.GetRotationFactor();
	EXPECT_EQ(gear2.GetRotationFactor(), -a);
	EXPECT_EQ(gear3.GetRotationFactor(), a);
	EXPECT_EQ(gear4.GetRotationFactor(), -a);
	EXPECT_EQ(gear5.GetRotationFactor(), a);
	EXPECT_EQ(gear6.GetRotationFactor(), -a);
}

TEST_F(Gear3DTest, ShouldHaveSameToothWidth) {
	EXPECT_EQ(gear1.GetToothWidth(), gear2.GetToothWidth());
}

//Circle, ShouldHaveMoreThanTwoEdges
//Gear2D, ShouldHaveMoreThanOneTeeth
//Gear3D, ShouldHaveMoreThanOneTeeth