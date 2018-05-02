//
//  Projection.cpp
//  StarMap
//
//  Created by Roel Zinkstok on 28/04/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#include <stdio.h>
#include "Point2D.h"
#include "Projection.h"

double Projection::reduce_longitude(double longitude) const {
    return reduce_angle(longitude, get_center_longitude());
}
