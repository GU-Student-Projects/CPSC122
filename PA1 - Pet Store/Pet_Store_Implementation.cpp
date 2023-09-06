/**
 * File:            Pet_Store_Implementations.cpp
 * Author:          Gabe DiMartino
 * Date Modified:   2 September 2023
 * Description:     Stores all of the functions for the Pet_Store.cpp
 */

#include "Pet_Store.h"



void PetStore::clearScreen(){ //function to clear terminal
#ifdef _WIN32 //If OS is WIN32 run cls else use clear
    system("cls");
#else
    system("clear");
#endif
}

bool PetStore::processData(const std::string& filename, //Reference vectors from the main
                           std::fstream& myFile,
                           std::vector<std::string>& headers,
                           std::vector<std::string>& petStoreName,
                           std::vector<std::string>& petName,
                           std::vector<std::string>& petType,
                           std::vector<int>& daysAtStore) {
    if (fileOpen(filename, myFile)) { //If the file can open run the following
        getData(myFile, headers, petStoreName, petName, petType, daysAtStore); //Get the data from CSV to the indivudal vectors

        clearScreen(); //Clear screen

        std::cout << "Processed " << headers.size() << " header columns: "; //Format the headers with commas
        for (size_t i = 0; i < headers.size(); i++) {
            std::cout << headers[i];
            if (i < headers.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl << std::endl;

        for (size_t i = 0; i < petStoreName.size(); i++) { //using the size of the csv, go through each element
            std::cout << "Processed a " << petType[i] << ", \"" << petName[i] << "\" ... "
            << daysAtStore[i] << " day(s) on site at store \"" << petStoreName[i] << "\"" << std::endl;
        }

        std::cout << "All pet store data processed!" <<std::endl << std::endl;

        fileClose(myFile); //Close the file
        return true;
    } else {
        std::cerr << "The file " + filename + " has encountered an error. Please make sure the file is in the correct directory and you have the appropriate permissions to read." << std::endl;
        return false; //If there was a problem show the error
    }
}

bool PetStore::writeSummary(const std::string& filename, //Reference vectors from the main
                            std::fstream& myFile,
                            std::vector<std::string>& petStoreName,
                            std::vector<std::string>& petName,
                            std::vector<std::string>& petType,
                            std::vector<int>& daysAtStore) {

    std::vector<std::string> uniquePetStoreName; //Initialize vectors for writeSummary NOT MAIN
    std::vector<int> numberOfPetsAtStore;

    std::cout<< "Generating summary report..." <<std::endl<<std::endl;
    getUniqueStoreNames(petStoreName, uniquePetStoreName); //Get the vector to sort only unique elements in alphabetic order
    getNumberofPetsByStore(petStoreName, uniquePetStoreName, numberOfPetsAtStore); //Get the vector for each pet store and how many times they were repeated

    if (fileOpen(filename, myFile)) { //Open the file and format it
        myFile << "Pet Store CSV Summary Report" << std::endl;
        myFile << "----------------------------" << std::endl << std::endl;
        myFile << "Pet Stores: ";
        
        for (size_t i = 0; i < uniquePetStoreName.size(); i++) {
            myFile << uniquePetStoreName[i];
            if (i < uniquePetStoreName.size() - 1) {
                myFile << ", ";
            }
        }
        myFile << std::endl;
        
        int mostPetsInStoreIndex = getStoreWithMostPets(petStoreName, uniquePetStoreName, numberOfPetsAtStore);

        myFile << "Total number of pets: " << getNumberOfPets(petType) << std::endl << std::endl;
        myFile << "Pet store with the most pets: " << uniquePetStoreName[mostPetsInStoreIndex] << std::endl;
        myFile << "Number of pets at " << uniquePetStoreName[mostPetsInStoreIndex] << ": " << numberOfPetsAtStore[mostPetsInStoreIndex] << std::endl << std::endl;
        myFile << "Pet average days on site across all stores: " << getAverageNumberOfDays(daysAtStore) << std::endl;
        myFile << "Employee of the month choice: \"" << randomPetName(petName) << "\"" << std::endl;

        fileClose(myFile); //Close the file

        std::cout<< "Done!" <<std::endl;
        return true;
    } else {
        std::cerr << "A fatal error has been encountered opening \"" + filename + "\". Please make sure you have the appropriate permissions to read/write." << std::endl;
        return false; //If there is an error send a message and return false
    }

    return true;
}



bool PetStore::fileOpen(const std::string& filename, std::fstream& myFile) {
    myFile.open(filename); //Open a file

    if(!myFile){ //If the file doesnt exist, make it
        myFile.open(filename,std::fstream::out);
    }

    return myFile.is_open();
}


void PetStore::getData(std::fstream& myFile, std::vector<std::string>& headers,
             std::vector<std::string>& petStoreName,
             std::vector<std::string>& petName,
             std::vector<std::string>& petType,
             std::vector<int>& daysAtStore) {
    std::string headerLine;
    std::string dataLine;

    if (std::getline(myFile, headerLine)) {//true if the file can read the first line
        std::istringstream lineToParse(headerLine); //stringstream to first line
        std::string cell; //individual element for vector

        while (std::getline(lineToParse, cell, ',')) { //For the text seperated by a comma add the element to the vector
            headers.push_back(cell); //For the first line only
        }

        while (std::getline(myFile, dataLine)) { //Loop for all lines on the CSV after the first
            std::istringstream dataToParse(dataLine);
            std::vector<std::string> rowData;

            while (std::getline(dataToParse, cell, ',')) {
                rowData.push_back(cell);
            }

            if (rowData.size() >= 4) {
                petStoreName.push_back(rowData[0]); //If in index assign to 
                petName.push_back(rowData[1]);
                petType.push_back(rowData[2]);

                int days;
                if (std::istringstream(rowData[3]) >> days) {
                    daysAtStore.push_back(days); //Convert string to int for the element
                } else {
                    std::cerr << "Error parsing days value." << std::endl;
                    //Throw an error
                }
            }
        }
    } else {
        std::cerr << "Error, couldn't read headers" << std::endl;
        //Through error if it fails
    }
}

void PetStore::fileClose(std::fstream& myFile) {
    myFile.close();
}



int PetStore::getNumberOfPets(std::vector<std::string>& petType) {
    return petType.size();
}

int PetStore::getAverageNumberOfDays(std::vector<int>& daysAtStore) {
    if (daysAtStore.empty()) {//If there is no information skipped
        return 0;
    }
    int averageNumberOfDays = 0;
    for (size_t i = 0; i < daysAtStore.size(); i++) {
        averageNumberOfDays += daysAtStore[i];
    }
    averageNumberOfDays /= static_cast<int>(daysAtStore.size());
    return averageNumberOfDays; //Find the average
}

void PetStore::getUniqueStoreNames(std::vector<std::string>& petStoreName, std::vector<std::string>& uniquePetStoreName) {
    std::set<std::string> uniqueNames;
    for (size_t i = 0; i < petStoreName.size(); i++) {
        uniqueNames.insert(petStoreName[i]);
    } //Use set to sort through all of the names in vector and assign it from beginning to end

    uniquePetStoreName.assign(uniqueNames.begin(), uniqueNames.end());
}

void PetStore::getNumberofPetsByStore(std::vector<std::string>& petStoreName, std::vector<std::string>& uniquePetStoreName, std::vector<int>& numberOfPetsAtStore) {
    for (size_t i = 0; i < uniquePetStoreName.size(); i++) {
        int tempValue = 0;
        for (size_t j = 0; j < petStoreName.size(); j++) {
            if (uniquePetStoreName[i] == petStoreName[j]) {
                tempValue++;
            }
        } //Go through all of the pet store names and match it with the unique names. If there is a duplicate it is added to the count
        numberOfPetsAtStore.push_back(tempValue);;
    }

}

int PetStore::getStoreWithMostPets(std::vector<std::string>& petStoreName, std::vector<std::string>& uniquePetStoreName, std::vector<int>& numberOfPetsAtStore) {
    int arrayElementOfMaximum = 0;

    for (size_t i = 0; i < numberOfPetsAtStore.size(); i++) {
        if (numberOfPetsAtStore[i] > numberOfPetsAtStore[arrayElementOfMaximum]) {
            arrayElementOfMaximum = i;
        }
    } //Match the element of the unique PetStoreName to the one with the most pets.

    return arrayElementOfMaximum;
}




int PetStore::getTotalPetsAtStore(std::vector<std::string>& petStoreName, std::vector<std::string>& uniquePetStoreName, std::vector<int>& numberOfPetsAtStore) {
    int arrayElementOfMaximum = getStoreWithMostPets(petStoreName, uniquePetStoreName, numberOfPetsAtStore);
    int totalPets = numberOfPetsAtStore[arrayElementOfMaximum]; //Get the number of pets at a store
    return totalPets;
}

std::string PetStore::randomPetName(std::vector<std::string>& petName) {
    int randomPet = rand() % petName.size(); //generate random employee of the month
    return petName[randomPet];
}
