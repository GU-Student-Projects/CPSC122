#ifndef PET_STORE_H
#define PET_STORE_H

#include <string>
#include <vector>
#include <fstream>

class PetStore {
public:
    // Constructor
    PetStore() = default;

    // Member functions
    bool processData(const std::string& filename,
                     std::ifstream& myFile,
                     std::vector<std::string>& headers,
                     std::vector<std::string>& petStoreName,
                     std::vector<std::string>& petName,
                     std::vector<std::string>& petType,
                     std::vector<int>& daysAtStore);

private:
    bool fileOpen(const std::string& filename, std::ifstream& myFile);
    void fileClose(std::ifstream& myFile);
    void getData(std::ifstream& myFile, std::vector<std::string>& headers,
                 std::vector<std::string>& petStoreName,
                 std::vector<std::string>& petName,
                 std::vector<std::string>& petType,
                 std::vector<int>& daysAtStore);
};

#endif
