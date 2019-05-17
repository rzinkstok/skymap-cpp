//
//  Tikz.h
//  StarMap
//
//  Created by Roel Zinkstok on 01/05/2018.
//  Copyright © 2018 Roel Zinkstok. All rights reserved.
//

#pragma once
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


// Function declarations
std::string exec(const char*);


// Constants
const std::string texbin= "";


// Classes

/**
 *   @brief  Tikz is the base class for a Tikz document.
 */
class Tikz {
private:
    bool landscape;
    int fontnormalsize;
	std::map<std::string, int> fontsizemap;
    papersize size;
    TikzPicture *current_picture;
    bool started;
    bool finished;
	std::string basedir;
	std::string name;
	std::string path;
	std::ofstream texfile;
    
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
    Tikz(std::string p_basedir, std::string p_name, std::string p_size, bool p_landscape, int p_fontsize):
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
    void set_size(std::string p_size) {
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
		std::cout << "Opening file " << path << std::endl;
		texfile.open(path);
        if (texfile.is_open()) {
			std::cout << "File opened correctly" << std::endl;
        }
        else {
			std::cout << "File not opened" << std::endl;
        }
    }
    
    /**
     *   @brief  Closes the tex file
     */
    void close() {
        if(!texfile.is_open()) {
            return;
        }
        
		std::cout << "Closing file" << std::endl;
        texfile.close();
    }
    
    /**
     *   @brief  Writes all boilerplate header stuff for a Tikz document
     */
    void write_header() {
        if(!texfile.is_open()) {
            return;
        }
		std::cout << "Writing header" << std::endl;
        texfile << "\\documentclass[" << fontnormalsize << "pt]{article}" << std::endl;
        texfile << "\\usepackage[paperwidth=" << size.width << "mm,paperheight=" << size.height << "mm]{geometry}" << std::endl;
        texfile << "\\usepackage{mathspec}" << std::endl;
        texfile << "\\usepackage{tikz}" << std::endl;
        texfile << "\\usetikzlibrary{positioning}" << std::endl;
        texfile << "\\defaultfontfeatures{Ligatures=TeX}" << std::endl;
        texfile << "\\setallmainfonts[Numbers={Lining,Proportional}]{MyriadPro-SemiCn}" << std::endl;
        texfile << std::endl;
        texfile << "\\makeatletter" << std::endl;
        texfile << "\\ifcase \\@ptsize \\relax% 10pt" << std::endl;
        texfile << "    \\newcommand{\\HUGE}{\\@setfontsize\\HUGE{45}{50}}" << std::endl;
        texfile << "    \\newcommand{\\miniscule}{\\@setfontsize\\miniscule{4}{5}}% \\tiny: 5/6" << std::endl;
        texfile << "    \\newcommand{\\nano}{\\@setfontsize\\nano{3}{4}}% \\tiny: 5/6" << std::endl;
        texfile << "\\or% 11pt" << std::endl;
        texfile << "    \\newcommand{\\miniscule}{\\@setfontsize\\miniscule{5}{6}}% \\tiny: 6/7" << std::endl;
        texfile << "    \\newcommand{\\nano}{\\@setfontsize\\nano{4}{5}}% \\tiny: 6/7" << std::endl;
        texfile << "\\or% 12pt" << std::endl;
        texfile << "    \\newcommand{\\miniscule}{\\@setfontsize\\miniscule{5}{6}}% \\tiny: 6/7" << std::endl;
        texfile << "    \\newcommand{\\nano}{\\@setfontsize\\nano{4}{5}}% \\tiny: 6/7" << std::endl;
        texfile << "\\fi" << std::endl;
        texfile << "\\makeatother" << std::endl;
        texfile << std::endl;
        texfile << "\\begin{document}" << std::endl;
        texfile << "\\pagenumbering{gobble}" << std::endl;
        texfile << std::endl;
        texfile << "\\newcommand\\normaltextheightem{0.75} % Text height for normalsize" << std::endl;
        texfile << "\\newcommand\\normaltextdepthem{0.24} % Text depth for normalsize" << std::endl;
        texfile << "\\pgfmathsetmacro{\\normaltextheight}{\\normaltextheightem em/1mm} % Converted to mm" << std::endl;
        texfile << "\\pgfmathsetmacro{\\normaltextdepth}{\\normaltextdepthem em/1mm} % Converted to mm" << std::endl;
        
        for (const auto &p: fontsizemap) {
            texfile << "\\pgfmathsetmacro{\\" << p.first << "textheight}{" << p.second << "*\\normaltextheight/" << fontnormalsize << "} % Text height for " << p.first << " (" << p.second << " pt)" << std::endl;
            texfile << "\\pgfmathsetmacro{\\" << p.first << "textdepth}{" << p.second << "*\\normaltextdepth/" << fontnormalsize << "} % Text depth for " << p.first << " (" << p.second << " pt)" << std::endl;
        }
        
        texfile << std::endl;
        texfile << "\\newfontfamily\\condensed{MyriadPro-SemiCn}[Numbers={Lining,Proportional}]" << std::endl;
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
		std::cout << "Writing footer" << std::endl;
        texfile << "\\end{document}" << std::endl;
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
		std::cout << "Rendering " << name << std::endl;
		std::ostringstream cmdss;
        cmdss << "cd " << basedir << " && " << texbin << "xelatex " << name << ".tex";
		std::string cmd = cmdss.str();
		std::string result = exec(cmd.c_str());
        result = exec(cmd.c_str());
		std::cout << result << std::endl;
    }
};