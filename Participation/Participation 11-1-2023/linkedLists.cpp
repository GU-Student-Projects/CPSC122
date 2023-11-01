/*
    11-1-2023
    CPSC 122
    Linked List
*/

#include <iostream>
#include <string>

using namespace std;

// global constants

// enums

// structs/classes
struct GroceryListNode
{
    string description;
    double price;
    GroceryListNode *nextPtr;
};



// main.cpp
// #include "header.h"
int main(void)
{
    GroceryListNode* headPtr = nullptr;

    GroceryListNode itemOne;
    itemOne.description = "Cheese";
    itemOne.price = 2.99;
    itemOne.nextPtr = nullptr;

    headPtr = &itemOne;

    GroceryListNode itemTwo;
    itemTwo.description = "Milk";
    itemTwo.price = 5.21;
    itemTwo.nextPtr = nullptr;

    itemOne.nextPtr = &itemTwo;

    GroceryListNode itemThree;
    itemThree.description = "Bacon";
    itemThree.price = 6.99;
    itemThree.nextPtr = nullptr;

    itemTwo.nextPtr = &itemThree;


    return 0;
}

// definitions.cpp
// #include "header.h"

// bool MyList::isEmpty(void){
//     //mtyList() has an attribute: headPtr
//     //headPtr is a pointer to a node in
//     //this linked list class

//     if(headPtr){
//         return false;
//     }
//     return true;
// }