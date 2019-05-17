//
//  TikzUtils.h
//  StarMap
//
//  Created by Roel Zinkstok on 11/05/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#pragma once
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "../Geometry/Point2D.h"


/**
 *   @brief  Converts a Point2D instance to a Tikz coordinate string
 *
 *   @param  p is a Point2D that is to be converted
 *   @return a string representing the coordinates of the point
 */
std::string point2coordinates(const Point2D &p) {
    double x = p.x;
    double y = p.y;
    if(abs(x) < 1e-4) {
        x = 0.0;
    }
    if(abs(y) < 1e-4) {
        y = 0.0;
    }
	std::ostringstream ss;
    ss << "(" << x << "mm," << y << "mm)";
    return ss.str();
}


/**
 *   @brief  Converts a vector of Point2D instances to a Tikz path
 *
 *   @param  points is a vector of Point2D instances
 *   @param  cycle indicates whether the path should be closed using --cycle
 *   @return a string representing the path
 */
std::string points2path(const std::vector<Point2D> points, bool cycle=true) {
    // Builds a Tikz path from the given list of points
	std::ostringstream path;
    
    for(int i=0; i<points.size(); i++) {
        if(i!=0) {
            path << "--";
        }
        path << point2coordinates(points[i]);
    }
    if(cycle) {
        path << "--cycle";
    }
    return path.str();
}


/**
 *   @brief  Context manager for clipping
 *
 *   @section Usage
 *   Delineate the scope of the clipping by using braces. Instantiate a TikzClip object before any
 *   other drawing commands.
 */
class TikzClip {
private:
	std::ofstream *texfile;
public:
    /**
     *   @brief  Constructor, starts the clipping scope and sets the clipping path
     *
     *   @param  p_texfile is the ofstream of the opened tex file
     *   @param  path is the clipping path to use
     */
    TikzClip(std::ofstream *p_texfile, std::vector<Point2D> &path) {
        texfile = p_texfile;
        *texfile << "\\begin{scope}" << std::endl;
        *texfile << "\\clip " << points2path(path) << ";" << std::endl;
    }
    
    /**
     *   @brief  Destructor, ends the clipping scope
     */
    ~TikzClip() {
        *texfile << "\\end{scope}" << std::endl;
    }
};