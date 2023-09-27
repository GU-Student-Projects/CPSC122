/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 10 Pointers 2
 Notes:	No questions
*/

#include <iostream>

using namespace std;

int* dynamicArray(int* originalArray, int* arraySize, int newValue);
void getNum(int* num);

int main(){
    int num;
    int arraySize = 0; //This variable keeps track of the size of your numDays dynamic array
    int* arraySizePtr = &arraySize;
    int* arrayPtr = new int[*arraySizePtr];

    getNum(&num);

    for(int i = 0; i < num; i++){
        arrayPtr = dynamicArray(arrayPtr, arraySizePtr, i);
    }

    for(int i= 1; i < *arraySizePtr; i++){
        cout << arrayPtr[*arraySizePtr-i] << endl;
    }

    delete[] arrayPtr;

    return 0;
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