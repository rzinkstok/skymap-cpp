//
//  TestAzimuthalEquidistantProjection.cpp
//  Test
//
//  Created by Roel Zinkstok on 01/05/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#include <stdio.h>
#include "Point2D.h"
#include "AzimuthalEquidistantProjection.h"
#include "catch.hpp"

using namespace std;


TEST_CASE("AzimuthalEquidistantProjection") {
    SphericalPoint sp1, sp2;
    Point2D p1;
    AzimuthalEquidistantProjection aep = AzimuthalEquidistantProjection(0, 40, false, true);
    
    sp1 = SphericalPoint(0, 90);
    p1 = aep.project(sp1);
    REQUIRE(p1 == Point2D(0, 0));
    sp1 = SphericalPoint(0, 50);
    p1 = aep.project(sp1);
    REQUIRE(p1 == Point2D(0, -1));
    sp1 = SphericalPoint(90, 50);
    p1 = aep.project(sp1);
    REQUIRE(p1 == Point2D(1, 0));
    sp1 = SphericalPoint(180, 50);
    p1 = aep.project(sp1);
    REQUIRE(p1 == Point2D(0, 1));
    sp1 = SphericalPoint(270, 50);
    p1 = aep.project(sp1);
    REQUIRE(p1 == Point2D(-1, 0));
    
    aep.set_celestial(true);
    
    sp1 = SphericalPoint(0, 50);
    p1 = aep.project(sp1);
    REQUIRE(p1 == Point2D(0, -1));
    sp1 = SphericalPoint(90, 50);
    p1 = aep.project(sp1);
    REQUIRE(p1 == Point2D(-1, 0));
    sp1 = SphericalPoint(180, 50);
    p1 = aep.project(sp1);
    REQUIRE(p1 == Point2D(0, 1));
    sp1 = SphericalPoint(270, 50);
    p1 = aep.project(sp1);
    REQUIRE(p1 == Point2D(1, 0));
    
    aep.set_celestial(false);
    p1 = Point2D(1, 0);
    sp1 = aep.backproject(p1);
    REQUIRE(sp1 == SphericalPoint(90, 50));
    p1 = Point2D(0, 1);
    sp1 = aep.backproject(p1);
    REQUIRE(sp1 == SphericalPoint(180, 50));
    p1 = Point2D(-1, 0);
    sp1 = aep.backproject(p1);
    REQUIRE(sp1 == SphericalPoint(270, 50));
    p1 = Point2D(0, -1);
    sp1 = aep.backproject(p1);
    REQUIRE(sp1 == SphericalPoint(0, 50));
    
    sp1 = SphericalPoint(225., 76.);
    p1 = aep.project(sp1);
    sp2 = aep.backproject(p1);
    REQUIRE(sp1 == sp2);
}
