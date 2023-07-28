#pragma once
#include <iostream>
#include <string>

using namespace std;

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
	string getFoodName() const;
	void setPortion(string);
	string getPortion() const;
	void setCharge(double);
	double getCharge() const;
	virtual double CalculateCharges();
	friend std::ostream& operator<<(std::ostream& os, const Dish& dish);
};

std::ostream& operator<<(std::ostream& os, const Dish& dish);

