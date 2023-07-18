#pragma once
#include<string>
#include<iostream>
using namespace std;

const int MAXSIZE = 100;

template <class T>

class Queue
{
private:
	T items[MAXSIZE];
	int  front;
	int  back;
	bool isFull;

public:
	// constructor
	Queue()
	{
		front = -1;
		back = -1;
		isFull = false;
	}
	// enqueue (add) item at back of the queue
	bool enqueue(T item)
	{
		if (isEmpty())
		{
			front = 0;
			back = 0;
		}
		else
		{
			back = (back + 1) % MAXSIZE;
		}

		items[back] = item;
		return true;

	}
	// dequeue (remove) item from front of the queue
	bool dequeue()
	{
		if (isEmpty())
		{
			cout << "Error: Queue is empty. Cannot dequeue item.\n";
			return false;
		}

		if (front == back)
		{
			front = -1;
			back = -1;
		}
		else
		{
			front = (front + 1) % MAXSIZE;
		}


		return true;
	}
	// retrieve (get) and dequeue item from front of the queue
	bool dequeue(T& item)
	{
		if (isEmpty())
		{
			cout << "Error: Queue is empty. Cannot dequeue item.\n";
			return false;
		}

		item = items[front];
		return dequeue();
	}
	// retrieve (get) item from front of queue
	void getFront(T& item)
	{
		if (isEmpty())
		{
			cout << "Error: Queue is empty. Cannot retrieve front item.\n";
			return;
		}

		item = items[front];
	}
	// check if the queue is empty
	bool isEmpty()
	{
		return (front == -1 && back == -1);
	}

};

