/*
Name: Gabe DiMartino
Class: CPSC122, Fall 2023
Date: November 5, 2023
Programming Assignment: PA5
Description: This cpp contains all of the definitions of functions
I AM ATTEMPTING THE BONUS CHALLENGE
*/

#include "header.h"

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
    * Date Last Modified: 11/5/23
    * Description: Opens any file passed to it. 
    * Input parameters: file name and the fStream variable
    * Returns: T/F if sucessful throws error if F
    * Pre: Read/Write access in directory
    * Post: Working file
    *************************************************************/

bool fileOpen(std::string filename, std::ifstream& inFile) {
    inFile.open(filename); //open file
    return inFile.is_open();
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
    * Date Last Modified: 11/6/23
    * Description: Converts the CSV data into a linked list
    * Input parameters: file, headers vector, list
    * Returns: void
    * Pre: Existing CSV file is opened
    * Post: populated list
    *************************************************************/

void getDataFromCSV(std::ifstream& inFile, PetStoreList& storeList) {
    std::vector<std::string> headers;
    std::string dataLine;

    getHeaderLine(inFile, headers); // Get the header line and store it in headers vector

    std::cout << "Processed " << headers.size() << " header columns: "; //Format the headers with commas
        for (size_t i = 0; i < headers.size(); i++) {
            std::cout << headers[i];
            if (i < headers.size() - 1) {
                std::cout << ", ";
            }
        }

    std::cout << std::endl << std::endl;

    while (std::getline(inFile, dataLine)) {
        std::istringstream dataToParse(dataLine);
        std::string storeName, pName, pType;
        int numDays;
        
        if (dataLine.empty()) {
            break; // Exit the loop if an empty line is encountered
        }

        std::getline(dataToParse, storeName, ','); //add input from CSV to each variable
        std::getline(dataToParse, pName, ',');
        std::getline(dataToParse, pType, ',');
        dataToParse >> numDays;

        std::cout << "Processed a " << pType << ", \"" << pName << "\" ... "
        << numDays << " day(s) on site at store \"" << storeName << "\"" << std::endl;

        storeList.addPetData(storeName,pName,pType,numDays);
    }
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
    * Function: processData ()
    * Date Created: 9/2/23
    * Date Last Modified: 11/5/23
    * Description: This function process the vectors and outputs
    * the result to the terminal
    * Input parameters: header row and column vectors
    * Returns: pointer int value for dynamic array
    * Pre: Data from CSV must be input into vectors
    * Post: Processed vectors in the terminal.
    *************************************************************/

bool processData(const std::string filename, std::ifstream& inFile, PetStoreList& storeList){

    if (fileOpen(filename, inFile)) { //If the file can open run the following
        clearScreen(); //Clear screen
        getDataFromCSV(inFile, storeList); //Get the data from CSV to the indivudal vectors
        std::cout << "All pet store data processed!" <<std::endl << std::endl;
        std::cout<< "Generating summary report..." <<std::endl<<std::endl;
        std::cout<< "Done!" <<std::endl<<std::endl;
        inFile.close(); //Close the file
        return true;

    } else {
        std::cerr << "The file " + filename + " has encountered an error. Please make sure the file is in the correct directory and you have the appropriate permissions to read." << std::endl;
        return false;
    }
}

    /*************************************************************
    * Function: PetStoreList ()
    * Date Created: 11/5/23
    * Date Last Modified: 11/5/23
    * Description: Default constructor to initialize the linked list
    * Input parameters: void
    * Returns: nullptr
    *************************************************************/

PetStoreList::PetStoreList(){
    headPtr = nullptr; //initiate with null pointer
};

    /*************************************************************
    * Function: ~PetStoreList ()
    * Date Created: 11/5/23
    * Date Last Modified: 11/5/23
    * Description: Default deconstructor to deinitialize the linked list
    * Input parameters: void
    * Returns: nullptr
    *************************************************************/

PetStoreList::~PetStoreList(){
    PetStoreData* nodePtr = headPtr;
    PetStoreData* helperNode = nullptr;

    while (nodePtr != nullptr){ // Go through and delete each node
        helperNode = nodePtr->nextStore;
        delete nodePtr;
        nodePtr = helperNode;
    }
};

    /*************************************************************
    * Function: createNode()
    * Date Created: 11/5/23
    * Date Last Modified: 11/5/23
    * Description: creates a node for a linked list
    * Input parameters: store name
    * Returns: PetStoreNode pointer
    *************************************************************/

PetStoreList::PetStoreData* PetStoreList::createNode(std::string storeName){
    PetStoreData* newPetStoreNode = new PetStoreData;
    newPetStoreNode->petStoreName = storeName; //create a new node from the storeName
    newPetStoreNode->nextStore = nullptr; //Initialize the nullptr

    return newPetStoreNode;
}

    /*************************************************************
    * Function: insertAtEnd()
    * Date Created: 11/5/23
    * Date Last Modified: 11/5/23
    * Description: Adds a node to the end of a linked list
    * Input parameters: Node pointer
    * Returns: void
    *************************************************************/

void PetStoreList::insertAtEnd(PetStoreData* newStoredata){
    if (headPtr == nullptr) {
            headPtr = newStoredata; //if there are no nodes, make it the head
    } else {
        PetStoreData* helperNodePtr = headPtr;
        while (helperNodePtr->nextStore != nullptr) {
            helperNodePtr = helperNodePtr->nextStore; //go through the list until at the end and insert the new node.
        }
        newStoredata->nextStore = nullptr;
        helperNodePtr->nextStore = newStoredata;
     }
}

    /*************************************************************
    * Function: storeInList()
    * Date Created: 11/5/23
    * Date Last Modified: 11/5/23
    * Description: Given store name, verify name exists in list
    * Input parameters: Store name
    * Returns: bool
    *************************************************************/

bool PetStoreList::storeInList(std::string name) {
    PetStoreData* helperPtr = headPtr;
    
    while (helperPtr != nullptr) {
        if (helperPtr->petStoreName == name) { //Go through the nodes comparing the string petStoreName
            return true;
        }
        helperPtr = helperPtr->nextStore;
    }
    
    return false;
}


    /*************************************************************
    * Function: addPetData()
    * Date Created: 11/5/23
    * Date Last Modified: 11/5/23
    * Description: Given pet data and store information, add to node
    * Input parameters: Store name and Store Data
    * Returns: void
    *************************************************************/

void PetStoreList::addPetData(std::string storeName, std::string pName, std::string pType, int numDays) {
    PetStoreData* helperNodePtr = headPtr;
    PetData newPetData;
    PetStoreData* newStore;

    if (storeInList(storeName)) {
        
        while (helperNodePtr != nullptr) {
            if (helperNodePtr->petStoreName == storeName) {
                newPetData.petName = pName;
                newPetData.petType = pType;
                newPetData.numDaysAtStore = numDays;
                helperNodePtr->petData.push_back(newPetData); //Push back everything to PetData vector
                return;
            }
            helperNodePtr = helperNodePtr->nextStore;
        }
    } else {
        // If the store doesnt exist, create it and then add the pet data
        newStore = createNode(storeName);
        insertAtEnd(newStore);
        addPetData(storeName, pName, pType, numDays); // Recursively call with the newly created store
    }
}

    /*************************************************************
    * Function: calculatePetSummary()
    * Date Created: 11/5/23
    * Date Last Modified: 11/5/23
    * Description: fill programer defined struct
    * with calculated information
    * Input parameters: void
    * Returns: void
    *************************************************************/

void PetStoreList::calculatePetSummary(){
    PetStoreData* helperPtr = headPtr;
    int tempVariable = 0; //initial value
    summaryData.numPets = 0; //initial value
    summaryData.minDaysAtStore = helperPtr->petData[0].numDaysAtStore; //initial value
    summaryData.maxDaysAtStore = 0; //initial value

    while (helperPtr != nullptr){ //go through the list
        for (size_t i = 0; i < helperPtr->petData.size(); i++) {
            tempVariable += helperPtr->petData[i].numDaysAtStore;
            if (helperPtr->petData[i].numDaysAtStore < summaryData.minDaysAtStore){
                summaryData.minDaysAtStore = helperPtr->petData[i].numDaysAtStore; //find the minimum days
            }
            if (helperPtr->petData[i].numDaysAtStore > summaryData.maxDaysAtStore){
            summaryData.maxDaysAtStore = helperPtr->petData[i].numDaysAtStore; //find the maximum days
            }
        }
        summaryData.numPets += helperPtr->petData.size(); //calculate and combine the size of each node
        helperPtr = helperPtr->nextStore;
    }

    if (summaryData.numPets != 0) {
        summaryData.averageDaysAtStore = tempVariable / summaryData.numPets; //calculate average
    } else {
        summaryData.averageDaysAtStore = 0; //if none, set 0
    }
}

    /*************************************************************
    * Function: displayPetList()
    * Date Created: 11/5/23
    * Date Last Modified: 11/5/23
    * Description: Visualize PetStore information in console
    * Input parameters: void
    * Returns: void
    *************************************************************/

void PetStoreList::displayPetSummary() const{
    std::cout<< "__________________________________" <<std::endl;
    std::cout<< "Total number of pets: "<< summaryData.numPets <<std::endl;
    std::cout<< "Average number of days at pet store: "<< summaryData.averageDaysAtStore <<std::endl;
    std::cout<< "Shortest stay at pet store: "<< summaryData.minDaysAtStore <<std::endl;
    std::cout<< "Longest stay at pet store: "<< summaryData.maxDaysAtStore <<std::endl;
}

    /*************************************************************
    * Function: displayPetList()
    * Date Created: 11/5/23
    * Date Last Modified: 11/5/23
    * Description: Visualize PetStore information in console
    * Input parameters: void
    * Returns: void
    *************************************************************/

void PetStoreList::displayPetList() const {
    PetStoreData* storePtr = headPtr;

    while (storePtr != nullptr) {
        std::cout<< "__________________________________" <<std::endl;
        std::cout << "Pet Store Name: " << storePtr->petStoreName << std::endl;
        std::cout << "**********************************" << std::endl;
        std::cout << "| Number of pets: " << storePtr->petData.size() << std::endl;
        std::cout << "| Pet Information: " << std::endl;

        for (size_t i = 0; i < storePtr->petData.size(); i++) {
            std::cout << "> Pet " << i + 1 << " Name: " << storePtr->petData[i].petName << std::endl;
            std::cout << "> Pet Type: " << storePtr->petData[i].petType << std::endl;
            std::cout << "> Number of days at store: " << storePtr->petData[i].numDaysAtStore << std::endl;
            std::cout<<"----------------------------"<<std::endl;
        }

        storePtr = storePtr->nextStore;
    }

}

    /*************************************************************
    * Function: writePetSummary()
    * Date Created: 11/5/23
    * Date Last Modified: 11/5/23
    * Description: Visualize PetStore information in txt
    * Input parameters: ofstream
    * Returns: void
    *************************************************************/

void PetStoreList::writePetSummary(std::ofstream& outfile){
    outfile<< "Pet Store CSV Summary Report" <<std::endl;
    outfile<< "__________________________________" <<std::endl;
    outfile<< "Total number of pets: "<< summaryData.numPets <<std::endl;
    outfile<< "Average number of days at pet store: "<< summaryData.averageDaysAtStore <<std::endl;
    outfile<< "Shortest stay at pet store: "<< summaryData.minDaysAtStore <<std::endl;
    outfile<< "Longest stay at pet store: "<< summaryData.maxDaysAtStore <<std::endl;
}

    /*************************************************************
    * Function: writePetList()
    * Date Created: 11/5/23
    * Date Last Modified: 11/5/23
    * Description: Visualize PetStore information in txt
    * Input parameters: ofstream
    * Returns: void
    *************************************************************/

void PetStoreList::writePetList(std::ofstream& outfile){
    PetStoreData* storePtr = headPtr;

    while (storePtr != nullptr) {
        outfile << "__________________________________" <<std::endl;
        outfile << "Pet Store Name: " << storePtr->petStoreName << std::endl;
        outfile << "**********************************" << std::endl;
        outfile << "| Number of pets: " << storePtr->petData.size() << std::endl;
        outfile << "| Pet Information: " << std::endl;

        for (size_t i = 0; i < storePtr->petData.size(); i++) {
            outfile << "> Pet " << i + 1 << " Name: " << storePtr->petData[i].petName << std::endl;
            outfile << "> Pet Type: " << storePtr->petData[i].petType << std::endl;
            outfile << "> Number of days at store: " << storePtr->petData[i].numDaysAtStore << std::endl;
            outfile<<"----------------------------"<<std::endl;
        }

        storePtr = storePtr->nextStore;
    }

}

    /*************************************************************
    * Function: insertAtFront()
    * Date Created: 11/5/23
    * Date Last Modified: 11/5/23
    * Description: inserts node as the head pointer/Front
    * Input parameters: newStoreData ptr
    * Returns: void
    *************************************************************/

void PetStoreList::insertAtFront(PetStoreData* newStoredata) {
    newStoredata->nextStore = headPtr; //append the original head
    headPtr = newStoredata; //Make new node head pointer
}

    /*************************************************************
    * Function: insertAtPosition()
    * Date Created: 11/5/23
    * Date Last Modified: 11/5/23
    * Description: inserts node any position
    * Input parameters: newStoreData ptr and input position
    * Returns: T/F
    *************************************************************/

bool PetStoreList::insertAtPosition(PetStoreData* newStoredata, int position) {
    PetStoreData* helperPtr = headPtr;
    int i = 0;
    position -= 1;

    if (position < 0) {
        return false; //if less than 0 do nothing
    }
    if (position == 0 || headPtr == nullptr) {
        insertAtFront(newStoredata); //if position = 0 insert at front
        return true;
    }
    while (helperPtr->nextStore != nullptr && i < position - 1) {
        helperPtr = helperPtr->nextStore;  //loop through the list till the position is found
        i++;
    }
    if (i == position - 1) {
        newStoredata->nextStore = helperPtr->nextStore;
        helperPtr->nextStore = newStoredata; //insert at location
        return true;
    }

    return false;
}



     /*************************************************************
    * Function: deleteStore()
    * Date Created: 11/5/23
    * Date Last Modified: 11/5/23
    * Description: deletes node by Name
    * Input parameters: store name
    * Returns: T/F
    *************************************************************/

bool PetStoreList::deleteStore(std::string nameOfStoreToRemove) {
    PetStoreData* tempPtr = headPtr; //temp node pointer
    PetStoreData* previousPtr = headPtr; //previous node pointer
    PetStoreData* currentPtr = headPtr->nextStore; //next node pointer
    
    if (!storeInList(nameOfStoreToRemove)) {
        return false;    } //if store doesnt exist do nothing

    if (headPtr != nullptr && headPtr->petStoreName == nameOfStoreToRemove) {
        headPtr = headPtr->nextStore;
        delete tempPtr; //remove initial store and set new head pointer
        return true;
    }

    while (currentPtr != nullptr) {
        if (currentPtr->petStoreName == nameOfStoreToRemove) { //find the store
            previousPtr->nextStore = currentPtr->nextStore; //create alternate path for the node pointers
            delete currentPtr; //delete the node
            return true;
        }
        previousPtr = currentPtr; //append the list to exclude the deleted node
        currentPtr = currentPtr->nextStore;
    }

    return false;
}