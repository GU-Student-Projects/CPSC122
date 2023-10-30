/*
Name: Gabe DiMartino
Class: CPSC122, Fall 2023
Date: October 29, 2023
Programming Assignment: PA4
Description: This cpp contains all of the implementations of functions
*/

#include "header.h"

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

    /*************************************************************
    * Function: fileOpen ()
    * Date Created: 9/2/23
    * Date Last Modified: 10/10/23
    * Description: Opens any file passed to it. 
    * Input parameters: file name and the fStream variable
    * Returns: T/F if sucessful throws error if F
    * Pre: Read/Write access in directory
    * Post: Working file
    *************************************************************/

bool fileOpen(const char* filename, std::ifstream& inFile) {
    inFile.open(filename); //open file
    return inFile.is_open();
}

   /*************************************************************
    * Function: pushBackPlayerCard()
    * Date Created: 10/10/23
    * Date Last Modified: 10/10/23
    * Description: adjusts the dynamically assigned array for an
    * increase in size and adds the new value
    * Returns: increased array size with push back characters
    * Pre: original array exists, and the new value is present
    * Post: completed array
    *************************************************************/

void pushBackPlayerCard(PlayerCard** originalArray, int* arraySize, PlayerCard newPlayer) {
    (*arraySize)++; //increase size of the array
    PlayerCard* newArray = new PlayerCard[*arraySize]; //create a new array with the larger size

    for (int i = 0; i < (*arraySize - 1); i++) {
        newArray[i] = (*originalArray)[i]; //copy all of the content from the original array into the new array
    }

    newArray[*arraySize - 1] = newPlayer; //add the new value to the last element of the new vector

    delete[] *originalArray; //delete the previous array

    *originalArray = newArray; //return the new array

}

   /*************************************************************
    * Function: importPlayerScoreCards()
    * Date Created: 10/10/23
    * Date Last Modified: 10/29/23
    * Description: from a TXT file, each line is read and added
    * the first and last name spots are specifically isolated and combined
    * Returns: populated array of a custom struct.
    * Pre: empty array
    * Post: completed array with read data.
    *************************************************************/

void importPlayerScoreCards(std::ifstream& inFile, PlayerCard** scoreCards, int* numCards) {
    int idValue;

    while (inFile >> idValue) { //while there is content in the file
        PlayerCard newUser(inFile, idValue); //create a user
        pushBackPlayerCard(scoreCards, numCards, newUser); //push back the player into the array
    }
}

   /*************************************************************
    * Function: initializePlayerScoreCard()
    * Date Created: 10/10/23
    * Date Last Modified: 10/29/23
    * Description: create a new user for the dart game by asking
    * there name and populating all other information
    * Returns: populated PlayerCard variable
    * Pre: empty user info
    * Post: filled user info added to the array
    *************************************************************/

void initializePlayerScoreCard(PlayerCard** scoreCards, int* numCards) {
    char lastName[MAXIMUM_CHARACTERS]; //create a variable to store the last name seperate from the first name
    char firstName [MAXIMUM_CHARACTERS];    

    std::cout << "What is your first and last name? ";
    std::cin >> firstName >> lastName; //import the first and last name into 2 variables

    int availableSpace = MAXIMUM_CHARACTERS - strlen(firstName) - 1; //if there is room in the overall arrat
    if (availableSpace > 0) {
        strncat(firstName, " ", availableSpace); //add a space
        strncat(firstName, lastName, availableSpace); //combine the lastname into the remaining spaces and cut off at 29
    }

    firstName[MAXIMUM_CHARACTERS- 1] = '\0'; //add the null terminating character

    PlayerCard player(firstName); //use a constructor to to generate a blank scorecard with specified name

    pushBackPlayerCard(scoreCards, numCards, player);

}

   /*************************************************************
    * Function: getDartRounds()
    * Date Created: 10/10/23
    * Date Last Modified: 10/10/23
    * Description: play the dart game and randomly assign points
    * Returns: finalized scores and average scores for the user
    * Pre: initialized player variable
    * Post: filled player variable
    *************************************************************/

bool getDartRounds(PlayerCard& player) {
    int randomScore = (std::rand() % 3) + 1; //randomly generate 1-3
    char select;
    bool validAnswer = false;

    std::cout << "You threw a dart!" << std::endl;

    if (randomScore == 2) {
        int score = (std::rand() % 5) + 1; //if it is a 2, generate a number between 1 and 5
        std::cout << "Oof, nice try but you hit a " << score << ". You should try again!" << std::endl;
        player.PlayerCard::setTotalScore(score);
    }
    else if (randomScore == 3) {
        int score = (std::rand() % 5) + 6; //if it is a 3 generate a number between 6 and 10
        std::cout << "Nice! You hit a " << score << ". Time to move on, I think." << std::endl;
        player.PlayerCard::setTotalScore(score);
    }
    else {
        std::cout << "Oh man... you missed" << std::endl;
    }

    player.updateAverageScore();

    std::cout << "Keep playing? (y/n): ";
    while (!validAnswer) { //loop until correct answer is chosen
        std::cin >> select;

        if (select == 'y') {
            validAnswer = true;
            return true;
        }
        else if (select == 'n') {
            validAnswer = true;
            return false;
        }
        else {
            std::cout << "Please select either 'y' or 'n'" << std::endl; //input validation
        }
    }
    return false; 
}

   /*************************************************************
    * Function: printPlayerScoreCard()
    * Date Created: 10/10/23
    * Date Last Modified: 10/10/23
    * Description: output the user data to the terminal
    * Returns: void
    * Pre: populated player variable
    * Post: console output
    *************************************************************/

void printPlayerScoreCard(const PlayerCard& player){ //output the player card
    std::cout<<"-----------------------|PID:"<<player.getPlayerID()<<"|"<<std::endl;
    std::cout<<player.getPlayerName()<<"'s Score Card"<<std::endl;
    std::cout<<"---------------------------------"<<std::endl;
    std::cout<<"Games Played: " << player.getNumberOfGames() << std::endl;
    std::cout<<"Running Score: " << player.getTotalScore() << std::endl;
    std::cout<< std::fixed << std::setprecision(2) <<"Average Score: " << player.getAverageScore() << std::endl;
    std::cout<<"---------------------------------"<<std::endl;
}

   /*************************************************************
    * Function: PlayerCard()
    * Date Created: 10/29/23
    * Date Last Modified: 10/29/23
    * Description: Default constructor to create a PlayerCard object
    * Returns: void
    * Pre: void
    * Post: void
    *************************************************************/

PlayerCard::PlayerCard() : PlayerCard("Default") {
}
   /*************************************************************
    * Function: PlayerCard(const char* name)
    * Date Created: 10/29/23
    * Date Last Modified: 10/29/23
    * Description: Default constructor to create a PlayerCard object
    * with option to input name
    * Returns: void
    * Pre: void
    * Post: void
    *************************************************************/

PlayerCard::PlayerCard(const char* nameValue){
    strcpy(playerName, nameValue);
    generatePlayerID();
    numberOfGames = 0;
    totalScore = 0;
    averageScore = 0.0;
}

   /*************************************************************
    * Function: PlayerCard(ifstream& inFile, int idValue)
    * Date Created: 10/29/23
    * Date Last Modified: 10/29/23
    * Description: Default constructor to create a PlayerCard object
    * with the option to pass an input file and PID value
    * Returns: void
    * Pre: void
    * Post: void
    *************************************************************/

PlayerCard::PlayerCard(std::ifstream& inFile, int idValue){
    char lastName[MAXIMUM_CHARACTERS]; //create a variable to store the last name seperate from the first name
    char firstName [MAXIMUM_CHARACTERS];
    int scoreValue, numberValue;
    double averageValue;

    PlayerCard::generatePlayerID(idValue);
    inFile >> firstName >> lastName;
    setPlayerName(firstName, lastName);


    inFile >> scoreValue; //import other info
    inFile >> numberValue;
    inFile >> averageValue;

    setTotalScore(scoreValue); //Explicitly use a setter to set each value in the class
    setNumberOfGames(numberValue);
    setAverageScore(averageValue);

}

   /*************************************************************
    * Function: ~PlayerCard()
    * Date Created: 10/29/23
    * Date Last Modified: 10/29/23
    * Description: Default deconstructor
    * Returns: void
    * Pre: void
    * Post: void
    *************************************************************/

PlayerCard::~PlayerCard(){ 
}


   /*************************************************************
    * Function: generatePlayerID()
    * Date Created: 10/29/23
    * Date Last Modified: 10/29/23
    * Description: create a random ID
    * Returns: void
    * Pre: void
    * Post: void
    *************************************************************/

void PlayerCard::generatePlayerID(){
    PlayerCard::setPlayerID(std::rand() % 9000 + 1000); //randomly create an ID
}

   /*************************************************************
    * Function: generatePlayerID(int)
    * Date Created: 10/29/23
    * Date Last Modified: 10/29/23
    * Description: update random PID
    * Returns: void
    * Pre: void
    * Post: void
    *************************************************************/

void PlayerCard::generatePlayerID(int newID){
    PlayerCard::setPlayerID(newID);
}

   /*************************************************************
    * Function: updateAverageScore()
    * Date Created: 10/29/23
    * Date Last Modified: 10/29/23
    * Description: increase the number of games and 
    * calculate the average
    * Returns: void
    * Pre: void
    * Post: void
    *************************************************************/

void PlayerCard::updateAverageScore(){
    numberOfGames++;
    PlayerCard::setAverageScore(double(totalScore)/numberOfGames);
}

   /*************************************************************
    * Function: setTotalScore()
    * Date Created: 10/29/23
    * Date Last Modified: 10/29/23
    * Description: bring the public score value into the private class
    * Returns: void
    * Pre: void
    * Post: void
    *************************************************************/

void PlayerCard::setTotalScore(int value){
    totalScore += value;
}

   /*************************************************************
    * Function: setPlayerID()
    * Date Created: 10/29/23
    * Date Last Modified: 10/29/23
    * Description: bring the public ID value into the private class
    * Returns: void
    * Pre: void
    * Post: void
    *************************************************************/

void PlayerCard::setPlayerID(int value){
    playerID = value;
}

   /*************************************************************
    * Function: setAverageaScore()
    * Date Created: 10/29/23
    * Date Last Modified: 10/29/23
    * Description: bring the public average value into the private class
    * Returns: void
    * Pre: void
    * Post: void
    *************************************************************/

void PlayerCard::setAverageScore(double value){
    averageScore = value;
}

   /*************************************************************
    * Function: setNumberOfGames()
    * Date Created: 10/29/23
    * Date Last Modified: 10/29/23
    * Description: bring the public number of games 
    * value into the private class
    * Returns: void
    * Pre: void
    * Post: void
    *************************************************************/

void PlayerCard::setNumberOfGames(int value){
    numberOfGames = value;
}

   /*************************************************************
    * Function: setPlayerName()
    * Date Created: 10/29/23
    * Date Last Modified: 10/29/23
    * Description: bring the public number of games 
    * value into the private class
    * Returns: void
    * Pre: void
    * Post: void
    *************************************************************/
void PlayerCard::setPlayerName( char* firstName, const char* lastName){
    strncat(firstName, " ", MAXIMUM_CHARACTERS - strlen(firstName) - 1); //add a space to the first name
    strncat(firstName, lastName, MAXIMUM_CHARACTERS - strlen(firstName) - 1); //add the last name to the first name
    firstName[MAXIMUM_CHARACTERS - 1] = '\0'; // add the null terminating character at the last index
    strcpy(playerName, firstName);
}