#pragma once
// Dictionary.h - - Specification of Dictionary ADT
#include<string>
#include<iostream>

#include "Dish.h"

const int MAX_DISH_SIZE = 101;
typedef Dish DishType;
typedef std::string DishKey;

struct dNode
{
	DishKey  key;   // search key
	DishType item;	// data item
	dNode* next;	// pointer pointing to next item
};

class DishDict
{
private:
	dNode* items[MAX_DISH_SIZE];
	int  size;			// number of items in the Dictionary

public:
	// constructor
	DishDict();

	// destructor
	~DishDict();

	int hash(DishKey key);

	// add a new item with the specified key to the Dictionary
	bool add(DishKey newKey, DishType newItem);

	// remove an item with the specified key in the Dictionary
	void remove(DishKey key);

	// get an item with the specified key in the Dictionary (retrieve)
	DishType get(DishKey key);

	// check if the Dictionary is empty
	bool isEmpty();

	// check the size of the Dictionary
	int getLength();

	//------------------- Other useful functions -----------------
	// display the items in the Dictionary
	void print();
};
