#include "bundle.h"

Bundle::Bundle(){
    this->inFile = "";
    this->outFile = "";
}

Bundle::Bundle(std::vector<std::string> commands){
    this->inFile = "";
    this->outFile = "";
    set_commands(commands);
}

Bundle::Bundle(std::string infile, std::string outfile){
    this->inFile = infile;
    this->outFile = outfile;
}

Bundle::Bundle(std::string infile, std::string outfile, std::vector<std::string> commands){
    this->inFile = infile;
    this->outFile = outfile;
    set_commands(commands);
}

void Bundle::set_inFile(std::string inFile){
    this->inFile = inFile;
}

std::string Bundle::get_inFile(){
    return this->inFile;
}

void Bundle::set_outFile(std::string outFile){
    this->outFile = outFile;
}

std::string Bundle::get_outFile(){
    return this->outFile;
}

void Bundle::set_commands(std::vector<std::string> commands){
    int length = commands.size();
    for(int i = 0; i < length; i++){
        this->commands.push_back(commands[i]);
    }
}

std::vector<std::string> Bundle::get_commands(){
    return this->commands;
}

Bundle& Bundle::operator=(const Bundle& other){
    if(this != &other){
        this->inFile = other.inFile;
        this->outFile = other.outFile;
        this->commands = other.commands;
        
    }
    return *this;
}