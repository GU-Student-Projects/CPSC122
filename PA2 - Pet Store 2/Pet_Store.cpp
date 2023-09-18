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
    

    int uniquePetStoreNameCountsSize = 0; //This variable keeps track of the size of your unique counts dynamic array
    int* uniquePetStoreNameCountsPtr =nullptr; //This variable is a pointer to your dynamic integer array
    std::vector<std::string> headers, petStoreNames, petNames, petTypes, uniquePetStoreNames, alphabetizedPetNames;

    std::string filename = "petstoredata.csv";
    std::ifstream inFile;
    std::ofstream outFile;

   if (processData(filename, inFile, headers, petStoreNames, petNames, petTypes, numDaysAtStorePtr, numDaysAtStoreSize)) {
    } else {

        std::cerr << "A fatal error has occured"<<std::endl; //if an error through the error and end the program
        return 1;
    }
    std::cout<<numDaysAtStorePtr[6]<<std::endl;

    return 0;
}