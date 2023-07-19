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
