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

using namespace std;

int* dynamicArray(int* originalArray, int* arraySize, int newValue);
void getNum(int* num);
void clearScreen();

int main(){
    int num;
    int arraySize = 0;
    int* arraySizePtr = &arraySize;
    int* arrayPtr = new int[*arraySizePtr];

    getNum(&num);
    clearScreen();

    for(int i = 0; i < num; i++){
        arrayPtr = dynamicArray(arrayPtr, arraySizePtr, i*i);
    }

    for(int i= 1; i < *arraySizePtr; i++){
        cout << arrayPtr[i] << endl;
    }

    delete[] arrayPtr;

    return 0;
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