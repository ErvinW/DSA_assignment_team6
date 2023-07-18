#include "Customer.h"
#include <iostream>
#include <string>
#include "Membership.h"
#include "Order.h"


Customer::Customer() {}

Customer::Customer(string a_Name, Order a_Order, Membership a_Membership)
{
	Name = a_Name;
	orderItem = a_Order;
	Member = a_Membership;

}

void Customer::setName(string a_Name)
{
	Name = a_Name;

}

string Customer::getName()
{
	return Name;
}

void Customer::setMember(Membership a_Membership)
{
	Member = a_Membership;
}

Membership Customer::getMembership()
{
	return Member;
}

void Customer::setOrder(Order a_Order)
{
	orderItem = a_Order;
}

Order Customer::getOrder()
{
	return orderItem;
}