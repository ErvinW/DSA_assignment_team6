#include "Dish.h"
using namespace std;

Dish::Dish() {}

Dish::Dish(string a_cuisine, string a_foodName, string a_portion, double a_charge) {
	cuisine = a_cuisine;
	foodName = a_foodName;
	portion = a_portion;
	charge = a_charge;
}

void Dish::setCuisine(string a_cuisine) {
	cuisine = a_cuisine;
}

string Dish::getCuisine() {
	return cuisine;
}

void Dish::setFoodName(string a_foodName) {
	foodName = a_foodName;
}

string Dish::getFoodName() const {
	return foodName;
}

void Dish::setPortion(string a_portion) {
	portion = a_portion;
}

string Dish::getPortion() const {
	return portion;
}

void Dish::setCharge(double a_charge) {
	charge = a_charge;
}

double Dish::getCharge() const {
	return charge;
}

double Dish::CalculateCharges() {
	return charge;
}

std::ostream& operator<<(std::ostream& os, const Dish& dish) {
	os << dish.getFoodName() << " - " << dish.getPortion() << " - $" << dish.getCharge();
	return os;
}
