/*
    11-3-2023
    CPSC 122
    Linked List
    I Have no questions about PA5
*/

#include <iostream>
#include <string>

using namespace std;

// global constants

// enums

// structs/classes
class GroceryLinkedList 
{
private:
    struct GroceryListNode
    {
    string description;
    double price;
    GroceryListNode *nextPtr;
    };

    GroceryListNode* headPtr;

    GroceryListNode* createNode(string, double);//create a node
public:
    GroceryLinkedList();//constructor
    ~GroceryLinkedList(){};//deconstructor

    void appendNode(string, double);//append a node
    void insertNode(string, double, string);//insert a node somewhere
    void deleteNode(string); //delete a node
    void displayList(void) const; //display all nodes

};





// main.cpp
// #include "header.h"
int main(void)
{
    GroceryLinkedList myList;

    myList.appendNode("Cheese",2.99);
    myList.appendNode("Milk", 5.21);
    myList.appendNode("Bacon",6.99);


    return 0;
}

// definitions.cpp
// #include "header.h"

GroceryLinkedList::GroceryLinkedList(){
    headPtr = nullptr;

};

GroceryLinkedList::GroceryListNode* GroceryLinkedList::createNode(string itemName, double itemValue)
{
    GroceryListNode* newNode = new GroceryListNode;
    newNode->description = itemName;
    newNode->price = itemValue;
    newNode->nextPtr = nullptr;

    return newNode;
}

void GroceryLinkedList::appendNode(string itemName, double itemValue)
{
    GroceryListNode* newNode = createNode(itemName, itemValue);
    GroceryListNode* helperNodePtr = nullptr;

    if (headPtr == nullptr){
        headPtr = newNode;
    } else {
        helperNodePtr = headPtr;
        while(helperNodePtr->nextPtr != nullptr){
            helperNodePtr = helperNodePtr->nextPtr;
        }
        helperNodePtr->nextPtr = newNode;
    }
}