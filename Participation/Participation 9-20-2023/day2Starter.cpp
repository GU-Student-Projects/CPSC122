/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 08-09 Demonstration
 Notes:	No questions
*/

#include "day2Starter.h"

int main(void)
{
	int numlist[] = { 17, 23, 5, 11, 2, 29, 3 }; //ANY ORDER
	int numlist2[] = { 2, 3, 5, 11, 17, 23, 29 }; //IN ORDER

	//-1 because the 'default' is that there is NO match
	int indexOfSearchMatch = -1;
	int targetValue = 11;
	indexOfSearchMatch = linearSearch(numlist, SIZE, targetValue);

	if(indexOfSearchMatch == -1){
		cout << "The number does not exist" << endl;
	} else {
	cout << "Found Index: " << indexOfSearchMatch << " For target value: "<< targetValue << endl;
	}

	targetValue = 29;
	indexOfSearchMatch = bindarySearch(numlist2, SIZE, targetValue);

	if(indexOfSearchMatch == -1){
		cout << "The number does not exist" << endl;
	} else {
	cout << "Found Index: " << indexOfSearchMatch << " For target value: "<< targetValue << endl;
	}

	return 0;
}


