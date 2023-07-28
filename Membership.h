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
	Membership(string s, int p);
	void setStatus(string s);
	string getStatus();
	void setPoint(int p);
	int getPoint();
	double EarnPoint(int d);
	bool RedeemPoints(int pt);

};
