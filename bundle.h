#ifndef BUNDLE_H
#define BUNDLE_H

#include <cctype>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <iostream>
#include <vector>

class Bundle{
    std::string inFile;
    std::string outFile;
    std::vector<std::string> commands;

    public:
    //Constructor
    Bundle();

    //Constructor
    Bundle(std::vector<std::string> commands);

    //Constructor
    Bundle(std::string infile, std::string outfile);

    //Constructor
    Bundle(std::string infile, std::string outfile, std::vector<std::string> commands);

    //Set input file
    void set_inFile(std::string inFile);

    //Get input file
    std::string get_inFile();

    //Set output file
    void set_outFile(std::string outFile);

    //Get output file
    std::string get_outFile();

    //Set shell commands
    void set_commands(std::vector<std::string> commands);

    //Get shell commands
    std::vector<std::string> get_commands();

    //Assignment operator for Bundle object
    Bundle& operator=(const Bundle& other);
};

#endif