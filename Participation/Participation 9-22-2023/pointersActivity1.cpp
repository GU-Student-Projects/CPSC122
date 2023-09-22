/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 09 Pointers 1
 Notes:	No questions
*/

#include <iostream>
#include <iomanip>
#include <cstdlib> //needed for rand() and srand()
#include <ctime> //needed for time(0) which we use in srand()

using namespace std;


void calculations(void);
void diceGame(void);
void computeSumMaxMin(int results[3], const int values[], int* numValues);


int main(void)
{
	srand(time(0)); //seed random number generator	

	calculations(); //practice activity
	diceGame(); //practice activity

	return 0;
}

void calculations() 
{

	int scores[] = { 56, 78, 12, 90, 85, 74, 95, 80, 40, 95 };
	int count = 10, i, sum = 0, max = scores[0], min = scores[0]; double average = 0.0;
	int results[3] = { 0 };
 
	int* countPtr = &count; int* iPtr = &i; int* sumPtr = &sum; int* maxPtr = &max; int* minPtr = &min;
	double* averagePtr = &average;

	for (*iPtr = 0; *iPtr < *countPtr; ++(*iPtr)) /* we loop from 0 to 9 */
	{
		*sumPtr += scores[i]; //keep track of the sum
		if (scores[i] > *maxPtr) //if the current index > max
			*maxPtr = scores[i];	//max is now the current score
		if (scores[i] < *minPtr) //if the current index < min
			*minPtr = scores[i];	//min is now the current score
	}

	computeSumMaxMin(results, scores, countPtr);

	*averagePtr = static_cast<double>(results[0]) / count; //Why cast?
	cout << fixed << setprecision(2) << "average: " << *averagePtr << endl;
	cout << "maximum: " << results[1] << endl;
	cout << "minimum: " << results[2] << endl;


}

void computeSumMaxMin(int results[3], const int values[], int* numValues)
{
	int count = 10, i, sum = 0, max = values[0], min = values[0];
	int* countPtr = &count;
	int* iPtr = &i;
	int* sumPtr = &sum;
	int* maxPtr = &max;
	int* minPtr = &min;


	for (*iPtr = 0; *iPtr < *countPtr; ++(*iPtr)) /* we loop from 0 to 9 */
	{
		*sumPtr += values[i]; //keep track of the sum
		if (values[i] > *maxPtr) //if the current index > max
			*maxPtr = values[i];	//max is now the current score
		if (values[i] < *minPtr) //if the current index < min
			*minPtr = values[i];	//min is now the current score
	}
	results[0] = *sumPtr;
	results[1] = *maxPtr;
	results[2] = *minPtr;
}

//this function does stuff, make it do "stuff" using pointers instead.
void diceGame(void)
{
	int die1 = 0, die2 = 0, sumDie = 0;
	int* die1Ptr = &die1;
	int* die2Ptr = &die2;
	int* sumDiePtr = &sumDie;
	char choice = '\0';
	char* choicePtr = &choice;

	do {
		cout << "Make a selection from the following menu:\n";		
		cout << "p) (p)lay the game!\n";
		cout << "q) (q)uit\n";
		cin >> *choicePtr;

		switch (*choicePtr)
		{		
		case 'p': //PLAY THE GAME
			
			*die1Ptr = rand() % 6 + 1;
			*die2Ptr = rand() % 20 + 1;

			*sumDiePtr = *die1Ptr + *die2Ptr;

			if (*sumDiePtr % 2 == 0)
			{
				cout << "Dice roll was an even sum! (" << *sumDiePtr << ")" << endl;
			}
			else
			{
				cout << "Dice roll was an odd sum! (" << *sumDiePtr << ")" << endl;
			}
			
			break;
		case 'q':
			cout << "Thank you for playing!" << endl;
			break;
		default:
			cout << "Adios!\n";
			break;
		}

	} while (*choicePtr != 'q');

	return;
}