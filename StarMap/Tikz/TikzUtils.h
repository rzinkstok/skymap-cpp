//
//  TikzUtils.h
//  StarMap
//
//  Created by Roel Zinkstok on 11/05/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#ifndef TikzUtils_h
#define TikzUtils_h


string point2coordinates(const Point2D &p) {
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


string points2path(const vector<Point2D> points, bool cycle=true) {
    // Builds a Tikz path from the given list of points
    ostringstream path;
    
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


class TikzClip {
private:
    ofstream *texfile;
public:
    TikzClip(ofstream *p_texfile, vector<Point2D> &path) {
        texfile = p_texfile;
        *texfile << "\\begin{scope}" << endl;
        *texfile << "\\clip " << points2path(path) << ";" << endl;
    }
    ~TikzClip() {
        *texfile << "\\end{scope}" << endl;
    }
};

#endif /* TikzUtils_h */
