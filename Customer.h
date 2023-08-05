
#pragma once
using namespace std;
#include <iostream>
#include <string>
#include "Membership.h"
#include "Order.h"
#include "List.h"


class Customer
{
private:



public:
	string Name;
	string Password;
	Membership Member;
	Order orderItem;
	List<Order> oL;

	Customer();
	Customer(string n, string p, List<Order> OL, Membership m);

	void setName(string n);
	string getName();

	void setPassword(string p);
	string getPassword();

	void setMember(Membership m);
	Membership getMembership();

	void setOrderList(List<Order> OL);
	List<Order> getOrderList();
};