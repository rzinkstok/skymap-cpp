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
#include "TikzFigure.h"
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
    try {
        TikzFigure t = TikzFigure();
        t.write();
        t.render();
    }
    catch(...) {
        return top_level_error( "Unexpected C++ exception." );
    }
    return 0;
}
