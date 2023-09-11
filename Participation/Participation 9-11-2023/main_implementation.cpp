/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 05 Demonstration
 Notes:		
*/

#include "main.h"

bool openInputFile(std::ifstream &infile, std::string filename){
	infile.open(filename);

	if (infile.is_open())
	{
		return true;
	}
	return false;
}

void parseLine(std::ifstream& infile){
    std::string line;
    while(std::getline(infile, line)){
        std::cout<<"Line: "<<line<<std::endl;
        std::cout<<std::endl;
        parseWord(line);
    }
    std::cout<<std::endl;

}

void parseWord(std::string line){
    std::istringstream lineToParse(line);
    std::string word;
    while(getline(lineToParse, word, ' ')){
        std::cout<<"Word: "<<word<<std::endl;
        parseCharacter(word);

    }
    std::cout<<std::endl;

}

void parseCharacter(std::string word){
    for(size_t i=0; i < word.size(); i++){
        std::cout<<"Character: "<<word[i]<<std::endl;
    }
    std::cout<<std::endl;
}