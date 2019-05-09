//
//  Tikz.cpp
//  StarMap
//
//  Created by Roel Zinkstok on 01/05/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <math.h>
using namespace std;


/**
 *   @brief  Executes a command in the shell
 *
 *   @param  cmd is the command to be executed
 *   @return a string containing the console output of the command
 */
string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    
    shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

