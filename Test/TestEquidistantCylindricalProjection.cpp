//
//  TestEquidistantCylindricalProjection.cpp
//  Test
//
//  Created by Roel Zinkstok on 01/05/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#include <stdio.h>
#include "Point2D.h"
#include "EquidistantCylindricalProjection.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("EquidistantCylindricalProjection") {
    SphericalPoint sp1, sp2;
    Point2D p1;
    EquidistantCylindricalProjection ecp = EquidistantCylindricalProjection(0, 30, false);
    
    sp1 = SphericalPoint(0, 0);
    p1 = ecp.project(sp1);
    REQUIRE( p1 == Point2D(0, 0) );
    sp1 = SphericalPoint(30, 0);
    p1 = ecp.project(sp1);
    REQUIRE( p1 == Point2D(1, 0));
    sp1 = SphericalPoint(-30, 0);
    p1 = ecp.project(sp1);
    REQUIRE( p1 == Point2D(-1, 0));
    sp1 = SphericalPoint(0, 30);
    p1 = ecp.project(sp1);
    REQUIRE( p1 == Point2D(0, 1));
    sp1 = SphericalPoint(0, -30);
    p1 = ecp.project(sp1);
    REQUIRE( p1 == Point2D(0, -1));
}
