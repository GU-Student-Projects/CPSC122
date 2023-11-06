/*
Name: Gabe DiMartino
Class: CPSC122, Fall 2023
Date: November 5, 2023
Programming Assignment: PA5
Description: This cpp runs the program
I AM ATTEMPTING THE BONUS CHALLENGE
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

        /* BONUS Additions*/
    storeList.insertAtFront(storeList.createNode("Pet Palace"));
    storeList.insertAtPosition(storeList.createNode("Prince of Pets"), 3);

    storeList.addPetData("Pet Palace","Molle","Cat",12);
    storeList.addPetData("Pet Palace","Madde","Dog",15);

    storeList.addPetData("Prince of Pets","Maize","Turtle",3);
    storeList.addPetData("Prince of Pets","Mavus","Rabbit",7);

    storeList.calculatePetSummary();
    std::cout<<std::endl<<std::endl<<"*******BONUS TASK******"<<std::endl;
    storeList.displayPetSummary();
    storeList.displayPetList();
    outFile<<std::endl<<std::endl<<"*******BONUS TASK******"<<std::endl;
    storeList.writePetSummary(outFile);
    storeList.writePetList(outFile);
    /*BONUS end of bonus*/

    outFile.close();

    return 0;
}