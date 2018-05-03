//
//  TestShapes.cpp
//  Test
//
//  Created by Roel Zinkstok on 03/05/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#include <stdio.h>
#include <exception>
#include <math.h>
#include <vector>
#include "Point2D.h"
#include "Shapes.h"
#include "catch.hpp"


TEST_CASE("Line") {
    Line l1 = Line(Point2D(0,0), Point2D(1,1));
    Line l2 = Line(Point2D(1,0), Point2D(0,1));
    Line l3 = Line(Point2D(0,1), Point2D(1,2));
    Line l4 = Line(Point2D(0,2), Point2D(1,2));
    
    REQUIRE(l1.length == Approx(sqrt(2)));
    REQUIRE(l1.angle == Approx(45));
    REQUIRE(l2.angle == Approx(135));
    
    REQUIRE(l1.point_on_line_segment(Point2D(-0.05, -0.05)) == false);
    REQUIRE(l1.point_on_line_segment(Point2D(0.05, 0.05)) == true);
    REQUIRE(l1.point_on_line_segment(Point2D(0.25, 0.25)) == true);
    REQUIRE(l1.point_on_line_segment(Point2D(0.95, 0.95)) == true);
    REQUIRE(l1.point_on_line_segment(Point2D(1.05, 1.05)) == false);
    REQUIRE(l1.point_on_line_segment(Point2D(0,1)) == false);
    REQUIRE(l1.point_on_line_segment(Point2D(0.5,0.49)) == false);
    
    REQUIRE(l1.intersect_line(l2) == Point2D(0.5, 0.5));
    REQUIRE_THROWS_AS(l1.intersect_line(l3), std::runtime_error);
    REQUIRE(l1.intersect_line(l4) == Point2D(2, 2));
    
    REQUIRE_THROWS_AS(l1.inclusive_intersect_line(l4), std::runtime_error);
};

TEST_CASE("Polygon") {
    Polygon p1 = Polygon();
    p1.add_point(Point2D(0,0));
    p1.add_point(Point2D(1,0));
    p1.add_point(Point2D(1,1));
    p1.add_point(Point2D(0,1));
    p1.close();
    REQUIRE(p1.points.size() == 4);
    REQUIRE(p1.lines.size() == 4);
    
    vector<Point2D> points;
    points.push_back(Point2D(0,0));
    points.push_back(Point2D(1,0));
    points.push_back(Point2D(0,1));
    
    Polygon p2 = Polygon(points, true);
    REQUIRE(p2.points.size() == 3);
    REQUIRE(p2.lines.size() == 3);
    cout << p2 << endl;
    
    Polygon p3 = Polygon(points, false);
    REQUIRE(p3.points.size() == 3);
    REQUIRE(p3.lines.size() == 2);
};


TEST_CASE("Circle") {
    Circle c = Circle();
    REQUIRE(c.center == Point2D(0, 0));
    REQUIRE(c.radius == Approx(1));
    
    
};

TEST_CASE("Rectangle") {
    Rectangle r1 = Rectangle();
    vector<Point2D> pp = r1.get_points();
};
