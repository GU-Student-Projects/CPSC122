/*
 Name: Gabe DiMartino
 Class: CPSC 122, Fall 2023
 Lecture 08-09 Demonstration
 Notes:	No questions
*/

#include "day2Starter.h"

    /*************************************************************
    * Function: linearSearch ()
    * Date Created: 9/20/23
    * Date Last Modified: 9/20/23
    * Description: Walk through an array and find the target value
    * Input parameters: populated array, array size, and target value
    * Returns: target value index
    * Pre: Populated array
    * Post: targetValue index
    *************************************************************/

int linearSearch(int arrayToSearch[], int size, int targetValue)
{
	int index = 0;
	int position = -1;
	bool found = false;

	while (index < size && !found)
	{
		if (arrayToSearch[index] == targetValue)
		{
			found = true;
			position = index;
		}
		index++;
	}

	return position;
}

    /*************************************************************
    * Function: binarySearch ()
    * Date Created: 9/20/23
    * Date Last Modified: 9/20/23
    * Description: From the middle, find the target value, if it is
    * less than, discard the right hand side and vise versa.
    * Input parameters: populated array, array size, and target value
    * Returns: target value index
    * Pre: Populated array
    * Post: targetValue index
    *************************************************************/
int bindarySearch(int arrayToSearch[], int size, int targetValue)
{
    int first = 0,
        last = size - 1,
        middle,
        position = -1;
    bool found = false;


    while (!found && first < size)
    {
        middle = (first + last)/2;
        if (arrayToSearch[middle] == targetValue){
            found = true;
			position = middle;
        }
        else if (arrayToSearch[middle] < targetValue){
            first = middle + 1;
        }
        else {
            last = middle - 1;
        }     

        }

        return position;

}