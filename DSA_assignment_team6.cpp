// DSA_ASG2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include<fstream>
#include<sstream>
#include <iomanip>
#include <cctype>
#include <algorithm>

#include "Admin.h"
#include "Customer.h"
#include "Dish.h"
#include "List.h"
#include "Membership.h"
#include "Order.h"
#include "Queue.h"
#include "Dictionary.h"
#include "DishDict.h"

Dictionary customerDict;
DishDict dishDict;
List<std::string> dishList;
List<Admin> adminList;
List<std::string> CustNames;



Queue queue1;
Queue queue2;
Queue queue3;


Customer sessionStorage;
Admin sessionAdmin;
std::string currentBranch;

using namespace std;


//------------- Input validation -------------//

bool check(std::string s) {

    try {
        int tryInt = std::stoi(s);
        return true;
    }

    catch (std::invalid_argument& e) {
        return false;
    }
}

bool checkstring(std::string str) {


    try {
        std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {return std::tolower(c); });
        return true;

    }

    catch (std::invalid_argument& e) {
        return false;

    }
}
//------------- Initialise data -------------//

void initCustomer() {

    std::ifstream inFile("Customer.csv");
    if (!inFile) {
        std::cerr << "Error opening Customer.csv for reading." << std::endl;
        return;
    }

    std::string line;

    while (getline(inFile, line)) {
        std::istringstream iss(line);
        std::string name, password, status;
        int points;
        if (getline(iss, name, ',') && getline(iss, password, ',') && getline(iss, status, ',') && (iss >> points)) {
            Membership member = Membership(status, points);
            Customer newCustomer = Customer(name, password, member);
            customerDict.add(name, newCustomer);
            CustNames.add(name);
        }
    }

}

void initDishList() {
    std::ifstream inFile("Dishes.csv");
    if (!inFile) {
        std::cerr << "Error opening Customer.csv for reading." << std::endl;
        return;
    }

    std::string line;
    while (getline(inFile, line)) {
        std::istringstream iss(line);
        std::string c, n;
        double ch;
        if (getline(iss, c, ',') && getline(iss, n, ',') && (iss >> ch)) {
            Dish newDish = Dish(c, n, ch);
            dishList.add(n);
            dishDict.add(n, newDish);

        }
    }
}

void initAdmins() {
    adminList.add(Admin("Adm1", "PassAdm1", 1));
    adminList.add(Admin("Adm2", "PassAdm2", 2));
    adminList.add(Admin("Adm3", "PassAdm3", 3));
}




//------------- Login functions -------------//

bool userLogin() {
    std::string userName;
    std::string password;

    std::cout << "Enter username: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, userName);


    std::cout << "Enter password: ";
    std::cin >> password;
    std::cout << "" << std::endl;

    Customer cust = customerDict.get(userName);

    if (cust.getName() == userName && cust.getPassword() == password) {
        sessionStorage = cust;
        return true;

    }

    else {
        return false;
    }
}



bool AdminLogin() {
    std::string userName;
    std::string password;

    std::cout << "Enter username: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, userName);

    std::cout << "Enter password: ";
    std::cin >> password;
    std::cout << "" << std::endl;

    for (int i = 0; i < adminList.getLength(); i++) {
        Admin tempAdmin = adminList.get(i);
        if (userName == tempAdmin.getUsername() && password == tempAdmin.getPassword()) {

            sessionAdmin = tempAdmin;
            return true;

        }
        else {

        }

    }
    return false;
}


bool regUser() {

    std::string customerName;
    std::string custPassword;

    std::cout << "Please enter your name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, customerName);
    std::cout << "Please enter your password: ";
    std::cin >> custPassword;
    bool isNewUser = true;

    for (int i = 0; i < CustNames.getLength(); i++)
    {
        std::string c = CustNames.get(i);
        Customer tempC = customerDict.get(c);

        if (tempC.getName() == customerName)
        {
            std::cout << "Username already taken, try another name. You can try " << tempC.getName() << "123123 instead" << std::endl;
            std::cout << "" << std::endl;
            isNewUser = false;
            return isNewUser; //

            //break;
        }
    }


    if (isNewUser == true) {

        int memberPoint = 0;
        std::string memberStatus = "Ordinary";
        Membership member = Membership(memberStatus, memberPoint);

        Customer newCust;
        newCust.setName(customerName);
        newCust.setPassword(custPassword);
        newCust.setMember(member);

        customerDict.add(customerName, newCust);

        std::ofstream file("Customer.csv", std::ios::app); // Open file in append mode

        if (!file.is_open()) {
            std::cerr << "Error opening file: Customer.csv" << std::endl;
        }

        file << customerName << "," << custPassword << ","
            << memberStatus << "," << memberPoint << std::endl;

        file.close();
        return true; //
    }

}


//-------------- View functions -------------//

void viewAllDishes() {

    for (int i = 0; i < dishList.getLength(); i++) {
        std::string name = dishList.get(i);
        Dish tempD = dishDict.get(name);
        std::cout << i + 1 << ". ";
        tempD.print();
    }

}

void viewBy() {
    std::string s;
    std::cout << "Enter category to sort by [3 to exit]: ";
    std::cin >> s;
    if (s == "3") {

    }
    bool cString = checkstring(s);
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {return std::tolower(c); });
    if (cString == true) {
        for (int x = 0; x < dishList.getLength(); x++) {
            std::string tDish = dishList.get(x);
            Dish tempD = dishDict.get(tDish);
            if (tempD.getCuisine() == s || tempD.getFoodName() == s) {
                tempD.print();

            }

            else {

            }
        }
    }
}






//------------- UI functions -------------//
std::string userPage(Customer cust) {

    std::string option;

    std::cout << "+--------------- Welcome ---------------+" << std::endl;
    cust.print();
    std::cout << "+---------------------------------------+" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "[1] View Menu" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "[2] Place an order" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "[3] Cancel an order" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "[4] View invoice" << std::endl;
    std::cout << std::endl;
    std::cout << "[5] Exit" << std::endl;
    std::cout << std::endl;

    std::cin >> option;
    return option;
}


std::string adminPage(Admin admin) {

    std::string option;

    std::cout << "+---------------Welcome " << admin.getUsername() << "---------------+" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "[1] View orders" << std::endl;

    std::cin >> option;
    return option;
}


void ViewMenu() {
    while (true) {
        std::cout << "+---------------+---------------+" << std::endl;
        std::cout << "1. View all dishes" << std::endl;
        std::cout << "2. Search for dish" << std::endl;
        std::cout << "3. Back" << std::endl;
        std::string option;
        std::cin >> option;

        if (option == "1") {
            viewAllDishes();
        }

        else if (option == "2") {
            viewBy();
            //search (Additional feature)
        }

        else if (option == "3") {
            break;

        }

        else {
            std::cout << "Invalid input" << std::endl;
            std::cout << "+---------------+---------------+" << std::endl;
        }
    }
}

void cancelOrder()
{
    List<Order> tempList;
    while (!queue1.isEmpty())
    {
        Order order;
        queue1.dequeue(order);

        if (order.getCustName() == sessionStorage.getName())
        {
            tempList.add(order);
            
        }
        else
        {
            queue1.enqueue(order);
        }
    }

    if (tempList.isEmpty())
    {
        cout << "You have not made an order" << endl;
        return;
    }

    for (int i = 0; i < tempList.getLength(); i++)
    {
        auto order = tempList.get(i);
        cout << "[" << i + 1 << "] " << order.getCustName() << " $" << order.getCharge() << endl;
    }

    int choice;
    cout << "Please select an order to cancel: ";
    cin >> choice;

    if (choice >= 1 && choice <= tempList.getLength())
    {
        tempList.remove(choice - 1);
        cout << "Order has been canceled" << endl;
    }
    else
    {
        cout << "Invalid choice" << endl;
    }

    for (int i = 0; i < tempList.getLength(); i++)
    {
        queue1.enqueue(tempList.get(i));
    }
    /*if (currentBranch == "1")
    {
        while (!queue1.isEmpty())
        {
            Order order;
            queue1.dequeue(order);

            if (order.getCustName() == sessionStorage.getName())
            {
                tempList.add(order);
            }
            else
            {
                queue1.enqueue(order);
            }
        }

        if (tempList.isEmpty())
        {
            cout << "You have not made an order" << endl;
            return;
        }

        for (int i = 0; i < tempList.getLength(); i++)
        {
            auto order = tempList.get(i);
            cout << "[" << i + 1 << "] " << order.getCustName() << " $" << order.getCharge() << endl;
        }

        int choice;
        cout << "Please select an order to cancel: ";
        cin >> choice;

        if (choice >= 1 && choice <= tempList.getLength())
        {
            tempList.remove(choice - 1);
            cout << "Order has been canceled" << endl;
        }
        else
        {
            cout << "Invalid choice" << endl;
        }

        for (int i = 0; i < tempList.getLength(); i++)
        {
            queue1.enqueue(tempList.get(i));
        }
    }
    else if (currentBranch == "2")
    {
        while (!queue1.isEmpty())
        {
            Order order;
            queue2.dequeue(order);

            if (order.getCustName() == sessionStorage.getName())
            {
                tempList.add(order);
            }
            else
            {
                queue2.enqueue(order);
            }
        }

        if (tempList.isEmpty())
        {
            cout << "You have not made an order" << endl;
            return;
        }

        for (int i = 0; i < tempList.getLength(); i++)
        {
            auto order = tempList.get(i);
            cout << "[" << i + 1 << "] " << order.getCustName() << " $" << order.getCharge() << endl;
        }

        int choice;
        cout << "Please select an order to cancel: ";
        cin >> choice;

        if (choice >= 1 && choice <= tempList.getLength())
        {
            tempList.remove(choice - 1);
            cout << "Order has been canceled" << endl;
        }
        else
        {
            cout << "Invalid choice" << endl;
        }

        for (int i = 0; i < tempList.getLength(); i++)
        {
            queue2.enqueue(tempList.get(i));
        }
    }
    else if (currentBranch == "3")
    {
        while (!queue1.isEmpty())
        {
            Order order;
            queue3.dequeue(order);

            if (order.getCustName() == sessionStorage.getName())
            {
                tempList.add(order);
            }
            else
            {
                queue3.enqueue(order);
            }
        }

        if (tempList.isEmpty())
        {
            cout << "You have not made an order" << endl;
            return;
        }

        for (int i = 0; i < tempList.getLength(); i++)
        {
            auto order = tempList.get(i);
            cout << "[" << i + 1 << "] " << order.getCustName() << " $" << order.getCharge() << endl;
        }

        int choice;
        cout << "Please select an order to cancel: ";
        cin >> choice;

        if (choice >= 1 && choice <= tempList.getLength())
        {
            tempList.remove(choice - 1);
            cout << "Order has been canceled" << endl;
        }
        else
        {
            cout << "Invalid choice" << endl;
        }

        for (int i = 0; i < tempList.getLength(); i++)
        {
            queue3.enqueue(tempList.get(i));
        }
    
    }*/
}


void CheckOut()
{

}



//some prob here//
void CreateOrder() {

    double charge = 0;
    List<std::string> tempDL;
    Order tempOrder;


    while (true) {

        std::cout << "+---------------Order Page---------------+" << std::endl;
        viewAllDishes();
        std::cout << "+----------------------------------------+" << std::endl;
        std::cout << "[1] Add Dish" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "[2] Finish Add Dish" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "[3] Cancel" << std::endl;
        std::cout << "" << std::endl;


        std::string option;
        std::cout << "Please enter an option: ";
        std::cin >> option;

        if (option == "1") {

            std::string choice;
            std::cout << "Please enter the index of a dish: ";
            std::cin >> choice;
            bool isNum = check(choice);

            if (isNum == true) {
                int iChoice = std::stoi(choice);
                std::string tDish = dishList.get(iChoice - 1);
                Dish toAdd = dishDict.get(tDish);
                tempDL.add(tDish);
                charge += toAdd.getCharge();
            }

            else {
                std::cout << "Invalid input" << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
            }
        }

        else if (option == "2") {

            tempOrder.setCustName(sessionStorage.getName());
            tempOrder.setDishList(tempDL);
            tempOrder.setCharge(charge);
            tempOrder.setisReady(false);
            queue1.enqueue(tempOrder);
            List<std::string> tDL = tempOrder.getDishList();
            int L = tDL.getLength();

            for (int i = 0; i < L; i++) {
                std::string dish = tDL.get(i);
                Dish d = dishDict.get(dish);
                d.print();
            }

            queue1.enqueue(tempOrder);
            std::cout << std::endl;
            std::cout << tempOrder.getCharge() << std::endl;
            /*if (currentBranch == "1")
            {
                
            }
            else if (currentBranch == "2")
            {
                queue2.enqueue(tempOrder);
            }
            else
            {
                queue3.enqueue(tempOrder);
            }*/

            break;

        }

        else 
        {
            break;
        }

    }


}
//-------------------------------------------//







void mainMenu() {

    std::cout << "+---------------Welcome To  Restaurant---------------+" << std::endl;
    std::cout << "1. User Login" << std::endl; //OK
    std::cout << "" << std::endl;
    std::cout << "2. Admin Login" << std::endl; //OK
    std::cout << "" << std::endl;
    std::cout << "3. Register User" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "4. View Incoming Orders" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "5. Check Out" << endl;
    std::cout << "" << std::endl;
    std::cout << "6. Exit app" << std::endl; //OK
    std::cout << std::endl;
    std::cout << "Please choose your role: ";

    std::string option;
    std::cin >> option;
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;

    if (option == "1") {
        bool login = userLogin();
        if (login == true) {
            bool loop = true; //
            while (loop) {
                std::string choice = userPage(sessionStorage);

                if (choice == "1") {
                    ViewMenu();
                }

                else if (choice == "2") {
                    CreateOrder();
                }

                else if (choice == "3") {
                    cancelOrder();
                }

                else if (choice == "4") {

                }
                
                else if (choice == "5")
                {

                }

                else if (choice == "6") {

                    std::cout << std::endl;
                    std::cout << std::endl;
                    std::cout << "Logging out" << std::endl;
                    loop = false; // 
                    mainMenu();

                }

                else {

                    std::cout << "Invalid input try again" << std::endl;

                }

            }
        }

        else {
            std::cout << "Incorrect username/password try again" << std::endl;
        }
    }

    else if (option == "2") {
        //admin login
        bool aLogin = AdminLogin();
        if (aLogin == true) {
            while (true) {
                std::string choice = adminPage(sessionAdmin);

                if (choice == "1") {
                    //view orders
                }

                else {
                    std::cout << "Invalid option, try again. " << std::endl;
                    adminPage(sessionAdmin);


                }
            }
        }

        else {
            std::cout << "Incorrect username/password try again" << std::endl;
        }
    }

    else if (option == "3") {
        bool reg = regUser();
        if (reg == true) {
            std::cout << "Account Created!" << std::endl;
            mainMenu();
        }

        else {
            mainMenu();
        }
    }

    else if (option == "4") {

        std::cout << "Exiting app... goodbye..." << std::endl;

    }

    else {

        std::cout << "Invalid input. Try again." << std::endl;
        mainMenu();

    }

}












//------------------------------------------//

int main()
{
    initCustomer();
    initDishList();
    initAdmins();


    mainMenu();


}

