#pragma once
#include<string>
#include<iostream>
#include "Order.h"

typedef Order Item;


class Queue
{
private:
    struct Node
    {
        Item item;	// item
        Node* next;	// pointer pointing to next item
    };

    Node* frontNode;	// point to the first item
    Node* backNode;	// point to the first item


public:
    // constructor
    Queue();  //Done
    ~Queue(); //Done

    // enqueue (add) item at the back of queue
    bool enqueue(Item item); //Done

    // dequeue (remove) item from front of queue
    bool dequeue();

    // dequeue (remove) and retrieve item from front of queue
    bool dequeue(Item& item); //Done

    // retrieve (get) item from front of queue
    void getFront(Item& item); //Done

    // check if the queue is empty
    bool isEmpty(); //Done

    // display items in queue from front to back
    void displayItems();

};