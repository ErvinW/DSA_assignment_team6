#include "DishDict.h"

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