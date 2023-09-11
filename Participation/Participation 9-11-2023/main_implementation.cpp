/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 05 Demonstration
 Notes:		
*/

#include "main.h"

bool openInputFile(ifstream &infile, string filename){
	infile.open(filename);

	if (infile.is_open())
	{
		return true;
	}
	return false;
}

void parseLine(ifstream& infile){
    string line;
    while(getline(infile, line)){
        cout<<"Line: "<<line<<endl;
        cout<<endl;
        parseWord(line);
    }
    cout<<endl;

}

void parseWord(string line){
    istringstream lineToParse(line);
    string word;
    while(getline(lineToParse, word, ' ')){
        cout<<"Word: "<<word<<endl;
        parseCharacter(word);

    }
    cout<<endl;

}

void parseCharacter(string word){
    for(size_t i=0; i < word.size(); i++){
        cout<<"Character: "<<word[i]<<endl;
    }
    cout<<endl;
}