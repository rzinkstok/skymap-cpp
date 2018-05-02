//
//  TikzFigure.cpp
//  StarMap
//
//  Created by Roel Zinkstok on 01/05/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <math.h>
#include "Point2D.h"
using namespace std;

string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    
    shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

string point2coordinates(Point2D &p) {
    double x = p.x;
    double y = p.y;
    if(abs(x) < 1e-4) {
        x = 0.0;
    }
    if(abs(y) < 1e-4) {
        y = 0.0;
    }
    ostringstream ss;
    ss << "(" << x << "mm," << y << "mm)";
    return ss.str();
}

string points2path(Point2D points[], int n, bool cycle=true) {
    // Builds a Tikz path from the given list of points
    ostringstream path;
    
    for(int i=0; i<n; i++) {
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
