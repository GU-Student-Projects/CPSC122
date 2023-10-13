/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 18 Structs
 Notes:	No questions
*/

#include <iostream>
#include <string>

using namespace std;


const double PI = 3.141592654;

enum PetType {DOG,CAT,PIG,DUCK,SNAKE};

enum class PetTypeTwo {DOG,SLUG};

struct PetData {
    string petStoreName, petName;
    PetType petType;
    int numDaysAtStore;
};

void doNothing();

int main(){   
    PetType myPetType = DOG;
    myPetType = static_cast<PetType>(1);

    myPetType = static_cast<PetType>(PetTypeTwo::DOG);

    PetData myPets = {"Pete's Pets"};
    myPets.petName = "Jeff";
    myPets.petType = DOG;
    myPets.numDaysAtStore = 5;

    myPets.petName = "Really Jeff";

    PetData* myPetPtr = nullptr;
    myPetPtr = &myPets;

    myPetPtr->petName = "Jeff";

    PetData* myNewPet = new PetData;

    myNewPet->petStoreName ="Fur get me not";
    myNewPet->numDaysAtStore =1;
    


        return 0;
}

void doNothing(){
    return;
}