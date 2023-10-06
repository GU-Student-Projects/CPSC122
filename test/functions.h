#ifndef FUNCTIONS_H  // Header guard: Checks if FUNCTIONS_H is not defined to prevent double inclusion of the header.
#define FUNCTIONS_H

#include <iostream>               // Include the standard input/output stream header.
#include <fstream>                // Include the file stream header.
#include <vector>                 // Include the vector header for using vector.
#include <ctime>                  // Include the C time header for time-related functions.
#include <cstdlib>                // Include the C standard library header for general-purpose functions.
#include <vector>    // Include the vector header for using vector.
#include <string>    // Include the string header for using string.

using namespace std;
// Function to append an integer to a dynamic array
int* pushBackInteger(int* originalArray, int& size, int newInt);

// Function to check if a string is in a vector
bool stringIsInVector(const vector<string>& searchVector, const string& targetString);

// Function to alphabetize pet names
void alphabetizePetNames(const vector<string>& petNames, vector<string>& alphabetizedNames);

// Function to read pet store data from a CSV file
bool ReadPetStoreData(ifstream& inputFile, vector<string>& petStoreNames,
                     vector<string>& petNames, vector<string>& petTypes,
                     int*& numDaysAtStorePtr, int& numDaysAtStoreSize);

// Function to process pet data and calculate summary information
void ProcessPetData(const vector<string>& petStoreNames, const vector<string>& petNames,
                   const vector<string>& petTypes, const int* numDaysAtStorePtr, const int numDaysAtStoreSize);

// Function to generate and save the CSV summary report
void GenerateCsvSummaryReport(ofstream& outputFile, const vector<string>& petStoreNames,
                             const vector<string>& petNames);
                             // Function to display pet data and messages to the console
void displayToConsole(const vector<string>& petStoreNames, const vector<string>& petNames,
                      const vector<string>& petTypes, const int* numDaysAtStorePtr, const int numDaysAtStoreSize);


#endif  // End of the header guard, marking the end of the header file.
