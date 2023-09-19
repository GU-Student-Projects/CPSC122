/*
Name: Gabe DiMartino
Class: CPSC122, Fall 2023
Date: September 17, 2023
Programming Assignment: PA2
Description: This cpp contains all of the implementations of functions
*/

#include "Pet_Store.h"

int main(){
    int numDaysAtStore = 0; //This variable keeps track of the size of your numDays dynamic array
    int* numDaysAtStoreSize = &numDaysAtStore;
    int* numDaysAtStorePtr = new int[*numDaysAtStoreSize];//This variable is a pointer to your dynamic integer array.
    std::vector<std::string> headers, petStoreNames, petNames, petTypes, uniquePetStoreNames, alphabetizedPetNames;

    std::string infilename = "petstoredata.csv";
    std::string outfilename = "petreport.txt";
    std::ifstream inFile;
    std::ofstream outFile;

   numDaysAtStorePtr = processData(infilename, inFile, headers, petStoreNames, petNames, petTypes, numDaysAtStorePtr, numDaysAtStoreSize);
    if (!numDaysAtStore){
        std::cerr << "A fatal error has occured"<<std::endl; //if an error through the error and end the program
        return 1;   
    }
    if (!writeSummary(outfilename, outFile,petStoreNames, petNames, petTypes, numDaysAtStorePtr, numDaysAtStoreSize)){
         std::cerr << "A fatal error has occured"<<std::endl; //if an error through the error and end the program
        return 1;        
    }

    return 0;
}