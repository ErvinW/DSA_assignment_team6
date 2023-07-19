#pragma once
using namespace std;
#include <iostream>
#include <string>
#include "Order.h"

class Admin
{
private:

public:
	string Name;
	Order orderItem;
	

	Admin();
	Admin(string);
	void setName(string);
	string getName();
	void setorderItem(Order);
	Order getorderItem();
};

