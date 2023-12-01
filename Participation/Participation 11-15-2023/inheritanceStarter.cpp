/*
	11-15-2023
	CPSC 122
	Inheritance
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//class
class Player
{
private:

	//static member variable
	static int numPlayers;

	string name;
	int playerId;
	int health;
	double power;

public:
	//default constructor	
	Player(string newName = "", int newId = -1);

	//copy constructor
	Player(const Player& player);

	//Destructor
	~Player();

	//getters and setters
	void setName(string newName) { name = newName; }
	string getName(void) const { return name; };

	void setHealth(int h) { health = h; }
	int getHealth(void) const { return health; }

	void setPlayerId(int id) { playerId = id; }
	int getPlayerId(void) const { return playerId; }

	void setPower(double pow) { power = pow; }
	double getPower(void) const { return power; }

	//can only be called after object defined
	void printTotalNumberOfPlayers(void) const { cout << "Total numberof Player objects: " << numPlayers << endl; }
	//can be called before object defined
	static void printTotalNumberOfPlayersStatic(void) { cout << "Total numberof Player objects: " << numPlayers << endl; }

	//overloaded to initialize object being referenced
	void initializePlayer(string newName);

	static void initializePlayer(Player& player, string name);

	//operator overloading
	const Player operator=(const Player& player);
};

class Wizard : public Player 
{
public:

void setMana(int man) {mana = man;}
private:
	int mana;
	string type = "Wizard";
};


//static member initialization
//inside the header still but not within our class! we initialize
int Player::numPlayers = 0;

//function prototypes

//print a Player struct
void printPlayerData(const Player& player); //constant reference

//main.cpp
//#include "header.h"
int main(void)
{
	Player p1;

	p1.initializePlayer("Bob Smith");

	printPlayerData(p1);
	
	Wizard w1;
	w1.initializePlayer("Wizzy Kid");
	cout << w1.getHealth() << endl;
	w1.setMana(100);



	return 0;
}

//definitions.cpp
//#include "header.h"

void printPlayerData(const Player& player)
{
	cout << "Player data:" << endl;
	cout << "name - " << player.getName() << endl;
	cout << "playerId - " << player.getPlayerId() << endl;
	cout << "health - " << player.getHealth() << endl;
	cout << "power - " << player.getPower() << endl;
	cout << endl;
}

Player::Player(string newName, int newId)
{
	//cout << "Normal constructor allocating ptr" << endl;

	cout << "Base (Parent) class constructor called" << endl;

	name = newName;
	playerId = newId;
	health = 0;
	power = 0;

	numPlayers++;
}

Player::Player(const Player& player)
{
	cout << "Copy constructor allocating ptr" << endl;
	name = player.name;
	playerId = player.playerId;
	health = player.health;
	power = player.power;
}

Player::~Player()
{
	cout << "Base (Parent) class destructor called" << endl;
	//cleanup any memory dynamically allocated by our class
}

void Player::initializePlayer(string newName)
{
	name = newName;
	health = ((rand() % 100) + 1);
	playerId = ((rand() % 100) + 1);
	power = ((rand() % 100) + 1.0);
}

void Player::initializePlayer(Player& player, string name)
{
	player.name = name;
	//player.setName(name);
	player.setHealth((rand() % 100) + 1);
	player.setPlayerId((rand() % 100) + 1);
	player.setPower((rand() % 100) + 1.0);
}

const Player Player::operator=(const Player& player)
{
	cout << "Calling overloaded assignment operator" << endl;
	this->name = player.name;
	this->playerId = player.playerId;
	this->health = player.health;
	this->power = player.power;
	return *this;
}