//
//  TikzPicture.h
//  StarMap
//
//  Created by Roel Zinkstok on 03/05/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#ifndef TikzPicture_h
#define TikzPicture_h
#include <sstream>
#include <string>
#include "Point2D.h"
#include "TikzUtils.h"


class TikzPicture {
private:
    double minx;
    double maxx;
    double miny;
    double maxy;
    bool box;
    bool opened;

    string color;
    double linewidth;
    bool dotted;
    bool dashed;
    ofstream *texfile;
    
public:
    Point2D p1;
    Point2D p2;
    Point2D origin;
    Rectangle bounding_box;
    
    TikzPicture(Point2D p_p1, Point2D p_p2, Point2D p_origin, bool p_box): p1{p_p1}, p2{p_p2}, box{p_box} {
        set_origin(p_origin);
        dotted = false;
        dashed = false;
        linewidth = 0.5;
        color = "black";
        opened = false;
    }
    TikzPicture(Point2D p_p1, Point2D p_p2, bool p_box): TikzPicture(p_p1, p_p2, Point2D(0, 0), p_box) {}
    TikzPicture(Point2D p_p1, Point2D p_p2): TikzPicture(p_p1, p_p2, Point2D(0, 0), false) {}
    ~TikzPicture() {}
    
    // Setters
    void set_origin(Point2D p_origin) {
        origin = p_origin;
        minx = p1.x - origin.x;
        maxx = p2.x - origin.x;
        miny = p1.y - origin.y;
        maxy = p2.y - origin.y;
    
        bounding_box = Rectangle(Point2D(minx, miny), Point2D(maxx, maxy));
    }
    
    void set_box(bool p_box) {
        box = p_box;
    }
    
    void set_texfile(ofstream &p_texfile) {
        texfile = &p_texfile;
    }
    
    // Open and close picture
    void open() {
        if(opened) {
            return;
        }
        
        ostringstream shift;
        if(origin != Point2D(0, 0)) {
            shift << "{([shift={" << point2coordinates(origin) << "}]current page.south west)}";
        }
        else {
            shift << "{(current page.south west)}";
        }
        
        cout << "Writing start of tikzpicture" << endl;
        *texfile << "\\begin{tikzpicture}[remember picture, overlay, shift=" << shift.str() << ", every node/.style={inner sep=0mm, outer sep=0mm, minimum size=0mm, text height=\\normaltextheight, text depth=\\normaltextdepth}]" << endl;
        opened = true;
        
        if(box) {
            draw_bounding_box();
        }
    }
    
    void close() {
        if(opened) {
            *texfile << "\\end{tikzpicture}" << endl << endl;
            texfile = NULL;
        }
    }
    
    // Drawing option methods
    void set_color(string color) {
        color = color;
    }
    
    void set_linewidth(double linewidth) {
        linewidth = linewidth;
    }
    
    void set_dashed(bool dashed) {
        this->dashed = dashed;
    }
    
    void dashed_on() {
        set_dotted(false);
        set_dashed(true);
    }
    
    void dashed_off() {
        set_dashed(false);
    }
    
    void set_dotted(bool dotted) {
        this->dotted = dotted;
    }
    
    void dotted_on() {
        set_dashed(false);
        set_dotted(true);
    }
    
    void dotted_of() {
        set_dotted(false);
    }
    
    string draw_options() {
        ostringstream options;
        options << "[";
        options << "line width=" << linewidth << "pt,";
        options << color;
        
        if(dotted) {
            options << ",dotted";
        }
        if(dashed) {
            options << ",dashed";
        }
        options << "]";
        
        return options.str();
    }
    
    // Drawing methods for shapes
    void draw_line(const Line l) {
        open();
        *texfile << "\\draw " << draw_options() << " " << point2coordinates(l.point1) << "--" << point2coordinates(l.point2) << ";" << endl;
    }
    
    void draw_path(const vector<Point2D> points, bool cycle=true) {
        open();
        *texfile << "\\draw " << draw_options() << " " << points2path(points, cycle) << ";" << endl;
    }
    
    void draw_polygon(const Polygon p) {
        draw_path(p.points, p.closed);
    }
    
    void draw_rectangle(const Rectangle r) {
        open();
        *texfile << "\\draw " << draw_options() << " " << point2coordinates(r.point1) << " rectangle " << point2coordinates(r.point2) << ";" << endl;
    }
    
    void fill_rectangle(const Rectangle r) {
        open();
        *texfile << "\\fill [" << color << "] " << point2coordinates(r.point1) << " rectangle " << point2coordinates(r.point2) << ";" << endl;
    }
    
    void draw_bounding_box() {
        draw_rectangle(bounding_box);
    }
    
    void draw_circle(const Circle c) {
        open();
        *texfile << "\\draw " << draw_options() << point2coordinates(c.center) << " circle (" << c.radius << "mm);" << endl;
    }
    
    void fill_circle(const Circle c) {
        open();
        *texfile << "\\fill [" << color << "] " << point2coordinates(c.center) << " circle (" << c.radius << "mm);" << endl;
    }
};

#endif /* TikzPicture_h */
