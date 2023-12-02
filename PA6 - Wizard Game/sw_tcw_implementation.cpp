/*
Name: Gabe DiMartino
Class: CPSC122, Fall 2023
Date: November 30, 2023
Programming Assignment: PA6
Description: implementation
I AM ATTEMPTING THE BONUS CHALLENGE
AND OTHER CODE HAS BEEN ADDED
*/

#include "header.h"

int Player::numPlayers = 0;
std::vector<int> Player::playerIds;

     /*************************************************************
    * Function: clearScreen ()
    * Date Created: 9/2/23
    * Date Last Modified: 9/2/23
    * Description: Uses an if statement to determine what OS is uesed
    * then runs the system command to clear the terminal
    * Input parameters: System OS
    * Returns: Clear Screen
    * Pre: Correct library
    * Post: Clear Screen
    *************************************************************/

void clearScreen(){ //function to clear terminal
#ifdef _WIN32 //If OS is WIN32 run cls else use clear
    system("cls");
#else
    system("clear");
#endif
}

int Player::generatePlayerId() const {
    int newID;
    do {
        newID = generateRandomStat(1, MAX_ID_VALUE);
    } while (playerIdIsInList(newID));

    playerIds.push_back(newID);
    return newID;
}


bool Player::playerIdIsInList(int id) {
    for (int playerId : playerIds) {
        if (playerId == id) {
            return true;
        }
    }
    return false;
}


int Player::generateRandomStat(int min, int max) const {
    return min + rand() % (max - min + 1);
}

std::string Player::convertAlignment(int alignment) const{
	if (alignment == Republic){
		return "The Galactic Republic";
	} else if (alignment == CIS) {
		return "Confederacy of Independent Systems";
	} else {
		return "The Highest Bidder";
	}
}


PlayerInventory::PlayerInventory(){
	head = nullptr;
	inventorySize = 0;
}

PlayerInventory::~PlayerInventory() {
    while (!isEmpty()) {
        pop();
    }
}

void PlayerInventory::push(InventoryItem tempItem){
	PlayerInventoryNode* tempNode = new PlayerInventoryNode;

	tempNode->item = tempItem;
	tempNode->nextPtr = head;
	head = tempNode;
	inventorySize++;
}

void PlayerInventory::pop() {
    if (isEmpty()) {
        return;
    }

    PlayerInventoryNode* helperNode = head->nextPtr;
    delete head;
    head = helperNode;

    if (head == nullptr) {
        inventorySize = 0;
    } else {
        inventorySize--;
    }
}


bool PlayerInventory::isEmpty(){
	return head == nullptr ? true : false;
}

bool PlayerInventory::isFull(){
	return inventorySize == MAX_INVENTORY ? true : false;
}

void PlayerInventory::displayList(PlayerInventoryNode* tempNode) const {
    if (tempNode == nullptr) { 
        return; 
    }

    std::cout << "Weapon: " << tempNode->item.weaponName;
    std::cout << " - Damage: " << tempNode->item.damage;
    std::cout << " Defence: " << tempNode->item.defence << std::endl;
    displayList(tempNode->nextPtr);
}

InventoryItem PlayerInventory::retrieveItem(){
    PlayerInventoryNode* helperNode = head;
    if (isEmpty()) {
        return {"Empty", 0, 0};
    }

    for(int i = 0; i < std::rand() % inventorySize; i++){
        helperNode = helperNode->nextPtr;
    }
    
    return helperNode->item;
}


void Jedi::initializePlayer(std::string newName) {
    subclass = "Jedi";
    name = newName;
    health = 100;
    playerId = generatePlayerId();
    alignment = Republic;

    lightsaberForm = generateRandomStat(1, 3);
    forceSensitivity = 0.01 * generateRandomStat(60, 100); // Accuracy

    defenceSkill = 0.01 * generateRandomStat(10, 60); // Defence Multiplier
    offenceSkill = 0.01 * generateRandomStat(10, 60); // Damage Multiplier

    if (forceSensitivity > 0.8) {
        if (lightsaberForm == 1) {
            defenceSkill = 0.01 * generateRandomStat(60, 100);
            offenceSkill = 0.01 * generateRandomStat(60, 100);
        } else if (lightsaberForm == 2) {
            offenceSkill = 0.01 * generateRandomStat(60, 100);
        } else if (lightsaberForm == 3) {
            defenceSkill = 0.01 * generateRandomStat(60, 100);
        }
    }

    // Main character adjustments
    if (name == "Anakin") {
        // Main Character Plot Armour
        forceSensitivity = 1.0;
        defenceSkill = 1.0;
        offenceSkill = 1.0;
        lightsaberForm = 5;
        health = 1000;
    }

    while(!playerInventory.isFull()){
        playerInventory.push(possibleItems[generateRandomStat(0,(possibleItems.size()-1))]);
    }

}


void Jedi::printPlayerClassInfo() const {
    std::cout << "Force Sensitivity: " << this->forceSensitivity << std::endl;
    std::cout << "Loyalty: " << convertAlignment(this->alignment) << std::endl;
    std::cout << "Lightsaber Form " << this->lightsaberForm << std::endl;
    std::cout << "Defence Skill " << this->defenceSkill << std::endl;
    std::cout << "Offence Skill " << this->offenceSkill << std::endl;

    if (this->name == "Anakin") {
        std::cout << "Specialty: The Chosen One" << std::endl;
    }
}

void Jedi::displayInventory() const{
    playerInventory.displayList(playerInventory.getHead());
    std::cout<< "Size: "<< playerInventory.getInventorySize() << std::endl;
}

void Jedi::removeInventoryItem() {
    playerInventory.pop();
}

void Jedi::addInventoryItem(InventoryItem tempItem) {
    playerInventory.push(tempItem);
}



void Sith::initializePlayer(std::string newName) {
    subclass = "Sith";
    name = newName;
    health = 100;
    playerId = generatePlayerId();
    alignment = CIS;

    lightsaberForm = generateRandomStat(1, 3);
    forceSensitivity = 0.01 * generateRandomStat(60, 100); // Accuracy

    defenceSkill = 0.01 * generateRandomStat(10, 60); // Defence Multiplier
    offenceSkill = 0.01 * generateRandomStat(10, 60); // Damage Multiplier

    if (forceSensitivity > 0.8) {
        if (lightsaberForm == 1) {
            defenceSkill = 0.01 * generateRandomStat(60, 100);
            offenceSkill = 0.01 * generateRandomStat(60, 100);
        } else if (lightsaberForm == 2) {
            offenceSkill = 0.01 * generateRandomStat(60, 100);
        } else if (lightsaberForm == 3) {
            defenceSkill = 0.01 * generateRandomStat(60, 100);
        }
    }

    while(!playerInventory.isFull()){
        playerInventory.push(possibleItems[generateRandomStat(0,(possibleItems.size()-1))]);
    }

}



void BountyHunter::initializePlayer(std::string newName) {
    subclass = "Bounty Hunter";
    name = newName;
    health = 100;
    playerId = generatePlayerId();
    alignment = Neutral;

    weaponType = generateRandomStat(1, 3);
    forceSensitivity = 0.01 * generateRandomStat(10, 60); // Accuracy

    defenceSkill = 0.01 * generateRandomStat(10, 60); // Defence Multiplier
    offenceSkill = 0.01 * generateRandomStat(10, 60); // Damage Multiplier

    if (forceSensitivity > 0.8) {
        if (weaponType == 1) {
            defenceSkill = 0.01 * generateRandomStat(60, 100);
            offenceSkill = 0.01 * generateRandomStat(60, 100);
        } else if (weaponType == 2) {
            offenceSkill = 0.01 * generateRandomStat(60, 100);
        } else if (weaponType == 3) {
            defenceSkill = 0.01 * generateRandomStat(60, 100);
        }
    }

    while(!playerInventory.isFull()){
        playerInventory.push(possibleItems[generateRandomStat(0,(possibleItems.size()-1))]);
    }

}

std::string BountyHunter::convertWeapon(int weaponType) const {
    if (weaponType == 1){
		return "Heavy Rifle Blaster";
	} else if (weaponType == 2) {
		return "Blaster Pistol";
	} else {
		return "Ion Blaster";
	}
}

void BountyHunter::printPlayerClassInfo() const {
    std::cout << "Accuracy: " << this->forceSensitivity << std::endl;
    std::cout << "Loyalty: " << convertAlignment(this->alignment) << std::endl;
    std::cout << "Weapon Type: " << convertWeapon(this->weaponType) << std::endl;
    std::cout << "Defence Skill: " << this->defenceSkill << std::endl;
    std::cout << "Offence Skill: " << this->offenceSkill << std::endl;
}

void BountyHunter::removeInventoryItem() {
    playerInventory.pop();
}

void BountyHunter::addInventoryItem(InventoryItem tempItem) {
    playerInventory.push(tempItem);
}

void BountyHunter::displayInventory() const{
    playerInventory.displayList(playerInventory.getHead());
    std::cout<< "Size: "<< playerInventory.getInventorySize() << std::endl;
}

void CloneTrooper::initializePlayer(std::string newName) {
    subclass = "Clone Trooper";
    name = newName;
    health = 100;
    playerId = generatePlayerId();
    alignment = Republic;

    weaponType = generateRandomStat(1, 3);
    forceSensitivity = 0.01 * generateRandomStat(10, 60); // Accuracy

    defenceSkill = 0.01 * generateRandomStat(10, 60); // Defence Multiplier
    offenceSkill = 0.01 * generateRandomStat(10, 60); // Damage Multiplier

    if (forceSensitivity > 0.8) {
        if (weaponType == 1) {
            defenceSkill = 0.01 * generateRandomStat(60, 100);
            offenceSkill = 0.01 * generateRandomStat(60, 100);
        } else if (weaponType == 2) {
            offenceSkill = 0.01 * generateRandomStat(60, 100);
        } else if (weaponType == 3) {
            defenceSkill = 0.01 * generateRandomStat(60, 100);
        }
    }

    while(!playerInventory.isFull()){
        playerInventory.push(possibleItems[generateRandomStat(0,(possibleItems.size()-1))]);
    }

}

void BattleDroid::initializePlayer(std::string newName) {
    subclass = "Battle Droid";
    name = newName;
    health = 100;
    playerId = generatePlayerId();
    alignment = CIS;

    weaponType = generateRandomStat(1, 3);
    forceSensitivity = 0.01 * generateRandomStat(10, 60); // Accuracy

    defenceSkill = 0.01 * generateRandomStat(10, 60); // Defence Multiplier
    offenceSkill = 0.01 * generateRandomStat(10, 60); // Damage Multiplier

    if (forceSensitivity > 0.8) {
        if (weaponType == 1) {
            defenceSkill = 0.01 * generateRandomStat(60, 100);
            offenceSkill = 0.01 * generateRandomStat(60, 100);
        } else if (weaponType == 2) {
            offenceSkill = 0.01 * generateRandomStat(60, 100);
        } else if (weaponType == 3) {
            defenceSkill = 0.01 * generateRandomStat(60, 100);
        }
    }

    while(!playerInventory.isFull()){
        playerInventory.push(possibleItems[generateRandomStat(0,(possibleItems.size()-1))]);
    }

}

std::string titleScreen(){
std::string title; 

title =  "    /$$$$$$   /$$                                /$$      /$$                                                                                  \n";
title += "    /$$__  $$ | $$                              | $$  /$ | $$                                                                                 \n";   
title += "   | $$  \\__/$$$$$$    /$$$$$$   /$$$$$$        | $$ /$$$| $$  /$$$$$$   /$$$$$$   /$$$$$$$ /$$                                                \n";
title += "   |  $$$$$$|_  $$_/   |____  $$ /$$__  $$      | $$/$$ $$ $$ |____  $$ /$$__  $$ /$$_____/|__/                                               \n";
title += "    \\____  $$ | $$      /$$$$$$$| $$  \\__/      | $$$$_  $$$$  /$$$$$$$| $$  \\__/|  $$$$$$                                                   \n";
title += "    /$$  \\ $$ | $$ /$$ /$$__  $$| $$            | $$$/ \\  $$$ /$$__  $$| $$       \\____  $$ /$$                                               \n";
title += "   |  $$$$$$/ |  $$$$/|  $$$$$$$| $$            | $$/   \\  $$|  $$$$$$$| $$       /$$$$$$$/|__/                                               \n";
title += "    \\______/   \\___/   \\_______/|__/            |__/     \\_/ \\_______/|__/      |_______/                                                    \n\n";
title += "    /$$$$$$$$ /$$                        /$$$$$$  /$$                                     /$$      /$$                                        \n";
title += "   |__  $$__/| $$                       /$$__  $$| $$                                    | $$  /$ | $$                                        \n";
title += "      | $$   | $$$$$$$   /$$$$$$       | $$  \\__/| $$  /$$$$$$  /$$$$$$$   /$$$$$$       | $$ /$$$| $$  /$$$$$$   /$$$$$$   /$$$$$$$          \n";
title += "      | $$   | $$__  $$ /$$__  $$      | $$      | $$ /$$__  $$| $$__  $$ /$$__  $$      | $$/$$ $$ $$ |____  $$ /$$__  $$ /$$_____/          \n";
title += "      | $$   | $$  \\ $$| $$$$$$$$      | $$      | $$| $$  \\ $$| $$  \\ $$| $$$$$$$$      | $$$$_  $$$$  /$$$$$$$| $$  \\__/|  $$$$$$           \n";
title += "      | $$   | $$  | $$| $$_____/      | $$    $$| $$| $$  | $$| $$  | $$| $$_____/      | $$$/ \\  $$$ /$$__  $$| $$       \\____  $$          \n";
title += "      | $$   | $$  | $$|  $$$$$$$      |  $$$$$$/| $$|  $$$$$$/| $$  | $$|  $$$$$$$      | $$/   \\  $$|  $$$$$$$| $$       /$$$$$$$/          \n";
title += "      |__/   |__/  |__/ \\_______/       \\______/ |__/ \\______/ |__/  |__/ \\_______/      |__/     \\__/ \\_______/|__/      |_______/           \n\n";
title += "     /$$$$$$        /$$$$$$$$                                /$$                     /$$        /$$$$$$                                       \n";
title += "    /$$__  $$      |__  $$__/                               |__/                    | $$       /$$__  $$                                      \n";
title += "   | $$  \\ $$         | $$  /$$$$$$   /$$$$$$  /$$$$$$/$$$$  /$$ /$$$$$$$   /$$$$$$ | $$      | $$  \\__/  /$$$$$$  /$$$$$$/$$$$   /$$$$$$     \n";
title += "   | $$$$$$$$         | $$ /$$__  $$ /$$__  $$| $$_  $$_  $$| $$| $$__  $$ |____  $$| $$      | $$ /$$$$ |____  $$| $$_  $$_  $$ /$$__  $$    \n";
title += "   | $$__  $$         | $$| $$$$$$$$| $$  \\__/| $$ \\ $$ \\ $$| $$| $$  \\ $$  /$$$$$$$| $$      | $$|_  $$  /$$$$$$$| $$ \\ $$ \\ $$| $$$$$$$$    \n";
title += "   | $$  | $$         | $$| $$_____/| $$      | $$ | $$ | $$| $$| $$  | $$ /$$__  $$| $$      | $$  \\ $$ /$$__  $$| $$ | $$ | $$| $$_____/    \n";
title += "   | $$  | $$         | $$|  $$$$$$$| $$      | $$ | $$ | $$| $$| $$  | $$|  $$$$$$$| $$      |  $$$$$$/|  $$$$$$$| $$ | $$ | $$|  $$$$$$$    \n";
title += "   |__/  |__/         |__/ \\_______/|__/      |__/ |__/ |__/|__/|__/  |__/ \\_______/|__/       \\______/ \\_______/|__/ |__/ |__/ \\_______/    \n";
                                                                                                                                         
return title;
}






void warGamesText(const std::string& text, int delayMS = 50) { //function to print characters one at a time
    for (char c : text) {
        std::cout << std::fixed << std::setprecision(2) << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMS));
    }
    std::cout << std::endl;
}

int mainMenu() {
    int choice;

    std::string menu = "|----------- Main Menu -----------|\n"
                       "  1. Programming Assignment Demo\n"
                       "  2. Full Game Mode\n"
                       "  3. Exit Game\n";

    warGamesText(menu, 1);

    while (true) {
        std::cout << "Select 1, 2, or 3: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInputBuffer(); // Clear the input buffer to prevent an infinite loop
            continue;
        }

        switch (choice) {
            case 1:
                warGamesText("Entering Demo Mode", 10);
                std::this_thread::sleep_for(std::chrono::seconds(3));
                break;
            case 2:
                warGamesText("Entering Full Mode", 10);
                std::this_thread::sleep_for(std::chrono::seconds(3));
                break;
            case 3:
                warGamesText("Exiting the Game", 10);
                std::this_thread::sleep_for(std::chrono::seconds(3));
                break;
            default:
                std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
                continue;
        }

        break; // Exit the loop if a valid choice is made
    }

    return choice;
}

/*
===============================================================================

WARING: The contents below are for the Full Game Mode. The code can be safely
        disregarded during the grading process as it does not influence the
        programing assignment. As the grader PLEASE feel free to look at my
        game design and play it, but it does not influence the workings of PA6

===============================================================================
*/

int characterSelection(){
    int choice;

    std::string menu = "\n|----- Character Selection -----|\n"
                       "      1. Jedi Knight\n"
                       "      2. Clone Trooper\n"
                       "      3. Battle Droid\n"
                       "      4. Sith Lord\n"
                       "      5. Bounty Hunter\n"
                       "      6. Quit the Game\n\n";

    warGamesText(menu, 1);

    while (true) {
        std::cout << "Selected a Character: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                std::cout<<std::endl;
                warGamesText("Luminous beings are we, not this crude matter.", 10);
                std::this_thread::sleep_for(std::chrono::seconds(3));
                break;
            case 2:
                std::cout<<std::endl;
                warGamesText("Us Clones were made for war.", 10);
                std::this_thread::sleep_for(std::chrono::seconds(3));
                break;
            case 3:
                std::cout<<std::endl;
                warGamesText("Roger, Roger.", 10);
                std::this_thread::sleep_for(std::chrono::seconds(3));
                break;
            case 4:
                std::cout<<std::endl;
                warGamesText("The Darkside of the force is a pathway to many abilities some consider to be unnatural.", 10);
                std::this_thread::sleep_for(std::chrono::seconds(3));
                break;
            case 5:
                std::cout<<std::endl;
                warGamesText("I can take you in warm, or I can take you in cold. You're choice.", 10);
                std::this_thread::sleep_for(std::chrono::seconds(3));
                break;
            case 6:
                std::cout<<std::endl;
                warGamesText("Exiting the Game", 10);
                std::this_thread::sleep_for(std::chrono::seconds(3));
                break;
            default:

                std::cout << std::endl << "Invalid choice. \n";
                continue;
        }

        break;
    }

    return choice;
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void pauseProgram() {
    std::cout << "Press enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void missionSuccess(Player* player){
    std::this_thread::sleep_for(std::chrono::seconds(3));
    clearScreen();
    warGamesText("MISSION SUCCESS", 50);
    warGamesText("\n▇▇▇▇▇▇▇▇▇▇\n",100);
    warGamesText("True Jedi!", 50);
    std::cout << std::endl;
    player->printPlayerInfo();
    pauseProgram();
}

void missionFailed(Player* player){
    warGamesText("MISSION FAILED", 50);
    player->printPlayerInfo();
    warGamesText("RESTARTING MISSION...", 50);
    pauseProgram();
    clearScreen();
    warGamesText("MISSION ONE ... ESCAPE FROM ONDERON", 50);
    std::cout << "You wake up dazed and confused in the streets of Onderon.\n\n";
}

void fullGameMode() {
    int choice;
    std::string name;
    Player* player;

    clearScreen();

    warGamesText("SELECT YOUR CHARACTER", 50);
    std::cout << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\nEnter your name: ";
    std::getline(std::cin, name);

    choice = characterSelection();


    if (choice == 1) {
        Jedi* jediPlayer = new Jedi;
        player = jediPlayer;
        jediPlayer->initializePlayer(name);
        jediPlayer->removeInventoryItem();
        jediPlayer->addInventoryItem(possibleItems[0]);
    } else if (choice == 2) {
        CloneTrooper* clonePlayer = new CloneTrooper;
        player = clonePlayer;
        clonePlayer->initializePlayer(name);
        clonePlayer->removeInventoryItem();
        clonePlayer->addInventoryItem(possibleItems[1]);
    } else if (choice == 3) {
        BattleDroid* droidPlayer = new BattleDroid;
        player = droidPlayer;
        droidPlayer->initializePlayer(name);
        droidPlayer->removeInventoryItem();
        droidPlayer->addInventoryItem(possibleItems[1]);
    } else if (choice == 4) {
        Sith* sithPlayer = new Sith;
        player = sithPlayer;
        sithPlayer->initializePlayer(name);
        sithPlayer->removeInventoryItem();
        sithPlayer->addInventoryItem(possibleItems[0]);
    } else if (choice == 5){
        BountyHunter* bountyHunterPlayer = new BountyHunter;
        player = bountyHunterPlayer;
        bountyHunterPlayer->initializePlayer(name);
        bountyHunterPlayer->removeInventoryItem();
        bountyHunterPlayer->addInventoryItem(possibleItems[1]);
    } else {
        return;
    }

    player->printPlayerInfo();
    pauseProgram();
    clearScreen();
    warGamesText("MISSION ONE ... ESCAPE FROM ONDERON", 50);
    warGamesText("You wake up dazed and confused in the streets of Onderon.",50);
    onderonStreets(player);
}

void onderonStreets(Player* player){
    int choice;
    bool invalidInput;
    std::cout << "\nYou stand in the streets of Onderon. Choose your next move:\n";
    std::cout << "1. Enter the Cantina\n";
    std::cout << "2. Head to the Space Port\n";
    std::cout << "3. Approach the Capitol\n";
    std::cout << "4. Quit the mission\n";
    
    do {
        invalidInput = false;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                cantina(player);
                return;
            case 2:
                spacePort(player);
                return;
            case 3:
                capitol(player);
                return;
            case 4:
                warGamesText("\nMission aborted. May the Force be with you!\n", 50);
                return;
            default:
                std::cout << "Invalid choice. Try again.\n";
                invalidInput = true;
                clearInputBuffer();
        }

    } while (choice != 4 && invalidInput);
}


void cantina(Player* player) {
    BountyHunter mando;
    mando.initializePlayer("Boba Fett");
    std::cout << std::endl;
    int choice;
    bool invalidInput;

    warGamesText("You enter the bustling cantina. Alien creatures and smugglers fill the room.", 50);
    warGamesText("You spot a group of shady-looking individuals in the corner.", 50);
    std::cout << "1. Approach the group\n";
    std::cout << "2. Find a quiet corner to observe\n";
    std::cout << "3. Leave the cantina\n";

    do {
        invalidInput = false;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (player->getAlignment() == mando.getAlignment()) {
                    warGamesText("Boba Fett: You've got a lot of nerve coming here after the last job we did back on Corelia. Time to pay up.", 50);
                } else {
                    warGamesText("Boba Fett: Your kind isn't allowed in here. And lucky for us... we can't let you leave either.", 50);
                }

                std::this_thread::sleep_for(std::chrono::seconds(1));
                player->loopRound((*player), mando, 1);

                if (player->getHealth() <= 0) {
                    missionFailed(player);
                    onderonStreets(player);
                } else {
                    if (player->getAlignment() == mando.getAlignment()) {
                        warGamesText("Boba Fett: you put up one hell of a fight, consider our little debt paid. Now get out of here!", 50);
                        pauseProgram();
                        onderonStreets(player);
                    } else {
                        warGamesText("Boba Fett: Watch your back, I'll be back for you.", 50);
                        pauseProgram();
                        onderonStreets(player);
                    }
                }
                break;

            case 2:
                warGamesText("You find a quiet corner and observe the surroundings.\n", 50);
                warGamesText("Boba Fett: Now, what is a person like you be doing in a place like this?", 50);

                if (player->getAlignment() == mando.getAlignment()) {
                    warGamesText("Boba Fett: Seems like you're collecting on old debts. I'll give you a ride. But after this, we're even.", 50);
                    missionSuccess(player);
                    clearScreen();
                } else {
                    warGamesText("Boba Fett: Watch your back, I'll be back for you.", 50);
                    pauseProgram();
                    onderonStreets(player);
                }
                break;

            case 3:
                warGamesText("You decide to leave the cantina and return to the streets.\n", 50);
                onderonStreets(player);
                break;

            default:
                std::cout << "Invalid choice. You hesitate and attract attention.\n";
                invalidInput = true;
                clearInputBuffer();
        }
    } while (choice >= 4 || invalidInput);
}


void spacePort(Player* player) {
    CloneTrooper arcTrooper;
    arcTrooper.initializePlayer("CT-5555");  
    int choice;  
    bool invalidInput;

    warGamesText("\nYou arrive at the busy space port. Galactic Republic clone troopers patrol the area.", 50);
    warGamesText("\nThe clone troopers approach you for identification.",50);
    std::cout << "1. Cooperate and show identification\n";
    std::cout << "2. Try to evade and run\n";
    std::cout << "3. Attempt to bluff your way through\n";
    

    do {
    invalidInput = false;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    std::cout << std::endl;
    switch (choice) {
        case 1:
            if (player->getAlignment() == arcTrooper.getAlignment()){
                warGamesText("CT-5555: It's good to see you in one piece commander, hurry up and get on board so we can leave this aweful system.",50);
                missionSuccess(player);
                clearScreen();
            } else {
                warGamesText("CT-5555: Thought you could get passed me huh?", 50);
                std::this_thread::sleep_for(std::chrono::seconds(1));
                player->loopRound((*player),arcTrooper,1);
                std::this_thread::sleep_for(std::chrono::seconds(3));
                if (player->getHealth() <= 0) {
                    missionFailed(player);
                    onderonStreets(player);
                } else {
                    warGamesText("\nCT-5555: The mission, the nightmares, they're finally... over.", 50);
                    onderonStreets(player);                
                }
            }

            break;
        case 2:
            warGamesText("You attempt to run, but the clone troopers quickly catch up.\n",50);
            warGamesText("CT-5555: You can't get away that easily!",50);
            if (!(player->attackPlayerSuccess((*player), arcTrooper))){
                warGamesText("CT-5555: My apologies commander, I did not recognize you.", 50);
                onderonStreets(player);
                break;
            }

            player->loopRound((*player),arcTrooper,1);
            std::this_thread::sleep_for(std::chrono::seconds(3));
            if (player->getHealth() <= 0) {
                missionFailed(player);
                onderonStreets(player);
            } else {
                warGamesText("\nCT-5555: The mission, the nightmares, they're finally... over.", 50);
                onderonStreets(player);                
            }
            break;
        case 3:
            warGamesText("You try to bluff your way through, but the clone troopers are suspicious.\n\n",50);
            warGamesText("CT-5555: You're an odd fellow arent ya. If I wasn't in such a rush I'd almost find this suspicious. On your way. ",50); 
            onderonStreets(player);
            break;
        default:
            std::cout << "Invalid choice. The clone troopers become more alert.\n";
            invalidInput = true;
            clearInputBuffer();
    }
    } while (choice >= 4 || invalidInput);
}

void capitol(Player* player) {
    BattleDroid b1;
    b1.initializePlayer("B1-268");
    int choice;
    bool invalidInput;

    warGamesText("\nYou cautiously approach the imposing capitol building. Seperatist forces are on high alert.", 50);
    warGamesText("Sepratist guards block your path.\n",50);
    std::cout << "1. Attempt to sneak past them\n";
    std::cout << "2. Confront the guards head-on\n";
    std::cout << "3. Look for an alternate route\n";
    
    do {
    invalidInput = false;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    switch (choice) {
        case 1:
            warGamesText("B1-268: Please halt and identify yourself.",50);
            if (!(player->attackPlayerSuccess((*player), b1))){
                warGamesText("B1-268: Thank you, and welcome to Onderon, Please speak with our other guards before meeting with Count Dooku.", 50);
                std::this_thread::sleep_for(std::chrono::seconds(3));
                capitol(player);
            } else  {
                warGamesText("B1-268: You are not authorized to be in this here, please remain calm as you are transported to detention cell 2187", 50);
                std::this_thread::sleep_for(std::chrono::seconds(1));
                player->loopRound((*player),b1,1);
                std::this_thread::sleep_for(std::chrono::seconds(3));
                if (player->getHealth() <= 0) {
                    missionFailed(player);
                    onderonStreets(player);
                } else {
                warGamesText("\nB1-268: Roger ... roger", 50);
                onderonStreets(player);  
                }
            }
            break;
        case 2:
            warGamesText("You confront the guards, drawing attention to yourself.",50);
            warGamesText("B1-268: Please halt and identify yourself troublemaker.",50);
            if (!(player->attackPlayerSuccess((*player), b1))){
                warGamesText("B1-268: Thank you, and welcome to Onderon. Right this way.", 50);
                missionSuccess(player);
                clearScreen();
            } else  {
                warGamesText("B1-268: You are not authorized to be in this here, please remain calm as you are transported to detention cell 2187", 50);
                std::this_thread::sleep_for(std::chrono::seconds(1));
                player->loopRound((*player),b1,1);
                std::this_thread::sleep_for(std::chrono::seconds(3));
                if (player->getHealth() <= 0) {
                    missionFailed(player);
                    onderonStreets(player);
                } else {
                warGamesText("\nB1-268: Roger ... roger", 50);
                onderonStreets(player);
                }
            }
            break;
        case 3:
            warGamesText("You decide to look for an alternate route, avoiding direct confrontation.",50);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            onderonStreets(player);
            break;
        default:
            std::cout << "Invalid choice. The Sepratist battle droids become suspicious of your presence.\n";
            invalidInput = true;
            clearInputBuffer();
    }
    } while (choice >= 4 || invalidInput);
}