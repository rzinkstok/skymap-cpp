//
//  EquidistantConicProjection.cpp
//  StarMap
//
//  Created by Roel Zinkstok on 30/04/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "../Geometry/Point2D.h"
#include "./Projection.h"
#include "./EquidistantConicProjection.h"


Point2D EquidistantConicProjection::project(SphericalPoint &sp) const {
    Point2D result = Point2D();
    double rho, theta;
    
    rho = (G - deg2rad(sp.latitude))/deg2rad(get_reference_scale());
    theta = deg2rad(n * (reduce_longitude(sp.longitude) - get_center_longitude()));
    if(get_celestial()) {
        theta *= -1;
    }
    
    result.x = rho * sin(theta);
    result.y = rho_0 - rho * cos(theta);
    return result;
}

SphericalPoint EquidistantConicProjection::backproject(Point2D &p) const {
    SphericalPoint result = SphericalPoint();
    double rho, theta;
    bool sign_n = (n > 0) - (n < 0);
    
    rho = deg2rad(get_reference_scale()) * sign_n * sqrt(p.x * p.x + (rho_0 - p.y) * (rho_0 - p.y));
    theta = rad2deg(atan2(p.x, rho_0 - p.y));
    if(get_celestial()) {
        theta *= -1;
    }
    
    result.longitude = get_center_longitude() + theta / n;
    result.latitude = rad2deg(G - rho);
    return result;
}
