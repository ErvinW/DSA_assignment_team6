
#include <iostream>
#include<fstream>
#include<sstream>
#include <iomanip>

#include"List.h"

#include"Queue.h"

#include"Membership.h"

#include"Dish.h"

#include"Order.h"

#include"Customer.h"

using namespace std;

List<Customer> customerList;
Customer TemplateCust;



void readCustFile() {

    ifstream inFile("Customer.csv");
    if (!inFile) {
        std::cerr << "Error opening Customer.csv for reading." << std::endl;
        return;
    }
    std::string line;
    while (getline(inFile, line)) {
        std::istringstream iss(line);
        std::string name, password, status;
        List<Dish> dL;
        int points;
        if (getline(iss, name, ',') && getline(iss, password, ',') && (iss >> points, ',') && getline(iss, status)) {
            Membership member = Membership(status, points);
            Order order = Order(name, dL, false, 0.0);
            Customer newCustomer = Customer(name, password, order, member);
            customerList.add(newCustomer);

        }
    }
}

void displayAllCustomer()
{
    // Print the header

    cout << left << setw(25) << "Name";
    cout << left << setw(15) << "Member Status";
    cout << right << setw(15) << "Member Points" << endl;
    cout << "" << endl;
    cout << "+-------------------------------------------------------+" << endl;

    // Print the food items
    for (int i = 0; i < customerList.getLength(); i++)
    {
        auto c = customerList.get(i);



        cout << left << setw(3) << i + 1;
        cout << left << setw(25) << c.getName();
        cout << left << setw(15) << c.Member.getStatus();
        cout << right << setw(10) << c.Member.getPoint() << endl;
        cout << "+-------------------------------------------------------+" << endl;

    }
}


void userRegister() {
    string customerName;
    string custPassword;

    cout << "Please enter your name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, customerName);
    cout << "Please enter your password: ";
    cin >> custPassword;
    bool isNewUser = true;
    for (int i = 0; i < customerList.getLength(); i++)
    {
        auto c = customerList.get(i);
        if (c.getName() == customerName)
        {
            cout << "You have registered for an account " << endl;
            cout << "" << endl;
            isNewUser = false;
            break;
        }
    }

    if (isNewUser == true)
    {
        int memberPoint = 0;
        std::string memberStatus = "Ordinary";
        List <Dish> dL;
        Membership member = Membership(memberStatus, memberPoint);
        Order order = Order(customerName,dL,false,0.0);
        Customer newCustomer = Customer(customerName, custPassword,order, member);
        TemplateCust = newCustomer;
        customerList.add(TemplateCust);

        std::ofstream file("Customer.csv", ios::app); // Open file in append mode

        if (!file.is_open()) {
            cerr << "Error opening file: Customer.csv" << std::endl;
        }

        // Write customer data to the file in CSV format
        file << customerName << "," << custPassword << ","
            << memberPoint << "," << memberStatus << endl;

        file.close();

    }   
}

void userLogin() {
    std:string userName;
    std::string password;

    std::cout << "Enter username: ";
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    std::getline(cin, userName);


    std::cout << "Enter password: ";
    std::cin >> password;
    std::cout << "" << std::endl;

    for (int i = 0; i < customerList.getLength(); i++) {
        Customer temp = customerList.get(i);
        std::string name = temp.getName();
        std::string pass = temp.getPassword();
        if (name == userName && pass == password) {
            TemplateCust = temp;
            std::cout << "Yes" << std::endl;

        }

        else {
            cout << "Please register for an account" << endl;
            break;
        }
    }


}


void mainMenu() {
    std::cout << "+---------------Welcome To  Restaurant---------------+" << std::endl;
    std::cout << "1. User Login" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "2. Admin Login" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "3. Register User" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Please choose your role: ";
    int option;
    std::cin >> option;
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;

    if (option == 1) {
        userLogin();
    }
    else if (option == 3) {
        userRegister();
    }


    else {
        std::cout << "Invalid input. Try again." << std::endl;
        mainMenu();
    }

}

int main()
{
    readCustFile();
    mainMenu();
}
            

