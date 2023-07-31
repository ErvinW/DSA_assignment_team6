#include"Order.h"

using namespace std;
#include<iostream>
#include<string>

Order::Order() {

}

Order::Order(string c, List<Dish> oL, bool iR, double ch) {
	custName = c;
	orderList = oL;
	isReady = iR;
	Charge = ch;

}

void Order::setCharge(double ch) {
	Charge = ch;

}
double Order::getCharge() {
	return Charge;

}

void Order::setCustName(string c) {
	custName = c;

}
string Order::getCustName() {
	return custName;
}

void Order::setOrderList(List<Dish> oL) {
	orderList = oL;

}
List<Dish> Order::getOrderList() {
	return orderList;

}


void Order::setisReady(bool iR) {
	isReady = iR;

}
bool Order::getisReady() {
	return isReady;

}

void Order::setBranch(string br) {
	branch = br;

}

string Order::getBranch() {
	return branch;

}