//
//  FontSize.h
//  StarMap
//
//  Created by Roel Zinkstok on 08/05/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#ifndef FontSize_h
#define FontSize_h



int calculateFontSize(int index, double normalsize) {
    // series for 11 pt at normal size (index = 7
    return (int)round((normalsize/11.0) * 3.8282 * exp(0.1515 * index));
}


map<string, int> getFontSize(double normalsize=11) {
    map<string, int> result;
    vector<string> texsizes = {"nano", "miniscule", "tiny", "scriptsize", "footnotesize", "small", "normalsize", "large", "Large", "LARGE", "huge", "Huge", "HUGE"};
    for(int i=0; i<texsizes.size(); i++) {
        result[texsizes[i]] = calculateFontSize(i+1, normalsize);
    }
//
//    result["nano"] = calculateFontSize(1);
//    point11["miniscule"] = 5;
//    point11["tiny"] = 6;
//    point11["scriptsize"] = 8;
//    point11["footnotesize"] = 9;
//    point11["small"] = 10;
//    point11["normalsize"] = 11;
//    point11["large"] = 12;
//    point11["Large"] = 14;
//    point11["LARGE"] = 17;
//    point11["huge"] = 21;
//    point11["Huge"] = 25;
//    point11["HUGE"] = 45;
    //return (int)round(point11[size] * normalsize/11.0);
    return result;
}

#endif /* FontSize_h */
