/*
Name: Gabe DiMartino
Class: CPSC122, Fall 2023
Date: September 17, 2023
Programming Assignment: PA2
Description: This cpp contains all of the implementations of functions
*/

#ifndef PET_STORE_H
#define PET_STORE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

void clearScreen();
bool fileOpen(const std::string& filename, std::ifstream& inFile);
bool fileWrite(const std::string& filename, std::ofstream& outFile);
void getDataFromCSV(std::ifstream& inFile, 
                    std::vector<std::string>& headers,
                    std::vector<std::string>& petStoreNames,
                    std::vector<std::string>& petNames,
                    std::vector<std::string>& petTypes,
                    int* numDaysAtStorePtr,
                    int* numDaysAtStoreSize);
void getHeaderLine(std::ifstream& inFile, std::vector<std::string>& headers);
int* pushBackInteger(int* originalArray, int* arraySize, int newValue );
bool processData(const std::string& filename, //Reference vectors from the main
                        std::ifstream& inFile,
                        std::vector<std::string>& headers,
                        std::vector<std::string>& petStoreName,
                        std::vector<std::string>& petName,
                        std::vector<std::string>& petType,
                        int* numDaysAtStorePtr,
                        int* numDaysAtStoreSize);



#endif