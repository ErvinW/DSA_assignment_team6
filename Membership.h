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

	void setStatus(std::string s);
	std::string getStatus();

	void setPoint(int p);
	int getPoint();

	double EarnPoint(int d);
	bool RedeemPoints(int pt);

	void print();

};

