#include "Pet_Store.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

bool PetStore::processData(const std::string& filename,
                           std::ifstream& myFile,
                           std::vector<std::string>& headers,
                           std::vector<std::string>& petStoreName,
                           std::vector<std::string>& petName,
                           std::vector<std::string>& petType,
                           std::vector<int>& daysAtStore) {
    if (fileOpen(filename, myFile)) {
        getData(myFile, headers, petStoreName, petName, petType, daysAtStore);

        std::cout << "Processed " << headers.size() << " header columns: ";
        for (size_t i = 0; i < headers.size(); ++i) {
            std::cout << headers[i];
            if (i < headers.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl << std::endl;

        for (size_t i = 0; i < petStoreName.size(); ++i) {
            std::cout << "Processed a " << petType[i] << ", \"" << petName[i] << "\" ... "
            << daysAtStore[i] << " day(s) on site at store \"" << petStoreName[i] << "\"" << std::endl;
        }

        std::cout << "All pet store data processed!" << std::endl;

        fileClose(myFile);
        return true;
    } else {
        std::cerr << "The file " + filename + " has encountered an error. Please make sure the file is in the correct directory and you have the appropriate permissions to read." << std::endl;
        return false;
    }
}

bool PetStore::fileOpen(const std::string& filename, std::ifstream& myFile) {
    myFile.open(filename);
    return myFile.is_open();
}

void PetStore::getData(std::ifstream& myFile, std::vector<std::string>& headers,
             std::vector<std::string>& petStoreName,
             std::vector<std::string>& petName,
             std::vector<std::string>& petType,
             std::vector<int>& daysAtStore) {
    std::string headerLine;
    std::string dataLine;

    if (std::getline(myFile, headerLine)) {
        std::istringstream lineToParse(headerLine);
        std::string cell;

        while (std::getline(lineToParse, cell, ',')) {
            headers.push_back(cell);
        }

        while (std::getline(myFile, dataLine)) {
            std::istringstream dataToParse(dataLine);
            std::vector<std::string> rowData;

            while (std::getline(dataToParse, cell, ',')) {
                rowData.push_back(cell);
            }

            if (rowData.size() >= 4) {
                petStoreName.push_back(rowData[0]);
                petName.push_back(rowData[1]);
                petType.push_back(rowData[2]);

                int days;
                if (std::istringstream(rowData[3]) >> days) {
                    daysAtStore.push_back(days);
                } else {
                    std::cerr << "Error parsing days value." << std::endl;
                }
            }
        }
    } else {
        std::cerr << "Error, couldn't read headers" << std::endl;
    }
}

void PetStore::fileClose(std::ifstream& myFile) {
    myFile.close();
}
