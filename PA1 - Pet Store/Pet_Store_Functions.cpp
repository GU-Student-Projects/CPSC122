/**
 * File:           Pet Store Functions.cpp
 * Author:          Gabe DiMartino
 * Date Modified:   31 August 2023
 * Description:     Functions for the Pet Store Main
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

bool fileOpen(std::string, std::ifstream&);
std::vector<std::string> getHeaders(std::ifstream&);
std::vector<std::string> getData(std::ifstream&);
void fileClose(std::ifstream&);
int countRows(std::ifstream& myFile);

int main(){
    std::ifstream myFile;
    std::string filename = "petstoredata.csv";

    bool isOpen;
    std::vector<std::vector<std::string>> data;

    isOpen = fileOpen(filename, myFile);

    if(isOpen){ 
        std::vector<std::string> headers = getHeaders(myFile);

        std::cout << "Processed " << headers.size() << " header columns: ";
        for (size_t i = 0; i < headers.size(); ++i) {
            std::cout << headers[i];
            if (i < headers.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;



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

 std::vector<std::string> getHeaders(std::ifstream& myFile){
    std::vector<std::string> headers;
    std::string headerLine;

    if (std::getline(myFile, headerLine)) {
        std::istringstream lineToParse(headerLine);
        std::string cell;

        while (std::getline(lineToParse, cell, ',')) {
            headers.push_back(cell);
        }
    } else {
        std::cerr << "Error, couldnt read" << std::endl;
    }
    
    return headers;
}


void fileClose(std::ifstream& myFile){
    myFile.close();
}
    

