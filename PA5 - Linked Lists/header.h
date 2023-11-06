/*
Name: Gabe DiMartino
Class: CPSC122, Fall 2023
Date: November 5, 2023
Programming Assignment: PA5
Description: This headerfile lists all of the function descriptions
I AM ATTEMPTING THE BONUS CHALLENGE
*/

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

class PetStoreList {
private:
	//programmer-defined data type
	//stores data related to a single pet
	struct PetData {
		std::string petName;
		std::string petType;
		int numDaysAtStore;
	};

	//programmer-defined data type
	//stores data related to a single
	//PetStoreList
	struct PetSummary {
		int numPets;
		int averageDaysAtStore;
		int minDaysAtStore;
		int maxDaysAtStore;
	};

	//programmer-defined data type
	//stores data related to a single store
	//includes the store name, a vector of all
	//pet data associated with that store, and
	//a pointer to the next store in the list
	struct PetStoreData {
		std::string petStoreName;
		std::vector<PetData> petData;
		PetStoreData* nextStore;
	};

	//a private member of the PetStoreList class
	//storing this class object's summary data
	//for all pet stores and pets
	PetSummary summaryData;
	//pointer to the start of this class object's
	//list of pet store and pet data
	PetStoreData* headPtr;

public:
	PetStoreList(); //class constructor
	~PetStoreList(); //class destructor

	/* createNode
	* creates a new PetStoreData variable and initializes the store name,
	* returns a pointer to the dynamically allocated memory. */
	PetStoreData* createNode(std::string storeName); //Note: extra step attention required to handle this return type

	/* insertAtEnd
	* accepts a pointer to PetStoreData variable
	* inserts the PetStoreData "node" at the end of the list */
	void insertAtEnd(PetStoreData* newStoredata);

	/* addPetData
	* adds pet name, pet type, and number of days that pet has been at the store
	* to the vector of pet data for the matching store name. */
	void addPetData(std::string storeName, std::string pName, std::string pType, int numDays);

	/* displayPetList
	* prints the contents of the PetStoreList in forward order
	* see example output */
	void displayPetList() const;

	/* writePetList
	* writes the contents of the PetStoreList in forward order to an output file
	* see example output */
	void writePetList(std::ofstream& outfile);

	/* storeInList
	* accepts a string store name
	* returns true if the store name is in this object's list of stores	*/
	bool storeInList(std::string name);

	/* calculatePetSummary
	* calculates/updates this object's PetSummary values
	* see PetSummary programmer-defined data type */
	void calculatePetSummary();

	/* displayPetSummary
	* prints this object's PetSummary values of the PetStoreList
	* see example output */
	void displayPetSummary() const;

	/* writePetSummary
	* writes this object's PetSummary values of the PetStoreList to an output file
	* see example output */
	void writePetSummary(std::ofstream& outfile);

	//bonus class member functions

	/* insertAtFront (BONUS)
	* accepts a pointer to PetStoreData variable
	* inserts the PetStoreData "node" at the front of the list */
	void insertAtFront(PetStoreData* newStoredata);

	/* insertAtPosition (BONUS)
	* accepts a pointer to PetStoreData variable and a position in the list
	* zero-based index just like arrays/vectors
	* inserts the PetStoreData "node" at the position location in the list
	* returns false if the position was not a valid position (e.g., out of range) */
	bool insertAtPosition(PetStoreData* newStoredata, int position);

	/* deleteStore
	* accepts the name of a store to remove from the list
	* deletes a store and all of its petData
	* returns false if the store was not found and/or if the deletion was unsuccessful */
	bool deleteStore(std::string nameOfStoreToRemove);
};

bool processData(const std::string filename, std::ifstream& inFile, PetStoreList& storeList);
void clearScreen();
bool fileOpen(std::string filename, std::ifstream& inFile);
bool fileWrite(const std::string filename, std::ofstream& outFile);
void getDataFromCSV(std::ifstream& inFile, PetStoreList& storeList);
void getHeaderLine(std::ifstream& inFile, std::vector<std::string>& headers);

#endif