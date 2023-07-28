
#include <iostream>
#include<fstream>
#include<sstream>

#include"List.h"

#include"Queue.h"


#include"Membership.h"

#include"Dish.h"

#include"Order.h"

#include"Customer.h"


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

void initCustomer() {
    Membership mem1 = Membership("Normal", 0);
    List<Dish> dL;
    Order order1 = Order("Ervin", dL, false, 0.0);
    customerList.add(Customer("Ervin", "Ew123", order1, mem1));

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


    else {
        std::cout << "Invalid input. Try again." << std::endl;
        mainMenu();
    }

}

int main()
{
    readCustFile();
    initCustomer();
    mainMenu();
}
            

