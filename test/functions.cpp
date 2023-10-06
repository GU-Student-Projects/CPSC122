#include "functions.h"  // Include the user-defined header file "functions.h".

int* pushBackInteger(int* originalArray, int& size, int newInt) {
    // Create a new array one size larger
    int* newArray = new int[size + 1];
    
    // Copy elements from the original array
    for (int i = 0; i < size; ++i) {
        newArray[i] = originalArray[i];
    }

    // Add the new integer at the back of the array
    newArray[size] = newInt;
    
    // Increment the size
    size++;

    // Free memory of the original array
    delete[] originalArray;
    
    return newArray;
}

bool stringIsInVector(const vector<string>& searchVector, const string& targetString) {
    // Linear search for the target string in the vector
    for (int i = 0; i < searchVector.size(); ++i) {
        if (searchVector[i] == targetString) {
            return true;
        }
    }
    return false;
}

void alphabetizePetNames(const vector<string>& petNames, vector<string>& alphabetizedNames) {
    // Copy the input vector to the output vector
    alphabetizedNames = petNames;

    // Sort the output vector alphabetically by the first character of each pet name
    for (int i = 0; i < alphabetizedNames.size(); ++i) {
        for (int j = i + 1; j < alphabetizedNames.size(); ++j) {
            if (alphabetizedNames[i].front() > alphabetizedNames[j].front()) {
                // Swap elements
                string temp = alphabetizedNames[i];
                alphabetizedNames[i] = alphabetizedNames[j];
                alphabetizedNames[j] = temp;
            }
        }
    }
}

bool ReadPetStoreData(fstream& inputFile, vector<string>& petStoreNames,
                     vector<string>& petNames, vector<string>& petTypes,
                     int*& numDaysAtStorePtr, int& numDaysAtStoreSize) {

    // Read and discard the header line
    string headerLine;
    if (!getline(inputFile, headerLine)) {
        return false;
    }

    // Read pet data from the file
    string storeName, petName, petType, daysStr;
    while (getline(inputFile, storeName, ',') && getline(inputFile, petName, ',') &&
           getline(inputFile, petType, ',') && getline(inputFile, daysStr)) {
        // Process and store pet data
        petStoreNames.push_back(storeName);
        petNames.push_back(petName);
        petTypes.push_back(petType);
        numDaysAtStorePtr = pushBackInteger(numDaysAtStorePtr, numDaysAtStoreSize, stoi(daysStr));
    }

    // Close the input file
    inputFile.close();

    return true;
}

void ProcessPetData(const vector<string>& petStoreNames, const vector<string>& petNames,
                   const vector<string>& petTypes, const int* numDaysAtStorePtr, const int numDaysAtStoreSize) {
    // Display header
    cout << "Processed 4 header columns: Pet Store, Pet Name, Pet Type, Days at Store" << endl;

    // Process and display pet data
    for (int i = 0; i < petStoreNames.size(); ++i) {
        cout << "Processed a " << petTypes[i] << ", \"" << petNames[i] << "\" ... "
                  << numDaysAtStorePtr[i] << " day(s) on site at store \"" << petStoreNames[i] << "\"" << endl;
    }

    // Alphabetize pet names
    vector<string> alphabetizedPetNames;
    alphabetizePetNames(petNames, alphabetizedPetNames);

    // Display completion message
    cout << "All pet store data processed!" << endl;
}
// Function to display pet data and messages to the console
void displayToConsole(const vector<string>& petStoreNames, const vector<string>& petNames,
                      const vector<string>& petTypes, const int* numDaysAtStorePtr, const int numDaysAtStoreSize) {
    // Display header
    cout << "Processed 4 header columns: Pet Store, Pet Name, Pet Type, Days at Store" << endl;

    // Process and display pet data
    for (int i = 0; i < petStoreNames.size(); ++i) {
        cout << "Processed a " << petTypes[i] << ", \"" << petNames[i] << "\" ... "
                  << numDaysAtStorePtr[i] << " day(s) on site at store \"" << petStoreNames[i] << "\"" << endl;
    }

    // Display completion message
    cout << "All pet store data processed!" << endl;

    // Alphabetize pet names
    vector<string> alphabetizedPetNames;
    alphabetizePetNames(petNames, alphabetizedPetNames);

    // Display alphabetized pet names
    cout << "Alphabetizing pet names... done:" << endl;
    for (int i = 0; i < alphabetizedPetNames.size(); ++i) {
        cout << alphabetizedPetNames[i];
        if (i < alphabetizedPetNames.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;

    // Display final message
    cout << "Generating summary report... Done!" << endl;
}

void GenerateCsvSummaryReport(const string& filename, const vector<string>& petStoreNames,
                             const vector<string>& petNames, const int* numDaysAtStorePtr, const int numDaysAtStoreSize) {
    // Open the output file
    ofstream outputFile(filename);

    // Check if the file was successfully opened
    if (!outputFile) {
        cout << "Failed to open output file." << endl;
        return;
    }

    // Write the header for the CSV summary report
    outputFile << "Pet Store CSV Summary Report" << endl;
    outputFile << "----------------------------" << endl;

    // Write the pet store names
    outputFile << "Pet Stores: ";
    for (int i = 0; i < petStoreNames.size(); ++i) {
        outputFile << petStoreNames[i];
        if (i < petStoreNames.size() - 1) {
            outputFile << ", ";
        }
    }
    outputFile << endl;

    // Write the total number of pets
    outputFile << "Total number of pets: " << petNames.size() << endl;

    // Write the pet store with the most pets
    string storeWithMostPets;
    int maxNumPets = 0;
    for (int i = 0; i < petStoreNames.size(); ++i) {
        int count = 0;
        for (int j = 0; j < petStoreNames.size(); ++j) {
            if (petStoreNames[i] == petStoreNames[j]) {
                count++;
            }
        }
        if (count > maxNumPets) {
            maxNumPets = count;
            storeWithMostPets = petStoreNames[i];
        }
    }
    outputFile << "Pet store with the most pets: " << storeWithMostPets << endl;

    // Write the number of pets at the store with the most pets
    int petsAtStoreWithMostPets = 0;
    for (int i = 0; i < petStoreNames.size(); ++i) {
        if (petStoreNames[i] == storeWithMostPets) {
            petsAtStoreWithMostPets++;
        }
    }
    outputFile << "Number of pets at " << storeWithMostPets << ": " << petsAtStoreWithMostPets << endl;

    // Calculate and write the pet average days on site across all stores
    int totalDays = 0;
    for (int i = 0; i < numDaysAtStoreSize; ++i) {
        totalDays += numDaysAtStorePtr[i];
    }
    double averageDays = static_cast<double>(totalDays) / petNames.size();
    outputFile << "Pet average days on site across all stores: " << averageDays << endl;

    // Randomly select a pet as Employee Pet of the Month
    int randomIndex = rand() % petNames.size();
    string employeePetOfTheMonth = petNames[randomIndex];
    outputFile << "Employee pet of the month choice: \"" << employeePetOfTheMonth << "\"" << endl;

    // Write the current pet inventory alphabetically
    vector<string> alphabetizedPetNames;
    alphabetizePetNames(petNames, alphabetizedPetNames);
    outputFile << "Current Pet Inventory: ";
    for (int i = 0; i < alphabetizedPetNames.size(); ++i) {
        outputFile << alphabetizedPetNames[i];
        if (i < alphabetizedPetNames.size() - 1) {
            outputFile << ", ";
        }
    }
    outputFile << endl;

    // Close the output file
    outputFile.close();
}
