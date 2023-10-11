/*
Name: Gabe DiMartino
Class: CPSC122, Fall 2023
Date: October 10, 2023
Programming Assignment: PA3
Description: This cpp contains all of the declerations of functions
*/

#ifndef DART_GAME_H_INCLUDED
#define DART_GAME_H_INCLUDED

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

struct PlayerCard {
    char playerName[30];
    int playerID, numberOfGames, totalScore;
    double averageScore;
};

const int MAXIMUM_CHARACTERS = 30;

void clearScreen();
bool fileOpen(const char* filename, std::ifstream& inFile);
int* pushBackInteger(int* originalArray, int* arraySize, int newValue );
void pushBackPlayerCard(PlayerCard** originalArray, int* arraySize, PlayerCard newPlayer);
void importPlayerScoreCards(std::ifstream& inFile, PlayerCard** scoreCards, int* numCards);
void initializePlayerScoreCard(PlayerCard* player);
bool getDartRounds(PlayerCard& player);
void printPlayerScoreCard(const PlayerCard& player);


#endif