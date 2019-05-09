//
//  Point2D.h
//  StarMap
//
//  Created by Roel Zinkstok on 28/04/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#ifndef Point2D_h
#define Point2D_h
#include <iostream>
#include <math.h>
#include <exception>
#define EPSILON 1e-10


/**
 *   @brief  Ensures an angle is within center + or - 180 degrees
 *
 *   @param  angle is the angle to reduce in degrees
 *   @param  center is the center of the 360 degree region in which to place the angle, in degrees
 *   @return the reduced angle
 */
inline double reduce_angle(double angle, double center=180.0) {
    while(angle < center - 180.0) {
        angle += 360.0;
    }
    while(angle >= center + 180.0) {
        angle -= 360;
    }
    return angle;
}


/**
 *   @brief  Converts radians to degrees
 *
 *   @param  rad is the angle to convert in radians
 *   @return the angle in degrees
 */
inline double rad2deg(double rad) {
    return 180.0 * rad / M_PI;
}


/**
 *   @brief  Converts degrees to radians
 *
 *   @param  deg is the angle to convert in degrees
 *   @return the angle in redians
 */
inline double deg2rad(double deg) {
    return M_PI * deg / 180.0;
}


/**
 *   @brief  Class representing a point in 2D space
 */
class Point2D {
public:
    double x;
    double y;
    
    /**
     *   @brief  Default constructor
     */
    Point2D(): x{0.0}, y{0.0} {}
    
    /**
     *   @brief  Constructor
     */
    Point2D(double x, double y): x{x}, y{y} {}
    
    /**
     *   @brief  Default destructor
     */
    ~Point2D() {}
    
    // Operators
    
    bool operator== (const Point2D &other) const {
        return ((abs(x - other.x) < EPSILON) && (abs(y - other.y) < EPSILON));
    }
    
    bool operator!= (const Point2D &other) const {
        return !(*this == other);
    }
    
    Point2D operator+ (const Point2D &other) const {
        return Point2D(x + other.x, y + other.y);
    }
    
    Point2D operator- (const Point2D &other) const {
        return Point2D(x - other.x, y - other.y);
    }
    
    Point2D operator- () const {
        return Point2D(-x, -y);
    }
    
    Point2D operator/ (const double s) const {
        double sinv = 1.0/s;
        return Point2D(x * sinv, y * sinv);
    }
    
    Point2D operator* (const double s) const {
        return Point2D(x * s, y * s);
    }
    
    double operator* (const Point2D &other) const {
        return x * other.x + y * other.y;
    }
    
    void operator+= (const Point2D &other) {
        x += other.x;
        y += other.y;
    }
    
    void operator-= (const Point2D &other) {
        x -= other.x;
        y -= other.y;
    }
    
    double operator[] (const int i) const {
        if(i==0) {
            return x;
        }
        else {
            return y;
        }
    }
    
    // utility functions
    
    /**
     *   @brief  Rotates the point around the origin
     *
     *   @param  angle is the angle through which to rotate
     *   @return a new Point2D instance corresponding to the rotated point
     */
    Point2D rotate(const double angle) const {
        return Point2D(cos(angle) * x - sin(angle) * y, sin(angle) * x + cos(angle) * y);
    }
    
    
    /**
     *   @brief  Calculates the distance to the origin
     *
     *   @return The distance to the origin
     */
    double magnitude() const {
        return sqrt(x * x + y * y);
    }
    
    /**
     *   @brief  Calculates the distance to another point
     *
     *   @param  other is the other point
     */
    double distance(const Point2D &other) const {
        return (*this - other).magnitude();
    }
    
    /**
     *   @brief  Normalize the point to have a distance of 1 to the origin
     */
    void normalize() {
        double m = magnitude();
        if(m == 0) {
            throw std::runtime_error("Origin Point2D cannot be normalized");
        }
        double minv = 1.0/m;
        x *= minv;
        y *= minv;
    }
    
    
};


inline Point2D operator* (const double s, const Point2D& p) {
    return p*s;
}


inline std::ostream& operator<<(std::ostream& os, const Point2D &p) {
    os << "Point2D(" << p.x << ", " << p.y << ")";
    return os;
}


/**
 *   @brief  Class representing a point on a sphere
 */
class SphericalPoint: public Point2D {
public:
    double &longitude;
    double &latitude;
    
    /**
     *   @brief  Default constructor
     */
    SphericalPoint(): Point2D(), longitude{x}, latitude{y} {}
    
    /**
     *   @brief  Constructor
     */
    SphericalPoint(double p_longitude, double p_latitude): Point2D(p_longitude, p_latitude), longitude{x}, latitude{y} {}
    
    /**
     *   @brief  Reduces the angle to the range of + or - 180 degrees
     */
    void reduce() {
        this->x = reduce_angle(longitude);
    }
    
    bool operator== (const SphericalPoint &other) const {
        SphericalPoint p1 = SphericalPoint(*this);
        SphericalPoint p2 = SphericalPoint(other);
        p1.reduce();
        p2.reduce();
        return ((abs(p1.x - p2.x) < EPSILON) && (abs(p1.y - p2.y) < EPSILON));
    }
    
    bool operator!= (const SphericalPoint &other) const {
        return !(*this==other);
    }
    
    SphericalPoint operator= (const SphericalPoint &other) {
        longitude = other.longitude;
        latitude = other.latitude;
        return *this;
    }
};


inline std::ostream& operator<<(std::ostream& os, const SphericalPoint& p)
{
    os << "SphericalPoint(" << p.x << ", " << p.y << ")";
    return os;
}


#endif /* Point2D_h */
