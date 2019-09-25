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
//
//TEST(Circle, ShouldInitializeToZeros) {
//	auto circle = GenerativeGeometry::Circle();
//	EXPECT_EQ(circle.GetCenter().X, 0.0);
//}
//
//TEST(Circle, ShouldMakeGoodVertices) {
//	auto circle = GenerativeGeometry::Circle(vec3( 0.0,0.0,0.0 ), 10.0, 16);
//	circle.Generate();
//	EXPECT_EQ(circle.GetVertexAt(0).X, 0.0);
//	EXPECT_FLOAT_EQ(circle.GetVertexAt(1).Y, 10.0);
//	auto w = floor(circle.GetVertexAt(16).Y);
//	EXPECT_EQ( w, 9);
//	EXPECT_EQ(circle.GetCenter().X, 0.0);
//}
//TEST(Circle, ShouldMakeGoodTriangles) {
//	auto circle = GenerativeGeometry::Circle(vec3( 0.0,0.0,0.0 ), 10.0, 16);
//	circle.Generate();
//	EXPECT_EQ(circle.GetTriangleAt(0),2);
//	EXPECT_EQ(circle.GetTriangleAt(1),1);
//	EXPECT_EQ(circle.GetTriangleAt(2),0);
//	EXPECT_EQ(circle.GetTriangleAt(16*3-2),16);
//}
//TEST(Circle, ShouldMakePredictableNormals) {
//	auto circle = GenerativeGeometry::Circle(vec3( 1.0,9.0,3.0 ), 1320.0, 32);
//	circle.Generate();
//	EXPECT_EQ(circle.GetNormalAt(0).X, 1);
//	EXPECT_EQ(circle.GetNormalAt(0).Y, 0);
//	EXPECT_EQ(circle.GetNormalAt(0).Z, 0);
//}
//TEST(Circle, ShouldHaveRightNumberOfVerts) {
//	auto circle = GenerativeGeometry::Circle(vec3( 1.0,9.0,3.0 ), 1320.0, 32);
//	circle.Generate();
//	EXPECT_EQ(circle.GetNumVerts(), 33);
//}
// 
//
//
//TEST(Gear2D, ShouldHaveRightNumberOfTeeth) {
//	auto gear = GenerativeGeometry::Gear2D(vec3( 0.0,0.0,0.0 ), 10, 16);
//	gear.Generate();
//	EXPECT_EQ(gear.GetNumTeeth(), 16);
//}
//
//TEST(Gear2D, ShouldHaveProperToothWidth){
//	GenerativeGeometry::Gear2D gear(vec3(), 55.0, 32);
//	gear.Generate();
//	EXPECT_FLOAT_EQ(gear.GetToothWidth(), 5.3996124);	
//}
//
//TEST(Gear2D, ShouldHaveRightNumberOfSpokes) {
//	auto gear = GenerativeGeometry::Gear2D(vec3( 0.0,0.0,0.0 ), 10, 16);
//	gear.Generate();
//	EXPECT_EQ(gear.GetNumSpokes(), 32);
//}
//
//TEST(Gear2D, ShouldHaveRightNumberOfVertices) {
//	auto gear = GenerativeGeometry::Gear2D(vec3( 0.0,0.0,0.0 ), 10, 16);
//	gear.Generate();
//	// 1 vert for center + 2*numSpokes, where numSpokes = 2*numTeeth  
//	EXPECT_EQ(gear.GetNumVerts(), 1 + gear.GetNumTeeth() * 4);
//}
//
//TEST(Gear2D, ShouldGetRightNumberOfVertsPublicly) {
//	auto gear = GenerativeGeometry::Gear2D(vec3( 0.0,.0,0.0 ), 10, 16);
//	gear.Generate();
//	EXPECT_EQ(gear.GetVertices().size(), 65);
//}
//
//TEST(Gear2D, ShouldHaveRightNumberOfNormals) {
//	auto gear = GenerativeGeometry::Gear2D(vec3( 0.0,0.0,0.0 ), 10, 16);
//	gear.Generate();
//	EXPECT_EQ(gear.GetNumNormals(), gear.GetNumVerts());
//}
//
//TEST(Gear2D, ShouldHaveRightNumberOfTriangleVertices) {
//	auto gear = GenerativeGeometry::Gear2D(vec3( 0.0,0.0,0.0 ), 10, 16);
//	gear.Generate();
//	// Each tooth zone = 3 vert indices for 1 triangles
//	// Each gap zone = 3 vert indices for 1 triangles
//	// Therefor: numSpokes * 3
//	EXPECT_EQ(gear.GetNumTriangleVertIndices(), 96);
//}

class Gear3DTest : public ::testing::Test, public GenerativeGeometry::Gear3D {
protected:
	Gear3DTest() {};
	void SetUp() override{
		gear1.Generate();
		gear2.Generate();
	}
	GenerativeGeometry::Gear3D gear0 = GenerativeGeometry::Gear3D(vec3(0.0,0.0,0.0));
	GenerativeGeometry::Gear3D gear1 = GenerativeGeometry::Gear3D(vec3(0.0, 1000.0, 10.0));
	GenerativeGeometry::Gear3D gear2 = GenerativeGeometry::Gear3D(vec3(0.0, 2200.0, 20.0));
	GenerativeGeometry::Gear3D gear3 = GenerativeGeometry::Gear3D(vec3(0.0, 2700.0, 20.0));
	GenerativeGeometry::Gear3D gear4 = GenerativeGeometry::Gear3D(vec3(0.0, 3000.0, 30.0));
	GenerativeGeometry::Gear3D gear5 = GenerativeGeometry::Gear3D(vec3(0.0, 4000.0, 40.0));
	GenerativeGeometry::Gear3D gear6 = GenerativeGeometry::Gear3D(vec3(0.0, 5500.0, 50.0));
	//GenerativeGeometry::Gear3D gear0;
	//GenerativeGeometry::Gear3D gear1;
	//GenerativeGeometry::Gear3D gear2;
	//GenerativeGeometry::Gear3D gear3;
	//GenerativeGeometry::Gear3D gear4;
	//GenerativeGeometry::Gear3D gear5;
	//GenerativeGeometry::Gear3D gear6;
};

/**
 * Because we're using a static pointer on Gear3D class, GTest seems to lose pointers.
 * So we shove all the tests into one TEST_F.
 */
TEST_F(Gear3DTest, ShouldDoABunchOfThings) {
	EXPECT_EQ(gear0.GetRadius(), 100.0);
	
	/** ShouldHaveRightNumberOfTriangleVertices */
	// Tooth zone = 7 triangles = 21 vertices
	// Gap zone = 3 triangles
	double nT = gear1.GetNumTeeth();
	EXPECT_EQ(gear1.GetNumTriangleVertIndices(), 21 * nT + 9 * nT);
	nT = gear2.GetNumTeeth();
	EXPECT_EQ(gear2.GetNumTriangleVertIndices(), 21 * nT + 9 * nT);

	/** ShouldComputeDistanceFromPrevious */	
	EXPECT_FLOAT_EQ(gear1.GetDistanceFromPrevious(), 1000.04999875);
	EXPECT_FLOAT_EQ(gear2.GetDistanceFromPrevious(), 1200.041665943);
	EXPECT_FLOAT_EQ(gear3.GetDistanceFromPrevious(), 500.0);
	EXPECT_FLOAT_EQ(gear4.GetDistanceFromPrevious(), 300.1666203961);

	/** ShouldComputeParamsFromDistanceToPrevious */
	//double tW = (2 * pi * gear2.GetRadius() / gear2.GetNumSpokes());
	//cout << tW << endl;
	//double outerRadius2 = sqrt(101) - 10;
	//cout << outerRadius2 << endl;
	//double radius2 = outerRadius2 - tW;
	//cout << radius2 << endl;
	//EXPECT_EQ(gear2.GetToothWidth(), tW);
	//EXPECT_EQ(gear2.GetRadius(), radius2);
	
	/** ShouldAlternateRotationFactor */
	int a = gear1.GetRotationFactor();
	EXPECT_EQ(gear2.GetRotationFactor(), -a);
	EXPECT_EQ(gear3.GetRotationFactor(), a);
	EXPECT_EQ(gear4.GetRotationFactor(), -a);
	EXPECT_EQ(gear5.GetRotationFactor(), a);
	EXPECT_EQ(gear6.GetRotationFactor(), -a);
	
	/** ShouldHaveSameToothWidth */
	EXPECT_EQ(gear1.GetToothWidth(), gear2.GetToothWidth());
}

//Circle, ShouldHaveMoreThanTwoEdges
//Gear2D, ShouldHaveMoreThanOneTeeth
//Gear3D, ShouldHaveMoreThanOneTeeth