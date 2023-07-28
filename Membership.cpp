#include "Membership.h"
using namespace std;
#include <iostream>
#include <string>

Membership::Membership() {}

Membership::Membership(string s, int p) {
	Status = s;
	Point = p;

}

void Membership::setStatus(string s) {
	Status = s;

}
string Membership::getStatus() {
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