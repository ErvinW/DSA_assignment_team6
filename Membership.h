#pragma once
using namespace std;
#include <iostream>
#include <string>

class Membership
{
private:


public:
	string Status;
	int Point;
	Membership();
	Membership(string, int);
	void setStatus(string);
	string getStatus();
	void setPoint(int);
	int getPoint();
	void EarnPoint(double);
	bool RedeemPoints(int);

};


