#pragma once
using namespace std;
#include <iostream>
#include <string>
#include "Dish.h"

class Western : public Dish
{
private:
	bool Alcohol;

public:
	Western();
	Western(string, string, string, double);
	void setAlcohol(bool);
	bool getAlcohol();
	virtual double CalculateCharges() override;
};

