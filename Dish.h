#pragma once
#include <iostream>
#include <string>



class Dish {
private:
	std::string cuisine;
	std::string foodName;
	//std::string portion;
	double charge;
	double totalRating; // Total rating received
	int ratingCount;    // Number of times the dish has been rated
	double averageRating;

public:
	Dish();
	Dish(std::string c, std::string fN, double ch);

	void setCuisine(std::string c);
	std::string getCuisine();

	void setFoodName(std::string fN);
	std::string getFoodName();

	/*void setPortion(std::string p);
	std::string getPortion();*/

	void setCharge(double ch);
	double getCharge();

	// Add a rating and update the total rating
	void addRating(int rating);

	double getAverageRating() const;

	void setAverageRating(double rating);


	void print();


};



