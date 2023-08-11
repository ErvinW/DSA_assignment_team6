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
List<Order> OrderList;




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

void ClearQueue() {

    while (!queue1.isEmpty()) {
        Order Io = queue1.getFront();
        queue1.dequeue(Io);
    }

    while (!queue2.isEmpty()) {
        Order Io2 = queue2.getFront();
        queue2.dequeue(Io2);
    }

    while (!queue1.isEmpty()) {
        Order Io3 = queue3.getFront();
        queue3.dequeue(Io3);
    }
}

void Queuing() {

    ClearQueue();

    for (int x = 0; x < OrderList.getLength(); x++) {
        Order order = OrderList.get(x);
        std::string branch = order.getBranch();

        if (branch == "1") {
            queue1.enqueue(order);

        }

        else if (branch == "2") {
            queue2.enqueue(order);

        }

        else if (branch == "3") {
            queue3.enqueue(order);

        }

        else {

        }
    }
}

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

void viewInvoice(Customer cust) {

    for (int i = 0; i < OrderList.getLength(); i++) {

        Order order = OrderList.get(i);

        if (order.getCustName() == cust.getName()) {
            std::cout << "--------------- Order " << i + 1 << " ---------------" << std::endl;

            List<std::string> DL = order.getDishList();

            for (int x = 0; x < DL.getLength(); x++) {

                Dish dish = dishDict.get(DL.get(x));
                dish.print();

                

            }
            std::cout << "Total: $" << order.getCharge() << std::endl;
            std::cout << "--------------------------------------" << std::endl;
        }

        std::cout << endl;
        std::cout << endl;

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
    std::cout << "[5] Edit order" << std::endl;
    std::cout << std::endl;
    std::cout << "[6] Check Out" << std::endl;
    std::cout << std::endl;
    std:cout  << "[7] Check order status" << std::endl;
    std::cout << std::endl;
    std::cout << "[8] Exit" << std::endl;
    std::cout << std::endl;
   

    std::cin >> option;
    return option;
}


std::string adminPage(Admin admin) {

    std::string option;

    std::cout << "+---------------Welcome " << admin.getUsername() << "---------------+" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "[1] View incoming orders" << std::endl;
    std::cout << "[2] Update order status" << std::endl;
    std::cout << "[3] Exit" << std::endl;
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

void CancelOrder()
{   
    List<Order> tempList;
    List<Order> tempList2;
    
    if (queue1.isEmpty())
    {
        std::cout << "You have not made an order" << endl;
        return;
    }
    // Move from Queue to List
    int queueSize = queue1.getLength(); // Get the initial queue size

    for (int i = 0; i < queueSize; i++) {
        Order tempOrder;
        queue1.dequeue(tempOrder);
        tempList.add(tempOrder);
    }

    
    int numOrder = 0;
    int length = tempList.getLength();

    for (int i = 0; i < length; i++)
    {
        auto order = tempList.get(i);
        if (order.getisReady() == true)
        {
            cout << "Order Status: true" << endl;
        }
        else
        {
            cout << "Order Status: false" << endl;
        }

        if (order.getisReady() == true)
        {
            break;
        }
        else if (order.getCustName() == sessionStorage.getName() && order.getisReady() == false)
        {
            tempList2.add(order);

            std::cout << "[" << i + 1 << "] " << order.getCustName() << " $" << order.getCharge() << endl;
        }
    }

    if (tempList2.isEmpty() != true)
    {
        int choice;
        std::cout << "Please select an order to cancel: ";
        std::cin >> choice;

        if (choice >= 1 && choice <= tempList.getLength())
        {
            tempList.remove(choice - 1);
            std::cout << "Order has been canceled" << endl;
        }
        else
        {
            std::cout << "Invalid choice" << endl;
        }

        if (tempList.isEmpty() != true)
        {
            for (int i = 0; i < tempList.getLength();i++)
            {
                queue1.enqueue(tempList.get(i));
            }
            tempList.clear();
            queue1.displayItems();
        }
    }    
    else
    {
        if (tempList.isEmpty() != true)
        {
            for (int i = 0; i < tempList.getLength();i++)
            {
                queue1.enqueue(tempList.get(i));
            }
            tempList.clear();
            tempList2.clear();
            std::cout << "Your order is preparing please wait" << endl;
            queue1.displayItems();
        }
        else
        {
            cout << "You have not make an order" << endl;
        }
    }    
}


void CheckOut()
{
    List<Order> tempList;
    List<Order> tempList2;

    if (queue1.isEmpty())
    {
        std::cout << "You have not made an order" << endl;
        return;
    }
    // Move from Queue to List
    int queueSize = queue1.getLength(); // Get the initial queue size

    for (int i = 0; i < queueSize; i++) {
        Order tempOrder;
        queue1.dequeue(tempOrder);
        tempList.add(tempOrder);
    }


    int numOrder = 0;
    int totalCharge = 0;
    int payment;
    string decision;
    int length = tempList.getLength();


    for (int i = length - 1; i >= 0; i--)
    {
        auto order = tempList.get(i);
        
        if (order.getisReady() == true)
        {
            cout << "Order Status: true" << endl;
        }
        else
        {
            cout << "Order Status: false" << endl;
        }

        if (order.getisReady() == false)
        {
            break;
        }
        else if(order.getCustName() == sessionStorage.getName() && order.getisReady() == true)
        {
            tempList2.add(order);
        }
    }
    if (tempList2.isEmpty() != true)
    {
        for (int i = length - 1; i >= 0; i--)
        {
            auto order = tempList.get(i);
            if (order.getCustName() == sessionStorage.getName() && order.getisReady() == true)
            {

                totalCharge += order.getCharge();
                tempList.remove(i);
            }
        }

        viewInvoice(sessionStorage);
        std::cout << "$Total Amount: " << totalCharge << endl;
        std::cout << "" << endl;
        while (true)
        {
            while (true)
            {

                int point;
                std::cout << "Current Point: " << sessionStorage.Member.getPoint() << endl;
                std::cout << "Do you want use point[Y/N] ";
                std::cin >> decision;
                if (decision == "N")
                {
                    break;
                }
                else if (decision == "Y")
                {
                    int currentPoint = sessionStorage.Member.getPoint();
                    if (currentPoint == 0)
                    {
                        std::cout << "You have 0 point" << endl;
                        std::cout << "" << endl;
                        break;
                    }
                    else
                    {
                        while (true)
                        {
                            std::cout << "Please enter point: ";
                            std::cin >> point;
                            if (sessionStorage.Member.RedeemPoints(point) == false)
                            {
                                std::cout << "Insufficient Points" << endl;

                            }
                            else
                            {
                                totalCharge -= point;
                                std::cout << "Successful Redeem Points" << endl;

                                break;
                            }
                        }
                        break;
                    }
                }
                else
                {
                    std::cout << "Invalid Input" << endl;
                }
            }
            std::cout << "" << endl;
            while (true)
            {
                std::cout << "$Total Amount: " << totalCharge << endl;
                std::cout << "Enter Payment amount: ";
                std::cin >> payment;
                std::cout << "" << endl;

                if (payment < totalCharge)
                {
                    std::cout << "Payment unsuccessful" << endl;
                }
                else
                {
                    std::cout << "Payment successful" << endl;
                    break;
                }
            }
            break;
        }

        sessionStorage.Member.EarnPoint(totalCharge);
        sessionStorage.Member.setStatus();

        if (tempList.isEmpty() != true)
        {
            for (int i = 0; i < tempList.getLength();i++)
            {
                queue1.enqueue(tempList.get(i));
            }
            tempList.clear();
            tempList2.clear();
            queue1.displayItems();
        }
    }
    else
    {
        if (tempList.isEmpty() != true)
        {
            for (int i = 0; i < tempList.getLength();i++)
            {
                queue1.enqueue(tempList.get(i));
            }
            tempList.clear();
            tempList2.clear();
            std::cout << "Your order is preparing please wait" << endl;
            queue1.displayItems();
        }
        else
        {
            cout << "You have not make an order" << endl;
        }
        
    }


}

void viewIncomingOrders() {
    if (OrderList.isEmpty()) {
        std::cout << "No incoming orders at the moment." << std::endl;
        return;
    }

    std::cout << "Incoming Orders:" << std::endl;
    for (int i = 0; i < OrderList.getLength(); i++) {
        Order order = OrderList.get(i);
        std::cout << "--------------- Order " << i + 1 << " ---------------" << std::endl;
        std::cout << "Customer Name: " << order.getCustName() << std::endl;
        std::cout << "Branch: " << order.getBranch() << std::endl;
        std::cout << "Total Charge: " << order.getCharge() << std::endl;
        std::cout << "Dishes: ";
        List<std::string> dishes = order.getDishList();
        for (int j = 0; j < dishes.getLength(); j++) {
            std::cout << dishes.get(j) << ", ";
        }
        std::cout << std::endl;
        std::cout << "Order Status: " << (order.getisReady() ? "Ready" : "Not Ready") << std::endl;
    }
}

void updateOrderStatus() {
    if (OrderList.isEmpty()) {
        std::cout << "No orders available to update." << std::endl;
        return;
    }

    // Display all orders
    std::cout << "Select an order to update:" << std::endl;
    for (int i = 0; i < OrderList.getLength(); i++) {
        Order order = OrderList.get(i);
        std::cout << (i + 1) << ". Order from " << order.getCustName() << " (Branch: " << order.getBranch() << ", Status: " << (order.getisReady() ? "Ready" : "Not Ready") << ")" << std::endl;
    }

    // Ask admin to select an order
    int selectedIndex;
    std::cout << "Enter the number of the order to update: ";
    std::cin >> selectedIndex;

    if (selectedIndex <= 0 || selectedIndex > OrderList.getLength()) {
        std::cout << "Invalid selection. Operation aborted." << std::endl;
        return;
    }

    // Get selected order
    Order selectedOrder = OrderList.get(selectedIndex - 1);

    // Ask for new status
    int statusChoice;
    std::cout << "Select the new status for the order:" << std::endl;
    std::cout << "1. Ready" << std::endl;
    std::cout << "2. Not Ready" << std::endl;
    std::cout << "Enter choice (1 or 2): ";
    std::cin >> statusChoice;

    if (statusChoice != 1 && statusChoice != 2) {
        std::cout << "Invalid choice. Operation aborted." << std::endl;
        return;
    }

    // Update order status
    selectedOrder.setisReady(statusChoice == 1);
    OrderList.remove(selectedIndex - 1);
    OrderList.add(selectedIndex - 1, selectedOrder);

    // Dequeue all existing orders from queue1
    int existingQueueSize = queue1.getLength();
    for (int i = 0; i < existingQueueSize; i++) {
        Item tempItem;
        queue1.dequeue(tempItem);
    }

    // Requeue orders from OrderList into queue1
    for (int i = 0; i < OrderList.getLength(); i++) {
        queue1.enqueue(OrderList.get(i));
    }

    // Confirm update
    std::cout << "Order status updated successfully!" << std::endl;

}
//This is my failed code to let customer check their own order status


/*
void viewCustomerOrders(const Customer& customer) {
    std::string customerName = customer.getName();

    // Check if there are any orders in the list
    if (OrderList.isEmpty()) {
        std::cout << "No orders found." << std::endl;
        return;
    }

    // Find and display orders that belong to the given customer
    bool ordersFound = false;
    std::cout << "Orders for " << customerName << ":" << std::endl;
    for (int i = 0; i < OrderList.getLength(); i++) {
        Order order = OrderList.get(i);
        if (order.getCustName() == customerName) {
            ordersFound = true;
            std::cout << "Order " << (i + 1) << " (Branch: " << order.getBranch() << ") - Status: " << (order.getisReady() ? "Ready" : "Not Ready") << std::endl;
        }
    }

    if (!ordersFound) {
        std::cout << "No orders found for " << customerName << "." << std::endl;
    }
}*/


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
            tempOrder.setBranch("1");
            //
            queue1.enqueue(tempOrder);
            if (tempOrder.getCharge() == 0)
            {
                std::cout << "You need to make an order" << endl;
                break;
            }
            List<std::string> tDL = tempOrder.getDishList();
            int L = tDL.getLength();

            for (int i = 0; i < L; i++) {
                std::string dish = tDL.get(i);
                Dish d = dishDict.get(dish);
                d.print();
            }

            std::cout << std::endl;
            std::cout << tempOrder.getCharge() << std::endl;
            OrderList.add(tempOrder);
            //Queuing();

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


int ChooseEdit(Customer cust) {
    viewInvoice(cust);
    std::string choose;
    std::cout << "Enter order to edit ";
    std::cin >> choose;
    bool checkInt = check(choose);
    if (checkInt == true) {
        return (std::stoi(choose) - 1);

    }

    else {
        std::cout << "Invalid option try again" << std::endl;

    }

}

List<std::string> AddDish(List<std::string> DL) {
    //std::cout << DL.getLength();
    viewAllDishes();
    std::string choice;
    std::cout << "Select dish to add ";
    std::cin >> choice;
    bool TryInt = check(choice);
    if (TryInt == true) {

        if ((std::stoi(choice) - 1) < dishList.getLength() && (std::stoi(choice) - 1) >= 0) {
            std::string NewDish = dishList.get((std::stoi(choice) - 1));

            DL.add(NewDish);
            return DL;
            //std::cout << DL.getLength();
        }

        else {
            std::cout << "Invalid input" << std::endl;
            return DL;

        }

    }

    else {
        std::cout << "Invalid input" << std::endl;
        return DL;

    }
}

List<std::string> RemoveDish(List<std::string> DLR) {
    std::cout << "+---------------++---------------++---------------+" << std::endl;
    for (int i = 0; i < DLR.getLength(); i++) {
        std::string str = DLR.get(i);
        Dish dish = dishDict.get(str);
        std::cout << i + 1 << ". ";
        dish.print();
    }
    std::cout << "+---------------++---------------++---------------+" << std::endl;
    std::string chooseR;
    std::cout << "Select dish to remove: ";
    std::cin >> chooseR;
    bool checkInt = check(chooseR);
    if (checkInt == true) {

        if ((std::stoi(chooseR) - 1) >= 0 || (std::stoi(chooseR) - 1) < DLR.getLength()) {
            DLR.remove((std::stoi(chooseR) - 1));
            return DLR;
        }

        else {
            std::cout << "Invalid input." << std::endl;
            return DLR;

        }
        

    }

    else {
        std::cout << "Invalid input." << std::endl;
        return DLR;
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
    std::cout << "5. Exit app" << std::endl; //OK
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
                    CancelOrder();
                }

                else if (choice == "4") {
                    //viewInvoice(sessionStorage); I think we can remove this? Since i think it's working 
                    // now and i placed it under Admin Login already - Javier, remove if needed!
                   

                }
                
                else if (choice == "5")
                {
                    int x = ChooseEdit(sessionStorage);
                    if (x >= OrderList.getLength() || x < 0) {
                        std::cout << "Invalid value." << std::endl;
                    }

                    else {
                        Order tempOrder = OrderList.get(x);
                        List<std::string> tempDL = tempOrder.getDishList();

                        //std::cout << x; test
                        std::string chooseOpt;
                        std::cout << "1. Add to order" << std::endl;
                        std::cout << "2. Remove dish" << std::endl;
                        std::cin >> chooseOpt;

                        if (chooseOpt == "1") {
                            //Add
                            tempDL = AddDish(tempDL);
                            tempOrder.setDishList(tempDL);
                            double charge = 0;
                            for (int i = 0; i < tempDL.getLength(); i++) {
                                std::string s = tempDL.get(i);
                                Dish dish = dishDict.get(s);
                                double nCharge = dish.getCharge();
                                charge += nCharge;

                            }
                            tempOrder.setCharge(charge);
                            OrderList.remove(x);
                            OrderList.add(tempOrder);
                            Queuing();




                        }

                        else if (chooseOpt == "2") {
                            //Remove
                            tempDL = RemoveDish(tempDL);
                            tempOrder.setDishList(tempDL);
                            double charge = 0;
                            for (int xs = 0; xs < tempDL.getLength(); xs++) {
                                std::string s = tempDL.get(xs);
                                Dish dish = dishDict.get(s);
                                double nCharge = dish.getCharge();
                                charge += nCharge;

                            }
                            tempOrder.setCharge(charge);
                            OrderList.remove(x);

                            if (tempDL.getLength() > 0) {
                                OrderList.add(tempOrder);
                                Queuing();
                            }

                          

                          
                            
                            
                        }

                        else {
                            std::cout << "Invalid option" << std::endl;
                            std::cout << endl;
                            std::cout << endl;

                        }
                    }
                   


                }

                else if (choice == "6")
                {
                    CheckOut();
                }
                else if (choice == "7") {
                    updateOrderStatus();
                }

                else if (choice == "8") {

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
            mainMenu();
        }
    }

    else if (option == "2") {
        //admin login
        bool aLogin = AdminLogin();
        if (aLogin == true) {
            while (true) {
                std::string choice = adminPage(sessionAdmin);

                if (choice == "1") {
                    viewIncomingOrders();
                }

                else if (choice == "2") {
                    updateOrderStatus();
                }

                else if (choice == "3") {
                    mainMenu();
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

    else if (option == "5") {

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

