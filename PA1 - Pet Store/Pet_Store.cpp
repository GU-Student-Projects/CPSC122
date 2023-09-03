#include "Pet_Store.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>

int main() {
    PetStore petStore;
    srand(time(NULL)); //generate seed

    std::fstream myFile; 
    std::string filename = "petstoredata.csv"; //Name of file
    std::vector<std::string> headers, petStoreName, petName, petType; //initialize vectors
    std::vector<int> daysAtStore;

    if (petStore.processData(filename, myFile, headers, petStoreName, petName, petType, daysAtStore)) {
    } else {

        std::cerr << "A fatal error has occured"<<std::endl; //if an error through the error and end the program
        return 1;
    }

    filename = "petreport.txt";

    if (petStore.writeSummary(filename, myFile, petStoreName, petName, petType, daysAtStore)) {
    } else {

        std::cerr << "A fatal error has occured"<<std::endl; //if an error through the error and end the program
        return 1;
    }

    return 0;
}
