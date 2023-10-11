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
    char lastName[MAXIMUM_CHARACTERS];
    PlayerCard newUser;

    while (inFile >> newUser.playerID) {
        inFile >> newUser.playerName;
        inFile >> lastName;

        strncat(newUser.playerName, " ", MAXIMUM_CHARACTERS - strlen(newUser.playerName) - 1);
        strncat(newUser.playerName, lastName, MAXIMUM_CHARACTERS - strlen(newUser.playerName) - 1);

        newUser.playerName[MAXIMUM_CHARACTERS - 1] = '\0';
        inFile >> newUser.totalScore;
        inFile >> newUser.numberOfGames;
        inFile >> newUser.averageScore;

        pushBackPlayerCard(scoreCards, numCards, newUser);
    }
}

void initializePlayerScoreCard(PlayerCard* player) {
    char lastName[MAXIMUM_CHARACTERS];

    player->playerID = std::rand() % 9000 + 1000;
    std::cout << "What is your first and last name? ";
    std::cin >> player->playerName >> lastName;

    int availableSpace = MAXIMUM_CHARACTERS - strlen(player->playerName) - 1;
    if (availableSpace > 0) {
        strncat(player->playerName, " ", availableSpace);
        strncat(player->playerName, lastName, availableSpace);
    }

    player->playerName[MAXIMUM_CHARACTERS- 1] = '\0';

    player->totalScore = 0;
    player->averageScore = 0.0;
    player->numberOfGames = 0;
}

bool getDartRounds(PlayerCard& player) {
    int randomScore = (std::rand() % 3) + 1;
    char select;
    bool validAnswer = false;

    std::cout << "You threw a dart!" << std::endl;

    if (randomScore == 2) {
        int score = (std::rand() % 5) + 1;
        std::cout << "Oof, nice try but you hit a " << score << ". You should try again!" << std::endl;
        player.totalScore += score;
    }
    else if (randomScore == 3) {
        int score = (std::rand() % 5) + 6;
        std::cout << "Nice! You hit a " << score << ". Time to move on, I think." << std::endl;
        player.totalScore += score;
    }
    else {
        std::cout << "Oh man... you missed" << std::endl;
    }

    player.numberOfGames++;

    std::cout << "Keep playing? (y/n): ";
    while (!validAnswer) {
        std::cin >> select;

        if (select == 'y') {
            validAnswer = true;
            return true;
        }
        else if (select == 'n') {
            validAnswer = true;
            player.averageScore = double(player.totalScore)/player.numberOfGames;
            return false;
        }
        else {
            std::cout << "Please select either 'y' or 'n'" << std::endl;
        }
    }
    return false; 
}

void printPlayerScoreCard(const PlayerCard& player){
    std::cout<<"-----------------------|PID:"<<player.playerID<<"|"<<std::endl;
    std::cout<<player.playerName<<"'s Score Card"<<std::endl;
    std::cout<<"---------------------------------"<<std::endl;
    std::cout<<"Games Played: " << player.numberOfGames << std::endl;
    std::cout<<"Running Score: " << player.totalScore << std::endl;
    std::cout<<"Average Score: " << player.averageScore << std::endl;
    std::cout<<"---------------------------------"<<std::endl;
}


