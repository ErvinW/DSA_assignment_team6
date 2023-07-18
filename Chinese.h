#pragma once
using namespace std;
#include <iostream>
#include <string>
#include "Dish.h"

class Chinese : public Dish
{
private:
	bool preBooked;
	bool Drink;

public:
	Chinese();
	Chinese(string, string, string, double);
	void setpreBooked(bool);
	bool getpreBooked();
	void setDrink(bool);
	bool getDrink();
	virtual double CalculateCharges() override;
};

