//
//  main.cpp
//  StarMap
//
//  Created by Roel Zinkstok on 28/04/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#define VERBOSE false
#include <iostream>
#include <math.h>
#include "Point2D.h"
#include "UnitProjection.h"
#include "EquidistantCylindricalProjection.h"
#include "AzimuthalEquidistantProjection.h"
#include "EquidistantConicProjection.h"
#include "Tikz.h"
#include "TikzPicture.h"
#include "Shapes.h"

using namespace std;

int top_level_error ( const char * const msg ) {
    if ( fprintf( stderr, "Application error: %s\n", msg ) < 0 ) {
        // It's hard to decide what to do here. At least let the developer know.
        assert( false );
    }
    return 1;
}

int main(int argc, const char * argv[]) {
    //try {
        Tikz t = Tikz();
        
        TikzPicture p = TikzPicture(Point2D(0, 0), Point2D(90, 60));
        t.set_landscape(true);
        
        t.add(p);
        
        p.set_origin(Point2D(45,30));
        p.set_boxed(true);
        
        
        p.draw_line(Line(Point2D(10,10), Point2D(80, 50)));
        p.dashed_on();
        p.draw_rectangle(Rectangle(Point2D(5,5), Point2D(85, 55)));
        p.dotted_on();
        p.draw_circle(Circle(Point2D(30,40), 25));
        p.fill_circle(Circle(Point2D(65,25), 10));
        p.fill_rectangle(Rectangle(Point2D(100,140), Point2D(120,150)));
        p.unbroken();
        p.set_clipping_path(p.get_bounding_box_path());
        {
            TikzClip tc = p.clip();
            p.draw_arc(Arc(Point2D(70,50), 50, 45, 370));
        }
        p.fill_circle(Circle(Point2D(70,50), 1));
        t.finish();
        t.render();
//    }
//    catch(...) {
//        return top_level_error( "Unexpected C++ exception." );
//    }
    return 0;
}
