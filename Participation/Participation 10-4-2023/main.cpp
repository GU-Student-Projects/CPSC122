/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 15 C Strings
 Notes:	No questions
*/

#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

int main(){   
    char word[60] = "";
    char word2[25] = "Hello"; 
    char words[] = {',',' ','W','o','r','l','d','!','\0'} ;
    char* myWordPtr = new char[4]; // Hi!
    
    cout << strlen(word2) << endl;

    cout << strcat(word2, words) << endl;
    
    strcpy(word, "Adios!");

    cout << word << endl;

    return 0;
}