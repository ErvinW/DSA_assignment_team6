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

void Membership::EarnPoint(double amt)
{
	if (Status == "Ordinary")
	{
		double pointsEarned = amt * 0.1;
		Point += ceil(pointsEarned);
	}
	else if (Status == "Silver")
	{
		double pointsEarned = amt * 0.2;
		Point += ceil(pointsEarned);
	}
	else if (Status == "Gold")
	{
		double pointsEarned = amt * 0.25;
		Point += ceil(pointsEarned);
	}
}

bool Membership::RedeemPoints(int pt) {
	if (Point < 0)
	{
		return false;
	}
	else
	{
		Point -= pt;
		setPoint(Point);
		return true;
	}
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