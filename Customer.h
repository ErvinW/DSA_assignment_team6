
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
	string Password;
	Membership Member;
	Order orderItem;

	Customer();
	Customer(string n, string p, Order oI, Membership m);

	void setName(string n);
	string getName();

	void setPassword(string p);
	string getPassword();

	void setMember(Membership m);
	Membership getMembership();

	void setOrder(Order o);
	Order getOrder();
};