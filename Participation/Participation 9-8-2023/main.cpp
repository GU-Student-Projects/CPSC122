//[INCLUDE NAME BLOCK ON EACH OF YOUR 3 FILES]
/*
 Name:
 Class: CPSC 122, Fall 2023
 Lecture 04 Demonstration
 Notes:		

 I do not have any questions.
*/

#include "count.h"


int main()
{
	// declare all local variables at the top of your functions (main in this case)
	ifstream infile;
	ofstream outfile;
	stringstream ss;
	string tempString = "", rowData = "";
	int tempInt = -1, currCol = 1;
	vector<string> headerData; // empty vector
	vector<string> col1Data;   // empty vector
	vector<int> col2Data;	   // empty vector
	// TODO: what about column 3 data?
	bool infileIsOpen = false;

	// random not needed for this code example, only used to demonstrate random number generation
	int randNum = 0;
	srand(time(0)); // seed random number generator, time(0) for
	randNum = rand() % 6 + 1;

	// after declaring all variables, THEN perform calculations, function calls, etc.
	infileIsOpen = openInputFile(infile, "data.csv");
	outfile.open("output.dat"); // could open the output file the same way as input file

	if (!infileIsOpen)
	{
		cout << "Input file failed to open successfully..." << endl;
		exit(-1);
	}

	///////////////////////////////// ROW 0 ///////////////////////////////////////////////////
	getline(infile, tempString);

	ss.clear();

	ss.str(tempString); //"header1,header2,header3"

	// Column 1
	getline(ss, rowData, ','); // getline(input stream, destination string, delimiter token);
	cout << rowData << " was parsed from the line " << tempString << endl;
	headerData.push_back(rowData); //"header1"

	// Column 2
	getline(ss, rowData, ','); // getline(input stream, destination string, delimiter token);
	cout << rowData << " was parsed from the line " << tempString << endl;
	headerData.push_back(rowData); //"header2"

	// Column 3
	getline(ss, rowData, ','); // getline(input stream, destination string, delimiter token);
	cout << rowData << " was parsed from the line " << tempString << endl;
	// for this example, we're not using column 3
	// headerData.push_back(rowData); //"header3"

	///////////////////////////////// ROW 1 ///////////////////////////////////////////////////
	// get row 1, row data
	// read a line from the input file
	getline(infile, tempString);

	ss.clear();

	ss.str(tempString); //"data11,42,data13"

	// Column 1
	getline(ss, rowData, ','); // getline(input stream, destination string, delimiter token);
	cout << rowData << " was parsed from the line " << tempString << endl;
	col1Data.push_back(rowData); //"data11"

	// Column 2 --> we have a problem here!
	// HALT!!! This code won't work as expected!!!
	getline(ss, rowData, ','); // getline(input stream, destination string, delimiter token);
	cout << rowData << " was parsed from the line " << tempString << endl;
	col1Data.push_back(rowData); // "42" --> but we don't want to treat it as a string! We also don't want to store it with our col1 data!

	// Column 3 --> MORE problems! This also won't work how you expect!
	getline(ss, rowData, ','); // getline(input stream, destination string, delimiter token);
	cout << rowData << " was parsed from the line " << tempString << endl;

	// WRITE to the output file
	// assumptions right now... our data was good and we successfully read all data in
	// both of our parallel vectors are the same size because of ^

	for (int i = 0; i < headerData.size(); i++)
	{
		outfile << "Header: " << headerData.at(i) << endl;

		switch (currCol)
		{
		case 1:
			for (int j = 0; j < col1Data.size(); j++)
			{
				outfile << "Data: " << col1Data.at(j) << endl;
			}
			break;
		case 2:
			// Doesn't work for current implementation! Best not run it for now...
			//  for (int j = 0; j < col1Data.size(); j++)
			//  {
			//  	outfile << "Data: " << col2Data.at(j) << endl;
			//  }
			break;
		case 3:
			// etc.
			break;
		default:
			outfile << "Input Error" << endl;
			break;
		}
		currCol++;
	}

	outfile << "Done processing input file!" << endl;

	infile.close();
	outfile.close();

	return 0;
}

