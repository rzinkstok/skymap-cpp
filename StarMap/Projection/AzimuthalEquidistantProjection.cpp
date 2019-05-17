//
//  AzimuthalEquidistantProjection.cpp
//  StarMap
//
//  Created by Roel Zinkstok on 29/04/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//


#include <iostream>
#include <cmath>
#include "../Geometry/Point2D.h"
#include "./Projection.h"
#include "./AzimuthalEquidistantProjection.h"


Point2D AzimuthalEquidistantProjection::project(SphericalPoint &sp) const {
    Point2D result = Point2D();
    double rho, theta;
    
    rho = (origin_latitude - sp.latitude) / get_reference_scale();
    theta = deg2rad(reduce_longitude(sp.longitude) - get_center_longitude());
    if(polar_direction_reversed()) {
        theta *= -1;
    }
    
    result.x = rho * sin(theta);
    result.y = -rho * cos(theta);
    return result;
}

SphericalPoint AzimuthalEquidistantProjection::backproject(Point2D &p) const {
    SphericalPoint result = SphericalPoint();
    double rho, theta;
    
    rho = Point2D(0, 0).distance(p);
    theta = reduce_angle(rad2deg(atan2(p.y, p.x)));
    if(polar_direction_reversed()) {
        theta *= -1;
    }
    
    result.longitude = reduce_angle(theta + get_center_longitude() + 90.0);
    result.latitude = -rho * get_reference_scale() + get_origin_latitude();
    return result;
}

