/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 10 Pointers 2
 Notes:	No questions
*/

#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif
#include <ctime>
#include <fstream>
#include <sstream>
using namespace std;

int* dynamicArray(int* originalArray, int* arraySize, int newValue);
void getNum(int* num);
void clearScreen();
int* getRandomNumbers(int size, int* arrayPtr, int* arraySizePtr);
void getRandomNumberArray();
string* addNewString(string* originalArray, int* arraySize, string newValue );
bool openInputFile(std::ifstream &infile, std::string filename);
string* parseLine(std::ifstream& infile, string* originalArray, int* arraySize);
string* parseWord(std::string line, string* originalArray, int* arraySize);

int main(){
    clearScreen();
    //srand(time(0));
    //getRandomNumberArray();
    ifstream infile;
	bool inputfileIsOpen = false;

    inputfileIsOpen = openInputFile(infile, "thisIsACoolFile.txt");
    infile.close();
    

    return 0;
}

bool openInputFile(std::ifstream &infile, std::string filename){
	infile.open(filename);

	if (infile.is_open())
	{
		return true;
	}
	return false;
}

string* parseLine(std::ifstream& infile, string* originalArray, int* arraySize){
    std::string line;
    while(std::getline(infile, line)){
        std::cout<<"Line: "<<line<<std::endl;
        std::cout<<std::endl;
        originalArray = parseWord(line, originalArray, arraySize);
    }
    return originalArray;

}

string* parseWord(std::string line, string* originalArray, int* arraySize){
    std::istringstream lineToParse(line);
    std::string word;
    while(getline(lineToParse, word, ' ')){
        originalArray = addNewString(originalArray, arraySize, word );
    }
    return originalArray;

}


void getRandomNumberArray(){
    int num;
    int arraySize = 0;
    int* arraySizePtr = &arraySize;
    int* arrayPtr = new int[*arraySizePtr];

    getNum(&num);

    arrayPtr = getRandomNumbers(num, arrayPtr, arraySizePtr);

    printf("Your output is: ");
    for(int i= 0; i < *arraySizePtr; i++){
        cout << arrayPtr[i] << " ";
    }
    cout<<endl;
    delete[] arrayPtr;
}

int* getRandomNumbers(int size, int* arrayPtr, int* arraySizePtr){
    int randomNumber;
    for(int i = 0; i < size; i++){
        randomNumber = rand() % 100;
        arrayPtr = dynamicArray(arrayPtr, arraySizePtr, randomNumber);
    }
    return arrayPtr;
}


void clearScreen(){ //function to clear terminal
#ifdef _WIN32 //If OS is WIN32 run cls else use clear
    system("cls");
#else
    system("clear");
#endif
}

void getNum(int* num){
    cout << "enter a number (integer):" << endl;
    cin >> *num;
}


int* dynamicArray(int* originalArray, int* arraySize, int newValue ){
    (*arraySize)++; 
    int* newArray = new int[*arraySize];
    for (int i = 0; i < (*arraySize - 1); i++){
        newArray[i] = originalArray[i]; 
    }
    newArray[*arraySize-1] = newValue; 

    if (originalArray != nullptr) {
        delete[] originalArray; 
    }

    return newArray; 

}

string* addNewString(string* originalArray, int* arraySize, string newValue ){
    (*arraySize)++; 
    string* newArray = new string[*arraySize];
    for (int i = 0; i < (*arraySize - 1); i++){
        newArray[i] = originalArray[i]; 
    }
    newArray[*arraySize-1] = newValue; 

    if (originalArray != nullptr) {
        delete[] originalArray; 
    }

    return newArray; 

}