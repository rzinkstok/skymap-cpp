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
    return (int)round((normalsize/11.0) * 3.8282 * exp(0.1515 * index));
}


map<string, int> getFontSize(double normalsize=11) {
    map<string, int> result;
    vector<string> texsizes = {"nano", "miniscule", "tiny", "scriptsize", "footnotesize", "small", "normalsize", "large", "Large", "LARGE", "huge", "Huge", "HUGE"};
    for(int i=0; i<texsizes.size(); i++) {
        result[texsizes[i]] = calculateFontSize(i+1, normalsize);
    }
    return result;
}

#endif /* FontSize_h */
