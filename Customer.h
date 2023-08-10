#pragma once
#include <iostream>
#include <string>
#include "Membership.h"



class Customer
{
private:



public:
	std::string Name;
	std::string Password;
	Membership Member;


	Customer();
	Customer(std::string n, std::string p,  Membership m);

	void setName(std::string n);
	std::string getName() ;

	void setPassword(std::string p);
	std::string getPassword();

	void setMember(Membership m);
	Membership getMembership();


	void print();


};