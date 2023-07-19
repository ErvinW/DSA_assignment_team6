#pragma once
using namespace std;
#include <iostream>
#include <string>


class Dish {
private:
	string cuisine;
	string foodName;
	string portion;
	double charge;

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