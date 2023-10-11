/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 17 Structs
 Notes:	No questions
*/

#include <iostream>
#include <string>

using namespace std;

struct PetData {
    string petStoreName, petName, petType;
    int numDaysAtStore;
};

void printPetData(PetData petsData[], int numPets);
bool petCompare(const PetData& pet1, const PetData& pet2);

int main(){   
    PetData petsData[100];
    int petDataIndex;
    string storeName = "This is a store Name";
    string Name = "This is a pet name";
    string type = "Dog";
    int days = 5;

    while(true){
    petsData[petDataIndex].petStoreName = storeName;
    petsData[petDataIndex].petName = Name;
    petsData[petDataIndex].petType = type;
    petsData[petDataIndex].numDaysAtStore = days;

    petDataIndex++;
    }

    PetData* myPetPtr = nullptr;
    PetData myPet = {"Pet's Pet",
                        "Slimy",
                        "Slug",
                        1};
    
    myPetPtr = &myPet;

    cout << myPetPtr->petName << endl;

    return 0;
}

void printPetData(PetData petsData[], int numPets){
    for(int i=0; i< numPets; i++){
        cout << petsData[i].petStoreName << endl;
        cout << petsData[i].petName << endl;
        cout << petsData[i].petType << endl;
        cout << petsData[i].numDaysAtStore << endl;
    }
}

bool petCompare(const PetData& pet1, const PetData& pet2){
    if (pet1.petStoreName == pet2.petStoreName &&
        pet1.petName == pet2.petName &&
        pet1.petType == pet2.petType &&
        pet1.numDaysAtStore == pet2.numDaysAtStore){
            return true;
        } else {
            return false;
        }
}