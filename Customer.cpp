#include "Customer.h"
#include <iostream>
#include <string>
#include "Membership.h"


Customer::Customer() {}

Customer::Customer(std::string n, std::string p, Membership m) {
	Name = n;
	Password = p;
	Member = m;
}

void Customer::setName(std::string n) {
	Name = n;

}
std::string Customer::getName() {
	return Name;

}

void Customer::setPassword(std::string p) {
	Password = p;

}
std::string Customer::getPassword() {
	return Password;

}

void Customer::setMember(Membership m) {
	Member = m;

}
Membership Customer::getMembership() {
	return Member;

}

void Customer::print() {
	std::cout << "Name: " << Name << "\n";
	Member.print();

}