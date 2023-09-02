#include "Pet_Store.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int main() {
    PetStore petStore;

    std::ifstream myFile;
    std::string filename = "petstoredata.csv";
    std::vector<std::string> headers, petStoreName, petName, petType;
    std::vector<int> daysAtStore;

    if (petStore.processData(filename, myFile, headers, petStoreName, petName, petType, daysAtStore)) {
        // Data processing was successful
        return 0;
    } else {
        // Data processing encountered an error
        return 1;
    }
}
