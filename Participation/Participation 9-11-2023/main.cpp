/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 05 Demonstration
 Notes:		

 I do not have any questions.
*/

#include "main.h"


int main()
{
	// declare all local variables at the top of your functions (main in this case)
	ifstream infile;
	bool inputfileIsOpen = false;

	// after declaring all variables, THEN perform calculations, function calls, etc.
	inputfileIsOpen = openInputFile(infile, "inputfile.txt");

	if (!inputfileIsOpen)
	{
		cout << "Input file failed to open successfully..." << endl;
		exit(1);
	}

    parseLine(infile);
    infile.close();

    return 0;
}