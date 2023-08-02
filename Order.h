#pragma once
#include <iostream>
#include <string>


#include"Dish.h"
#include"List.h"


using namespace std;

class Order {
private:

public:
	string custName;
	List<Dish> orderList;
	bool isReady;
	double Charge;
	string branch;


	Order();
	Order(string c, List<Dish> oL, bool iR, double ch, string br);

	void setCharge(double ch);//
	double getCharge(); //

	void setCustName(string c);//
	string getCustName(); //

	void setOrderList(List<Dish> oL);//
	List<Dish> getOrderList();//


	void setisReady(bool iR); //
	bool getisReady(); //

	void setBranch(string br);//
	string getBranch(); //

	void viewIncomingOrders(int index = 0);
};
