#pragma once
#include <iostream>
#include <string>

template <class T>
class List {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    int size;

public:
    List() : head(nullptr), size(0) {}

    bool add(T item) {
        Node* newNode = new Node(item);
        if (!newNode)
            return false;

        if (!head) {
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next)
                current = current->next;
            current->next = newNode;
        }

        size++;
        return true;
    }

    bool add(int index, T item) {
        if (index < 0 || index > size)
            return false;

        Node* newNode = new Node(item);
        if (!newNode)
            return false;

        if (index == 0) {
            newNode->next = head;
            head = newNode;
        }
        else {
            Node* current = head;
            for (int i = 0; i < index - 1; i++)
                current = current->next;
            newNode->next = current->next;
            current->next = newNode;
        }

        size++;
        return true;
    }

    void traverse(void (*func)(T&)) const {
        Node* current = head;
        while (current) {
            func(current->data);
            current = current->next;
        }
    }

    T get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Invalid index");
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        return current->data;
    }

    int getLength() const {
        return size;
    }




    void remove(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Invalid index");
        }

        if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        else {
            Node* prev = nullptr;
            Node* current = head;
            for (int i = 0; i < index; i++) {
                prev = current;
                current = current->next;
            }
            prev->next = current->next;
            delete current;
        }

        size--;
    }

    

    // Destructor to clean up memory
    ~List() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};
