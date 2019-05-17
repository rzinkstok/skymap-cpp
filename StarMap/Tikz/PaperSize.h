//
//  PaperSize.h
//  StarMap
//
//  Created by Roel Zinkstok on 08/05/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#ifndef PaperSize_h
#define PaperSize_h
#include <string>

// Defines a paper size struct containing width, height (both in mm) and the name of the papersize
struct papersize {
    int width;
    int height;
	std::string name;
};


/**
 *   @brief  Gets the papersize for A-series paper sizes
 *
 *   @param  index indicates the numerical value of the paper size (e.g. the 4 in A4)
 *   @param  landscape indicates whether to return the size for a landscape orientation
 */
papersize getAPaperSize(int index, bool landscape=false) {
    if(index<0) {
        throw "Invalid papersize";
    }
    
    int x = (int)round(sqrt(1000000.0/(pow(2, index) * sqrt(2))));
    int y = (int)round(sqrt(2) * x);
    
    if(landscape) {
        return papersize{y, x, "A" + std::to_string(index)};
    }
    else {
        return papersize{x, y, "A" + std::to_string(index)};
    }
}


/**
 *   @brief  Gets the papersize for B-series paper sizes
 *
 *   @param  index indicates the numerical value of the paper size (e.g. the 4 in B4)
 *   @param  landscape indicates whether to return the size for a landscape orientation
 */
papersize getBPaperSize(int index, bool landscape=false) {
    if(index<0) {
        throw "Invalid papersize";
    }
    
    papersize ps1 = getAPaperSize(index, landscape);
    papersize ps2 = getAPaperSize(index+1, landscape);
    
    return papersize{(int)round(0.5*(ps1.width + ps2.width)), (int)round(0.5*(ps1.height + ps2.height)), "B" + std::to_string(index)};
}


/**
 *   @brief  Gets the papersize for C-series paper sizes
 *
 *   @param  index indicates the numerical value of the paper size (e.g. the 4 in C4)
 *   @param  landscape indicates whether to return the size for a landscape orientation
 */
papersize getCPaperSize(int index, bool landscape=false) {
    if(index<0) {
        throw "Invalid papersize";
    }
    
    papersize ps1 = getAPaperSize(index, landscape);
    papersize ps2 = getBPaperSize(index, landscape);
    
    return papersize{(int)round(0.5*(ps1.width + ps2.width)), (int)round(0.5*(ps1.height + ps2.height)), "C" + std::to_string(index)};
}


/**
 *   @brief  Gets the papersize for A, B or C-series paper sizes
 *
 *   @param  ps is a string containing the paper size name
 *   @param  landscape indicates whether to return the size for a landscape orientation
 */
papersize getPaperSize(std::string ps, bool landscape=false) {
    int index = std::stoi(ps.substr(1));
    
    switch(ps[0]) {
        case 'A':
            return getAPaperSize(index, landscape);
        case 'B':
            return getBPaperSize(index, landscape);
        case 'C':
            return getCPaperSize(index, landscape);
        default:
            return papersize{};
    }
}


#endif /* PaperSize_h */
