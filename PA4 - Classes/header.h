/*
Name: Gabe DiMartino
Class: CPSC122, Fall 2023
Date: October 29, 2023
Programming Assignment: PA4
Description: This cpp contains all of the declerations of functions
*/

#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

const int MAXIMUM_CHARACTERS = 30;

class PlayerCard {
    private:
        char playerName[30];
        int playerID{}, numberOfGames{}, totalScore{};
        double averageScore{};

    public:

        int getPlayerID() const {return playerID;};
        int getNumberOfGames() const {return numberOfGames;};
        int getTotalScore() const {return totalScore;};
        const char* getPlayerName() const {return playerName;};
        double getAverageScore() const {return averageScore;};

        void generatePlayerID(void);
        void generatePlayerID(int);
        void updateAverageScore(void);
        void setTotalScore(int);
        void setNumberOfGames(int);
        void setPlayerName(const char*);        


        PlayerCard(); //Default Constructor
        PlayerCard(std::ifstream&, int idValue); //Constructor with passed file and PID
        PlayerCard(const char*); //Constructor with passed name
        ~PlayerCard();

    private:

        void setAverageScore(double);
        void setPlayerID(int);

};

bool getDartRounds(PlayerCard& player);
void printPlayerScoreCard(const PlayerCard& player);
void initializePlayerScoreCard(PlayerCard** scoreCards, int* numCards);
void importPlayerScoreCards(std::ifstream& inFile, PlayerCard** scoreCards, int* numCards);
bool fileOpen(const char* filename, std::ifstream& inFile);
void pushBackPlayerCard(PlayerCard** originalArray, int* arraySize, PlayerCard newPlayer);
void clearScreen();
    

#endif