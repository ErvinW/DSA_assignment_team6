#pragma once
using namespace std;
#include <iostream>
#include <string>

class Dish
{
private:
	string Cuisine;
	string foodName;
	string Portion;
	double Charge;

public:
	Dish();
	Dish(string, string, string, double);
	void setCuisine(string);
	string getCuisine();
	void setFoodName(string);
	string getFoodName();
	void setPortion(string);
	string getPortion();
	void setCharge(double);
	double getCharge();
	virtual double CalculateCharges();



};

