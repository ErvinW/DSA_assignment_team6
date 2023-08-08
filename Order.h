#pragma once
#include <iostream>
#include <string>


#include"Dish.h"
#include"List.h"

class Order {
private:

public:
	std::string custName;
	List<Dish> DishList;
	bool isReady;
	double Charge;
	std::string branch;


	Order();
	Order(std::string c, /*List<Dish> dL,*/ bool iR, double ch, std::string br);

	void setCharge(double ch);//
	double getCharge(); //

	void setCustName(std::string c);//
	std::string getCustName(); //

	void setDishList(List<Dish> dL);//
	List<Dish> getDishList();//


	void setisReady(bool iR); //
	bool getisReady(); //

	void setBranch(std::string br);//
	std::string getBranch(); //

	void printDish();

};
