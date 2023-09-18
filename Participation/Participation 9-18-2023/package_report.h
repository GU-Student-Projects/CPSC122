/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 07 Quiz
 Notes:		
*/

/*
If the functions, namespace and libraries have not been added, add them to the cpp file
This prevents double inclusion on multiple files which can slow down the program
*/

#ifndef MAIN_H
#define MAIN_H 

#include <iostream> //need for console IO
#include <string> //don't forget to include libraries if we are using their functions!
#include <fstream> //need for file IO
#include <vector> //need for vectors
#include <iomanip> //need for fixed precision output

using namespace std;

using namespace std;

//function decleration to import the log. can be called from main
void importPackagesLog(ifstream&, vector<string>&, vector<string>&, vector<double>&); 

//function decleration to ouput the input information to the commandline
bool printPackageList(string, vector<string>, vector<string>, vector<double>); 


#endif