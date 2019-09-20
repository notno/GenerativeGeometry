#include "pch.h"

#include <iostream>
#include <cmath>

#include "../GenerativeGeometry/GG_Math.h"
#include "../GenerativeGeometry/GG_Geometry.h"
#include "../GenerativeGeometry/GG_Circle.h"


TEST(RandRangeInt, ProbablyDoesntProduceBadResults) {
  EXPECT_LT(GenerativeGeometry::Math::RandRangeInt(20,30), 31);
  EXPECT_GT(GenerativeGeometry::Math::RandRangeInt(1, 2), 0);
  EXPECT_EQ(GenerativeGeometry::Math::RandRangeInt(1, 1), 1);
}

TEST(Circle, ShouldInitializeToZeros) {
	auto c = GenerativeGeometry::Circle();
	EXPECT_EQ(c.GetCenter().x, 0.0);
}

TEST(Circle, ShouldMakeGoodVertices) {
	auto c = GenerativeGeometry::Circle(GenerativeGeometry::vec3{ 0.0,0.0,0.0 }, 10.0, 16);
	c.Draw();
	EXPECT_EQ(c.GetVertexAt(0).x, 0.0);
	EXPECT_FLOAT_EQ(c.GetVertexAt(1).y, 10.0);
	auto w = floor(c.GetVertexAt(16).y);
	EXPECT_EQ( w, 9);
	EXPECT_EQ(c.GetCenter().x, 0.0);
}
TEST(Circle, ShouldMakeGoodTriangles) {
	auto c = GenerativeGeometry::Circle(GenerativeGeometry::vec3{ 0.0,0.0,0.0 }, 10.0, 16);
	c.Draw();
	EXPECT_EQ(c.GetTriangleAt(0),2);
	EXPECT_EQ(c.GetTriangleAt(1),1);
	EXPECT_EQ(c.GetTriangleAt(2),0);
	EXPECT_EQ(c.GetTriangleAt(16*3-2),16);
}
TEST(Circle, ShouldMakePredictableNormals) {
	auto c = GenerativeGeometry::Circle(GenerativeGeometry::vec3{ 1.0,9.0,3.0 }, 1320.0, 32);
	c.Draw();
	EXPECT_EQ(c.GetNormalAt(0).x, 1);
	EXPECT_EQ(c.GetNormalAt(0).y, 0);
	EXPECT_EQ(c.GetNormalAt(0).z, 0);
}
