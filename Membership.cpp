#include "Membership.h"
#include <iostream>
#include <string>

Membership::Membership() {}

Membership::Membership(std::string s, int p) {
	Status = s;
	Point = p;

}

void Membership::setStatus(std::string s) {
	Status = s;

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

double Membership::EarnPoint(int d) {
	return Point += d;

}
bool Membership::RedeemPoints(int pt) {
	if (Point <= pt) {
		return false;

	}

	else {
		return true;
	}
}

void Membership::print() {

	std::cout << "Member: " << Status << "\nPoints: " << Point << std::endl;

}