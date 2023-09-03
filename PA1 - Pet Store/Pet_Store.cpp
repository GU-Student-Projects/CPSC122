/**
 * File:            Pet_Store.cpp
 * Author:          Gabe DiMartino
 * Date Modified:   2 September 2023
 * Description:     Main file to run the Pet Store
 */

#include "Pet_Store.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>

int main() {
// SW development method
// 1. problem requirements
// Extract a 2d array from a CSV file and sort it into vectors. From the vectors, output to
// both the console and a TXT file.
// 2. analyze the problem
// inputs: CSV
// outputs: process console and write to TXT
// relationships:
// Pet Name, Pet Type, Pet Store Name, Days at Store, Header
// Pet Type = Size of List
// Pet Store Names to Unique Pet Store Names and how many pets are at each store
// Days at Store to average days
// Pet name to random pet name based on size of CSV
// 3. design the algorithm (pseudocode)
// Get row 1 and sort to headers
// Get Rest of rows and seperate into 4 vectors
// Compute average days
// Compute Pets at each store
// Compute Unique Pet Stores
// Compute Random Pet Name
// Compute Total amount of pets
// display total amount result
// print result to text
// 4. implement the algorithm (C++)

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
