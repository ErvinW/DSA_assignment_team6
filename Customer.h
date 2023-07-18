#pragma once
using namespace std;
#include <iostream>
#include <string>
#include "Membership.h"
#include "Order.h"

class Customer
{
private:



public:
	string Name;
	Membership Member;
	Order orderItem;
	Customer();
	Customer(string, Order, Membership);
	void setName(string);
	string getName();
	void setMember(Membership);
	Membership getMembership();
	void setOrder(Order);
	Order getOrder();
};

