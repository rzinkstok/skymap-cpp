//
//  Shapes.h
//  StarMap
//
//  Created by Roel Zinkstok on 01/05/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#ifndef Shapes_h
#define Shapes_h

#include <cmath>
#include <cstdio>
#include <vector>
#include <exception>
#include "Point2D.h"


class Shape {
public:
    Shape() {}
    ~Shape() {}
};


class Line: public Shape {
public:
    Point2D point1;
    Point2D point2;
    Point2D vector;
    double length;
    double angle;
    
    Line(): Line(Point2D(), Point2D(1,1)) {}
    Line(Point2D p_point1, Point2D p_point2): point1{p_point1}, point2{p_point2} {
        vector = Point2D(point2 - point1);
        length = point1.distance(point2);
        angle = rad2deg(atan2(vector.y, vector.x));
    }
    ~Line() {}
    
    Point2D intersect_line(const Line &other) const {
        double a1 = this->point1.y - this->point2.y;
        double b1 = this->point2.x - this->point1.x;
        double c1 = this->point1.x * this->point2.y - this->point2.x * this->point1.y;
        
        double a2 = other.point1.y - other.point2.y;
        double b2 = other.point2.x - other.point1.x;
        double c2 = other.point1.x * other.point2.y - other.point2.x * other.point1.y;
        
        double den = (a1 * b2 - a2 * b1);
        if(abs(den) == 0.0) {
            throw std::runtime_error("Parallel lines do not intersect");
        }
        
        Point2D result = Point2D();
        result.y = (c1 * a2 - c2 * a1) / den;
        result.x = (b1 * c2 - c1 * b2) / den;
        return result;
    }
    
    Point2D inclusive_intersect_line(Line &other) const {
        Point2D p = intersect_line(other);
        
        if(point_on_line_segment(p) && other.point_on_line_segment(p)) {
            return p;
        }
        throw std::runtime_error("Intersection not within line segment(s)");
    }
    
    bool point_on_line_segment(Point2D p) const {
        Point2D point_vector = p - point1;
        double component = point_vector * vector/length;
        return (abs(point_vector.magnitude() - component) < EPSILON) && (component >= 0) && (component <= length);
    }
};

inline std::ostream& operator<<(std::ostream& os, const Line& l)
{
    os << "Line(" << l.point1 << " - " << l.point2 << ")";
    return os;
}


class Polygon: public Shape {
public:
    std::vector<Point2D> points;
    std::vector<Line> lines;
    bool closed;
    
    Polygon(): Polygon{{}, false} {}
    Polygon(std::vector<Point2D> p_points, bool p_closed=true): closed{p_closed} {
        for(auto const& p: p_points) {
            add_point(p);
        }
        if(closed) {
            close();
        }
    }
    ~Polygon() {}
    
    void add_point(Point2D p) {
        points.push_back(p);
        if(points.size() > 1) {
            Point2D p0 = points[points.size()-2];
            lines.push_back(Line(p0, p));
        }
    }
    
    void close() {
        if(points.size() >= 2) {
            Point2D p0 = points[0];
            Point2D p1 = points[points.size()-1];
            lines.push_back(Line(p0, p1));
        }
        closed = true;
    }
};

inline std::ostream& operator<<(std::ostream& os, const Polygon& p)
{
    os << "Polygon(";
    for(auto const& p: p.points) {
        os << p << "..";
    }
    if(p.closed) {
        os << "closed";
    }
    os << ")";
    return os;
}


class Circle: public Shape {
public:
    Point2D center;
    double radius;
    
    Circle(): center{Point2D()}, radius{1.0} {}
    Circle(Point2D p_center, double p_radius): center{p_center}, radius{p_radius} {}
    ~Circle() {}
    
    double area() const {
        return M_PI * pow(radius, 2);
    }
};

inline std::ostream& operator<<(std::ostream& os, const Circle& c)
{
    os << "Circle(" << c.center << ", " << c.radius << ")";
    return os;
}


class Arc: public Circle {
public:
    double start_angle;
    double stop_angle;
    Point2D start_point;
    Point2D stop_point;
    
    Arc(): Arc(Point2D(), 1.0, 0, 90) {}
    Arc(Point2D p_center, double p_radius, double p_start_angle, double p_stop_angle):
        Circle{p_center, p_radius}, start_angle{p_start_angle}, stop_angle{p_stop_angle}
    {
        double a1 = deg2rad(start_angle);
        double a2 = deg2rad(stop_angle);
        start_point = center + radius * Point2D(cos(a1), sin(a1));
        stop_point = center + radius * Point2D(cos(a2), sin(a2));
    }
    ~Arc() {}
    
    double area() const {
        return pow(radius, 2.0) * M_PI * abs(stop_angle - start_angle) / 360.0;
    }
    
	std::vector<Point2D> interpolated_points(int npoints=100) const {
        double angle;
        Point2D p;
		std::vector<Point2D> points;
        double delta_angle = stop_angle - start_angle;
        for(int i=0; i<npoints; i++) {
            angle = start_angle + i * delta_angle / (npoints-1);
            p = center + radius * Point2D(cos(deg2rad(angle)), sin(deg2rad(angle)));
            points.push_back(p);
        }
        return points;
    }
};


class Rectangle: public Shape {
private:
    double sizex;
    double sizey;
public:
    Point2D point1;
    Point2D point2;
    
    Rectangle(): Rectangle{Point2D(0,0), Point2D(1,1)} {}
    Rectangle(Point2D p_point1, Point2D p_point2) {
        point1.x = fmin(p_point1.x, p_point2.x);
        point1.y = fmin(p_point1.y, p_point2.y);
        point2.x = fmax(p_point1.x, p_point2.x);
        point2.y = fmax(p_point1.y, p_point2.y);
        sizex = (point2 - point1).x;
        sizey = (point2 - point1).y;
    }
    Rectangle(double p_sizex, double p_sizey, Point2D p_origin): Rectangle(p_origin, Point2D(p_origin.x + p_sizex, p_origin.y + p_sizey)) {}
    ~Rectangle() {}
    
    double area() const {
        return sizex * sizey;
    }
    
    double get_sizex() const {
        return sizex;
    }
    
    double get_sizey() const {
        return sizey;
    }
    
	std::vector<Point2D> get_points() const {
		std::vector<Point2D> points;
        points.push_back(point1);
        points.push_back(Point2D(point2.x, point1.y));
        points.push_back(point2);
        points.push_back(Point2D(point1.x, point2.y));
        return points;
    }
};


inline std::ostream& operator<<(std::ostream& os, const Rectangle& r)
{
    os << "Rectangle(" << r.point1 << ", " << r.point2 << ")";
    return os;
}
#endif /* Shapes_h */
