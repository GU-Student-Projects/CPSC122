/*
Name: Gabe DiMartino
Class: CPSC122, Fall 2023
Date: October 10, 2023
Programming Assignment: PA3
Description: This cpp contains all of the implementations of functions
*/

#include "Dart_Game.h"

     /*************************************************************
    * Function: clearScreen ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/2/23
    * Description: Uses an if statement to determine what OS is uesed
    * then runs the system command to clear the terminal
    * Input parameters: System OS
    * Returns: Clear Screen
    * Pre: Correct library
    * Post: Clear Screen
    *************************************************************/

void clearScreen(){ //function to clear terminal
#ifdef _WIN32 //If OS is WIN32 run cls else use clear
    system("cls");
#else
    system("clear");
#endif
}

    /*************************************************************
    * Function: fileOpen ()
    * Date Created: 9/2/23
    * Date Last Modified: 10/10/23
    * Description: Opens any file passed to it. 
    * Input parameters: file name and the fStream variable
    * Returns: T/F if sucessful throws error if F
    * Pre: Read/Write access in directory
    * Post: Working file
    *************************************************************/

bool fileOpen(const char* filename, std::ifstream& inFile) {
    inFile.open(filename);
    return inFile.is_open();
}

   /*************************************************************
    * Function: pushBackInteger ()
    * Date Created: 9/17/23
    * Date Last Modified: 9/18/23
    * Description: adjusts the dynamically assigned array for an
    * increase in size and adds the new value
    * Returns: increased array size with push back integer
    * Pre: original array exists, and the new value is present
    * Post: completed array
    *************************************************************/

int* pushBackInteger(int* originalArray, int* arraySize, int newValue ){
    (*arraySize)++; //increase size of the array
    int* newArray = new int[*arraySize]; //create a new array with the larger size
    for (int i = 0; i < (*arraySize - 1); i++){
        newArray[i] = originalArray[i]; //copy all of the content from the original array into the new array
    }
    newArray[*arraySize-1] = newValue; //add the new value to the last element of the new vector

    if (originalArray != nullptr) {
        delete[] originalArray; //if the array is not null, delete it
    }

    return newArray; //return the new array

}

   /*************************************************************
    * Function: pushBackPlayerCard()
    * Date Created: 10/10/23
    * Date Last Modified: 10/10/23
    * Description: adjusts the dynamically assigned array for an
    * increase in size and adds the new value
    * Returns: increased array size with push back characters
    * Pre: original array exists, and the new value is present
    * Post: completed array
    *************************************************************/

void pushBackPlayerCard(PlayerCard** originalArray, int* arraySize, PlayerCard newPlayer) {
    (*arraySize)++;
    PlayerCard* newArray = new PlayerCard[*arraySize];

    for (int i = 0; i < (*arraySize - 1); i++) {
        newArray[i] = (*originalArray)[i];
    }

    newArray[*arraySize - 1] = newPlayer;

    delete[] *originalArray;

    *originalArray = newArray;
}

void importPlayerScoreCards(std::ifstream& inFile, PlayerCard** scoreCards, int* numCards) {
    char lastName[30];
    PlayerCard newUser;

    while (inFile >> newUser.playerID) {
        inFile >> newUser.playerName;
        inFile >> lastName;

        strncat(newUser.playerName, " ", sizeof(newUser.playerName) - strlen(newUser.playerName) - 1);
        strncat(newUser.playerName, lastName, sizeof(newUser.playerName) - strlen(newUser.playerName) - 1);

        newUser.playerName[sizeof(newUser.playerName) - 1] = '\0';
        inFile >> newUser.totalScore;
        inFile >> newUser.numberOfGames;
        inFile >> newUser.averageScore;

        pushBackPlayerCard(scoreCards, numCards, newUser);
    }
}