//
//  Tikz.h
//  StarMap
//
//  Created by Roel Zinkstok on 01/05/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#ifndef Tikz_h
#define Tikz_h

#define _USE_MATH_DEFINES
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "../Geometry/Shapes.h"
#include "./PaperSize.h"
#include "./FontSize.h"
#include "./TikzUtils.h"
#include "./TikzPicture.h"

using namespace std;

// Function declarations
string exec(const char*);


// Constants
const string texbin= "/Library/TeX/texbin/";


// Classes

/**
 *   @brief  Tikz is the base class for a Tikz document.
 */
class Tikz {
private:
    bool landscape;
    int fontnormalsize;
    map<string, int> fontsizemap;
    papersize size;
    TikzPicture *current_picture;
    bool started;
    bool finished;
    string basedir;
    string name;
    string path;
    ofstream texfile;
    
public:
    /**
     *   @brief  Default constructor.
     */
    Tikz(): Tikz("c:\\temp\\", "test", "A4", false, 11) {}
    
    /**
     *   @brief  Constructor
     *
     *   @param  p_basedir is the directory where the tex files will be generated
     *   @param  p_name is the file basename for the tex file
     *   @param  p_size is the papersize used (e.g. "A4")
     *   @param  p_landscape indicates whether the page is oriented landscape
     *   @param  p_fontsize indicates the fontsize for the normalsize font
     */
    Tikz(string p_basedir, string p_name, string p_size, bool p_landscape, int p_fontsize):
        basedir(p_basedir), name(p_name), current_picture(NULL), started(false), finished(false), path(basedir + name + ".tex"), landscape(p_landscape)
    {
        set_size(p_size);
        set_fontsize(p_fontsize);
    }
    
    /**
     *   @brief  Copy constructor
     */
    Tikz(const Tikz &other) {}
    
    /**
     *   @brief  Default destructor
     */
    ~Tikz() {}
    
    /**
     *   @brief  Copy assignment operator
     */
    Tikz& operator= (const Tikz &other) {
        return *this;
    }
    
    /**
     *   @brief  Sets the paper size
     *
     *   @param  p_size is the requested paper size (e.g. "A4")
     */
    void set_size(string p_size) {
        if(started) {
            throw "Cannot set size when Tikz is already started";
        }
        size = getPaperSize(p_size, landscape);
    }
    
    /**
     *   @brief  Sets the orientation
     *
     *   @param  p_landscape indicates whether the page is oriented landscape
     */
    void set_landscape(bool p_landscape) {
        if(started) {
            throw "Cannot set landscape when Tikz is already started";
        }
        landscape = p_landscape;
        size = getPaperSize(size.name, landscape);
    }
    
    /**
     *   @brief  Sets the fontsize for the normalsize font
     *
     *   @param  p_fontsize indicates the fontsize for the normalsize font
     */
    void set_fontsize(int p_fontsize) {
        if(started) {
            throw "Cannot set fontsize when Tikz is already started";
        }
        fontnormalsize = p_fontsize;
        fontsizemap = getFontSize(fontnormalsize);
    }
    
    /**
     *   @brief  Opens the tex file
     */
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
    
    /**
     *   @brief  Closes the tex file
     */
    void close() {
        if(!texfile.is_open()) {
            return;
        }
        
        cout << "Closing file" << endl;
        texfile.close();
    }
    
    /**
     *   @brief  Writes all boilerplate header stuff for a Tikz document
     */
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
    
    /**
     *   @brief  Writes all boilerplate footer stuff for a Tikz document
     */
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
    
    /**
     *   @brief  Starts a Tikz document by opening the tex file and writing the header
     */
    void start() {
        open();
        write_header();
        started = true;
    }

    /**
     *   @brief  Finishes a Tikz document by writing the footer and closing the tex file
     */
    void finish() {
        write_footer();
        close();
        finished = true;
    }
    
    /**
     *   @brief  Adds a TikzPicture to the current document
     *
     *   @param  picture is a TikzPicture that is to be added to the document
     */
    void add(TikzPicture &picture) {
        if(!started) {
            start();
        }
        if(current_picture != NULL) {
            current_picture->close();
        }
        current_picture = &picture;
        picture.set_texfile(texfile);
    }
    
    /**
     *   @brief  Render the Tikz document by running XeLaTeX twice on the tex file
     */
    void render() {
        if(!started) {
            start();
        }
        if(!finished) {
            finish();
        }
        cout << "Rendering " << name << endl;
        ostringstream cmdss;
        cmdss << "cd " << basedir << " && " << texbin << "xelatex " << name << ".tex";
        string cmd = cmdss.str();
        string result = exec(cmd.c_str());
        result = exec(cmd.c_str());
        cout << result << endl;
    }
};

#endif /* Tikz_h */
