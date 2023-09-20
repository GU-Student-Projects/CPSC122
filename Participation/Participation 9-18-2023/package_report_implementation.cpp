/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 07 Quiz
 Notes:		
*/

#include "package_report.h"

     /*************************************************************
    * Function: importPackagesLog ()
    * Date Created: 9/18/23
    * Date Last Modified: 9/18/23
    * Description: takes an input from a .log file and imports 
	* the contents into vectors
    * Input parameters: opened file, names, sizes, and weights
    * Returns: variables seperated into vectors
    * Pre: opened file and initialized vectors
    * Post: filled vectors
    *************************************************************/

void importPackagesLog(ifstream& infile, vector<string>& names, vector<string>& sizes, vector<double>& weights)
{
	string tempString;
	double tempWeight;

	while (!infile.eof() && !infile.fail())
	{
		getline(infile, tempString); //name

		if (tempString.size() == 0)
		{
			//empty string, something went wrong
			//also detects an extra newline at the end of our file
			break;
		}

		names.push_back(tempString);
		getline(infile, tempString); //sizes
		sizes.push_back(tempString);
		infile >> tempWeight; //weights
		weights.push_back(tempWeight);
		getline(infile, tempString); //newline in the input buffer
		getline(infile, tempString); //don't forget the newline between data sets!
	}

	return;
}

     /*************************************************************
    * Function: printPackageList ()
    * Date Created: 9/18/23
    * Date Last Modified: 9/18/23
    * Description: takes the input from vectors and outputs to cli
    * Input parameters: packagesListName, vector names, sizes, and weights
    * Returns: command out report
    * Pre: opened file and filled vectors vectors
    * Post: command line output
    *************************************************************/

bool printPackageList(string packagesListName, vector<string> names, vector<string> sizes, vector<double> weights)
{
	//If our list name is not an empty string and our vectors are the same size...
	if (packagesListName.size() > 0 && (names.size() == sizes.size() && names.size() == weights.size()))
	{
		cout << "Package List Name: " << packagesListName << endl << endl;
		for (int i = 0; i < names.size(); i++) //we can use this size because we know all our vectors are the same size
		{
			cout << "Recipient Name: " << names.at(i) << endl;
			cout << "Package Size: " << sizes.at(i) << endl;
			cout << "Package Weight: " << fixed << setprecision(2) << weights.at(i) << endl << endl; //extra endl to put a newline between packages
		}
	}
	else
	{
		//something is wrong!
		return false;
	}
	return true; //success! we will only get here if we do NOT enter the else statement above
}