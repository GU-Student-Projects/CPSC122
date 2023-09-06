/* Top level comment block


1. Are you having any issues setting up your programming environment? If so, have you sought help resolving your issues? 
    All of my enviornments are setup correctly and seem to be running fine. I have run into some issues with running CPP in
    linux mint in the passed but nothing too major and is easily fixed

2. What is your chosen programming environment setup? For example, VSCode on Windows.
    My chosen programming environment is 

3. Do you have any concerns about the course topics as they are laid out on the schedule?


*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

bool openInputFile(ifstream& infile, string filename);

int main(){

    ifstream infile;
    ofstream outfile;
    stringstream ss;
    vector<string> headerData;
    vector<string> row1Data;
    bool infileIsOpen = false;
    int randNum = 0;

    srand(time(0));
    randNum = rand() % row1Data.size();

    infileIsOpen = openInputFile(infile, "data.csv");
    outfile.open("output.data");


    return 0;
}

bool openInputFile(ifstream& infile, string filename){
    infile.open(filename);

    if (infile.is_open()){
        return true;
    }
    return false;
}