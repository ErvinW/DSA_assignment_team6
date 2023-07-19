#include "Admin.h"
using namespace std;
#include <iostream>
#include <string>


Admin::Admin() {}

Admin::Admin(string a_Name, Order a_orderItem)
{
	Name = a_Name;
	orderItem = a_orderItem;
}

void Admin::setName(string a_Name)
{
	Name = a_Name;
}

string Admin::getName()
{
	return Name;
}

void Admin::setorderItem(Order a_orderItem)
{
	orderItem = a_orderItem;
}

Order Admin::getorderItem()
{
	return orderItem;
}
