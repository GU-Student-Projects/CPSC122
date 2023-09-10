/*
Name: Gabe DiMartino
Class: CPSC122, Fall 2023
Date: September 2, 2023
Programming Assignment: PA1
Description: This headerfile lists all of the function descriptions
*/

#ifndef PET_STORE_H
#define PET_STORE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>
#include <cstdlib>
#include <ctime>
#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

class PetStore {
public: //Public functions accessed by main

    PetStore() = default;//default constructor


    bool processData(const std::string& filename,
                     std::fstream& myFile,
                     std::vector<std::string>& headers,
                     std::vector<std::string>& petStoreName,
                     std::vector<std::string>& petName,
                     std::vector<std::string>& petType,
                     std::vector<int>& daysAtStore);



    bool writeSummary(const std::string& filename,
                    std::fstream& myFile,
                    std::vector<std::string>& petStoreName,
                    std::vector<std::string>& petName,
                    std::vector<std::string>& petType,
                    std::vector<int>& daysAtStore);

private: //private functions used by the 2 public functions
    bool fileOpen(const std::string& filename, std::fstream& myFile);
    void clearScreen();
    void fileClose(std::fstream& myFile);
    void getData(std::fstream& myFile, std::vector<std::string>& headers,
                 std::vector<std::string>& petStoreName,
                 std::vector<std::string>& petName,
                 std::vector<std::string>& petType,
                 std::vector<int>& daysAtStore);
    int getNumberOfPets(std::vector<std::string>& petType);
    int getAverageNumberOfDays(std::vector<int>& daysAtStore);
    void getUniqueStoreNames(std::vector<std::string>& petStoreName,std::vector<std::string>& uniquePetStoreName);
    int getStoreWithMostPets(std::vector<std::string>& petStoreName,std::vector<std::string>& uniquePetStoreName, std::vector<int>& numberOfPetsAtStore);
    int getTotalPetsAtStore(std::vector<std::string>& petStoreName, std::vector<std::string>& uniquePetStoreName, std::vector<int>& numberOfPetsAtStore); 
    std::string randomPetName(std::vector<std::string>& petName);     
    void getNumberofPetsByStore(std::vector<std::string>& petStoreName, std::vector<std::string>& uniquePetStoreName, std::vector<int>& numberOfPetsAtStore);
};

#endif
