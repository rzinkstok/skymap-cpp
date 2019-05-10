//
//  AzimuthalEquidistantProjection.h
//  StarMap
//
//  Created by Roel Zinkstok on 29/04/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#ifndef AzimuthalEquidistantProjection_h
#define AzimuthalEquidistantProjection_h

#define _USE_MATH_DEFINES
#include "../Geometry/Point2D.h"
#include "./Projection.h"

class AzimuthalEquidistantProjection: public Projection {
private:
    bool north;  // Whether the center of projection is the north pole
    double origin_latitude;  // The latitude of the origin (+90 or -90 depending on the pole
public:
    AzimuthalEquidistantProjection():
        Projection(), north(true)
    {
        origin_latitude = (north ? 90 : -90);
#if VERBOSE
        std::cout << "Created AzimuthalEquidistantProjection()" << std::endl;
#endif
    }
    
    AzimuthalEquidistantProjection(double p_center_longitude, double p_reference_scale, bool p_celestial, bool p_north):
        Projection(p_center_longitude, p_reference_scale, p_celestial), north(p_north)
    {
        origin_latitude = (north ? 90 : -90);
#if VERBOSE
        std::cout << "Created AzimuthalEquidistantProjection(double, double, bool, bool)" << std::endl;
#endif
    }
    
    virtual ~AzimuthalEquidistantProjection() {
#if VERBOSE
        std::cout << "Destroyed AzimuthalEquidistantProjection" << std::endl;
#endif
    }
    
    bool get_north() const { return north; }
    double get_origin_latitude() const { return origin_latitude; }
    bool polar_direction_reversed() const { return get_north() == get_celestial(); }
    
    virtual Point2D project(SphericalPoint &) const;
    virtual SphericalPoint backproject(Point2D &) const;
};

#endif /* AzimuthalEquidistantProjection_h */
