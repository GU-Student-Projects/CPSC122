/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 04 Demonstration
 Notes:		
*/

#include "main.h"

bool openInputFile(ifstream &infile, string filename)
{
	infile.open(filename);

	if (infile.is_open())
	{
		return true;
	}
	return false;
}