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

inline double reduce_angle(double angle, double center=180.0) {
    while(angle < center - 180.0) {
        angle += 360.0;
    }
    while(angle >= center + 180.0) {
        angle -= 360;
    }
    return angle;
}


inline double rad2deg(double rad) {
    return 180.0 * rad / M_PI;
}


inline double deg2rad(double deg) {
    return M_PI * deg / 180.0;
}


class Point2D {
public:
    double x;
    double y;
    
    Point2D(): x{0.0}, y{0.0} {}
    Point2D(double x, double y): x{x}, y{y} {}
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
    Point2D rotate(const double angle) const {
        return Point2D(cos(angle) * x - sin(angle) * y, sin(angle) * x + cos(angle) * y);
    }
    
    double magnitude() const {
        return sqrt(x * x + y * y);
    }
    
    double distance(const Point2D &other) const {
        return (*this - other).magnitude();
    }
    
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

// SphericalPoint class
class SphericalPoint: public Point2D {
public:
    double &longitude;
    double &latitude;
    
    SphericalPoint(): Point2D(), longitude{x}, latitude{y} {}
    SphericalPoint(double p_longitude, double p_latitude): Point2D(p_longitude, p_latitude), longitude{x}, latitude{y} {}
    
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
