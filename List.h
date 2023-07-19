#pragma once
#include <iostream>
#include<string>

using namespace std;


const int MAX_SIZE = 100;
//typedef Person ItemType;
template <class T>
class List
{
private:
	T items[MAX_SIZE];
	int      size;

public:

	List() { size = 0; }

	// add an item to the back of the list (append)
	bool add(T item)
	{
		bool success = size < MAX_SIZE;
		if (success)
		{
			items[size] = item;    // add to the end of the list
			size++;                // increase the size by 1
		}
		return success;
	}

	// add an item at a specified position in the list (insert)
	bool add(int index, T item)
	{
		bool success = (index >= 0) && (index <= size) && (size < MAX_SIZE);
		if (success)
		{  // make room for the item by shifting all items at
		   // positions >= index toward the end of the
		   // List (no shift if index == size + 1)
			for (int pos = size; pos >= index; pos--)
				items[pos] = items[pos - 1];
			// insert the item
			items[index] = item;
			size++;  // increase the size by 1
		}
		return success;
	}

	// remove an item at a specified position in the list
	void remove(int index)
	{
		bool success = (index >= 0) && (index < size);
		if (success)
		{  // delete item by shifting all items at positions >
		   // index toward the beginning of the list
		   // (no shift if index == size)
			for (int pos = index; pos < size; pos++)
				items[pos] = items[pos + 1];
			size--;  // decrease the size by 1
		}

	}

	// get an item at a specified position of the list (retrieve)
	T& get(int index)
	{
		bool success = (index >= 0) && (index < size);
		if (success)
			return items[index];
		else
			throw std::out_of_range("Invalid index");  // Throw an exception if the index is invalid
	}


	// check if the list is empty
	bool isEmpty() { return size == 0; }

	// check the size of the list
	int getLength() { return size; }

	// display the items in the list
	void print()
	{
		for (int i = 0; i < size; i++)
		{
			cout << items[i] << endl;
		}
	}

	// replace the  item in the specified index in the list
	void replace(int index, T item)
	{
		if (index >= 0 && index < size)
		{
			// Replace the item at the specified index
			items[index] = item;
		}
		else
		{
			// Handle the case when the index is out of bounds
			cout << "Error: Invalid index. Index should be between 0 and " << (MAX_SIZE - 1) << endl;
		}
	}

	T* begin() { return items; }
	T* end() { return items + size; }
	const T* begin() const { return items; }
	const T* end() const { return items + size; }
};


