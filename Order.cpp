#include"Order.h"

#include<iostream>
#include<string>

Order::Order() {

}

Order::Order(std::string c, /*List<Dish> dL,*/ bool iR, double ch, std::string br) {
	custName = c;
	//DishList = dL;
	isReady = iR;
	Charge = ch;
	branch = br;

}

void Order::setCharge(double ch) {
	Charge = ch;

}
double Order::getCharge() {
	return Charge;

}

void Order::setCustName(std::string c) {
	custName = c;

}
std::string Order::getCustName() {
	return custName;
}

void Order::setDishList(List<std::string> dL) {
	DishList = dL;

}
List<std::string> Order::getDishList() {
	return DishList;

}

void Order::setisReady(bool iR) {
	isReady = iR;

}
bool Order::getisReady() {
	return isReady;

}

void Order::setBranch(std::string br) {
	branch = br;

}

std::string Order::getBranch() {
	return branch;

}

/*
void Order::printDish() {
	for (int i = 0; i < DishList.getLength(); i++) {
		Dish tempDish = DishList.get(i);
		tempDish.print();

	}
}*/

