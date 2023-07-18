#include "Western.h"
using namespace std;
#include <iostream>
#include <string>
#include "Dish.h"

Western::Western() {}

Western::Western(string Cuisine, string foodName, string Portion, double Charge) : Dish(Cuisine, foodName, Portion, Charge)
{

}

void Western::setAlcohol(bool a_Alcohol)
{
    Alcohol = a_Alcohol;
}

bool Western::getAlcohol()
{
    return Alcohol;
}


double Western::CalculateCharges()
{
    if (Alcohol == true)
    {
        double chargePerday = getCharge() + 50;
        return chargePerday;
    }
    else
    {
        return getCharge();
    }
}

