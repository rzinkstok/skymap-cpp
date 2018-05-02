//
//  Shapes.h
//  StarMap
//
//  Created by Roel Zinkstok on 01/05/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#ifndef Shapes_h
#define Shapes_h
#include <math.h>
#include <stdio.h>


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
        vector = point2 - point1;
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
            throw "Zero denominator";
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
        throw "Point not on line";
    }
    
    bool point_on_line_segment(Point2D p) const {
        Point2D point_vector = p - point1;
        double ip = point1 * point_vector;
        double comp = ip/length;
        return (comp >= 0) && (comp <= length);
    }
};

inline std::ostream& operator<<(std::ostream& os, const Line& l)
{
    os << "Line(" << l.point1 << " - " << l.point2 << ")";
    return os;
}



class Circle: public Shape {
public:
    Point2D center;
    double radius;
    
    Circle(): center{Point2D()}, radius{1.0} {}
    Circle(Point2D p_center, double p_radius): center{p_center}, radius{p_radius} {}
    ~Circle() {}
};


class Rectangle: public Shape {
public:
    double sizex;
    double sizey;
    Point2D origin;
    
    Rectangle(): sizex{1.0}, sizey{1.0}, origin{Point2D()} {}
    Rectangle(double p_sizex, double p_sizey, Point2D p_origin): sizex{p_sizex}, sizey{p_sizey}, origin{p_origin} {}
    ~Rectangle() {}
};

#endif /* Shapes_h */
