#ifndef MAIN_H
#define MAIN_H

#include <iostream> //needed for input/output streams from the console
#include <fstream>	//needed for file streams
#include <sstream>	//needed for string streams
#include <string>	//neeeded for string data type

bool openInputFile(std::ifstream &infile, std::string filename);
void parseLine(std::ifstream& infile);
void parseWord(std::string line);
void parseCharacter(std::string word);

#endif