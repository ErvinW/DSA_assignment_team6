#pragma once
#include <iostream>
#include <string>

class Membership
{
private:


public:
	std::string Status;
	int Point;

	Membership();
	Membership(std::string s, int p);

	void setStatus();
	std::string getStatus();

	void setPoint(int p);
	int getPoint();

	void EarnPoint(int d);
	bool RedeemPoints(int pt);
	std::string status();
	void print();

};

