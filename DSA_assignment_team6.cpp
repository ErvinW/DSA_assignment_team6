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

//using namespace std;

//------------- Input validation functions -------------//

bool check(std::string s) {

    try {
        int tryInt = std::stoi(s);
        return true;
    }

    catch (std::invalid_argument& e) {
        return false;
    }
}

bool checkDouble(std::string s) {

    try {
        int tryInt = std::stod(s);
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

    catch (std::invalid_argument& ) {
        return false;

    }
}
//------------- Initialise data -------------//

//clears the queue
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

//Uses orderList to queue all orders into their respective queues
void Queuing() {

    ClearQueue();

    for (int x = 0; x < OrderList.getLength(); x++) {
        Order order = OrderList.get(x);
        std::string branch = order.getBranch();

        if (order.getisReady() == false)
        {
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
        else
        {

        }
    }
}

//Read customer.csv and populate the hashtable customerDict and CustNames list
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

//Read Dishes.csv and populate the hashtable dishDict and dishList list
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

//Initialise admin accounts into adminList
void initAdmins() {
    adminList.add(Admin("Adm1", "PassAdm1", 1));
    adminList.add(Admin("Adm2", "PassAdm2", 2));
    adminList.add(Admin("Adm3", "PassAdm3", 3));
}




//------------- Login functions -------------//

//Gets user input and checks if username and password entered matches an object in customerDict hash table
//Customer object is stored in global variable SessionStorage
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


// Gets user input and checks if username and password entered matches an object in adminList list
//Admin object is stored in global variable adminStorage
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


//Gets user input and checks if username and password entered matches an object in customerDict hash table
//If no, create new customer object and update customer.csv, customerDict hash table and CustNames list
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


//Loops through dishList list, retrieve keys for dishDict
//Retrieve the corresponding object and run print function
void viewAllDishes() {
    for (int i = 0; i < dishList.getLength(); i++) {
        std::string name = dishList.get(i);
        Dish tempD = dishDict.get(name);
        std::cout << i + 1 << ". ";
        tempD.print();
        std::cout << " - Rating: " << tempD.getAverageRating() << "/5" << std::endl; // Display the rating
    }
}


//Gets user input. Checks if it matches keys in dishList or cuisine name in dish objects. Retrieve dish objects that match and run their print function
void viewBy() {
    std::string s;
    std::cout << "Enter category/ dish name to sort by [3 to exit]: ";
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


//Uses customer object in SessionStorage. Retrieves Order objects that have customer's name as its custName attribute
//From Order object, retrieve dish keys from its dishList and retireve dish object from dishDict
//Run dish objects' print function and print the Order objects status. Ready if true and Not ready if False
void viewInvoice(Customer cust) {

    if (OrderList.getLength() == 0)
    {
        std::cout << "There is no order" << std::endl;
        return;
    }
    for (int i = 0; i < OrderList.getLength(); i++) {

        Order order = OrderList.get(i);

        if (order.getCustName() == cust.getName()) {
            std::cout << "--------------- Order " << i + 1 << " ---------------" << std::endl;
            if (order.getisReady() == true) {
                std::cout << "Order ready" << std::endl;

            }

            else {
                std::cout << "Order not ready" << std::endl;
            }

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

//UI for user to select next action
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
            return;

        }

        else {
            std::cout << "Invalid input" << std::endl;
            std::cout << "+---------------+---------------+" << std::endl;
        }
    }
}


//Runs viewInvoice function
//Gets user input to select the order they want to cancel. 
//Removes order from List OrderList and runs the function Queuing()
void CancelOrder()
{   
    while (true)
    {
        viewInvoice(sessionStorage);
        std::cout << "Please select order to remove[Press 0 to Exit] ";
        std::string choose;
        std::cin >> choose;
        if (choose == "0")
        {
            return;
        }
        bool checkInt = check(choose);
        if (checkInt == true)
        {
            int choice = std::stoi(choose);
            if (choice - 1 < OrderList.getLength() && choice - 1 >= 0)
            {
                if (OrderList.get(choice - 1).getisReady() == false)
                {
                    OrderList.remove(choice - 1);
                    Queuing();
                    std::cout << "Order Canceled" << std::endl;
                }
                else
                {
                    std::cout << "Unable to delete order" << endl;
                }
            }
            else
            {
                std::cout << "Invalid Input" << std::endl;
            } 
        }
        else
        {
            std::cout << "Invalid Input" << std::endl;
        }
        
    }

}


//display all orders in OrderList
void viewIncomingOrders() {
    while (true) {
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
}


//displays first Order in OrderList. 
//Recieve user's input
//If user enters 1, update order object's isready boolean to true
//IF enter 2, update to False
void updateOrderStatus() {
    while (true) {
        if (OrderList.getLength() == 0) {
            std::cout << "No orders available to update." << std::endl;
            return;
        }

        // Get the order at the front of the list
        Order frontOrder = OrderList.get(0);

        std::cout << "Order to update: " << frontOrder.getCustName() << " (Branch: " << frontOrder.getBranch() << ", Status: " << (frontOrder.getisReady() ? "Ready" : "Not Ready") << ")" << std::endl;

        // Displaying some of the order details (modify as needed)
        List<std::string> dishList = frontOrder.getDishList();
        for (int i = 0; i < dishList.getLength(); i++) {
            Dish dish = dishDict.get(dishList.get(i));
            dish.print(); // Assuming Dish has a print() method to print details
        }
        // Ask for new status
        int statusChoice;
        std::cout << "Select the new status for the order [Select 0 to stop]:" << std::endl;
        std::cout << "1. Ready" << std::endl;
        std::cout << "2. Not Ready" << std::endl;
        std::cout << "Enter choice (1 or 2): ";
        std::cin >> statusChoice;

        if (statusChoice == 0)
        {
            break;
        }
        if (statusChoice != 1 && statusChoice != 2) {
            std::cout << "Invalid choice. Operation aborted." << std::endl;
            return;
        }

        // Update order status
        frontOrder.setisReady(statusChoice == 1);
        OrderList.remove(0); // Remove the order from the front of the list
        OrderList.add(OrderList.getLength(), frontOrder); // Add the updated order to the back of the list

        // Confirm update
        std::cout << "Order status updated successfully!" << std::endl;


        if (statusChoice == 1)
        {
            Customer customer = customerDict.get(frontOrder.getCustName());
            customer.Member.EarnPoint(frontOrder.getCharge());
            customer.Member.setStatus();

            customerDict.remove(customer.getName());
            customerDict.add(customer.getName(), customer);

            string customerName = customer.getName();
            string custPassword = customer.getPassword();
            string memberStatus = customer.Member.getStatus();
            int memberPoint = customer.Member.getPoint();

            std::ifstream inputFile("Customer.csv");
            std::ofstream outputFile("TempCustomer.csv");


            if (!inputFile.is_open() || !outputFile.is_open()) {
                std::cerr << "Error opening files." << std::endl;
                return;
            }

            std::string line;
            while (std::getline(inputFile, line)) {
                std::istringstream iss(line);
                std::string name, password, status, point;
                if (std::getline(iss, name, ',') && name == customerName &&
                    std::getline(iss, password, ',') && std::getline(iss, status, ',') && std::getline(iss, point)) {
                    outputFile << customerName << "," << custPassword << "," << memberStatus << "," << memberPoint << "\n";
                }
                else {
                    outputFile << line << "\n";
                }
            }

            inputFile.close();
            outputFile.close();

            std::remove("Customer.csv");
            std::rename("TempCustomer.csv", "Customer.csv");
        }
   }
        
}


//View all attributes of the selected order
//Retrieve customer object from customerDict using custname attribute from order as the key
//display customer object's attribute values
void viewCustomerInformation() {
    while (true) {
        if (OrderList.isEmpty()) {
            std::cout << "No orders available." << std::endl;
            return;
        }

        // Display all orders
        std::cout << "Select an order to view customer information:" << std::endl;
        for (int i = 0; i < OrderList.getLength(); i++) {
            Order order = OrderList.get(i);
            std::cout << (i + 1) << ". Order from " << order.getCustName()
                << " (Branch: " << order.getBranch()
                << ", Status: " << (order.getisReady() ? "Ready" : "Not Ready")
                << ")" << std::endl;
        }

        // Ask admin to select an order
        int selectedIndex;
        std::cout << "Enter the number of the order to view: ";
        std::cin >> selectedIndex;

        if (selectedIndex <= 0 || selectedIndex > OrderList.getLength()) {
            std::cout << "Invalid selection. Operation aborted." << std::endl;
            return;
        }

        // Get selected order
        Order selectedOrder = OrderList.get(selectedIndex - 1);

        // Display customer information
        std::cout << "Customer Information for Selected Order:" << std::endl;
        std::cout << "Customer Name: " << selectedOrder.getCustName() << std::endl;
        std::cout << "Branch: " << selectedOrder.getBranch() << std::endl;
        std::cout << "Charge: $" << selectedOrder.getCharge() << std::endl;
        std::cout << "Order Status: " << (selectedOrder.getisReady() ? "Ready" : "Not Ready") << std::endl;

        std::cout << "Customer information displayed successfully!" << std::endl;
   }
}


//get input to create dish object
//Add dish name to dishList and add Dish to DishDict
//Update csv file
void CreateDish() {
    
    while (true) {
        std::string cuisine;
        std::cout << "Enter cuisine: ";
        std::cin >> cuisine;
        std::cout << std::endl;

        std::string name;
        std::cout << "Enter dish name: ";
        std::cin >> name;
        std::cout << std::endl;

        std::string charge;
        std::cout << "Enter price: ";
        std::cin >> charge;
        bool check_dbl = checkDouble(charge);
        double tCharge = 0;
        std::cout << std::endl;

        if (check_dbl == true) {
            tCharge += std::stod(charge);



            std::string cfm;
            std::cout << "Press 1 to confirm new dish. Press any other button to cancel.";
            std::cin >> cfm;

            if (cfm == "1") {
                Dish newDish = Dish(cuisine, name, tCharge);
                dishList.add(name);
                dishDict.add(name, newDish);


                std::ofstream file("Dishes.csv", std::ios::app); // Open file in append mode

                if (!file.is_open()) {
                    std::cerr << "Error opening file: Dishes.csv" << std::endl;
                }

                file << cuisine << "," << name << ","
                    << charge << std::endl;

                file.close();




                std::cout << std::endl;
                return;

            }

            else {
                std::cout << "Cancelled" << std::endl;
                return;
            }

        }

        else {
            std::cout << "Invalid input" << std::endl;
            return;
        }

       
    }



}



//UI for admin to select next action
void adminPage(Admin admin) {

    while (true) {
        std::string option;

        std::cout << "+---------------Welcome " << admin.getUsername() << "---------------+" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "[1] View incoming orders" << std::endl;
        std::cout << "[2] Update order status" << std::endl;
        std::cout << "[3] View customer information" << std::endl;
        std::cout << "[4] Create a new dish" << std::endl;
        std::cout << "[5] Exit" << std::endl;
        std::cin >> option;

        if (option == "1") {
            viewIncomingOrders();
        }

        else if (option == "2") {
            updateOrderStatus();
        }
        else if (option == "3") {
            viewCustomerInformation();
        }

        else if (option == "4") {
            CreateDish();
        }

        else if (option == "5") {
            return;

        }

        else {
            std::cout << "Invalid option " << std::endl;

        }
   }

}


//Page for user to complete order
void MakePayment(double amt)
{
    viewInvoice(sessionStorage);
    std::cout << "Total Amount: $" << amt << endl;
    std::cout << "" << endl;
    while (true)
    {
        while (true)
        {
            
            std::cout << "Current Point: " << sessionStorage.Member.getPoint() << endl;
            std::cout << "Do you want use point[Y/N] ";
            string decision;
            std::cin >> decision;
            bool validation = checkstring(decision);
            if (validation == true)
            {
                if (decision == "N" || decision == "n")
                {
                    break;
                }
                else if (decision == "Y" || decision == "y")
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
                            string pt;
                            std::cout << "Please enter point: ";
                            std::cin >> pt;
                            bool checkInt = check(pt);
                            if (checkInt == true)
                            {
                                int point = std::stoi(pt);
                                if (point > amt)
                                {
                                    std::cout << "Unsuccessful Redeem Points" << endl;
                                    
                                }
                                else if (currentPoint < point)
                                {
                                    std::cout << "Insufficient Points" << endl;
                                    cout << "" << endl;
                                }
                                else
                                {
                                    sessionStorage.Member.RedeemPoints(point);

                                    Membership member = Membership(sessionStorage.Member.getStatus(), currentPoint - point);
                                    Customer customer2 = Customer(sessionStorage.getName(), sessionStorage.getPassword(), member);
                                    customerDict.remove(sessionStorage.getName());
                                    customerDict.add(sessionStorage.getName(), customer2);
                                
                                    string customerName = customer2.getName();
                                    string custPassword = customer2.getPassword();
                                    string memberStatus = customer2.Member.getStatus();
                                    int memberPoint = customer2.Member.getPoint();

                                    std::ifstream inputFile("Customer.csv");
                                    std::ofstream outputFile("TempCustomer.csv");


                                    if (!inputFile.is_open() || !outputFile.is_open()) {
                                        std::cerr << "Error opening files." << std::endl;
                                        return;
                                    }

                                    std::string line;
                                    while (std::getline(inputFile, line)) {
                                        std::istringstream iss(line);
                                        std::string name, password, status, point;
                                        if (std::getline(iss, name, ',') && name == customerName &&
                                            std::getline(iss, password, ',') && std::getline(iss, status, ',') && std::getline(iss, point)) {
                                            outputFile << customerName << "," << custPassword << "," << memberStatus << "," << memberPoint << "\n";
                                        }
                                        else {
                                            outputFile << line << "\n";
                                        }
                                    }

                                    inputFile.close();
                                    outputFile.close();

                                    std::remove("Customer.csv");
                                    std::rename("TempCustomer.csv", "Customer.csv");
                                    amt -= point;
                                    if (amt < 1)
                                    {
                                        amt = 0;
                                    }
                                    std::cout << "Successful Redeem Points" << endl;

                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
            }
            else if(validation == false)
            {
                std::cout << "Invalid Input" << endl;
            }
        }
        std::cout << "" << endl;
        while (true)
        {
            std::cout << "Total Amount: $" << amt << endl;
            if (amt <= 0)
            {
                std::cout << "Payment successful" << endl;
                break;
            }
            std::cout << "Enter Payment amount: ";
            string pay;
            std::cin >> pay;
            std::cout << "" << endl;
            bool validationDouble = checkDouble(pay);

            if (validationDouble == true)
            {
                double payment = std::stod(pay);
                if (payment < amt || payment > amt)
                {
                    std::cout << "Payment unsuccessful" << endl;
                    std::cout << "" << endl;
                }
                else
                {
                    std::cout << "Payment successful" << endl;
                    break;
                }
            }
            else
            {
                std::cout << "Invalid Input" << endl;
                
            }
        }
        break;
    }

}

//Creates new order object
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
            tempOrder.setBranch(currentBranch);
            
            
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
            OrderList.add(tempOrder);
            MakePayment(charge);

            if (currentBranch == "1")
            { 
                queue1.enqueue(tempOrder);
            }
            else if (currentBranch == "2")
            {
                queue2.enqueue(tempOrder);
            }
            else
            {
                queue3.enqueue(tempOrder);
            }

            break;

        }

        else 
        {
            return;
        }

    }


}




//Adds to list in order object's dishList attribute
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


//Removes from list in order object's dishList attribute
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


//Updates rating.csv 
void saveAndExit(DishDict& dishes) {
    dishes.saveRatingsToFile("ratings.csv");
    std::cout << "Ratings saved. Exiting program.\n";
    exit(0);
}


//Select order to edit
void ChooseEdit(Customer cust) {

    while (true) {
        viewInvoice(cust);
        std::string choose;
        std::cout << "Enter order to edit ";
        std::cin >> choose;

        if (choose == "0") {
            return;
        }

        bool checkInt = check(choose);
        if (checkInt == true) {
            int choice = std::stoi(choose);

            if (choice - 1 >= OrderList.getLength() || choice - 1 < 0) {
                std::cout << "Invalid value." << std::endl;
            }

            

            else {

                Order tempOrder = OrderList.get(choice - 1);
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
                    OrderList.remove(choice - 1);
                    OrderList.add(tempOrder);
                    Queuing();
                    return;



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
                    OrderList.remove(choice - 1);

                    if (tempDL.getLength() > 0) {
                        OrderList.add(tempOrder);
                        Queuing();
                        return;
                    }




                }


                else {
                    std::cout << "Invalid option try again" << std::endl;

                }
            }
        }
    }

}




//-------------------------------------------//

//UI for user to select next action
void userPage(Customer cust) {

    while (true) {

        std::string option;
        Customer tempcust = customerDict.get(sessionStorage.getName());
        std::cout << "+--------------- Welcome ---------------+" << std::endl;
        tempcust.print();
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
        std::cout << "[6] Rate Dishes" << std::endl;
        std::cout << std::endl;
        std::cout << "[0] Exit" << std::endl;
        std::cout << std::endl;


        std::cin >> option;

        if (option == "1") {
            ViewMenu();
        }

        else if (option == "2") {
            CreateOrder();
        }

        else if (option == "3") {
            CancelOrder();
        }

        else if (option == "4") {
            viewInvoice(sessionStorage);
        }

        else if (option == "5") {
            
            ChooseEdit(sessionStorage);

        }
        else if (option == "6") {
            dishDict.rateDishByName();
        }

        else if (option == "0") {
            std::cout << "Logging out..." << std::endl;
            std::cout << std::endl;
            return;
        }

        else {
            std::cout << "Invalid option " << std::endl;

        }
    }


}





//UI for user to select next action
void Main() {
    while (true) {
        std::cout << "+---------------Welcome To  Restaurant---------------+" << std::endl;
        std::cout << "1. User Login" << std::endl; //OK
        std::cout << "" << std::endl;
        std::cout << "2. Admin Login" << std::endl; //OK
        std::cout << "" << std::endl;
        std::cout << "3. Register User" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "4. Exit" << std::endl; //OK
        std::cout << std::endl;
        std::cout << "Please choose your role: ";

        std::string option;
        std::cin >> option;
        std::cout << "" << std::endl;
        std::cout << "" << std::endl;


   

        if (option == "1") { //user done
            bool login = userLogin();
            if (login == true) {
                userPage(sessionStorage);
            }

            else {
                std::cout << "Invalid option" << std::endl;

            }

        }

        else if (option == "2") { //admin
            bool aLogin = AdminLogin();
            if (aLogin == true) {
                adminPage(sessionAdmin);
            }

            else {
                std::cout << "Invalid option" << std::endl;

            }

        }

        else if (option == "3") {
            bool Reg = regUser();
            if (Reg == true) {
                std::cout << "User registered" << std::endl;

            }

            else {

            }
        }

     

        else if (option == "4") {
            std::cout << "Exiting.." << std::endl;
            return;

        }
  }

}

//UI for user to select branch
// value selected is saved to currentBranch
void SelectBranch() {
    while (true) {
        std::string Location;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Select branch" << std::endl;
        std::cout << "[1] Punggol" << std::endl;
        std::cout << "[2] Clementi" << std::endl;
        std::cout << "[3] Tiong Bahru" << std::endl;
        std::cout << "[4] Exit" << std::endl;

        std::cin >> Location;

        if (Location == "1" || Location == "2" || Location == "3") {
            currentBranch = Location;
            Main();

        }

        else if (Location == "4") {
            return;
        }


        else {
            std::cout << "Invalid input. " << std::endl;

        }
    }
}







//------------------------------------------//
int main()
{
    DishDict dishes;
   


    initCustomer();
    initDishList();
    dishDict.loadRatingsFromFile("ratings.csv"); // Load ratings after dishes are created
    initAdmins();
    SelectBranch();

    return 0;
}
