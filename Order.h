#pragma once
using namespace std;
#include <iostream>
#include <string>
#include "List.h"
#include "Dish.h"

class Order
{
private:



public:
	bool isReady;
	List<Dish> orderList;
	Order();
	Order(bool);
	void setisReady(bool);
	bool getisReady();
	void addDish(Dish);
	double CalculateTotal();



};

