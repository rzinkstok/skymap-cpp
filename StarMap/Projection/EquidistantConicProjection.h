//
//  EquidistantConicProjection.h
//  StarMap
//
//  Created by Roel Zinkstok on 30/04/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#ifndef EquidistantConicProjection_h
#define EquidistantConicProjection_h

#define _USE_MATH_DEFINES
#include <cmath>
#include "../Geometry/Point2D.h"
#include "./Projection.h"


class EquidistantConicProjection: public Projection {
private:
    double center_latitude;
    double standard_parallel1;
    double standard_parallel2;
    double cone_angle;
    double n;
    double G;
    double rho_0;
public:
    EquidistantConicProjection():
        EquidistantConicProjection(SphericalPoint(0, 0), 30, 60, 45, false)
    {
#if VERBOSE
        std::cout << "Created EquidistantConicProjection()" << std::endl;
#endif
    }
    
    EquidistantConicProjection(SphericalPoint p_center, double p_standard_parallel1, double p_standard_parallel2, double p_reference_scale, bool p_celestial):
        Projection(p_center.longitude, p_reference_scale, p_celestial), center_latitude(p_center.latitude), standard_parallel1(p_standard_parallel1), standard_parallel2(p_standard_parallel2)
    {
        cone_angle = 90 - 0.5 * abs(standard_parallel1 + standard_parallel2);
        double phi1 = deg2rad(standard_parallel1);
        double phi2 = deg2rad(standard_parallel2);
        n = (cos(phi1) - cos(phi2)) / (phi2 - phi1);
        G = cos(phi1) / n + phi1;
        rho_0 = (G - deg2rad(center_latitude))/deg2rad(get_reference_scale());
#if VERBOSE
        std::cout << "Created EquidistantConicProjection(SphericalPoint, double, double, double, bool)" << std::endl;
#endif
    }
        
    virtual ~EquidistantConicProjection() {
#if VERBOSE
        std::cout << "Destroyed EquidistantConicProjection" << std::endl;
#endif
    }

    SphericalPoint get_center() const { return SphericalPoint(get_center_longitude(), center_latitude); }
    double get_center_latitude() const { return center_latitude; }
    double get_standard_parallel1() const { return standard_parallel1; }
    double get_standard_parallel2() const { return standard_parallel2; }
    double get_cone_angle() const { return cone_angle; }
        
    virtual Point2D project(SphericalPoint &) const;
    virtual SphericalPoint backproject(Point2D &) const;
};

#endif /* EquidistantConicProjection_h */
