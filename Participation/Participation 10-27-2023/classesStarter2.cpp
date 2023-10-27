/*
    10-27-2023
    CPSC 122
    Classes
*/

#include <iostream>
#include <string>

using namespace std;

// global constants
const int NUM_PLAYERS = 2;

// enums

// structs/classes
class Player
{
public:
    //public attributes/members
    string name;
    //NOTE: haven't tested this out in Linux but addresses warning c26495 https://learn.microsoft.com/en-us/cpp/code-quality/c26495
    // remove {} from the following if it causes compiler errors
    int playerId{};
    int health{};
    //public member functions
    double getPower(void) const;
    void setPower(double);
    Player initializePlayer(int& numPlayers);
    Player* initializePlayer(int* numPlayers);
    Player(string);
    Player(string, int, int, double, int);

    Player()
    {
        name = "Default";
        playerId = 0;
        health = 100;
        power = 0.0;
        secretPowerMultiplier = 42;
    }

    ~Player();

private:
    //private attributes/members
    double power{};
    int secretPowerMultiplier{};
    //private member functions
    
};

void initializePlayers(Player players[], int count, int& numPlayers);

void printPlayerData(const Player& player); // constant reference
void printPlayerData(Player* player);       // via a pointer to a struct

// print an array of Player structs
void printPlayersData(const Player players[], int numPlayers);

// initialize a Player struct


// initialize an array of Player structs


// main.cpp
// #include "header.h"
int main(void)
{
    int numPlayers = 0;
    Player testPlayer;
    Player myPlayer("Bob Smith");
    Player otherPlayer("John Jones", 0, 100, 0.0, 42);
    printPlayerData(myPlayer);
    printPlayerData(otherPlayer);

    Player players[NUM_PLAYERS];

    initializePlayers(players, NUM_PLAYERS, numPlayers);

    printPlayersData(players, numPlayers);

    return 0;
}

// definitions.cpp
// #include "header.h"

/**
 * The function "printPlayerData" prints out the data of a player object.
 *
 * Args:
 *   player (Player): The parameter "player" is of type "Player", which is a user-defined structure or
 * class. It contains the following member variables:
 */
void printPlayerData(const Player& player)
{
    cout << "Player data:" << endl;
    cout << player.name << endl;
    cout << player.playerId << endl;
    cout << player.health << endl;
    cout << player.getPower() << endl;
    cout << endl;
}

/**
 * The function "printPlayerData" prints out the data of a player object.
 *
 * Args:
 *   player (Player): A pointer to a Player object.
 */
void printPlayerData(Player* player)
{
    cout << "Player data:" << endl;
    cout << (*player).name << endl;
    cout << player->playerId << endl;
    cout << player->health << endl;
    cout << (*player).getPower() << endl;
    cout << endl;
}

/**
 * The function "printPlayersData" prints the data of an array of Player objects.
 *
 * Args:
 *   players (Player): An array of Player objects, representing the players' data.
 *   numPlayers (int): The number of players in the array "players".
 */
void printPlayersData(const Player players[], int numPlayers)
{
    for (int i = 0; i < numPlayers; i++)
    {
        printPlayerData(players[i]);
    }
}

/**
 * The function initializes a player object with default values and prompts the user to enter a name
 * for the player.
 *
 * Args:
 *   numPlayers (int): A reference to an integer variable that keeps track of the total number of
 * players.
 *
 * Returns:
 *   a Player object.
 */
Player Player::initializePlayer(int& numPlayers)
{
    Player newPlayer;

    newPlayer.health = 100;
    newPlayer.playerId = ++numPlayers;
    newPlayer.setPower(42.0);

    cout << "Enter a name for this player: ";
    getline(cin, newPlayer.name);

    return newPlayer;
}

/**
 * The function initializes a new player object with default values and prompts the user to enter a
 * name for the player.
 *
 * Args:
 *   numPlayers (int): A pointer to an integer variable that keeps track of the number of players.
 *
 * Returns:
 *   a pointer to a Player object.
 */
Player* Player::initializePlayer(int* numPlayers)
{
    Player* newPlayer = new Player;

    newPlayer->health = 100;
    newPlayer->playerId = ++(*numPlayers);
    newPlayer->setPower(42.0);

    cout << "Enter a name for this player: ";
    getline(cin, newPlayer->name);

    return newPlayer;
}

/**
 * The function initializes an array of Player objects with the specified count and updates the
 * numPlayers variable.
 *
 * Args:
 *   players (Player): An array of Player objects, where each element represents a player in the game.
 *   count (int): The parameter "count" represents the number of players that need to be initialized.
 *   numPlayers (int): The variable "numPlayers" is passed by reference, which means that any changes
 * made to it inside the function will affect the original variable outside the function.
 */
void initializePlayers(Player players[], int count, int& numPlayers)
{
    for (int i = 0; i < count; i++)
    {
        players[i] = players[i].initializePlayer(numPlayers);
    }
}

double Player::getPower(void) const
{
    return power * secretPowerMultiplier;
}

void Player::setPower(double powerValue)
{
    power = powerValue;
}

Player::Player(string nameValue, int playerValue, int healthValue, double powerValue, int secretPowerMultiplierValue)
{
    name = nameValue;
    playerId = playerValue;
    health = healthValue;
    power = powerValue;
    secretPowerMultiplier = secretPowerMultiplierValue;

}

Player::Player(string stringValue)
{
    name = stringValue;
    playerId = 0;
    health = 100;
    power = 0.0;
    secretPowerMultiplier = 42;
}

Player::~Player(){
    
}