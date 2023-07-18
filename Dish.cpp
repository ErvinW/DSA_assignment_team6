#include "Dish.h"
using namespace std;
#include <iostream>
#include <string>

Dish::Dish() {};

Dish::Dish(string a_Cuisine, string a_foodName, string a_Portion, double a_Charge)
{
	Cuisine = a_Cuisine;
	foodName = a_foodName;
	Portion = a_Portion;
	Charge = a_Charge;
}

void Dish::setCuisine(string a_foodName)
{
	Cuisine = a_foodName;
}

string Dish::getCuisine()
{
	return Cuisine;
}

void Dish::setFoodName(string a_foodName)
{
	foodName = a_foodName;
}

string Dish::getFoodName()
{
	return foodName;
}

void Dish::setPortion(string a_Portion)
{
	Portion = a_Portion;
}

string Dish::getPortion()
{
	return Portion;
}

void Dish::setCharge(double a_Charge)
{
	Charge = a_Charge;
}

double Dish::getCharge()
{
	return Charge;
}


double Dish::CalculateCharges()
{
	return 0;
}
