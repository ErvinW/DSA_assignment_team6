#include "Order.h"
using namespace std;
#include <iostream>
#include <string>

Order::Order()
{

}

Order::Order(bool a_isReady)
{
    isReady = a_isReady;
}

void Order::setisReady(bool a_isReady)
{
    isReady = a_isReady;
}

bool Order::getisReady()
{
    return isReady;
}

void Order::addDish(Dish dish)
{
    orderList.add(dish);
}

double Order::CalculateTotal()
{
    double total = 0;

    for (auto d : orderList)
    {
        total += d.CalculateCharges();
    }

    return total;
}

void updateStatus(Order order) {
    order.isReady = true;
}

void Order::createOrder(List<Dish> dishes)
{
    isReady = false;
    for (auto dish : dishes)
    {
        addDish(dish);
    }
}

/// /// ///
void Order::setCustName(string n) {
    CustName = n;

}

string Order::getCustName() {
    return CustName;

}

/// /// ///
void Order::setOrderList(List<Dish> oL) {
    orderList = oL;

}



List<Dish> Order::getOrderList() {
    return orderList;

}

/// /// ///
void Order::setCharge(double c) {
    Charge = c;
}

double Order::getCharge() {
    return Charge;

}