//
//  EquidistantCylindricalProjection.h
//  StarMap
//
//  Created by Roel Zinkstok on 29/04/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#ifndef EquidistantCylindricalProjection_h
#define EquidistantCylindricalProjection_h

#include "../Geometry/Point2D.h"
#include "Projection.h"

class EquidistantCylindricalProjection: public Projection {
public:
    EquidistantCylindricalProjection():
        Projection()
    {
#if VERBOSE
        std::cout << "Created EquidistantCylinidricalProjection()" << std::endl;
#endif
    }
    EquidistantCylindricalProjection(double p_center_longitude, double p_reference_scale, bool p_celestial):
        Projection(p_center_longitude, p_reference_scale, p_celestial)
    {
#if VERBOSE
        std::cout << "Created EquidistantCylinidricalProjection(double, double, bool)" << std::endl;
#endif
    }
    virtual ~EquidistantCylindricalProjection() {
#if VERBOSE
        std::cout << "Destroyed EquidistantCylinidricalProjection" << std::endl;
#endif
    }
    
    virtual Point2D project(SphericalPoint &) const;
    virtual SphericalPoint backproject(Point2D &) const;
};

#endif /* EquidistantCylindricalProjection_h */
