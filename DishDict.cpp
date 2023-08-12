#include "DishDict.h"
#include <iomanip>
#include <fstream>
#include <sstream>


DishDict::DishDict() {
    size = 0;
    for (int i = 0; i < MAX_DISH_SIZE; i++) {
        items[i] = nullptr;
    }
}

DishDict::~DishDict() {
    for (int i = 0; i < MAX_DISH_SIZE; i++) {
        dNode* current = items[i];
        while (current != nullptr) {
            dNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

int DishDict::hash(DishKey key) {
    // Simple hash function
    int sum = 0;
    for (char c : key) {
        sum += c;
    }
    return sum % MAX_DISH_SIZE;
}

bool DishDict::add(DishKey newKey, DishType newItem) {
    int index = hash(newKey);

    // Check if the key already exists in the Dictionary
    dNode* current = items[index];
    while (current != nullptr) {
        if (current->key == newKey) {
            std::cout << "Key already exists. Cannot add item." << std::endl;
            return false;
        }
        current = current->next;
    }

    // Create a new node and add it to the Dictionary
    dNode* newNode = new dNode;
    newNode->key = newKey;
    newNode->item = newItem;
    newNode->next = items[index];
    items[index] = newNode;
    size++;

    return true;
}

void DishDict::remove(DishKey key) {
    int index = hash(key);

    // Handle the case when the key is at the front
    if (items[index] != nullptr && items[index]->key == key) {
        dNode* temp = items[index];
        items[index] = items[index]->next;
        delete temp;
        size--;
        return;
    }

    // Traverse the list to find the key and remove the node
    dNode* current = items[index];
    while (current != nullptr && current->next != nullptr) {
        if (current->next->key == key) {
            dNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
            size--;
            return;
        }
        current = current->next;
    }

    std::cout << "Key not found. Cannot remove item." << std::endl;
}

DishType DishDict::get(DishKey key) {
    int index = hash(key);

    // Traverse the list to find the key and retrieve the item
    dNode* current = items[index];
    while (current != nullptr) {
        if (current->key == key) {
            return current->item;
        }
        current = current->next;
    }

    return DishType();
}

bool DishDict::isEmpty() {
    return (size == 0);
}

int DishDict::getLength() {
    return size;
}

void DishDict::loadRatingsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for loading ratings: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        double rating;
        std::getline(iss, name, ',');
        iss >> rating;

        int index = hash(name);
        dNode* current = items[index];
        while (current != nullptr && current->key != name) {
            current = current->next;
        }
        if (current != nullptr) {
            current->item.setAverageRating(rating);
        }
    }

    file.close();
}


void DishDict::saveRatingsToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for saving ratings: " << filename << std::endl;
        return;
    }

    for (int i = 0; i < MAX_DISH_SIZE; i++) {
        dNode* current = items[i];
        while (current != nullptr) {
            file << current->key << "," << current->item.getAverageRating() << "\n";
            current = current->next;
        }
    }

    file.close();


    std::cout << "Ratings saved to file." << std::endl;
}



void DishDict::rateDishByName() {
    // Display dishes with ratings
    for (int i = 0; i < MAX_DISH_SIZE; i++) {
        dNode* current = items[i];
        while (current != nullptr) {
            std::cout << current->key << " - Rating: " << current->item.getAverageRating() << "/5" << std::endl;
            current = current->next;
        }
    }

    // Ask customer for the name of the dish to rate
    std::string dishName;
    std::cout << "Enter the name of the dish you want to rate: ";
    std::cin.ignore(); // Clear the input buffer
    std::getline(std::cin, dishName);

    int index = hash(dishName);
    dNode* current = items[index];
    while (current != nullptr && current->key != dishName) {
        current = current->next;
    }

    if (current == nullptr) {
        std::cout << "Dish not found. Operation aborted." << std::endl;
        return;
    }

    int rating;
    while (true) {
        std::cout << "Enter your rating for " << dishName << " (0 to 5): ";
        std::cin >> rating;

        if (std::cin.fail() || rating < 0 || rating > 5) {
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining input
            std::cout << "Invalid rating. Please enter a number between 0 and 5." << std::endl;
        }
        else {
            break;
        }
    }

    current->item.addRating(rating);
    std::cout << std::fixed << std::setprecision(1); // Set the output to one decimal place
    std::cout << "Thank you for rating " << dishName << "! Updated Rating: " << current->item.getAverageRating() << "/5" << std::endl;
}
  

void DishDict::print() {
    for (int i = 0; i < MAX_DISH_SIZE; i++) {
        dNode* current = items[i];
        while (current != nullptr) {
            Dish tempDish = current->item;

            std::cout << "Key: " << current->key << ", Item: ";
            tempDish.print();
            current = current->next;
        }
    }
}