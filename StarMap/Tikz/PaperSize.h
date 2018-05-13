//
//  PaperSize.h
//  StarMap
//
//  Created by Roel Zinkstok on 08/05/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#ifndef PaperSize_h
#define PaperSize_h


struct papersize {
    double width;
    double height;
};


papersize getAPaperSize(int index) {
    if(index<0) {
        throw "Invalid papersize";
    }
    
    double x = sqrt(1000000.0/(pow(2, index) * sqrt(2)));
    double y = sqrt(2) * x;
    
    return papersize{x, y};
}


papersize getBPaperSize(int index) {
    if(index<0) {
        throw "Invalid papersize";
    }
    
    papersize ps1 = getAPaperSize(index);
    papersize ps2 = getAPaperSize(index+1);
    return papersize{0.5*(ps1.width + ps2.width), 0.5*(ps1.height + ps2.height)};
}


papersize getCPaperSize(int index) {
    if(index<0) {
        throw "Invalid papersize";
    }
    
    papersize ps1 = getAPaperSize(index);
    papersize ps2 = getBPaperSize(index);
    return papersize{0.5*(ps1.width + ps2.width), 0.5*(ps1.height + ps2.height)};
    
}


papersize getPaperSize(string ps) {
    int index = stoi(ps.substr(1));
    papersize result;
    
    switch(ps[0]) {
        case 'A':
            result = getAPaperSize(index);
        case 'B':
            result = getBPaperSize(index);
        case 'C':
            result = getCPaperSize(index);
        default:
            return result;
    }
}


#endif /* PaperSize_h */
