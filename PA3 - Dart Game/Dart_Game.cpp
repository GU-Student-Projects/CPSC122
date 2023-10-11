/*
Name: Gabe DiMartino
Class: CPSC122, Fall 2023
Date: October 10, 2023
Programming Assignment: PA3
Description: This cpp runs the program
*/

#include "Dart_Game.h"

int main(){
    const char filename[] = "playercards.txt";
    std::ifstream inFile;

    if (!fileOpen(filename, inFile)) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return 1;
    }

    int numCards = 0;
    PlayerCard* scoreCards = nullptr;

    srand(time(nullptr));

    importPlayerScoreCards(inFile, &scoreCards, &numCards);
    std::cout << scoreCards[3].playerID << std::endl;

    delete[] scoreCards;

    return 0;
}

