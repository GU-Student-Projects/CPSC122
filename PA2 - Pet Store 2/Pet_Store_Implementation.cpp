/*
Name: Gabe DiMartino
Class: CPSC122, Fall 2023
Date: September 17, 2023
Programming Assignment: PA2
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

void clearScreen(){ //function to clear terminal
#ifdef _WIN32 //If OS is WIN32 run cls else use clear
    system("cls");
#else
    system("clear");
#endif
}

    /*************************************************************
    * Function: fileOpen ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/17/23
    * Description: Opens any file passed to it. 
    * Input parameters: file name and the fStream variable
    * Returns: T/F if sucessful throws error if F
    * Pre: Read/Write access in directory
    * Post: Working file
    *************************************************************/

bool fileOpen(const std::string filename, std::ifstream& inFile) {
	inFile.open(filename);

	if (inFile.is_open())
	{
		return true;
	}
	return false;
}

    /*************************************************************
    * Function: fileWrite ()
    * Date Created: 9/17/23
    * Date Last Modified: 9/17/23
    * Description: Opens any file passed to it. If the file doesnt exist
    * the program creates it
    * Input parameters: file name and the fStream variable
    * Returns: T/F if sucessful throws error if F
    * Pre: Read/Write access in directory
    * Post: Working file
    *************************************************************/

bool fileWrite(const std::string filename, std::ofstream& outFile){
    outFile.open(filename, std::ofstream::out | std::ofstream::trunc ); //open a file to write to

    if (!outFile.is_open()) {
        outFile.clear(); //if it does not exist

        outFile.open(filename, std::ofstream::out); //create file

        if (!outFile.is_open()) { 
            return false; //after a second attempt, error the file
        }

        outFile.close(); //close file
        outFile.open(filename, std::ios::in | std::ios::out); //open again
    }

    return outFile.is_open();

}

   /*************************************************************
    * Function: getDataFromCSV ()
    * Date Created: 9/17/23
    * Date Last Modified: 9/19/23
    * Description: Converts the CSV data into several vectors
    * and a dynamically assigned array
    * Input parameters: row vectors, file, and numberOfDays ptr
    * Returns: pointer int value for dynamic array
    * Pre: Existing CSV file is opened
    * Post: Vectors containing CSV data
    *************************************************************/

int* getDataFromCSV(std::ifstream& inFile, 
                    std::vector<std::string>& headers,
                    std::vector<std::string>& petStoreNames,
                    std::vector<std::string>& petNames,
                    std::vector<std::string>& petTypes,
                    int* numDaysAtStorePtr,
                    int* numDaysAtStoreSize){
    
    std::string dataLine, cell;
    int numCell;
    getHeaderLine(inFile, headers); //get headline vector

    while(std::getline(inFile, dataLine)){ //while there are lines, go through each line cell by cell
        std::istringstream dataToParse(dataLine);
        for (int i = 0; i < 4; i++){
            std::getline(dataToParse, cell, ','); //during each line, iterate over it 4 times for the 4 columns
            if (i == 0){
                petStoreNames.push_back(cell); //depending on the iteration a different pushback is used
            }
            else if (i == 1){
                petNames.push_back(cell);
            }
            else if (i == 2){
                petTypes.push_back(cell);
            }
            else if (i == 3){
                std::istringstream numStream(cell);
                numStream >> numCell;
                numDaysAtStorePtr = pushBackInteger(numDaysAtStorePtr, numDaysAtStoreSize, numCell);//set a new arrayPtr equal to the original pointer
            }                        
        }      
    }
    return numDaysAtStorePtr; //pass through the pointer array
}

   /*************************************************************
    * Function: getHeaderLine ()
    * Date Created: 9/17/23
    * Date Last Modified: 9/18/23
    * Description: Converts the CSV header line into a vector
    * Input parameters: opened file and header vector
    * Returns: vectors containing header row
    * Pre: Existing CSV file is opened
    * Post: Vectors containing CSV data
    *************************************************************/

void getHeaderLine(std::ifstream& inFile, std::vector<std::string>& headers){
    std::string headerLine, cell;

    std::getline(inFile, headerLine);
    std::istringstream lineToParse(headerLine);
    while (std::getline(lineToParse, cell, ',')) { //For the text seperated by a comma add the element to the vector
        headers.push_back(cell); //For the first line only
    }

}

   /*************************************************************
    * Function: pushBackInteger ()
    * Date Created: 9/17/23
    * Date Last Modified: 9/18/23
    * Description: adjusts the dynamically assigned array for an
    * increase in size and adds the new value
    * Returns: increased array size with push back integer
    * Pre: original array exists, and the new value is present
    * Post: completed array
    *************************************************************/

int* pushBackInteger(int* originalArray, int* arraySize, int newValue ){
    (*arraySize)++; //increase size of the array
    int* newArray = new int[*arraySize]; //create a new array with the larger size
    for (int i = 0; i < (*arraySize - 1); i++){
        newArray[i] = originalArray[i]; //copy all of the content from the original array into the new array
    }
    newArray[*arraySize-1] = newValue; //add the new value to the last element of the new vector

    if (originalArray != nullptr) {
        delete[] originalArray; //if the array is not null, delete it
    }

    return newArray; //return the new array

}

    /*************************************************************
    * Function: processData ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/17/23
    * Description: This function process the vectors and outputs
    * the result to the terminal
    * Input parameters: header row and column vectors
    * Returns: pointer int value for dynamic array
    * Pre: Data from CSV must be input into vectors
    * Post: Processed vectors in the terminal.
    *************************************************************/

int* processData(const std::string filename, //Reference vectors from the main
                        std::ifstream& inFile,
                        std::vector<std::string>& headers,
                        std::vector<std::string>& petStoreNames,
                        std::vector<std::string>& petNames,
                        std::vector<std::string>& petTypes,
                        int* numDaysAtStorePtr,
                        int* numDaysAtStoreSize){

    if (fileOpen(filename, inFile)) { //If the file can open run the following
        numDaysAtStorePtr = getDataFromCSV(inFile, headers, petStoreNames, petNames, petTypes, numDaysAtStorePtr, numDaysAtStoreSize); //Get the data from CSV to the indivudal vectors

        clearScreen(); //Clear screen
        
        std::cout << "Processed " << headers.size() << " header columns: "; //Format the headers with commas
        for (size_t i = 0; i < headers.size(); i++) {
            std::cout << headers[i];
            if (i < headers.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl << std::endl;

        for (size_t i = 0; i < petStoreNames.size(); i++) { //using the size of the csv, go through each element
            std::cout << "Processed a " << petTypes[i] << ", \"" << petNames[i] << "\" ... "
            << numDaysAtStorePtr[i] << " day(s) on site at store \"" << petStoreNames[i] << "\"" << std::endl;
        }

        std::cout << "All pet store data processed!" <<std::endl << std::endl;

        inFile.close(); //Close the file
        return numDaysAtStorePtr; //pass the array back to main
    } else {
        std::cerr << "The file " + filename + " has encountered an error. Please make sure the file is in the correct directory and you have the appropriate permissions to read." << std::endl;
        return 0; //If there was a problem show the error
    }
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

int* getNumberOfPets(std::vector<std::string>& petTypes) {
    int numberOfPets = petTypes.size();
    int* numberOfPetsPtr = &numberOfPets; //create a pointer referencing the int value of petTypes size
    return numberOfPetsPtr;
}

    /*************************************************************
    * Function: getAverageNumberOfDays ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/19/23
    * Description: Finds the average amount of days a pet is at a store
    * Input parameters: numberOfDays dynamic array
    * Returns: Average days at store
    * Pre: Populated vector with data from CSV
    * Post: int days at store
    *************************************************************/

int* getAverageNumberOfDays(int* numDaysAtStorePtr, int* numDaysAtStoreSize) {
    if (*numDaysAtStoreSize==0) {//If there is no information, exit the function
        return 0;
    }
    int averageNumberOfDays = 0;
    int* averageNumberOfDaysPtr = &averageNumberOfDays;
    for (int i = 0; i < *numDaysAtStoreSize; i++) {
        *averageNumberOfDaysPtr += numDaysAtStorePtr[i]; //calculate sum
    }
    *averageNumberOfDaysPtr /= *numDaysAtStoreSize; //divide by count
    return averageNumberOfDaysPtr; //Find the average
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

std::string randomPetName(std::vector<std::string>& petNames) {
    int randomPet = rand() % petNames.size(); //generate random employee of the month
    int* randomPetPtr = &randomPet; //pointer for the integer
    return petNames[*randomPetPtr];
}

     /*************************************************************
    * Function: stringIsInVector ()
    * Date Created: 9/19/23
    * Date Last Modified: 9/19/23
    * Description: Determines if a string exists in a vector
    * Input parameters: vector, string
    * Returns: T/F string exists
    * Pre: populated vectors
    * Post: T/F string is in vector
    *************************************************************/ 

bool stringIsInVector(std::vector<std::string> searchVector, std::string targetWord){
    for (size_t i = 0; i < searchVector.size(); i++){
        if (targetWord == searchVector[i]){ //search through a vector to see if the target element exists
            return true;
        }
    }
    return false;
}

     /*************************************************************
    * Function: getUniqueNames ()
    * Date Created: 9/19/23
    * Date Last Modified: 9/19/23
    * Description: Adds unique names to a new vector
    * Input parameters: vector
    * Returns: filled vector
    * Pre: populated names vectors
    * Post: populated unique names vector
    *************************************************************/ 

void getUniqueNames(const std::vector<std::string>& petStoreNames, std::vector<std::string>& uniquePetStoreNames) {
    for (size_t i = 0; i < petStoreNames.size(); i++) {
        if (!stringIsInVector(uniquePetStoreNames, petStoreNames[i])) { //uses the stringIsInVector function to find all names
            uniquePetStoreNames.push_back(petStoreNames[i]);
        }
    }
}

    /*************************************************************
    * Function: getOfPetsAtStores( ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/19/23
    * Description: compares the vectors of uniquePetStoreName and petStoreName and counts
    * how many times a petstore name occurs
    * Input parameters: petStoreName uniquePetStoreName & numberOfPetsAtStore dynamic array
    * Returns: populated uniquePetStoreNameCountsPtr
    * Pre: Populated vector with data from CSV
    * Post: uniquePetStoreNameCountsPtr dynamic array
    *************************************************************/  

int* getNumOfPetsAtStores(const std::vector<std::string>& petStoreNames, 
                            const std::vector<std::string> uniquePetStoreNames, 
                            int* uniquePetStoreNameCountsPtr, 
                            int* uniquePetStoreNameCountsSize){
    for (size_t i = 0; i < uniquePetStoreNames.size(); i++) {
        int tempValue = 0;
        int* tempPtr = &tempValue;
        for (size_t j = 0; j < petStoreNames.size(); j++) {
            if (uniquePetStoreNames[i] == petStoreNames[j]) {
                (*tempPtr)++;
            }
        } //Go through all of the pet store names and match it with the unique names. If there is a duplicate it is added to the count
        uniquePetStoreNameCountsPtr = pushBackInteger(uniquePetStoreNameCountsPtr, uniquePetStoreNameCountsSize, *tempPtr);
    }
    return uniquePetStoreNameCountsPtr;

}

    /*************************************************************
    * Function: getStoreWithMostPetsIndex ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/19/23
    * Description: using the number of pets at store vector, find the
    * index of the store with the maximum number of pets
    * Input parameters: uniquePetStoreNameCountsPtr, uniquePetStoreNameCountsSize 
    * Returns: int index of the maximum
    * Pre: Populated vector with data from CSV
    * Post: int index of maximum
    *************************************************************/

int* getStoreWithMostPetsIndex(const int* uniquePetStoreNameCountsPtr, const int* uniquePetStoreNameCountsSize) {
    int indexOfMaximum = 0;
    int* indexOfMaximumPtr = &indexOfMaximum;
    for (int i = 0; i < *uniquePetStoreNameCountsSize; i++) {
        if (uniquePetStoreNameCountsPtr[i] > uniquePetStoreNameCountsPtr[*indexOfMaximumPtr]) {
            *indexOfMaximumPtr = i;
        }
    } //Match the element of the unique PetStoreName to the one with the most pets.

    return indexOfMaximumPtr;
}

    /*************************************************************
    * Function: alphabetizePetNames ()
    * Date Created: 9/19/23
    * Date Last Modified: 9/19/23
    * Description: This function does a bubble search to swap until 
    * sorted alphabetically
    * Input parameters: pet name vectors and an empty vector
    * Returns: alphabetically sorted names
    * Pre: Data from CSV must be input into vectors
    * Post: populated vector.
    *************************************************************/

void alphabetizePetNames(const std::vector<std::string>& petNames, std::vector<std::string>& alphabetizedPetNames){
    alphabetizedPetNames = petNames; //copy all contents from pet names to alphabetized pet names

    bool bubbleSwap;

    do{ //using a do while loop to atleast run through the list once and make sure everything is ordered correctly
        bubbleSwap = false;
        for (size_t i = 0; i < (alphabetizedPetNames.size() - 1); i++){
            if (alphabetizedPetNames[i] > alphabetizedPetNames[i+1]){
                std::string tempName = alphabetizedPetNames[i]; //swap the values
                alphabetizedPetNames[i] = alphabetizedPetNames[i + 1];
                alphabetizedPetNames[i + 1] = tempName;
                bubbleSwap = true; //if something is not placed correctly, swap it and run again
            }
        }
    } while(bubbleSwap);
}
    

    /*************************************************************
    * Function: writeSummary ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/19/23
    * Description: This function process the vectors/arrays and outputs
    * the result to the a TXT file
    * Input parameters: column vectors
    * Returns: T/F if sucessful and outputs to terminal
    * Pre: Data from CSV must be input into vectors
    * Post: Processed vectors in a TXT.
    *************************************************************/

bool writeSummary(const std::string& filename, //Reference vectors and pointers from the main
                        std::ofstream& outFile,
                        std::vector<std::string>& petStoreNames,
                        std::vector<std::string>& petNames,
                        std::vector<std::string>& petTypes,
                        int* numDaysAtStorePtr,
                        int* numDaysAtStoreSize) {

    int* mostPetsInStoreIndex;
    int uniquePetStoreNameCounts = 0; //This variable keeps track of the size of your unique counts dynamic array
    int* uniquePetStoreNameCountsSize = &uniquePetStoreNameCounts;
    int* uniquePetStoreNameCountsPtr = new int[*uniquePetStoreNameCountsSize]; //This variable is a pointer to your dynamic integer array
    std::vector<std::string> uniquePetStoreNames, alphabetizedPetNames;
    

    std::cout<< "Generating summary report..." <<std::endl<<std::endl;
    getUniqueNames(petStoreNames, uniquePetStoreNames); //Get the vector to sort only unique elements in alphabetic order
    uniquePetStoreNameCountsPtr = getNumOfPetsAtStores(petStoreNames, uniquePetStoreNames, uniquePetStoreNameCountsPtr, uniquePetStoreNameCountsSize); //Get the dynamic array for each pet store and how many times they were repeated
    alphabetizePetNames(petNames, alphabetizedPetNames);

    if (fileWrite(filename, outFile)) { //Open the file and format it
        outFile << "Pet Store CSV Summary Report" << std::endl;
        outFile << "----------------------------" << std::endl << std::endl;
        outFile << "Pet Stores: ";
        
        for (int i = 0; i < *uniquePetStoreNameCountsSize; i++) {
            outFile << uniquePetStoreNames[i];
            if (i < *uniquePetStoreNameCountsSize - 1) {
                outFile << ", ";
            }
        }
        outFile << std::endl;
        
        mostPetsInStoreIndex = getStoreWithMostPetsIndex(uniquePetStoreNameCountsPtr,uniquePetStoreNameCountsSize);

        outFile << "Total number of pets: " << *getNumberOfPets(petTypes) << std::endl << std::endl;
        outFile << "Pet store with the most pets: " << uniquePetStoreNames[*mostPetsInStoreIndex] << std::endl;
        outFile << "Number of pets at " << uniquePetStoreNames[*mostPetsInStoreIndex] << ": " << uniquePetStoreNameCountsPtr[*mostPetsInStoreIndex] << std::endl << std::endl;
        outFile << "Pet average days on site across all stores: " << *getAverageNumberOfDays(numDaysAtStorePtr,numDaysAtStoreSize) << std::endl;
        outFile << "Employee of the month choice: \"" << randomPetName(petNames) << "\"" << std::endl << std::endl;
        outFile << "Current Pet Inventory: ";

        for (size_t i = 0; i < petNames.size(); i++) {
            outFile << alphabetizedPetNames[i];
            if (i < alphabetizedPetNames.size() - 1) {
                outFile << ", ";
            }
        }

        outFile.close(); //Close the file

        std::cout<< "Done!" <<std::endl;
        return true;
    } else {
        std::cerr << "A fatal error has been encountered opening \"" + filename + "\". Please make sure you have the appropriate permissions to read/write." << std::endl;
        return false; //If there is an error send a message and return false
    }

    return true;
}