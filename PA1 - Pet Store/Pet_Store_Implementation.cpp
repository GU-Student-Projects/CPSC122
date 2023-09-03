#include "Pet_Store.h"
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

void PetStore::clearScreen(){ //function to clear terminal
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

bool PetStore::processData(const std::string& filename,
                           std::fstream& myFile,
                           std::vector<std::string>& headers,
                           std::vector<std::string>& petStoreName,
                           std::vector<std::string>& petName,
                           std::vector<std::string>& petType,
                           std::vector<int>& daysAtStore) {
    if (fileOpen(filename, myFile)) {
        getData(myFile, headers, petStoreName, petName, petType, daysAtStore);

        clearScreen();

        std::cout << "Processed " << headers.size() << " header columns: ";
        for (size_t i = 0; i < headers.size(); i++) {
            std::cout << headers[i];
            if (i < headers.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl << std::endl;

        for (size_t i = 0; i < petStoreName.size(); i++) {
            std::cout << "Processed a " << petType[i] << ", \"" << petName[i] << "\" ... "
            << daysAtStore[i] << " day(s) on site at store \"" << petStoreName[i] << "\"" << std::endl;
        }

        std::cout << "All pet store data processed!" <<std::endl << std::endl;

        fileClose(myFile);
        return true;
    } else {
        std::cerr << "The file " + filename + " has encountered an error. Please make sure the file is in the correct directory and you have the appropriate permissions to read." << std::endl;
        return false;
    }
}

bool PetStore::writeSummary(const std::string& filename,
                            std::fstream& myFile,
                            std::vector<std::string>& petStoreName,
                            std::vector<std::string>& petName,
                            std::vector<std::string>& petType,
                            std::vector<int>& daysAtStore) {

    std::vector<std::string> uniquePetStoreName;
    std::vector<int> numberOfPetsAtStore;

    std::cout<< "Generating summary report..." <<std::endl<<std::endl;
    getUniqueStoreNames(petStoreName, uniquePetStoreName);
    getNumberofPetsByStore(petStoreName, uniquePetStoreName, numberOfPetsAtStore);

    if (fileOpen(filename, myFile)) {
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

        fileClose(myFile);

        std::cout<< "Done !" <<std::endl;
        return true;
    } else {
        std::cerr << "A fatal error has been encountered opening \"" + filename + "\". Please make sure you have the appropriate permissions to read/write." << std::endl;
        return false;
    }

    return true;
}



bool PetStore::fileOpen(const std::string& filename, std::fstream& myFile) {
    myFile.open(filename);

    if(!myFile){
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

    if (std::getline(myFile, headerLine)) {
        std::istringstream lineToParse(headerLine);
        std::string cell;

        while (std::getline(lineToParse, cell, ',')) {
            headers.push_back(cell);
        }

        while (std::getline(myFile, dataLine)) {
            std::istringstream dataToParse(dataLine);
            std::vector<std::string> rowData;

            while (std::getline(dataToParse, cell, ',')) {
                rowData.push_back(cell);
            }

            if (rowData.size() >= 4) {
                petStoreName.push_back(rowData[0]);
                petName.push_back(rowData[1]);
                petType.push_back(rowData[2]);

                int days;
                if (std::istringstream(rowData[3]) >> days) {
                    daysAtStore.push_back(days);
                } else {
                    std::cerr << "Error parsing days value." << std::endl;
                }
            }
        }
    } else {
        std::cerr << "Error, couldn't read headers" << std::endl;
    }
}

void PetStore::fileClose(std::fstream& myFile) {
    myFile.close();
}



int PetStore::getNumberOfPets(std::vector<std::string>& petType) {
    return petType.size();
}

int PetStore::getAverageNumberOfDays(std::vector<int>& daysAtStore) {
    if (daysAtStore.empty()) {
        return 0;
    }
    int averageNumberOfDays = 0;
    for (size_t i = 0; i < daysAtStore.size(); i++) {
        averageNumberOfDays += daysAtStore[i];
    }
    averageNumberOfDays /= static_cast<int>(daysAtStore.size());
    return averageNumberOfDays;
}

void PetStore::getUniqueStoreNames(std::vector<std::string>& petStoreName, std::vector<std::string>& uniquePetStoreName) {
    std::set<std::string> uniqueNames;
    for (size_t i = 0; i < petStoreName.size(); i++) {
        uniqueNames.insert(petStoreName[i]);
    }

    uniquePetStoreName.assign(uniqueNames.begin(), uniqueNames.end());
}

void PetStore::getNumberofPetsByStore(std::vector<std::string>& petStoreName, std::vector<std::string>& uniquePetStoreName, std::vector<int>& numberOfPetsAtStore) {
    for (size_t i = 0; i < uniquePetStoreName.size(); i++) {
        int tempValue = 0;
        for (size_t j = 0; j < petStoreName.size(); j++) {
            if (uniquePetStoreName[i] == petStoreName[j]) {
                tempValue++;
            }
        }
        numberOfPetsAtStore.push_back(tempValue);;
    }

}

int PetStore::getStoreWithMostPets(std::vector<std::string>& petStoreName, std::vector<std::string>& uniquePetStoreName, std::vector<int>& numberOfPetsAtStore) {
    int arrayElementOfMaximum = 0;

    for (size_t i = 0; i < numberOfPetsAtStore.size(); i++) {
        if (numberOfPetsAtStore[i] > numberOfPetsAtStore[arrayElementOfMaximum]) {
            arrayElementOfMaximum = i;
        }
    }

    return arrayElementOfMaximum;
}




int PetStore::getTotalPetsAtStore(std::vector<std::string>& petStoreName, std::vector<std::string>& uniquePetStoreName, std::vector<int>& numberOfPetsAtStore) {
    int arrayElementOfMaximum = getStoreWithMostPets(petStoreName, uniquePetStoreName, numberOfPetsAtStore);
    int totalPets = numberOfPetsAtStore[arrayElementOfMaximum];
    return totalPets;
}

std::string PetStore::randomPetName(std::vector<std::string>& petName) {
    int randomPet = rand() % petName.size();
    return petName[randomPet];
}
