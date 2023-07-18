#include "Membership.h"
using namespace std;
#include <iostream>
#include <string>

Membership::Membership() {}

Membership::Membership(string a_Status, int a_Point)
{
	Status = a_Status;
	Point = a_Point;
}

void Membership::setStatus(string a_Status)
{
	Status = a_Status;
}

string Membership::getStatus()
{
	return Status;
}

void Membership::setPoint(int a_Point)
{
	Point = a_Point;
}

int Membership::getPoint()
{
	return Point;
}

void Membership::EarnPoint(double amt)
{
	int pointsEarned = static_cast<int>(amt) / 10;
	Point += pointsEarned;
	if (Point < 100)
	{
		Status = "Ordinary";
	}
	else if (Point >= 100 && Point < 200 && Status == "Ordinary")
	{
		Status = "Sliver";
	}
	else if (Point >= 200 && Status == "Sliver")
	{
		Status = "Gold";
	}
}

bool Membership::RedeemPoints(int points)
{
	Point -= points;
	return true;
}
