//
//  TestEquidistantConicProjection.cpp
//  Test
//
//  Created by Roel Zinkstok on 01/05/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#include <stdio.h>
#include "Point2D.h"
#include "EquidistantConicProjection.h"
#include "catch.hpp"
using namespace std;


TEST_CASE("EquidistantConicProjection") {
    SphericalPoint sp1, sp2;
    Point2D p1;
    EquidistantConicProjection ecp = EquidistantConicProjection(SphericalPoint(0, 45), 30, 60, 10, false);
    
    REQUIRE(ecp.get_cone_angle() == 45.0);
    
    sp1 = SphericalPoint(0, 45);
    p1 = ecp.project(sp1);
    REQUIRE(p1 == Point2D(0, 0));
    sp1 = SphericalPoint(0, 50);
    p1 = ecp.project(sp1);
    REQUIRE(p1 == Point2D(0, 0.5));
    sp1 = SphericalPoint(0, 35);
    p1 = ecp.project(sp1);
    REQUIRE(p1 == Point2D(0, -1));
    
    sp1 = SphericalPoint(15, 45);
    p1 = ecp.project(sp1);
    sp2 = ecp.backproject(p1);
    REQUIRE(sp1 == sp2);
    sp1 = SphericalPoint(-15, 45);
    p1 = ecp.project(sp1);
    sp2 = ecp.backproject(p1);
    REQUIRE(sp1 == sp2);
    sp1 = SphericalPoint(29, 32);
    p1 = ecp.project(sp1);
    sp2 = ecp.backproject(p1);
    REQUIRE(sp1 == sp2);
}
