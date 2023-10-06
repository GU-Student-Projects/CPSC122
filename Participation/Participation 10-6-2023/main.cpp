/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 16 C Strings
 Notes:	No questions
*/

#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

void stringCopy(char destination[], char source[]);
void safeStringCopy(char destination[], char source[], const int MAX_SIZE);

int main(){   
    char word[60] = "This is a short message\0";
    char word2[100] = "Hello, I am trying to make something that has more characters than allowed\0"; 
    const int MAX_SIZE = 30;

    cout << word << endl;
    
    // stringCopy(word,word2);
    safeStringCopy(word,word2,MAX_SIZE);

    cout << word << endl;

    return 0;
}

void stringCopy(char destination[], char source[])
{
    int index = 0;
    while(source[index] != '\0'){
        destination[index] = source[index];
        index++;
    }
    destination[index] = '\0';
}

void safeStringCopy(char destination[], char source[], const int MAX_SIZE){
    int index = 0;
    while(source[index] != '\0' && index < MAX_SIZE-1){
        destination[index] = source[index];
        index++;
    }
    destination[index] = '\0';
}