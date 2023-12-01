/*
	CPSC 122
	PA6 - Players Starter Code
	You should NOT be submitting a file named "pa6Starter.cpp"
	Please use this as a starting point.
	Cite all sources used.
*/

#include "header.h"

//don't forget about static variables.

int main(void)
{
	int choice;
	Jedi jediMaster;
	BountyHunter mando;
	CloneTrooper captain;
	Sith sithLord;

	clearScreen();
	warGamesText(titleScreen(), 1);
	warGamesText("WELCOME TO MY SIMPLE STAR WARS THEMED TERMINAL GAME",50);
	std::cout<<std::endl;
	warGamesText("PLEASE SELECT THE VERSION OF THE GAME YOU WANT TO PLAY.",50);
	std::cout<<"FOR PROGRAMING ASSIGNMENT DEMONSTRATION, PLEASE SELECT \"PROGRAMING ASSIGNMENT\""<<std::endl;
	std::cout<<std::endl;
	choice = mainMenu();

	if (2 == choice){ 
		fullGameMode();
		return 0;}
	else if (3 == choice) { return 0;}
	else {
	clearScreen();
	srand(time(NULL)); //generate seed

	jediMaster.initializePlayer("Mace Windu");
	mando.initializePlayer("Jango Fett");

	std::cout << "Filled the list ... " << std::endl;
	std::cout << "Demonstrating printing the list ... " << std::endl;
	jediMaster.displayInventory();
	std::cout << "Demonstrating removing an item from the list ... " << std::endl;
	jediMaster.removeInventoryItem();
	jediMaster.displayInventory();

	std::cout << "\nWelcome to the battle arena!\nToday we will be seeing a battle between a Jedi and a Bounty Hunter.\nOur first participant is:\n" << std::endl;
	jediMaster.printPlayerInfo();
	std::cout << "And our second particpant is: \n" << std::endl;
	mando.printPlayerInfo();

	std::cout<<"Let the battle commence!"<<std::endl;

	jediMaster.loopRound(jediMaster,mando,1);

	jediMaster.printPlayerInfo();
	mando.printPlayerInfo();

	std::cout<<"\nRound Two! (Derived Classes)"<<std::endl;
	captain.initializePlayer("Rex");
	sithLord.initializePlayer("Dooku");
	std::cout << "\nWelcome to the battle arena!\nToday we will be seeing a battle between a Clone Captain and a Sith Lord.\nOur first participant is:\n" << std::endl;
	captain.printPlayerInfo();
	std::cout << "And our second particpant is: \n" << std::endl;
	sithLord.printPlayerInfo();

	std::cout<<"Let the battle commence!"<<std::endl;

	captain.loopRound(captain,sithLord,1);

	captain.printPlayerInfo();
	sithLord.printPlayerInfo();
	
	}

	return 0;
}



