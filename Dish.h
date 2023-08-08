#pragma once
#include <iostream>
#include <string>



class Dish {
private:
	std::string cuisine;
	std::string foodName;
	//std::string portion;
	double charge;
	//double rating;
	//double ratingNum;

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


	void print();


};



