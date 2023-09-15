/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 06 Demonstration
 Notes:		
*/

#include "main.h"

     /*************************************************************
    * Function: thisIsAnOutput ()
    * Date Created: 9/15/23
    * Date Last Modified: 9/15/23
    * Description: outputs a cout
    * Input parameters: nothing
    * Returns: Cout
    *************************************************************/

void thisIsAnOutput()
{
	std::cout << "This is a really cool output demonstrating my understanding of three file format." << std::endl;
}

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