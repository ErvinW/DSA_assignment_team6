#include "Customer.h"
#include <iostream>
#include <string>
#include "Membership.h"
#include "Order.h"

Customer::Customer() {}

Customer::Customer(string n, string p, List<Order> OL, Membership m) {
	Name = n;
	Password = p;
	oL = OL;
	Member = m;
}

void Customer::setName(string n) {
	Name = n;

}
string Customer::getName() {
	return Name;

}

void Customer::setPassword(string p) {
	Password = p;

}
string Customer::getPassword() {
	return Password;

}

void Customer::setMember(Membership m) {
	Member = m;

}
Membership Customer::getMembership() {
	return Member;

}

void Customer::setOrder(Order oI) {
	orderItem = oI;

}
Order Customer::getOrder() {
	return orderItem;

}