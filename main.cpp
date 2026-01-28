#include "inc/Array.h"
#include <iostream>
#include <vector>

template<typename T>
void PrintArray(const std::string& label, Array<T> &arr) {
    std::cout << label << ": ";
    for (auto it =arr.begin(); it != arr.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

struct Contact {
    std::string name;
    std::string phoneNumber;

    Contact() : name(""), phoneNumber("") {
    }

    Contact(std::string name, std::string phoneNum) : name(name), phoneNumber(phoneNum) {
    }

    bool operator<(Contact const &other) const {
        return name < other.name;
    }

    bool operator>(const Contact &other) const {
        return name > other.name;
    }

    bool operator==(Contact const &other) const {
        return name == other.name;
    }

    bool operator!=(Contact const &other) const {
        return name != other.name;
    }

    void SaveBinary(std::ofstream &outFile) const {
        Serializer<std::string>::Save(outFile, name);
        Serializer<std::string>::Save(outFile, phoneNumber);
    }

    void LoadBinary(std::ifstream &inFile) {
        Serializer<std::string>::Load(inFile, name);
        Serializer<std::string>::Load(inFile, phoneNumber);
    }

    friend std::ostream &operator<<(std::ostream &os, Contact const &obj) {
        os << "{" << obj.name << " : " << obj.phoneNumber << "}";
        return os;
    }
};

int main() {
    

    std::cout << "=========================================" << std::endl;
    std::cout << "      FINAL PROJECT DEMONSTRATION        " << std::endl;
    std::cout << "=========================================\n" << std::endl;

    std::cout << "--- Part 1: Managing Custom Objects (Contacts) ---" << std::endl;
    //Filling the arr
    Array<Contact> contacts(5);
    contacts.push_back(Contact("Zack", "555-999-945"));
    contacts.push_back(Contact("Alice", "555-123-124"));
    contacts.push_back(Contact("Bob", "555-567-458"));
    contacts.push_back(Contact("Charlie", "555-000-670"));

    //testing sort
    PrintArray("Unsorted Contacts", contacts);

    std::cout << "-> Sorting Contacts by Name..." << std::endl;
    contacts.Sort();
    PrintArray("Sorted Contacts", contacts);

    //Finding contact
    Contact target("Alice", "555-123-124");
    std::cout << "-> Searching for Alice (555-123-124)..." << std::endl;
    int index = contacts.Find(target);
    if (index != -1) {
        std::cout << "[*]   SUCCESS: Found at index " << index << "\n" << std::endl;
    } else {
        std::cout << "[x]   FAILURE: Not found\n" << std::endl;
    }

    //Serialization
    std::cout << "--- Part 2: Serialization (Saving/Loading Objects) ---" << std::endl;

    std::string filename = "contacts.bin";

    // Save
    std::cout << "-> Saving " << contacts.Size() << " contacts to binary file '" << filename << "'..." << std::endl;
    try {
        contacts.Save(filename);
        std::cout << "[*]   Save Successful." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[x]   Save Failed: " << e.what() << std::endl;
    }

    // Load
    std::cout << "-> Loading data into a new array..." << std::endl;
    Array<Contact> loadedContacts(1); // Start empty

    try {
        loadedContacts.Load(filename);
        std::cout << "[*]   Load Successful." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[x]   Load Failed: " << e.what() << std::endl;
    }

    // Verify
    PrintArray("Loaded Contacts from Disk", loadedContacts);

    std::cout << "->Veryfying data"<<std::endl;
    if (loadedContacts.Size() == 4 && loadedContacts[0].name == "Alice") {
         std::cout << "[*] Data integrity confirmed!" << std::endl;
    }
    else {
        std::cout << "[x]   Data integrity lost!" << std::endl;
    }

    return 0;
}
