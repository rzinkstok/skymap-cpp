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
using namespace std;

string exec(const char* cmd);
const string texbin= "/Library/TeX/texbin/";


class TikzFigure {
public:
    string basedir;
    string name;
    string path;
    ofstream texfile;
    bool landscape;
    int fontsize;
    double paperwidth;
    double paperheight;
    
    TikzFigure():
        basedir{"/Users/rzinkstok/temp/tikz/"},
        landscape{true},
        fontsize{11},
        paperwidth{297},
        paperheight{210}
    {
        name = "test";
        path = basedir + name + ".tex";
    }
    TikzFigure(const TikzFigure &other) {}
    ~TikzFigure() {}
    
    TikzFigure& operator= (const TikzFigure &other) {
        return *this;
    }
    
    void open() {
        cout << "Opening file" << path << endl;
        texfile.open(path);
        if (texfile.is_open()) {
            cout << "File opened correctly" << endl;
        }
        else {
            cout << "File not opened" << endl;
        }
    }
        
    void write_header() {
        if(!texfile.is_open()) {
            return;
        }
        cout << "Writing header" << endl;
        texfile << "\\documentclass[";
        
        if(landscape) {
            texfile << "landscape,";
        }
        texfile << fontsize << "pt]{{article}}" << endl;
        texfile << "\\usepackage[paperwidth=" << paperwidth << "mm,paperheight=" << paperheight << "mm]{{geometry}}" << endl;
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
        texfile << "" << endl;
        texfile << "\\begin{document}" << endl;
        texfile << "\\pagenumbering{gobble}" << endl;
        texfile << "" << endl;
        texfile << "\\newcommand\\normaltextheightem{0.75} % Text height for normalsize" << endl;
        texfile << "\\newcommand\\normaltextdepthem{0.24} % Text depth for normalsize" << endl;
        texfile << "\\pgfmathsetmacro{\\normaltextheight}{\\normaltextheightem em/1mm} % Converted to mm" << endl;
        texfile << "\\pgfmathsetmacro{\\normaltextdepth}{\\normaltextdepthem em/1mm} % Converted to mm" << endl;
        
//            for fontsize, pointsize in self.fontsizes.items():
//                texfile << "\\pgfmathsetmacro{{\\{}textheight}}{{{}*\\normaltextheight/{}}} % Text height for {} ({} pt)\n".format(fontsize, pointsize, self.fontsize, fontsize, pointsize))
//                texfile << "\\pgfmathsetmacro{{\\{}textdepth}}{{{}*\\normaltextdepth/{}}} % Text depth for {} ({} pt)\n".format(fontsize, pointsize, self.fontsize, fontsize, pointsize))
//                texfile << "" << endl;
//                texfile << "\\newfontfamily\\condensed{Myriad Pro Condensed}[Numbers={Lining,Proportional}]" << endl;
//                texfile << "" << endl;
    }
    
    void write_footer() {
        if(!texfile.is_open()) {
            return;
        }
        cout << "Writing footer" << endl;
        texfile << "\\end{document}" << endl;
    }
    
    void close() {
        if(!texfile.is_open()) {
            return;
        }
        cout << "Closing file" << endl;
        texfile.close();
    }
    
    void write() {
        open();
        write_header();
        
        texfile << "\\begin{tikzpicture}" << endl;
        texfile << "\\draw (0,0) circle (5mm);" << endl;
        texfile << "\\end{tikzpicture}" << endl;
        
        write_footer();
        close();
    }
    
    void render() {
        cout << "Rendering " << name << endl;
        ostringstream cmdss;
        cmdss << "cd " << basedir << " && " << texbin << "xelatex " << name << ".tex";
        string cmd = cmdss.str();
        string result = exec(cmd.c_str());
        //cout << result << endl;
    }
};

#endif /* TikzFigure_h */
