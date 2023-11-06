/*
Name: Gabe DiMartino
Class: CPSC122, Fall 2023
Date: November 5, 2023
Programming Assignment: PA5
Description: This cpp runs the program
*/

#include "header.h"

int main(){
    PetStoreList storeList;
    std::string infilename = "petstoredata.csv";
    std::string outfilename = "petreport.txt";
    std::ifstream inFile;
    std::ofstream outFile;

   
    if (!processData(infilename, inFile, storeList)){
        std::cerr << "A fatal error has occured"<<std::endl; //if an error through the error and end the program
        return 1;   
    }

    storeList.calculatePetSummary();
    storeList.displayPetSummary();
    storeList.displayPetList();
    
    if (!fileWrite(outfilename, outFile)){
         std::cerr << "A fatal error has occured"<<std::endl; //if an error through the error and end the program
        return 1;        
    }

    storeList.writePetSummary(outFile);
    storeList.writePetList(outFile);

    return 0;
}