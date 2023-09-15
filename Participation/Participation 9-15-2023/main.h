/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 06 Demonstration
 Notes:		
*/

#ifndef MAIN_H
#define MAIN_H

#include <iostream> //needed for input/output streams from the console
#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

void thisIsAnOutput();
void clearScreen();

#endif