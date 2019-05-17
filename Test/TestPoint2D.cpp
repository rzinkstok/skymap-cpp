//
//  TestPoint2D.cpp
//  Test
//
//  Created by Roel Zinkstok on 02/05/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#include <iostream>
#include <exception>
#include <cmath>
#include "../StarMap/Geometry/Point2D.h"
#include "./catch.hpp"


TEST_CASE("Point2D") {
    Point2D p = Point2D();
    
    REQUIRE(p == Point2D(0, 0));
    REQUIRE(p.x == Approx(0));
    REQUIRE(p.y == Approx(0));
    REQUIRE_THROWS_AS(p.normalize(), std::runtime_error);
    
    p = Point2D(-4.1, 6.23);
    REQUIRE(p == p);
    REQUIRE(p.x == Approx(-4.1));
    REQUIRE(p.y == Approx(6.23));
    
    p = -p;
    REQUIRE(p.x == Approx(4.1));
    REQUIRE(p.y == Approx(-6.23));
    
    Point2D p2 = Point2D(4.3, 1.76);
    Point2D p3 = p + p2;
    REQUIRE(p3.x == Approx(8.4));
    REQUIRE(p3.y == Approx(-4.47));
    
    p3 = p - p2;
    REQUIRE(p3.x == Approx(-0.2));
    REQUIRE(p3.y == Approx(-7.99));
    
    REQUIRE(p3[0] == p3.x);
    REQUIRE(p3[1] == p3.y);
    
    p3 = p*2.5;
    REQUIRE(p3.x == Approx(10.25));
    REQUIRE(p3.y == Approx(-15.575));
    
    p3 = 2.5*p;
    REQUIRE(p3.x == Approx(10.25));
    REQUIRE(p3.y == Approx(-15.575));
    
    p3 = p/2.0;
    REQUIRE(p3.x == Approx(2.05));
    REQUIRE(p3.y == Approx(-3.115));
    
    p = Point2D(3,4);
    REQUIRE(p.magnitude() == Approx(5));
    
    p.normalize();
    REQUIRE(p.magnitude() == Approx(1));
    REQUIRE(p.x == Approx(0.6));
    REQUIRE(p.y == Approx(0.8));
    
    p2 = p.rotate(M_PI_2);
    REQUIRE(p2.x == Approx(-0.8));
    REQUIRE(p2.y == Approx(0.6));
    
    REQUIRE(p.distance(p2) == Approx(sqrt(2)));
    
    REQUIRE(reduce_angle(315.21) == Approx(315.21));
    REQUIRE(reduce_angle(-43.1) == Approx(360-43.1));
    REQUIRE(reduce_angle(3643.1) == Approx(43.1));
    
    REQUIRE(rad2deg(M_PI_4) == Approx(45));
    REQUIRE(deg2rad(45) == Approx(M_PI_4));
}
