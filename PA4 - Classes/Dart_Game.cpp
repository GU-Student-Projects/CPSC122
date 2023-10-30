/*
Name: Gabe DiMartino
Class: CPSC122, Fall 2023
Date: October 29, 2023
Programming Assignment: PA4
Description: This cpp runs the program
*/

#include "header.h"

int main() {
    const char filename[] = "playercards.txt"; //char array for the file name
    std::ifstream inFile;
    int numCards = 0;
    PlayerCard* scoreCards = nullptr;

    if (!fileOpen(filename, inFile)) {
        std::cerr << "Failed to open file: " << filename << std::endl; //if the file cant open just end the program
        return 1;
    }

    srand(time(nullptr)); //seed the rand
    clearScreen();

    std::cout<<"Welcome to the game of darts!"<<std::endl;
    std::cout<<"It's completely skill-based and not random luck, I promise!"<<std::endl;
    std::cout<<"..."<<std::endl;
    std::cout<<"*wink*"<<std::endl;
    std::cout<<std::endl;
    initializePlayerScoreCard(&scoreCards, &numCards); //get the player data
    importPlayerScoreCards(inFile, &scoreCards, &numCards); //import the player cards
    std::cout<<std::endl;
    printPlayerScoreCard(scoreCards[0]); //print score card
    std::cout<<std::endl;
    while(getDartRounds(scoreCards[0])); //loop until game ends
    std::cout<<std::endl;
    std::cout<<"Here's your final score card!"<<std::endl;

    printPlayerScoreCard(scoreCards[0]);

    std::cout<<std::endl;
    std::cout<<"See how your score compares to previous players:"<<std::endl; //print final results
    for(size_t i = 1; i < sizeof(scoreCards); i++){
        printPlayerScoreCard(scoreCards[i]);
        std::cout << std::endl;
    }

    delete[] scoreCards;

    return 0;
}

