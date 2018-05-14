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
    int width;
    int height;
    string name;
};


papersize getAPaperSize(int index, bool landscape=false) {
    if(index<0) {
        throw "Invalid papersize";
    }
    
    int x = (int)round(sqrt(1000000.0/(pow(2, index) * sqrt(2))));
    int y = (int)round(sqrt(2) * x);
    
    if(landscape) {
        return papersize{y, x, "A" + to_string(index)};
    }
    else {
        return papersize{x, y, "A" + to_string(index)};
    }
}


papersize getBPaperSize(int index, bool landscape=false) {
    if(index<0) {
        throw "Invalid papersize";
    }
    
    papersize ps1 = getAPaperSize(index, landscape);
    papersize ps2 = getAPaperSize(index+1, landscape);
    
    return papersize{(int)round(0.5*(ps1.width + ps2.width)), (int)round(0.5*(ps1.height + ps2.height)), "B" + to_string(index)};
}


papersize getCPaperSize(int index, bool landscape=false) {
    if(index<0) {
        throw "Invalid papersize";
    }
    
    papersize ps1 = getAPaperSize(index, landscape);
    papersize ps2 = getBPaperSize(index, landscape);
    
    return papersize{(int)round(0.5*(ps1.width + ps2.width)), (int)round(0.5*(ps1.height + ps2.height)), "C" + to_string(index)};
}


papersize getPaperSize(string ps, bool landscape=false) {
    int index = stoi(ps.substr(1));
    
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
