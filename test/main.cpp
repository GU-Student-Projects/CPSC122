#include "functions.h"            // Include a user-defined header file called "functions.h" that likely contains function declarations and prototypes.

int main() {
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(nullptr)));

    // Declare variables
    vector<string> petStoreNames;  // Create a vector to store pet store names.
    vector<string> petNames;       // Create a vector to store pet names.
    vector<string> petTypes;       // Create a vector to store pet types.
    int numDaysAtStoreSize = 0;              // Initialize an integer variable for the size of an array.
    int* numDaysAtStorePtr = nullptr;        // Declare an integer pointer and initialize it to nullptr.

    // Open input and output files
    ifstream inputFile("petstoredata.csv");   // Create an input file stream and open "petstoredata.csv".
    ofstream outputFile("petreport.txt");     // Create an output file stream and open "petreport.txt".

    // Check if files are open
    if (!inputFile.is_open() || !outputFile.is_open()) {
        cout << "Error: Unable to open files." << endl;  // If either file couldn't be opened, display an error message and exit.
        return 1;
    }

    // Read pet store data from the input file
    if (!ReadPetStoreData(inputFile, petStoreNames, petNames, petTypes, numDaysAtStorePtr, numDaysAtStoreSize)) {
        cout << "Error: Failed to read pet store data." << endl;  // If reading data from the input file fails, display an error message and exit.
        return 1;
    }

    // // Close the input file
    // inputFile.close();

    // // Process and generate a summary report based on the read data
    // ProcessPetData(petStoreNames, petNames, petTypes, numDaysAtStorePtr, numDaysAtStoreSize);
    // GenerateCsvSummaryReport(outputFile, petStoreNames, petNames);

    // // Add this line to display the data and messages to the console
    // displayToConsole(petStoreNames, petNames, petTypes, numDaysAtStorePtr, numDaysAtStoreSize);


    // // Close the output file
    // outputFile.close();

    // cout << "All pet store data processed!" << endl;  // Display a success message after processing data.

    return 0;  // Exit the program with a success code.
}
