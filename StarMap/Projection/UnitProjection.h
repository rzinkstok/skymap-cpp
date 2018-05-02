//
//  UnitProjection.h
//  StarMap
//
//  Created by Roel Zinkstok on 29/04/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#ifndef UnitProjection_h
#define UnitProjection_h

#include "Point2D.h"
#include "Projection.h"

class UnitProjection: public Projection {
public:
    UnitProjection():
        Projection()
    {
        std::cout << "Created UnitProjection()" << std::endl;
    }
    UnitProjection(double p_center_longitude, double p_reference_scale, bool p_celestial):
        Projection(p_center_longitude, p_reference_scale, p_celestial)
    {
        std::cout << "Created UnitProjection(double, double, bool)" << std::endl;
    };
    virtual ~UnitProjection() {
        std::cout << "Destroyed UnitProjection" << std::endl;
    }
    
    virtual Point2D project(SphericalPoint &sp) const {
        return Point2D(sp.longitude, sp.latitude);
    }
    virtual SphericalPoint backproject(Point2D &p) const {
        return SphericalPoint(p.x, p.y);
    }
};

#endif /* UnitProjection_h */
