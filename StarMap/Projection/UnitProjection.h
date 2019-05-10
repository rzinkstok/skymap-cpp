//
//  UnitProjection.h
//  StarMap
//
//  Created by Roel Zinkstok on 29/04/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#ifndef UnitProjection_h
#define UnitProjection_h

#define _USE_MATH_DEFINES
#include "../Geometry/Point2D.h"
#include "./Projection.h"

class UnitProjection: public Projection {
public:
    UnitProjection():
        Projection()
    {
#if VERBOSE
        std::cout << "Created UnitProjection()" << std::endl;
#endif
    }
    UnitProjection(double p_center_longitude, double p_reference_scale, bool p_celestial):
        Projection(p_center_longitude, p_reference_scale, p_celestial)
    {
#if VERBOSE
        std::cout << "Created UnitProjection(double, double, bool)" << std::endl;
#endif
    };
    virtual ~UnitProjection() {
#if VERBOSE
        std::cout << "Destroyed UnitProjection" << std::endl;
#endif
    }
    
    virtual Point2D project(SphericalPoint &sp) const {
        return Point2D(sp.longitude, sp.latitude);
    }
    virtual SphericalPoint backproject(Point2D &p) const {
        return SphericalPoint(p.x, p.y);
    }
};

#endif /* UnitProjection_h */
