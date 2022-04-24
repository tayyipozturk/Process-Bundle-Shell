#ifndef BUNDLE_H
#define BUNDLE_H

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

class Bundle{
    std::string name;
    std::string inFile;
    std::string outFile;
    std::vector<char**> commands;
    
    public:
    //Constructor
    Bundle();

    //Destructor
    ~Bundle();

    //Constructor
    Bundle(std::string name, std::vector<char**> commands);

    //Constructor
    Bundle(std::string name, std::string inFile, std::string outFile);

    //Constructor
    Bundle(std::string name, std::string inFile, std::string outFile, std::vector<char**> commands);

    //Set bundle name
    void set_name(std::string name);

    //Get bundle name
    std::string get_name();

    //Set input file
    void set_inFile(std::string inFile);

    //Get input file
    std::string get_inFile();

    //Set output file
    void set_outFile(std::string outFile);

    //Get output file
    std::string get_outFile();

    //Set shell commands
    void set_commands(std::vector<char**> commands);

    //Add shell command
    void add_command(char** cmd);

    //Get shell commands
    std::vector<char**> get_commands();

    //Assignment operator for Bundle object
    Bundle& operator=(const Bundle& other);

    //Print bundle info
    void print();

    //Execute just the specified bundle
    int execute();
};

#endif