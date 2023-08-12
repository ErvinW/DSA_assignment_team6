#pragma once
#include <iostream>
#include <string>



class Dish {
private:
	std::string cuisine;
	std::string foodName;
	//std::string portion;
	double charge;
	double totalRating = 0; // Total rating received
	int ratingCount = 0;    // Number of times the dish has been rated


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
	void setRatingFromLoad(int total, int count);
	int getRatingCount() const;



	void print();


};



