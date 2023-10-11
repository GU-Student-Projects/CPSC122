/*
Name: Gabe DiMartino
Class: CPSC122, Fall 2023
Date: October 10, 2023
Programming Assignment: PA3
Description: This cpp runs the program
Bonus: I did the bonus for this assignment from the beginning and rcommented out the vector implementation
*/

#include "Dart_Game.h"

int main() {
    const char filename[] = "playercards.txt"; //char array for the file name
    std::ifstream inFile;
    PlayerCard newPlayer;
    int numCards = 0;
    PlayerCard* scoreCards = nullptr;
    std::vector<PlayerCard> vectorScoreCard;

    if (!fileOpen(filename, inFile)) {
        std::cerr << "Failed to open file: " << filename << std::endl; //if the file cant open just end the program
        return 1;
    }

    srand(time(nullptr)); //seed the rand

    importPlayerScoreCards(inFile, &scoreCards, &numCards, vectorScoreCard); //import the player cards
    clearScreen();
    std::cout<<"Welcome to the game of darts!"<<std::endl;
    std::cout<<"It's completely skill-based and not random luck, I promise!"<<std::endl;
    std::cout<<"..."<<std::endl;
    std::cout<<"*wink*"<<std::endl;
    initializePlayerScoreCard(&newPlayer); //get the player data
    pushBackPlayerCard(&scoreCards, &numCards, newPlayer);
    //vectorScoreCard.push_back(newPlayer);

    printPlayerScoreCard(scoreCards[sizeof(scoreCards)-1]); //print score card
    //printPlayerScoreCard(vectorScoreCard[sizeof(scoreCards)-1]); //print score card vector

    while(getDartRounds(scoreCards[sizeof(scoreCards)-1])); //loop until game ends
    //while(getDartRounds(vectorScoreCard[sizeof(scoreCards)-1])); //loop until game ends vector
    std::cout<<std::endl;
    std::cout<<"Here's your final score card!"<<std::endl;
    printPlayerScoreCard(scoreCards[sizeof(scoreCards)-1]);
    //printPlayerScoreCard(vectorScoreCard[sizeof(scoreCards)-1]);
    std::cout<<std::endl;
    std::cout<<"See how your score compares to previous players:"<<std::endl; //print final results
    for(size_t i = 0; i < sizeof(scoreCards)-1; i++){
        printPlayerScoreCard(scoreCards[i]);
        //printPlayerScoreCard(vectorScoreCard[i]);
        std::cout << std::endl;
    }

    delete[] scoreCards;

    return 0;
}

