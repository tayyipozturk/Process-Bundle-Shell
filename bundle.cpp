#include "bundle.h"

Bundle::Bundle(){
    this->name = "";
    this->inFile = "";
    this->outFile = "";
}

Bundle::~Bundle(){
    this->name = "";
    this->inFile = "";
    this->outFile = "";
    this->commands.clear();
}

Bundle::Bundle(std::string name, std::vector<char**> commands){
    this->name = "";
    this->inFile = "";
    this->outFile = "";
    set_commands(commands);
}

Bundle::Bundle(std::string name, std::string inFile, std::string outFile){
    this->name = name;
    this->inFile = inFile;
    this->outFile = outFile;
}

Bundle::Bundle(std::string name, std::string inFile, std::string outFile, std::vector<char**> commands){
    this->name = name;
    this->inFile = inFile;
    this->outFile = outFile;
    set_commands(commands);
}

void Bundle::set_name(std::string name){
    this->name = name;
}

std::string Bundle::get_name(){
    return this->name;
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

void Bundle::set_commands(std::vector<char**> commands){
    int length = commands.size();
    for(int i = 0; i < length; i++){
        this->commands.push_back(commands[i]);
    }
}

void Bundle::add_command(char** cmd){
    this->commands.push_back(cmd);
}

std::vector<char**> Bundle::get_commands(){
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

void Bundle::print(){
    int n = this->commands.size();
    std::cout << "Bundle Name: \"" << this->name << "\""<<std::endl;
    for(int i = 0; i < n; i++){
        std::cout << "Command " << i+1 << " : ";
        for(int j = 0; this->commands[i][j] != NULL; j++){
            std::cout << "\""<< this->commands[i][j]<< "\" ";
        }
        std::cout<<std::endl;
    }
    if(inFile != ""){
        std::cout << "Infile: \"" << this->inFile << "\"" << std::endl;
    }
    if(outFile != ""){
        std::cout << "Outfile: \"" << this->outFile << "\"" << std::endl;
    }
}

int Bundle::execute(){
    std::vector<char**> cmd = this->get_commands();
    std::vector<pid_t> pids;
    int parent = 1;

    for(int i = 0; i < cmd.size(); i++){
        char **command = cmd[i];
        pid_t pid = fork();
        //Child process
        if(pid == 0){
            parent=0;
            if(inFile != ""){
                int infile_desc = open(this->inFile.c_str(), O_RDONLY, 00700);
                dup2(infile_desc, 0);
                close(infile_desc);
            }

            if(outFile!=""){
                int outfile_desc = open(this->outFile.c_str(), O_CREAT | O_APPEND | O_WRONLY, 00700);
                dup2(outfile_desc, STDOUT_FILENO);
                close(outfile_desc);
            }
            int status = execvp(command[0], command);
            if(status == -1){
                std::cout << "Error: " << strerror(errno) << std::endl;
                exit(1);
            }
            exit(0);
        }
        else{
            pids.push_back(pid);
        }
    }
    //Wait for child processes to finish
    if(parent){
        for(int i = 0; i < pids.size(); i++){
            int status;
            //std::cout<< "Waiting process " << i << std::endl;
            waitpid(pids[i], &status, 0);
        }
    }
    return 0;
}