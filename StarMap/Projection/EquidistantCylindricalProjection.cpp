//
//  EquidistantCylindricalProjection.cpp
//  StarMap
//
//  Created by Roel Zinkstok on 29/04/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#define _USE_MATH_DEFINES
#include <iostream>
#include "../Geometry/Point2D.h"
#include "./Projection.h"
#include "./EquidistantCylindricalProjection.h"


Point2D EquidistantCylindricalProjection::project(SphericalPoint &sp) const {
    Point2D result = Point2D();
    result.x = (reduce_longitude(sp.longitude) - get_center_longitude()) / get_reference_scale();
    if(get_celestial()) {
        result.x *= -1;
    }
    result.y = sp.latitude / get_reference_scale();
    return result;
}

SphericalPoint EquidistantCylindricalProjection::backproject(Point2D &p) const {
    SphericalPoint result = SphericalPoint();
    result.longitude = get_center_longitude() + get_reference_scale() * p.x;
    if(get_celestial()) {
        result.longitude *= -1;
    }
    result.latitude = p.y * get_reference_scale();
    return result;
}
