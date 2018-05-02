//
//  Projection.h
//  StarMap
//
//  Created by Roel Zinkstok on 28/04/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#ifndef Projection_h
#define Projection_h
#include "Point2D.h"

class Projection {
private:
    double center_longitude;
    double reference_scale;
    bool celestial;
public:
    Projection(): center_longitude{0.0}, reference_scale{1.0}, celestial{false} {
        std::cout << "Created Projection()" << std::endl;
    }
    Projection(double p_center_longitude, double p_reference_scale, bool p_celestial):
        center_longitude{p_center_longitude}, reference_scale{p_reference_scale}, celestial{p_celestial} {
        std::cout << "Created Projection(double, double, bool)" << std::endl;
    }
    virtual ~Projection() { std::cout << "Destroyed Projection" << std::endl; }

    double get_center_longitude() const { return center_longitude; }
    double get_reference_scale() const { return reference_scale; }
        
    bool get_celestial() const {return celestial; }
    void set_celestial(bool p_celestial) { celestial = p_celestial; }
    
    // Project a point with longitude/latitude in degrees to a point on the plane
    virtual Point2D project(SphericalPoint &) const = 0;
    // Backproject a point on the plane to a point with longitude/latitude in degrees
    virtual SphericalPoint backproject(Point2D &) const = 0;
    
    double reduce_longitude(double) const;
};

#endif /* Projection_h */
