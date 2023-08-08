#include "Dictionary.h"

Dictionary::Dictionary() {
    size = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        items[i] = nullptr;
    }
}

Dictionary::~Dictionary() {
    for (int i = 0; i < MAX_SIZE; i++) {
        Node* current = items[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

int Dictionary::hash(KeyType key) {
    // Simple hash function
    int sum = 0;
    for (char c : key) {
        sum += c;
    }
    return sum % MAX_SIZE;
}

bool Dictionary::add(KeyType newKey, ItemType newItem) {
    int index = hash(newKey);

    // Check if the key already exists in the Dictionary
    Node* current = items[index];
    while (current != nullptr) {
        if (current->key == newKey) {
            std::cout << "Key already exists. Cannot add item." << std::endl;
            return false;
        }
        current = current->next;
    }

    // Create a new node and add it to the Dictionary
    Node* newNode = new Node;
    newNode->key = newKey;
    newNode->item = newItem;
    newNode->next = items[index];
    items[index] = newNode;
    size++;

    return true;
}

void Dictionary::remove(KeyType key) {
    int index = hash(key);

    // Handle the case when the key is at the front
    if (items[index] != nullptr && items[index]->key == key) {
        Node* temp = items[index];
        items[index] = items[index]->next;
        delete temp;
        size--;
        return;
    }

    // Traverse the list to find the key and remove the node
    Node* current = items[index];
    while (current != nullptr && current->next != nullptr) {
        if (current->next->key == key) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            size--;
            return;
        }
        current = current->next;
    }

    std::cout << "Key not found. Cannot remove item." << std::endl;
}

ItemType Dictionary::get(KeyType key) {
    int index = hash(key);

    // Traverse the list to find the key and retrieve the item
    Node* current = items[index];
    while (current != nullptr) {
        if (current->key == key) {
            return current->item;
        }
        current = current->next;
    }

    return ItemType();
}

bool Dictionary::isEmpty() {
    return (size == 0);
}

int Dictionary::getLength() {
    return size;
}

void Dictionary::print() {
    for (int i = 0; i < MAX_SIZE; i++) {
        Node* current = items[i];
        while (current != nullptr) {
            Customer tempCust = current->item;

            std::cout << "Key: " << current->key << ", Item: ";
            tempCust.print();
            current = current->next;
        }
    }
}