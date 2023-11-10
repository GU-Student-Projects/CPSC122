/*
	11-8-2023
	CPSC 122
	more classes - static and overloading
	starting code
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

	int* dynamicInt;

	//default constructor
	Player(string newName = "", int newId = -1);
	Player(const Player &obj);

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

	//other member functions
	static void initializePlayer(Player& player, string name);
	//static member function
	static void printTotalNumberOfPlayers(void);

	//overload
	const Player operator=(const Player& player);
};

//inside the header still
//but not within our class
int Player::numPlayers = 0;

//function prototypes

//print a Player struct
void printPlayerData(const Player& player); //constant reference

//main.cpp
//#include "header.h"
int main(void)
{
	//numPlayers is 0
	Player::printTotalNumberOfPlayers();
	Player p1, p3;
	//numPlayers is 3
	Player::printTotalNumberOfPlayers();

	Player p4, p5;
	//numPlayers is 5
	Player::printTotalNumberOfPlayers();

	srand(9001); //seeding random number generator with a constant value so it's not random every time
	
	Player::initializePlayer(p1, "Bob Smith");

	

	//Player::initializePlayer(p2, "Jane Doe");
	Player p2;
	p2 = p1;
	*p1.dynamicInt = 42;

	printPlayerData(p1);
	cout << "p1 dynamicInt address:" << p1.dynamicInt << endl;
	cout << "p1 dynamicInt value:" << *p1.dynamicInt << endl;
	printPlayerData(p2);
	cout << "p2 dynamicInt address:" << p2.dynamicInt << endl;
	cout << "p2 dynamicInt value:" << *p2.dynamicInt << endl;

	return 0;
}

//definitions.cpp
//#include "header.h"

void printPlayerData(const Player& player)
{
	cout << "Player data:" << endl;
	cout << "name - " << player.getName() << endl;
	cout << "Id - " << player.getPlayerId() << endl;
	cout << "health - " << player.getHealth() << endl;
	cout << "power - " << player.getPower() << endl;
	cout << "dynamicInt - " << *player.dynamicInt << endl;
	cout << endl;
}

//class member functions

Player::Player(string newName, int newId)
{
	cout << "Normal constructor allocating ptr" << endl;

	name = newName;
	playerId = newId;
	health = 0;
	power = 0;

	dynamicInt = new int;
	*dynamicInt = 0;

	numPlayers++;
}

Player::~Player()
{
	//cleanup any memory dynamically allocated by our class
	//delete dynamicInt;
}

void Player::initializePlayer(Player& player, string name)
{
	player.setName(name);
	player.setHealth((rand() % 100) + 1);
	player.setPlayerId((rand() % 100) + 1);
	player.setPower((rand() % 100) + 1.0);
	*player.dynamicInt = rand() % 100 + 1;
}

void Player::printTotalNumberOfPlayers(void)
{
	cout << "Total Number of Players: "
		 << numPlayers << endl;
	return;
}

Player::Player(const Player &obj){
	cout << "Calling the copy instructor" << endl;

	name = obj.name;
	playerId = obj.playerId;
	health = obj.health;
	power = obj.power;

	dynamicInt = new int;
	*dynamicInt = *obj.dynamicInt;

	numPlayers++;

}

const Player Player::operator=(const Player& obj){
	cout << "Calling overload" << endl;
	name = obj.name;
	this->playerId = obj.playerId;
	this->health = obj.health;
	this->power = obj.power;

	this->dynamicInt = new int;
	*(this->dynamicInt) = *obj.dynamicInt;

	return *this;
}

