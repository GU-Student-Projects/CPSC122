/*
Name: Gabe DiMartino
Class: CPSC122, Fall 2023
Date: November 30, 2023
Programming Assignment: PA6
Description: Header File
I AM ATTEMPTING THE BONUS CHALLENGE
AND OTHER CODE HAS BEEN ADDED
*/

#ifndef HEADER_H
#define HEADER_H

#include <iostream> //need for IO
#include <string> //need for string data type and member functions
#include <cstdlib> //need for random
#include <ctime> //need for random
#include <vector> //need for vector data type
#include <iomanip> //need to format output

#include <chrono>
#include <limits>
#include <thread>
#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

//Global constant to set upper limit on number of playerIds generated
const int MAX_ID_VALUE = 1000;
const int MAX_INVENTORY = 10;

//This struct is used to populate possibleItems. This is it's 
//only purpose. You are not expected to use it as a member 
//variable in your classes
struct InventoryItem
{
	std::string weaponName;
	int damage;
	int defence;
};

//Global CONSTANT variable. You should modify and fill this
//vector with predefined possible weapons for your player
//objects.
const std::vector<InventoryItem> possibleItems{
	{"Lightsaber", 100, 100},
	{"Blaster", 50, 15},
	{"Slugh Thrower", 25 , 0},
	{"Concusion Grenade", 25, 0},
	{"Holocron", 0, 2},
	{"Helmet", 2, 25},
	{"Chestplate", 2, 25},
	{"Boots", 2, 25},
	{"Robes", 0, 15},
	{"Shocker", 10 , 0},
	{"Screwdriver", 2 , 0},
	{"Thermal Detonator", 50 , 0},
	{ "Droid Popper", 5, 0} };

const std::vector<std::string> friendlyFireMessages {
    {"Caution! Friendly fire, watch your aim!"},
    {"Easy there, ally! Check your targets."},
    {"Hold your fire! I'm on your side."},
    {"Watch your shots, comrade! Allies here."},
    {"Mind your aim, warrior! Teammates nearby."},
    {"Beware of friendly fire! Allies in your sights."},
    {"Precision matters! We fight together."},
    {"Identify your targets, soldier! Allies are not foes."},
    {"Friendly fire, not the path to victory."},
    {"Steady, friend! I'm not your adversary."},
    {"Patience, comrade! Save your strikes for enemies."},
    {"Check your targets, ally! We're on the same side."},
    {"Hold your blaster bolts, friend! Allies in the fray."},
    {"Easy on the trigger! Teammates in your line of fire."},
};

void clearScreen();
void clearInputBuffer() ;
void pauseProgram();
void warGamesText(const std::string&, int);

//Class for your inventory
//This should be implemented as one of the following:
//1. A doubly linked list
//2. A stack (linked list)
//3. A queue (linked list)
class PlayerInventory
{
private:
	int inventorySize;

	struct PlayerInventoryNode{
		InventoryItem item;
		PlayerInventoryNode* nextPtr;
	};

	PlayerInventoryNode* head;

public:
	PlayerInventory();
	~PlayerInventory();

	PlayerInventoryNode* getHead(void) const { return head; };
	int getInventorySize() const {return inventorySize;};

	void push(InventoryItem item);
	void pop();
	void displayList(PlayerInventoryNode*) const;
	bool isEmpty();
	bool isFull();
	InventoryItem retrieveItem();

};

//Abstract Base Class
class Player
{
private:

	//static member variable keeping track of the number of players generated
	static int numPlayers;
	//static list of playerIds generated.
	//used to make sure no players have the same id
	static std::vector<int> playerIds;

protected:
	std::string subclass;
	std::string name;
	int playerId;
	int health;
	int experience;
	int alignment;
	std::string turnWeapon;
	int turnDamage;
	int turnHealth;
	bool turnSuccess;
	double defenceSkill;
	double offenceSkill;
	

	double forceSensitivity; //damage multiplier. This should vary depending on class

	//Inventory is the name of your doubly linked list, stack linked list, or queue linked list class
	PlayerInventory playerInventory;

	//mutator/setter for player id
	void setPlayerId(int id) { playerId = id; }

	//used to generate a random stat value between min and max, e.g., 50 and 150
	//used when initializing player stats
	int generateRandomStat(int min, int max) const;

	//checks if an id is already in the playerIds vector.
	static bool playerIdIsInList(int id);

	//convert the enumarated value of Alignment to a string value
	std::string convertAlignment(int alignment) const;

	//generates a UNIQUE player id. player id can be between 1 and MAX_ID_VALUE
	//if number generated is in playerIds, generate again otherwise, add to 
	//playerIds vector (to keep track of id generated) and return value to be 
	//used in initialization
	int generatePlayerId(void) const;

public:
	//Default constructor
	enum Alignment { Neutral, Republic, CIS };

	Player() {
		subclass = "Player";
		name = "";
		playerId = -1;
		health = -1;
		experience = 0;
		forceSensitivity = 1.0;
		alignment = Neutral;
		turnWeapon = "";
		turnHealth = -1;
		turnDamage = 0;
		turnSuccess = false;
		offenceSkill = 1.0;
		defenceSkill = 1.0;
		
		numPlayers++;

		//TODO: initialize PlayerInventory member (fill it with "weapons" from global constant vector)
	}

	//Destructor
	~Player() {
    	numPlayers--;
		playerIds.clear();
	}

	//accessors/getters and mutators/setters
	void setName(std::string newName) { name = newName; }
	std::string getName(void) const { return name; };
	void setHealth(int h) { health = h; }
	int getHealth(void) const { return health; }
	int getPlayerId(void) const { return playerId; }
	void setExperience(int exp) { experience = exp; }
	int getExperience(void) const { return experience; }
	void setAlignment(int newAlign) {alignment = newAlign;}
	int getAlignment(void) const{ return alignment;}

	void setTurnWeapon(std::string weapon) {turnWeapon = weapon;}
	std::string getTurnWeapon(void) const{ return turnWeapon;}
	void setTurnHealth(int h) {turnHealth = h;}
	int getTurnHealth(void) const{ return turnHealth;}
	void setTurnDamage(int d) {turnDamage = d;}
	int getTurnDamage(void) const{ return turnDamage;}
	void setTurnSuccess(bool s) {turnSuccess = s;}
	bool getTurnSuccess(void) const{ return turnSuccess;}
	double getDefenceSkill(void) const { return defenceSkill; }
	void setOffenceSkill(double skill) { offenceSkill = skill; }
	double getOffenceSkill(void) const { return offenceSkill; }

	const PlayerInventory& getInventory() const { return playerInventory; }

	//Pure Virtual Functions
	//initializes a player of given name with randomly allocated stats
	virtual void initializePlayer(std::string newName) = 0;
	virtual void printPlayerClassInfo(void) const = 0;

	//Virtual Functions
	virtual double getForceSensitivity(void) const { return forceSensitivity; }

		virtual void printPlayerInfo(void) final
	{
		std::string skull = "\n    _____\n   /     \\\n  | () () |\n   \\  ^  /\n    |||||\n";
		std::string tombstone = "\n       ,-=-.\n      /  +  \\\n      | ~~~ |\n      |R.I.P|\n      |_____| \n";

		std::string healthValue = this->health > 0 ? std::to_string(this->health) : tombstone; //"~RIP~"
		std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>|PID:" << this->playerId << "|" << std::endl;
		std::cout << ">>" << this->name << "'s info" << std::endl;
		std::cout << "Health: " << healthValue << std::endl;
		std::cout << "Experience: " << this->experience << std::endl;
		std::cout << "---------------------------------" << std::endl;
		std::cout << "Class: " << this->subclass << std::endl;
		printPlayerClassInfo();
		std::cout << "_________________________________" << std::endl;
		std::cout << std::endl;
	}

	//Template Functions
	//prints out the "header" information for each attack turn
	//see example output
	template <class T1, class T2>
	void loopRound(T1& p1, T2& p2, int turn){
		while ((p1.getHealth() > 0) && (p2.getHealth() > 0)) {
		p1.playGame(p1, p2);
		p2.playGame(p2, p1);
		p1.printBattleCard(p1, p2, turn);
		std::cout<<std::endl;
		if (p2.getTurnSuccess()){
			p1.setHealth(p1.getTurnHealth());
		}
		if (p1.getTurnSuccess()){
			p2.setHealth(p2.getTurnHealth());
		}
		turn++;
		}
	}

	template <class T1, class T2>
	void playGame(T1& p1, T2& p2){
		p1.setTurnSuccess(p1.attackPlayerSuccess(p1, p2));
		InventoryItem tempItem  = p1.playerInventory.retrieveItem();
		p1.setTurnWeapon(tempItem.weaponName);

		if (p1.getTurnSuccess()) {
			p1.setTurnDamage(((tempItem.damage * p1.getOffenceSkill()) + tempItem.damage)*p2.getDefenceSkill());
			p2.setTurnHealth(p2.getHealth() - p1.getTurnDamage());
			p1.setExperience(p1.getExperience() + generateRandomStat(1,15));
		}
	}

	template <class T1, class T2>
	static void printBattleCard(const T1& p1, const T2& p2, int turn) 
	{
		std::cout << "|------- Turn " << turn << " -------|" << std::endl;
		std::cout << p1.getName() << "'s Health: " << p1.getHealth() << " - ";
		std::cout << p2.getName() << "'s Health: " << p2.getHealth() << " - " << std::endl;

		// Player 1 attacks Player 2
		if (p1.getTurnSuccess()) {
			std::cout << p1.getName() << " attacks " << p2.getName() << " with a(n) " << p1.getTurnWeapon();
			std::cout << " ...hits for " << p1.getTurnDamage() << "!" << std::endl;
		} else {
			std::cout << p1.getName() << " attacks " << p2.getName() << " with a(n) " << p1.getTurnWeapon();
			std::cout << " ...misses!" << std::endl;
		}

		// Player 2 attacks Player 1
		if (p2.getTurnSuccess()) {
			std::cout << p2.getName() << " attacks " << p1.getName() << " with a(n) " << p2.getTurnWeapon();
			std::cout << " ...hits for " << p2.getTurnDamage() << "!" << std::endl;
		} else {
			std::cout << p2.getName() << " attacks " << p1.getName() << " with a(n) " << p2.getTurnWeapon();
			std::cout << " ...misses!" << std::endl;
		}

		return;
	}


	template <class T1, class T2>
	bool attackPlayerSuccess(const T1& p1, const T2& p2)
	{
		std::string message;
		try {
			if (p1.getAlignment() == p2.getAlignment()) {
				if (p1.getAlignment() == Player::Neutral) {
					message =  p1.getName() + ": Nothing personal mate, just business.";
					warGamesText(message, 50);
					return true;
				} else {
					message = p2.getName() + ": " + friendlyFireMessages[generateRandomStat(0, (friendlyFireMessages.size() - 1))];
					warGamesText(message, 50);
					return false;
				}
			}
			return (generateRandomStat(1, 100) / 100.0 <= p1.getForceSensitivity());
		} catch (...) {
			std::cerr << "An exception occurred during the attackPlayerSuccess function." << std::endl;
			return false;
		}
	}


};

class Jedi : public Player {	

	protected:
		int lightsaberForm = 1;


	public:
	//Getters and Setters for The Jedi Class
	void seLlightsaberForm(int form) { lightsaberForm = form; }
	int getLightsaberForm(void) const { return lightsaberForm; }	

	void initializePlayer(std::string newName);
	void printPlayerClassInfo(void) const;
	void removeInventoryItem();
	void displayInventory() const;
	void addInventoryItem(InventoryItem);

	~Jedi(){}
};

class BountyHunter : public Player {

	protected:
		int weaponType = 1;

	public:
		void setWeaponType(int form) { weaponType = form; }
		int getWeaponType(void) const { return weaponType; }

		void initializePlayer(std::string newName);
		void printPlayerClassInfo() const;
		std::string convertWeapon(int weaponType) const;
		void removeInventoryItem();
		void displayInventory() const;
		void addInventoryItem(InventoryItem tempItem);

		~BountyHunter(){}

};

class CloneTrooper : public BountyHunter {
	public:
		void initializePlayer(std::string newName);
		~CloneTrooper(){}
};

class BattleDroid : public BountyHunter {
	
	public:
	void initializePlayer(std::string newName);
	~BattleDroid(){}
};

class Sith : public Jedi {
	public:
	void initializePlayer(std::string newName);
	~Sith(){}
};

std::string titleScreen();
void fullGameMode();
int mainMenu();
int characterSelection();
void missionSuccess(Player*);
void missionFailed(Player*);

void onderonStreets(Player*);
void cantina(Player*);
void spacePort(Player*);
void capitol(Player*);

#endif