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

std::string Membership::status() {
	std::string currentStatus = getStatus(); // Assuming there's a getStatus function
	if (getPoint() >= 20 && (currentStatus == "Ordinary" || currentStatus == "Silver")) {
		return "Gold";
	}
	else if (getPoint() >= 10 && currentStatus == "Ordinary") {
		return "Silver";
	}
	else {
		return currentStatus; // The status remains the same if conditions are not met
	}
}

void Membership::print() {

	std::cout << "Member: " << Status << "\nPoints: " << Point << std::endl;

}