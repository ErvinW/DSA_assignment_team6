#include "Chinese.h"
using namespace std;
#include <iostream>
#include <string>
#include "Dish.h"

Chinese::Chinese() {}

Chinese::Chinese(string Cuisine, string foodName, string Portion, double Charge) :Dish(Cuisine, foodName, Portion, Charge)
{

}

void Chinese::setpreBooked(bool a_preBooked)
{
    preBooked = a_preBooked;
}

bool Chinese::getpreBooked()
{
    return preBooked;
}

void Chinese::setDrink(bool a_Drink)
{
    Drink = a_Drink;
}

bool Chinese::getDrink()
{
    return Drink;
}

double Chinese::CalculateCharges()
{
    if (preBooked == true && Drink == true)
    {
        double chargePerday = getCharge() + 30;
        return chargePerday;
    }

    else if (Drink == true)
    {
        double chargePerday = getCharge() + 10;
        return chargePerday;
    }

    else if (preBooked == true)
    {
        double chargePerday = getCharge() + 20;
        return chargePerday;
    }

    else
    {
        return getCharge();
    }
}
