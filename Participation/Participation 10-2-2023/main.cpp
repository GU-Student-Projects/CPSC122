/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 13 Pointers 2
 Notes:	No questions
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void prIntArray();
int* getMoreRandomNumbers(int size, int* arrayPtr, int* arraySizePtr);
void getNum(int* num);
int* dynamicArray(int* originalArray, int* arraySize, int newValue );
void getRandomNumbers(int size, int** myInts);

string* addNewString(string* originalArray, int* arraySize, string newValue );

int main(){    
    srand(time(nullptr));
    prIntArray();

    ifstream infile;
    int sizeCount = 0;
    int* sizeCountPtr = &sizeCount;
    string* words = new string[*sizeCountPtr];
    string word = "";
    infile.open("thisIsACoolFile.txt");
    while (!infile.eof()){
        getline(infile, word);
        words = addNewString(words, sizeCountPtr, word);
    }

    delete[] words;

    return 0;
}

     /*************************************************************
    * Function: prIntArray ()
    * Date Created: 10/2/23
    * Date Last Modified: 10/2/23
    * Description: Creates a dynamic array and with random numbers
    * Input parameters: User inputs for size of array
    * Returns: terminal output
    *************************************************************/

void prIntArray(){
    int num;
    int arraySize = 0;
    int* arraySizePtr = &arraySize;
    int* arrayPtr = new int[*arraySizePtr];
    int* anotherArrayPtr = new int[*arraySizePtr];

    getNum(&num);

    arrayPtr = getMoreRandomNumbers(num, arrayPtr, arraySizePtr);

    cout << "Your output for getMoreRandomNumbers is: ";
    for(int i= 0; i < *arraySizePtr; i++){
        cout << arrayPtr[i] << " ";
    }
    cout<<endl;
    delete[] arrayPtr;
}

     /*************************************************************
    * Function: getNum ()
    * Date Created: 10/2/23
    * Date Last Modified: 10/2/23
    * Description: gets an input value from the user
    * Returns: size int
    *************************************************************/

void getNum(int* num){
    cout << "enter a number (integer):" << endl;
    cin >> *num;
}

void getRandomNumbers(int size, int** myInts){
    int numInts = 0;
    cout << "How many random nubers?";
    cin >> numInts;

    *myInts = new int[numInts];
    for (int i = 0; i < numInts; i++){
        (*myInts)[i] = rand() % 100 + 1;
    }

    cout << "Your output for getRandomNumbers is: ";
    for(int i= 0; i < numInts; i++){
        cout << (*myInts)[i] << " ";
    }
    cout<<endl;
    delete[] *myInts;

}
     /*************************************************************
    * Function: getMoreRandomNumbers ()
    * Date Created: 10/2/23
    * Date Last Modified: 10/2/23
    * Description: generates random number to the array
    * Returns: populated array
    *************************************************************/

int* getMoreRandomNumbers(int size, int* arrayPtr, int* arraySizePtr){
    int randomNumber;
    for(int i = 0; i < size; i++){
        randomNumber = rand() % 100 + 1;
        arrayPtr = dynamicArray(arrayPtr, arraySizePtr, randomNumber);
    }
    return arrayPtr;
}
    /*************************************************************
    * Function: dynamicArray ()
    * Date Created: 10/2/23
    * Date Last Modified: 10/2/23
    * Description: dynamically add an integer to the array and
    * delete the previous array
    * Returns: populated array
    *************************************************************/

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