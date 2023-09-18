/*
Name: Gabe DiMartino
Class: CPSC122, Fall 2023
Date: September 2, 2023
Programming Assignment: PA1
Description: This cpp contains all of the implementations of functions
*/

#include "Pet_Store.h"

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

void PetStore::clearScreen(){ //function to clear terminal
#ifdef _WIN32 //If OS is WIN32 run cls else use clear
    system("cls");
#else
    system("clear");
#endif
}

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

bool PetStore::writeSummary(const std::string& filename, //Reference vectors from the main
                            std::ofstream& outFile,
                            std::vector<std::string>& petStoreName,
                            std::vector<std::string>& petName,
                            std::vector<std::string>& petType,
                            std::vector<int>& daysAtStore) {

    std::vector<std::string> uniquePetStoreName; //Initialize vectors for writeSummary NOT MAIN
    std::vector<int> numberOfPetsAtStore;

    std::cout<< "Generating summary report..." <<std::endl<<std::endl;
    getUniqueStoreNames(petStoreName, uniquePetStoreName); //Get the vector to sort only unique elements in alphabetic order
    getNumberofPetsByStore(petStoreName, uniquePetStoreName, numberOfPetsAtStore); //Get the vector for each pet store and how many times they were repeated

    if (fileWrite(filename, outFile)) { //Open the file and format it
        outFile << "Pet Store CSV Summary Report" << std::endl;
        outFile << "----------------------------" << std::endl << std::endl;
        outFile << "Pet Stores: ";
        
        for (size_t i = 0; i < uniquePetStoreName.size(); i++) {
            outFile << uniquePetStoreName[i];
            if (i < uniquePetStoreName.size() - 1) {
                outFile << ", ";
            }
        }
        outFile << std::endl;
        
        int mostPetsInStoreIndex = getStoreWithMostPets(petStoreName, uniquePetStoreName, numberOfPetsAtStore);

        outFile << "Total number of pets: " << getNumberOfPets(petType) << std::endl << std::endl;
        outFile << "Pet store with the most pets: " << uniquePetStoreName[mostPetsInStoreIndex] << std::endl;
        outFile << "Number of pets at " << uniquePetStoreName[mostPetsInStoreIndex] << ": " << numberOfPetsAtStore[mostPetsInStoreIndex] << std::endl << std::endl;
        outFile << "Pet average days on site across all stores: " << getAverageNumberOfDays(daysAtStore) << std::endl;
        outFile << "Employee of the month choice: \"" << randomPetName(petName) << "\"" << std::endl;

        outFile.close(); //Close the file

        std::cout<< "Done!" <<std::endl;
        return true;
    } else {
        std::cerr << "A fatal error has been encountered opening \"" + filename + "\". Please make sure you have the appropriate permissions to read/write." << std::endl;
        return false; //If there is an error send a message and return false
    }

    return true;
}

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

bool PetStore::fileOpen(const std::string& filename, std::fstream& inFile) {
	inFile.open(filename);

	if (inFile.is_open())
	{
		return true;
	}
	return false;
}

bool PetStore::fileWrite(const std::string& filename, std::ofstream& outFile){
    outFile.open(filename, std::ofstream::out | std::ofstream::trunc ); 

    if (!outFile.is_open()) {
        outFile.clear();

        outFile.open(filename, std::ofstream::out);

        if (!outFile.is_open()) { 
            return false; 
        }

        outFile.close();
        outFile.open(filename, std::ios::in | std::ios::out);
    }

    return outFile.is_open();

}


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

void PetStore::fileClose(std::fstream& myFile) {
    myFile.close();
}

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

int PetStore::getNumberOfPets(std::vector<std::string>& petType) {
    return petType.size();
}

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

void PetStore::getUniqueStoreNames(std::vector<std::string>& petStoreName, std::vector<std::string>& uniquePetStoreName) {
    std::set<std::string> uniqueNames;
    for (size_t i = 0; i < petStoreName.size(); i++) {
        uniqueNames.insert(petStoreName[i]);
    } //Use set to sort through all of the names in vector and assign it from beginning to end

    uniquePetStoreName.assign(uniqueNames.begin(), uniqueNames.end());
}

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

int PetStore::getStoreWithMostPets(std::vector<std::string>& petStoreName, std::vector<std::string>& uniquePetStoreName, std::vector<int>& numberOfPetsAtStore) {
    int arrayElementOfMaximum = 0;

    for (size_t i = 0; i < numberOfPetsAtStore.size(); i++) {
        if (numberOfPetsAtStore[i] > numberOfPetsAtStore[arrayElementOfMaximum]) {
            arrayElementOfMaximum = i;
        }
    } //Match the element of the unique PetStoreName to the one with the most pets.

    return arrayElementOfMaximum;
}

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


int PetStore::getTotalPetsAtStore(std::vector<std::string>& petStoreName, std::vector<std::string>& uniquePetStoreName, std::vector<int>& numberOfPetsAtStore) {
    int arrayElementOfMaximum = getStoreWithMostPets(petStoreName, uniquePetStoreName, numberOfPetsAtStore);
    int totalPets = numberOfPetsAtStore[arrayElementOfMaximum]; //Get the number of pets at a store
    return totalPets;
}

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

std::string PetStore::randomPetName(std::vector<std::string>& petName) {
    int randomPet = rand() % petName.size(); //generate random employee of the month
    return petName[randomPet];
}
