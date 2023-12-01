/*
	11-15-2023
	CPSC 122
	Inheritance
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

template <class TV>
TV addTwoValues(TV value, TV value2) {
    TV value3 = value + value2;
    return value3;
};


int main() {
    int outOfRangeIndex = 10;
    const int smallArraySize = 1;
    int smallArray[smallArraySize];

    try{
        //stoi("");
        //OutOfRangeIndex = 0;
        if(outOfRangeIndex >= smallArraySize){
            throw (outOfRangeIndex);
        }
    } catch (string size){
        cout << "Error! " << size << " is >= array size." << endl;
    } catch (const std::invalid_argument& e){
        cout << "Exception: " << e.what() << endl;
    } catch (...){
        cout << "Catch All!" << endl;
    }

    cout << "ADD two values: 1 + 2 = " << addTwoValues(1,2) << endl;

    return 0;
}