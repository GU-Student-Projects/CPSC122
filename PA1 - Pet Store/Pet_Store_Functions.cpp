/**
 * File:           Pet Store Functions.cpp
 * Author:          Gabe DiMartino
 * Date Modified:   31 August 2023
 * Description:     Functions for the Pet Store Main
 */

#include <iostream>
#include <fstream>
#include <vector>

bool fileOpen(std::string, std::ifstream&);
std::string printFile(std::ifstream&);
void fileClose(std::ifstream&);

int main(){
    std::ifstream myFile;
    std::string filename = "petstoredata.csv";

    bool isOpen;
    std::string text;

    isOpen = fileOpen(filename, myFile);

    if(isOpen){ 
        text = printFile(myFile);
        std::cout << text <<std::endl;
        fileClose(myFile);
    }
    else 
        std::cout << "The file " + filename + " has encountered an error. Please make sure the file is in the correct directory and you have the appropriate permissions to read/write/execute" << std::endl;
    return 0;
}



bool fileOpen(std::string filename, std::ifstream& myFile){
    myFile.open(filename);
    if(myFile.is_open())
        return true;
    else
        return false;

}

std::string printFile(std::ifstream& myFile){
    std::string line;
    std::string text;

    while (std::getline(myFile, line)){
        text += line + "\n";
    }
    return text;
}

void fileClose(std::ifstream& myFile){
    myFile.close();
}
    

