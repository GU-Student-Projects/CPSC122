/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 05 Demonstration
 Notes:		
*/

#include "main.h"

    /*************************************************************
    * Function: openInputFile()
    * Date Created: 9/11/23
    * Date Last Modified: 9/11/23
    * Description: Opens the file
    * Input parameters: ifstream, filename
    * Returns: opened file, ifstream
    * Pre: Populated txt file
    * Post: opened file
    *************************************************************/
bool openInputFile(std::ifstream &infile, std::string filename){
	infile.open(filename);

	if (infile.is_open())
	{
		return true;
	}
	return false;
}

    /*************************************************************
    * Function: parseLine()
    * Date Created: 9/11/23
    * Date Last Modified: 9/11/23
    * Description: While there are lines, gets the line
    * Input parameters: ifstream
    * Returns: COUT line
    * Pre: Populated txt file, opened file
    * Post: runs parseWord
    *************************************************************/
void parseLine(std::ifstream& infile){
    std::string line;
    while(std::getline(infile, line)){
        std::cout<<"Line: "<<line<<std::endl;
        std::cout<<std::endl;
        parseWord(line);
    }
    std::cout<<std::endl;

}

    /*************************************************************
    * Function: parseWord()
    * Date Created: 9/11/23
    * Date Last Modified: 9/11/23
    * Description: While there are words, gets the word
    * Input parameters: line
    * Returns: COUT word
    * Pre: populated line variable
    * Post: runs parseCharacter
    *************************************************************/
void parseWord(std::string line){
    std::istringstream lineToParse(line);
    std::string word;
    while(getline(lineToParse, word, ' ')){
        std::cout<<"Word: "<<word<<std::endl;
        parseCharacter(word);

    }
    std::cout<<std::endl;

}

    /*************************************************************
    * Function: parseCharacter()
    * Date Created: 9/11/23
    * Date Last Modified: 9/11/23
    * Description: get the size of the word and output the character
    * Input parameters: word
    * Returns: COUT character
    * Pre: populated word variable
    * Post: COUT characters
    *************************************************************/
void parseCharacter(std::string word){
    for(size_t i=0; i < word.size(); i++){
        std::cout<<"Character: "<<word[i]<<std::endl;
    }
    std::cout<<std::endl;
}