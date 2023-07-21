#pragma once
using namespace std;
#include <iostream>
#include <string>
#include "List.h"
#include "Dish.h"

class Order
{
private:

public:
	string CustName;//
	bool isReady;
	List<Dish> orderList;
	double Charge; //
	Order();
	Order(bool);
	void setCharge(double);//
	double getCharge(); //
	void setCustName(string);//
	void setisReady(bool);
	void setOrderList(List<Dish> oL);//
	List<Dish> getOrderList();//
	bool getisReady();
	string getCustName(); //
	void addDish(Dish);
	double CalculateTotal();
	void updateStatus(Order order);
	void createOrder(List<Dish> dishes);
};
