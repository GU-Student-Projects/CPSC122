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

    /*************************************************************
    * Function: processData ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/2/23
    * Description: This function process the vectors and outputs
    * the result to the terminal
    * Input parameters: header row and column vectors
    * Returns: T/F if sucessful and outputs to terminal
    * Pre: Data from CSV must be input into vectors
    * Post: Processed vectors in the terminal.
    *************************************************************/

    bool processData(const std::string& filename,
                     std::fstream& myFile,
                     std::vector<std::string>& headers,
                     std::vector<std::string>& petStoreName,
                     std::vector<std::string>& petName,
                     std::vector<std::string>& petType,
                     std::vector<int>& daysAtStore);

    /*************************************************************
    * Function: writeSummary ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/2/23
    * Description: This function process the vectors and outputs
    * the result to the a TXT file
    * Input parameters: column vectors
    * Returns: T/F if sucessful and outputs to terminal
    * Pre: Data from CSV must be input into vectors
    * Post: Processed vectors in a TXT.
    *************************************************************/

    bool writeSummary(const std::string& filename,
                    std::fstream& myFile,
                    std::vector<std::string>& petStoreName,
                    std::vector<std::string>& petName,
                    std::vector<std::string>& petType,
                    std::vector<int>& daysAtStore);

private: //private functions used by the 2 public functions

    /*************************************************************
    * Function: fileOpen ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/2/23
    * Description: Opens any file passed to it. If the file doesnt exist
    * the program creates it
    * Input parameters: file name and the fStream variable
    * Returns: T/F if sucessful throws error if F
    * Pre: Read/Write access in directory
    * Post: Working file
    *************************************************************/

    bool fileOpen(const std::string& filename, std::fstream& myFile);

     /*************************************************************
    * Function: clearScreen ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/2/23
    * Description: Uses an if statement to determine what OS is uesed
    * then runs the system command to clear the terminal
    * Input parameters: System OS
    * Returns: Clear Screen
    * Pre: Correct library
    * Post: Clear Screen
    *************************************************************/

    void clearScreen();

    /*************************************************************
    * Function: fileClose ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/2/23
    * Description: Closes any file passed to it. 
    * Input parameters: fStream variable
    * Returns: Closed file
    * Pre: Read/Write access in directory
    * Post: Closed file
    *************************************************************/

    void fileClose(std::fstream& myFile);

    /*************************************************************
    * Function: getData ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/2/23
    * Description: Converts the CSV data into several vectors
    * Input parameters: file name and column/row vectors
    * Returns: vectors containing all data
    * Pre: Existing CSV file is opened
    * Post: Vectors containing CSV data
    *************************************************************/

    void getData(std::fstream& myFile, std::vector<std::string>& headers,
                 std::vector<std::string>& petStoreName,
                 std::vector<std::string>& petName,
                 std::vector<std::string>& petType,
                 std::vector<int>& daysAtStore);

    /*************************************************************
    * Function: getNumberOfPets ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/2/23
    * Description: Finds the size of the vector passed
    * Input parameters: petType vector
    * Returns: Number of pets
    * Pre: Populated vector with data from CSV
    * Post: int Number of pets
    *************************************************************/

    int getNumberOfPets(std::vector<std::string>& petType);

    /*************************************************************
    * Function: getAverageNumberOfDays ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/2/23
    * Description: Finds the average amount of days a pet is at a store
    * Input parameters: numberOfDays vector
    * Returns: Average days at store
    * Pre: Populated vector with data from CSV
    * Post: int days at store
    *************************************************************/

    int getAverageNumberOfDays(std::vector<int>& daysAtStore);

    /*************************************************************
    * Function: getUniqueStoreNames ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/2/23
    * Description: uses Set to sort a unique vector with non duplicated names of stores
    * Input parameters: petStoreName vector
    * Returns: vector of 3 names in alphabetic order
    * Pre: Populated vector with data from CSV
    * Post: populated uniqueName vector
    *************************************************************/

    void getUniqueStoreNames(std::vector<std::string>& petStoreName,std::vector<std::string>& uniquePetStoreName);

    /*************************************************************
    * Function: getStoreWithMostPets ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/2/23
    * Description: using the number of pets at store vector, find the
    * index of the store with the maximum number of pets
    * Input parameters: petStoreName uniquePetStoreName & numberOfPetsAtStore vector
    * Returns: int index of the maximum
    * Pre: Populated vector with data from CSV
    * Post: int index of maximum
    *************************************************************/

    int getStoreWithMostPets(std::vector<std::string>& petStoreName,std::vector<std::string>& uniquePetStoreName, std::vector<int>& numberOfPetsAtStore);
    
     /*************************************************************
    * Function: getTotalPetsAtStore ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/2/23
    * Description: uses the output of getStoreWithMostPets to relate an index to the actual element
    * and output the number of pets
    * Input parameters: petStoreName, UniquePetStoreName, numberofPets
    * Returns: number of pets at a specific store
    * Pre: Populated vector with data from CSV
    * Post: int number of pets
    *************************************************************/   

    int getTotalPetsAtStore(std::vector<std::string>& petStoreName, std::vector<std::string>& uniquePetStoreName, std::vector<int>& numberOfPetsAtStore);

     /*************************************************************
    * Function: randomPetName ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/2/23
    * Description: takes the size of pet names and finds a random
    * Input parameters: petName
    * Returns: string random pet name
    * Pre: Populated vector with data from CSV
    * Post: string random name
    *************************************************************/     
    std::string randomPetName(std::vector<std::string>& petName);

    /*************************************************************
    * Function: getNumberofPetsByStore ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/2/23
    * Description: compares the vectors of uniquePetStoreName and petStoreName and counts
    * how many times a petstore name occurs
    * Input parameters: petStoreName uniquePetStoreName & numberOfPetsAtStore vector
    * Returns: populated numberOfPetsAtStore
    * Pre: Populated vector with data from CSV
    * Post: numerOfPetsAtStore vector
    *************************************************************/       
    void getNumberofPetsByStore(std::vector<std::string>& petStoreName, std::vector<std::string>& uniquePetStoreName, std::vector<int>& numberOfPetsAtStore);
};

#endif
