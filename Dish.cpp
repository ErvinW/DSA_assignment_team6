#include "Dish.h"


Dish::Dish() {}

Dish::Dish(std::string c, std::string fN, double ch) {
	cuisine = c;
	foodName = fN;
	//portion = p;
	charge = ch;
	totalRating = 0;
	ratingCount = 0;
}

void Dish::setCuisine(std::string c) {
	cuisine = c;
}

std::string Dish::getCuisine() {
	return cuisine;
}

void Dish::setFoodName(std::string fN) {
	foodName = fN;
}

std::string Dish::getFoodName() {
	return foodName;
}

/*void Dish::setPortion(std::string p) {
	portion = p;
}

std::string Dish::getPortion() {
	return portion;
}*/

void Dish::setCharge(double ch) {
	charge = ch;
}

double Dish::getCharge() {
	return charge;
}




double Dish::getAverageRating() const {
	if (ratingCount == 0) return 0.0; // To prevent division by zero
	return static_cast<double>(totalRating) / ratingCount;
}



void Dish::addRating(int rating) {
	totalRating += rating;
	ratingCount++;
}

void Dish::setRatingFromLoad(int total, int count) {
	totalRating = total;
	ratingCount = count;
}

int Dish::getRatingCount() const {
	return ratingCount;
}

void Dish::print() {
	std::cout << foodName << "-----Price: " << charge << std::endl;
}