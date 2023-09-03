#ifndef PET_STORE_H
#define PET_STORE_H

#include <string>
#include <vector>
#include <fstream>

class PetStore {
public:

    PetStore() = default;

    bool processData(const std::string& filename,
                     std::fstream& myFile,
                     std::vector<std::string>& headers,
                     std::vector<std::string>& petStoreName,
                     std::vector<std::string>& petName,
                     std::vector<std::string>& petType,
                     std::vector<int>& daysAtStore);

    bool writeSummary(const std::string& filename,
                    std::fstream& myFile,
                    std::vector<std::string>& petStoreName,
                    std::vector<std::string>& petName,
                    std::vector<std::string>& petType,
                    std::vector<int>& daysAtStore);

private:
    bool fileOpen(const std::string& filename, std::fstream& myFile);
    void fileClose(std::fstream& myFile);
    void getData(std::fstream& myFile, std::vector<std::string>& headers,
                 std::vector<std::string>& petStoreName,
                 std::vector<std::string>& petName,
                 std::vector<std::string>& petType,
                 std::vector<int>& daysAtStore);
    int getNumberOfPets(std::vector<std::string>& petType);
    int getAverageNumberOfDays(std::vector<int>& daysAtStore);
    void getUniqueStoreNames(std::vector<std::string>& petStoreName,std::vector<std::string>& uniquePetStoreName);
    int getStoreWithMostPets(std::vector<std::string>& petStoreName,std::vector<std::string>& uniquePetStoreName, std::vector<int>& numberOfPetsAtStore);
    int getTotalPetsAtStore(std::vector<std::string>& petStoreName, std::vector<std::string>& uniquePetStoreName, std::vector<int>& numberOfPetsAtStore);
    std::string randomPetName(std::vector<std::string>& petName);
    void getNumberofPetsByStore(std::vector<std::string>& petStoreName, std::vector<std::string>& uniquePetStoreName, std::vector<int>& numberOfPetsAtStore);
};

#endif
