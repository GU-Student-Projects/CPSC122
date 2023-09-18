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

bool fileOpen(const std::string& filename, std::ifstream& inFile) {
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

bool fileWrite(const std::string& filename, std::ofstream& outFile){
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

void getDataFromCSV(std::ifstream& inFile, 
                    std::vector<std::string>& headers,
                    std::vector<std::string>& petStoreNames,
                    std::vector<std::string>& petNames,
                    std::vector<std::string>& petTypes,
                    int* numDaysAtStorePtr,
                    int* numDaysAtStoreSize){
    
    std::string dataLine, cell;
    int numCell;
    getHeaderLine(inFile, headers);

    while(std::getline(inFile, dataLine)){
        std::istringstream dataToParse(dataLine);
        for (int i = 0; i < 4; i++){
            std::getline(dataToParse, cell, ',');
            if (i == 0){
                petStoreNames.push_back(cell);
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
                numDaysAtStorePtr = pushBackInteger(numDaysAtStorePtr, numDaysAtStoreSize, numCell );
            }                        
        }      
    }
    std::cout<<numDaysAtStorePtr[6]<<std::endl;
}

void getHeaderLine(std::ifstream& inFile, std::vector<std::string>& headers){
    std::string headerLine, cell;

    std::getline(inFile, headerLine);
    std::istringstream lineToParse(headerLine);
    while (std::getline(lineToParse, cell, ',')) { //For the text seperated by a comma add the element to the vector
        headers.push_back(cell); //For the first line only
    }

}


int* pushBackInteger(int* originalArray, int* arraySize, int newValue ){
    (*arraySize)++;
    int* newArray = new int[*arraySize];
    for (int i = 0; i < (*arraySize - 1); i++){
        newArray[i] = originalArray[i];
    }
    newArray[*arraySize-1] = newValue;

    if (originalArray != nullptr) {
        delete[] originalArray;
    }

    return newArray;

}

    /*************************************************************
    * Function: processData ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/17/23
    * Description: This function process the vectors and outputs
    * the result to the terminal
    * Input parameters: header row and column vectors
    * Returns: T/F if sucessful and outputs to terminal
    * Pre: Data from CSV must be input into vectors
    * Post: Processed vectors in the terminal.
    *************************************************************/

bool processData(const std::string& filename, //Reference vectors from the main
                        std::ifstream& inFile,
                        std::vector<std::string>& headers,
                        std::vector<std::string>& petStoreName,
                        std::vector<std::string>& petName,
                        std::vector<std::string>& petType,
                        int* numDaysAtStorePtr,
                        int* numDaysAtStoreSize){

    if (fileOpen(filename, inFile)) { //If the file can open run the following
        getDataFromCSV(inFile, headers, petStoreName, petName, petType, numDaysAtStorePtr, numDaysAtStoreSize); //Get the data from CSV to the indivudal vectors

        //clearScreen(); //Clear screen
        std::cout<<numDaysAtStorePtr[6]<<std::endl;
        
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
            << numDaysAtStorePtr[i] << " day(s) on site at store \"" << petStoreName[i] << "\"" << std::endl;
        }

        std::cout << "All pet store data processed!" <<std::endl << std::endl;

        inFile.close(); //Close the file
        return true;
    } else {
        std::cerr << "The file " + filename + " has encountered an error. Please make sure the file is in the correct directory and you have the appropriate permissions to read." << std::endl;
        return false; //If there was a problem show the error
    }
}