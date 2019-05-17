//
//  FontSize.h
//  StarMap
//
//  Created by Roel Zinkstok on 08/05/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#pragma once
#include <cmath>
#include <string>
#include <vector>
#include <map>

/**
 *   @brief  Calculates the pointsize for a TeX fontsize using the specified normalsize as reference
 *
 *   @param  index indicates the
 *   @param  normalsize specifies the point size for normalsize fonts
 */
int calculateFontSize(int index, double normalsize) {
    return (int)round((normalsize/11.0) * 3.8282 * exp(0.1515 * index));
}


/**
 *   @brief  Generates a map containing the point sizes for all TeX fontsizes given a specified normalsize as reference
 *
 *   @param  normalsize specifies the point size for normalsize fonts
 */
std::map<std::string, int> getFontSize(double normalsize=11) {
	std::map<std::string, int> result;
	std::vector<std::string> texsizes = {"nano", "miniscule", "tiny", "scriptsize", "footnotesize", "small", "normalsize", "large", "Large", "LARGE", "huge", "Huge", "HUGE"};
    for(int i=0; i<texsizes.size(); i++) {
        result[texsizes[i]] = calculateFontSize(i+1, normalsize);
    }
    return result;
}