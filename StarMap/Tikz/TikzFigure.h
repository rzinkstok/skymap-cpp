//
//  TikzFigure.h
//  StarMap
//
//  Created by Roel Zinkstok on 01/05/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#ifndef TikzFigure_h
#define TikzFigure_h
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "Shapes.h"
#include "PaperSize.h"
#include "FontSize.h"
#include "TikzUtils.h"
#include "TikzPicture.h"

using namespace std;

// Function declarations
string exec(const char*);


// Constants
const string texbin= "/Library/TeX/texbin/";


// Classes

class TikzFigure {
public:
    string basedir;
    string name;
    string path;
    ofstream texfile;
    bool landscape;
    int fontnormalsize;
    map<string, int> fontsizemap;
    papersize size;
    TikzPicture *current_picture;
    
    TikzFigure(): TikzFigure("/Users/rzinkstok/temp/tikz/", "test", "A4", 11) {}
    TikzFigure(string p_basedir, string p_name, string p_papersize, int p_fontsize):
        basedir{p_basedir}, name{p_name}, fontnormalsize{p_fontsize}
    {
        path = basedir + name + ".tex";
        size = getPaperSize(p_papersize);
        fontsizemap = getFontSize(fontnormalsize);
        current_picture = NULL;
        start();
    }
    TikzFigure(const TikzFigure &other) {}
    ~TikzFigure() {}
    
    TikzFigure& operator= (const TikzFigure &other) {
        return *this;
    }
    
    void open() {
        cout << "Opening file " << path << endl;
        texfile.open(path);
        if (texfile.is_open()) {
            cout << "File opened correctly" << endl;
        }
        else {
            cout << "File not opened" << endl;
        }
    }
    
    void close() {
        if(!texfile.is_open()) {
            return;
        }
        
        cout << "Closing file" << endl;
        texfile.close();
    }
        
    void write_header() {
        if(!texfile.is_open()) {
            return;
        }
        cout << "Writing header" << endl;
        texfile << "\\documentclass[" << fontnormalsize << "pt]{{article}}" << endl;
        texfile << "\\usepackage[paperwidth=" << size.width << "mm,paperheight=" << size.height << "mm]{{geometry}}" << endl;
        texfile << "\\usepackage{mathspec}" << endl;
        texfile << "\\usepackage{tikz}" << endl;
        texfile << "\\usetikzlibrary{positioning}" << endl;
        texfile << "\\defaultfontfeatures{Ligatures=TeX}" << endl;
        texfile << "\\setallmainfonts[Numbers={Lining,Proportional}]{Myriad Pro SemiCondensed}" << endl;
        texfile << endl;
        texfile << "\\makeatletter" << endl;
        texfile << "\\ifcase \\@ptsize \\relax% 10pt" << endl;
        texfile << "    \\newcommand{\\HUGE}{\\@setfontsize\\HUGE{45}{50}}" << endl;
        texfile << "    \\newcommand{\\miniscule}{\\@setfontsize\\miniscule{4}{5}}% \\tiny: 5/6" << endl;
        texfile << "    \\newcommand{\\nano}{\\@setfontsize\\nano{3}{4}}% \\tiny: 5/6" << endl;
        texfile << "\\or% 11pt" << endl;
        texfile << "    \\newcommand{\\miniscule}{\\@setfontsize\\miniscule{5}{6}}% \\tiny: 6/7" << endl;
        texfile << "    \\newcommand{\\nano}{\\@setfontsize\\nano{4}{5}}% \\tiny: 6/7" << endl;
        texfile << "\\or% 12pt" << endl;
        texfile << "    \\newcommand{\\miniscule}{\\@setfontsize\\miniscule{5}{6}}% \\tiny: 6/7" << endl;
        texfile << "    \\newcommand{\\nano}{\\@setfontsize\\nano{4}{5}}% \\tiny: 6/7" << endl;
        texfile << "\\fi" << endl;
        texfile << "\\makeatother" << endl;
        texfile << endl;
        texfile << "\\begin{document}" << endl;
        texfile << "\\pagenumbering{gobble}" << endl;
        texfile << endl;
        texfile << "\\newcommand\\normaltextheightem{0.75} % Text height for normalsize" << endl;
        texfile << "\\newcommand\\normaltextdepthem{0.24} % Text depth for normalsize" << endl;
        texfile << "\\pgfmathsetmacro{\\normaltextheight}{\\normaltextheightem em/1mm} % Converted to mm" << endl;
        texfile << "\\pgfmathsetmacro{\\normaltextdepth}{\\normaltextdepthem em/1mm} % Converted to mm" << endl;
        
        for (const auto &p: fontsizemap) {
            texfile << "\\pgfmathsetmacro{\\" << p.first << "textheight}{" << p.second << "*\\normaltextheight/" << fontnormalsize << "} % Text height for " << p.first << " (" << p.second << " pt)" << endl;
            texfile << "\\pgfmathsetmacro{\\" << p.first << "textdepth}{" << p.second << "*\\normaltextdepth/" << fontnormalsize << "} % Text depth for " << p.first << " (" << p.second << " pt)" << endl;
        }
        
        texfile << endl;
        texfile << "\\newfontfamily\\condensed{Myriad Pro Condensed}[Numbers={Lining,Proportional}]" << endl;
    }
    
    void write_footer() {
        if(!texfile.is_open()) {
            return;
        }
        if(current_picture != NULL) {
            current_picture->close();
        }
        cout << "Writing footer" << endl;
        texfile << "\\end{document}" << endl;
    }
    
    void start() {
        open();
        write_header();
    }

    void finish() {
        write_footer();
        close();
    }
    
    void add(TikzPicture &picture) {
        cout << "Enter add" << endl;
        if(current_picture != NULL) {
            cout << "Current picture is not NULL" << endl;
            current_picture->close();
        }
        cout << "Assigning picture" << endl;
        current_picture = &picture;
        cout << "Setting texfile" << endl;
        picture.set_texfile(texfile);
    }
    
    void render() {
        cout << "Rendering " << name << endl;
        ostringstream cmdss;
        cmdss << "cd " << basedir << " && " << texbin << "xelatex " << name << ".tex";
        string cmd = cmdss.str();
        string result = exec(cmd.c_str());
        cout << result << endl;
    }
    
    
    
 
    
    
};

#endif /* TikzFigure_h */
