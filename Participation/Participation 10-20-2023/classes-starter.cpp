/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 20 Classes
 Notes:	No questions
*/

#include <iostream>
#include <string>

using namespace std;

// global constants
const int STRING_SIZE = 30;

// enums
// see Gaddis for a refresher
// enum Month { JAN = 1, FEB };
/* The `enum Month` is defining a set of named constants for the months of the year. Each constant is
assigned a value starting from 1 for `JAN` and incrementing by 1 for each subsequent month. This
allows you to use these constants instead of hardcoding the month values in your code, making it
more readable and maintainable. */
enum Month
{
    JAN = 1,
    FEB,
    MAR,
    APR,
    MAY,
    JUN,
    JUL,
    AUG,
    SEP,
    OCT,
    NOV,
    DEC
};
/* The `enum class ErrorTypes` is defining an enumeration with two named constants: `RangeError` and
`TypeMismatchError`. By using the `enum class` syntax, the enumeration is scoped to the `ErrorTypes`
class, meaning that the constants can only be accessed using the class name followed by the scope
resolution operator (`::`). This helps to prevent naming conflicts and makes the code more readable
and maintainable. */
enum class ErrorTypes
{
    RangeError,
    TypeMismatchError
};

// structs
class Player
{ public:

    Player() = default;

    string name;
    int playerId;
    int health;
    double getPower(void) const;
    void setPower(double);
    Player *initializePlayer(int *numPlayers);
private:
    double power;
    int secretNumber;
};

// function prototypes

// print a Player struct
// void printPlayerData(Player player); //by value
void printPlayerData(const Player &player); // constant reference
void printPlayerData(Player *player);       // via a pointer to a struct

// print an array of Player structs
void printPlayersData(const Player players[], int numPlayers);

// initialize a Player struct
Player initializePlayer(int &numPlayers);
Player *initializePlayer(int *numPlayers);

// initialize an array of Player structs
void initializePlayers(Player players[], int count, int &numPlayers);

// main.cpp
// #include "header.h"
int main(void)
{
    string myString = "hello";
    myString.size();

    int numPlayers = 0;
    int *myPtr = nullptr;
    /*Player p1 = initializePlayer(numPlayers);
    Player* p2Ptr = initializePlayer(&numPlayers);*/
    Player p3;

    Player players[3];

    initializePlayers(players, 3, numPlayers);

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
void printPlayerData(const Player &player)
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
void printPlayerData(Player *player)
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
Player initializePlayer(int &numPlayers)
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
Player *Player::initializePlayer(int *numPlayers)
{
    Player *newPlayer = new Player;

    newPlayer->health = 100;
    newPlayer->playerId = ++(*numPlayers);
    newPlayer->power=42.0;

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
void initializePlayers(Player players[], int count, int &numPlayers)
{
    for (int i = 0; i < count; i++)
    {
        players[i] = initializePlayer(numPlayers);
    }
}

double Player::getPower(void) const
{
    double realPower = power * secretNumber;
    return realPower;
}

void Player::setPower(double value)
{
    power = value;
}