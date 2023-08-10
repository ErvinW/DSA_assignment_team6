#include "Membership.h"
#include <iostream>
#include <string>
#include <cmath>

Membership::Membership() {}

Membership::Membership(std::string s, int p) {
	Status = s;
	Point = p;

}

void Membership::setStatus() {
	Status = status();

}
std::string Membership::getStatus() {
	return Status;

}

void Membership::setPoint(int p) {
	Point = p;

}
int Membership::getPoint() {
	return Point;
}

void Membership::EarnPoint(int amt)
{
	double pointsEarned = amt * 0.1;
	Point += llround(pointsEarned);
}

bool Membership::RedeemPoints(int pt) {
	int minus = Point -= pt;
	if (Point < 0)
	{
		Point += pt;
		return false;
	}
	setPoint(minus);
	return true;
}

std::string Membership::status()
{
	if (getStatus() == "Silver" || getStatus() == "Gold")
	{
		return getStatus();  // Keep Silver or Gold status even if points are less than 10
	}
	else if (getPoint() < 10)
	{
		return "Ordinary";
	}
	else if (getPoint() >= 10 && getPoint() < 20)
	{
		return "Silver";
	}
	else if (getPoint() >= 20)
	{
		return "Gold";
	}
}

void Membership::print() {

	std::cout << "Member: " << Status << "\nPoints: " << Point << std::endl;

}