/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 07 Quiz
 Notes:		

 I do not have any questions.
*/

#include "main.h"

int main() {
	string inputFileName = "packages.log";
	string line = "", packageListName = "";
	bool readSuccess = false;

	//These are three EMPTY vectors! They have NO size!
	//We CANNOT access them using an index value while the are empty!
	//We have to INCREASE their size when adding new items to our vector
	//(hint: see vector member functions)
	//We are using these as three PARALLEL vectors -- you should be familiar with this
	//concept, if not, use this as a chance to ask for help or look it up! (hint it's important)
	vector<string> names;
	vector<string> sizes;
	vector<double> weights;

	ifstream infile;
	infile.open(inputFileName);

	//test file is open
	if (!infile.is_open())
	{
		cout << "Failed to open " << inputFileName << ". Exiting program." << endl;
		return -1;
	}

	//read package list name
	getline(infile, packageListName);
	//get rid of the newline
	getline(infile, line);

	//read package data from the input file and store it into vectors
	importPackagesLog(infile, names, sizes, weights);

	//print out log summary report
	readSuccess = printPackageList(packageListName, names, sizes, weights);

	if (readSuccess)
		cout << "Successfully read the packages list!" << endl;
	else
		cout << "Failed to read the packages list!" << endl;

	infile.close();

	return 0;
}