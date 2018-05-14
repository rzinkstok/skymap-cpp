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
#include "Shapes.h"
#include "TikzUtils.h"


/**
 *   @brief  Class representing a Tikz picture
 */
class TikzPicture {
private:
    Point2D p1;
    Point2D p2;
    Point2D origin;
    Rectangle bounding_box;
    double minx;
    double maxx;
    double miny;
    double maxy;
    
    bool boxed;
    bool opened;
    
    string color;
    double linewidth;
    bool dotted;
    bool dashed;
    
    ofstream *texfile;
    
public:
    /**
     *   @brief  Full constructor
     *
     *   @param  p_p1 is the lower left corner of the picture, in paper coordinates
     *   @param  p_p2 is the upper right corner of the picture, in paper coordinates
     *   @param  p_origin is the location of the origin of the picture's coordinate system, in paper coordinates
     *   @param  p_boxed indicates whether a box is drawn around the picture
     */
    TikzPicture(Point2D p_p1, Point2D p_p2, Point2D p_origin, bool p_boxed): p1{p_p1}, p2{p_p2}, boxed{p_boxed} {
        set_origin(p_origin);
        dotted = false;
        dashed = false;
        linewidth = 0.5;
        color = "black";
        opened = false;
    }
    
    /**
     *   @brief  Shorter constructor
     *
     *   @param  p_p1 is the lower left corner of the picture, in paper coordinates
     *   @param  p_p2 is the upper right corner of the picture, in paper coordinates
     *   @param  p_boxed indicates whether a box is drawn around the picture
     */
    TikzPicture(Point2D p_p1, Point2D p_p2, bool p_boxed): TikzPicture(p_p1, p_p2, Point2D(0, 0), p_boxed) {}
    
    /**
     *   @brief  Even shorter constructor
     *
     *   @param  p_p1 is the lower left corner of the picture, in paper coordinates
     *   @param  p_p2 is the upper right corner of the picture, in paper coordinates
     */
    TikzPicture(Point2D p_p1, Point2D p_p2): TikzPicture(p_p1, p_p2, Point2D(0, 0), false) {}
    
    /**
     *   @brief  Default destructor
     */
    ~TikzPicture() {}
    
    // Setters
    
    /**
     *   @brief  Sets the origin of the picture. Also sets the boundary values and bounding box.
     *
     *   @param  p_origin is the location of the origin of the picture's coordinate system, in paper coordinates
     */
    void set_origin(Point2D p_origin) {
        origin = p_origin;
        minx = p1.x - origin.x;
        maxx = p2.x - origin.x;
        miny = p1.y - origin.y;
        maxy = p2.y - origin.y;
    
        bounding_box = Rectangle(Point2D(minx, miny), Point2D(maxx, maxy));
    }
    
    /**
     *   @brief  Sets the parameter for drawing a box around the picture
     *
     *   @param  p_boxed indicates whether a box is drawn around the picture
     */
    void set_boxed(bool p_boxed) {
        if(opened) {
            throw "Cannot set boxed when TikzPicture is already opened";
        }
        boxed = p_boxed;
    }
    
    /**
     *   @brief  Sets the texfile ofstream
     *
     *   @param  p_texfile is a reference to the texfile that can be used for writing.
     */
    void set_texfile(ofstream &p_texfile) {
        if(opened) {
            throw "Cannot set texfile when TikzPicture is already opened";
        }
        texfile = &p_texfile;
    }
    
    /**
     *   @brief  Gets the texfile ofstream used for writing
     *
     *   @return a pointer to the texfile ofstream
     */
    ofstream *get_texfile() const {
        return texfile;
    }
    
    /**
     *   @brief  Gets the path of the bounding box
     *
     *   @return a vector of Point2D instances representing the bounding box of the picture
     */
    vector<Point2D> get_bounding_box_path() const {
        return bounding_box.get_points();
    }
    
    // Open and close picture
    
    /**
     *   @brief  Opens the figure by writing the appropriate begin statement
     */
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
        
        cout << "Open TikzPicture" << endl;
        *texfile << "\\begin{tikzpicture}[remember picture, overlay, shift=" << shift.str() << ", every node/.style={inner sep=0mm, outer sep=0mm, minimum size=0mm, text height=\\normaltextheight, text depth=\\normaltextdepth}]" << endl;
        opened = true;
        
        if(boxed) {
            draw_bounding_box();
        }
    }
    
    /**
     *   @brief  Closes the figure by writing the appropriate end statement
     */
    
    void close() {
        if(opened) {
            cout << "Close TikzPicture" << endl;
            *texfile << "\\end{tikzpicture}" << endl << endl;
            texfile = NULL;
        }
    }
    
    // Drawing option methods
    
    /**
     *   @brief  Sets the color to be used from now on
     *
     *   @param  p_color is a color name
     */
    void set_color(string p_color) {
        color = p_color;
    }
    
    /**
     *   @brief  Sets the linewidth to be used from now on
     *
     *   @param  p_linewidth is the linewidth to be used in points
     */
    void set_linewidth(double p_linewidth) {
        linewidth = p_linewidth;
    }
    
    /**
     *   @brief  Sets whether to use a dashed line style from now on
     *
     *   @param  p_dashed indicates whether to use a dashed pattern for lines
     */
    void set_dashed(bool p_dashed) {
        dashed = p_dashed;
    }
    
    /**
    *   @brief  Switches to a dashed line style
    */
    void dashed_on() {
        set_dotted(false);
        set_dashed(true);
    }
    
    /**
     *   @brief  Switches to a non-dashed line style
     */
    void dashed_off() {
        set_dashed(false);
    }
    
    /**
     *   @brief  Sets whether to use a dotted line style from now on
     *
     *   @param  p_dotted indicates whether to use a dashed pattern for lines
     */
    void set_dotted(bool p_dotted) {
        dotted = p_dotted;
    }
    
    /**
     *   @brief  Switches to a dotted line style
     */
    void dotted_on() {
        set_dashed(false);
        set_dotted(true);
    }
    
    /**
     *   @brief  Switches to a non-dotted line style
     */
    void dotted_off() {
        set_dotted(false);
    }
    
    /**
     *   @brief  Switches to an unbroken line style
     */
    void unbroken() {
        set_dotted(false);
        set_dashed(false);
    }
    
    /**
     *   @brief  compiles the active draw options for use in a Tikz statement
     *
     *   @return a string containing all the active draw options
     */
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
    
    /**
     *   @brief  Draws the given Line in the picture
     *
     *   @param  l is the Line object that is to be drawn
     */
    void draw_line(const Line l) {
        open();
        *texfile << "\\draw " << draw_options() << " " << point2coordinates(l.point1) << "--" << point2coordinates(l.point2) << ";" << endl;
    }
    
    /**
     *   @brief  Draws the given path in the picture
     *
     *   @param  points is a vector of Point2D instances that indicate the path to be drawn
     *   @param  cycle indicates whether to close the path
     */
    void draw_path(const vector<Point2D> points, bool cycle=false) {
        open();
        *texfile << "\\draw " << draw_options() << " " << points2path(points, cycle) << ";" << endl;
    }
    
    /**
     *   @brief  Draws the given Polygon in the picture
     *
     *   @param  p is the Polygon object that is to be drawn
     */
    void draw_polygon(const Polygon p) {
        draw_path(p.points, p.closed);
    }
    
    /**
     *   @brief  Draws the given Rectangle in the picture
     *
     *   @param  r is the Rectangle object that is to be drawn
     */
    void draw_rectangle(const Rectangle r) {
        open();
        *texfile << "\\draw " << draw_options() << " " << point2coordinates(r.point1) << " rectangle " << point2coordinates(r.point2) << ";" << endl;
    }
    
    /**
     *   @brief  Draws the given Rectangle in the picture as a filled rectangle
     *
     *   @param  r is the Rectangle object that is to be drawn
     */
    void fill_rectangle(const Rectangle r) {
        open();
        *texfile << "\\fill [" << color << "] " << point2coordinates(r.point1) << " rectangle " << point2coordinates(r.point2) << ";" << endl;
    }
    
    /**
     *   @brief  Draws the rectangle corresponding to the bounding box of the picture
     */
    void draw_bounding_box() {
        draw_rectangle(bounding_box);
    }
    
    /**
     *   @brief  Draws the given Circle in the picture
     *
     *   @param  c is the Cirle object that is to be drawn
     */
    void draw_circle(const Circle c) {
        open();
        *texfile << "\\draw " << draw_options() << point2coordinates(c.center) << " circle (" << c.radius << "mm);" << endl;
    }
    
    /**
     *   @brief  Draws the given Circle in the picture as a filled circle
     *
     *   @param  c is the Circle object that is to be drawn
     */
    void fill_circle(const Circle c) {
        open();
        *texfile << "\\fill [" << color << "] " << point2coordinates(c.center) << " circle (" << c.radius << "mm);" << endl;
    }
    
    /**
     *   @brief  Draws the given Arc in the picture. For large radius Arcs, interpolation is used.
     *
     *   @param  a is the Arc object that is to be drawn
     */
    void draw_arc(const Arc a) {
        if(a.radius > 2000) {
            draw_path(a.interpolated_points());
        }
        *texfile << "\\draw " << draw_options() << " ([shift=(" << a.start_angle << ":" << a.radius << "mm)]" << a.center.x << "mm," << a.center.y << "mm) ";
        *texfile << "arc (" << a.start_angle << ":" << a.stop_angle << ":" << a.radius << "mm);" << endl;
    }
    
    void draw_label() {
        
    }
    
    // Clipping
    
    /**
     *   @brief  Creates a TikzClip object that can be used for creating clipping scopes
     *
     *   @param  path is a vector of Point2D instances describing the clipping path
     */
    TikzClip clip(vector<Point2D> path) {
        return TikzClip(texfile, path);
    }
};

#endif /* TikzPicture_h */
