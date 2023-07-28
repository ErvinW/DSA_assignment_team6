
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
List<Dish> dishList;

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

void readDishFile() {
    ifstream inFile("Dishes.csv");
    if (!inFile) {
        std::cerr << "Error opening Customer.csv for reading." << std::endl;
        return;
    }

    std::string line;
    while (getline(inFile, line)) {
        std::istringstream iss(line);
        std::string c, n, p;
        double ch;
        if (getline(iss, c, ',') && getline(iss, n, ',') && getline(iss, p, ',') && (iss >> ch)) {
            Dish newDish = Dish(c,n,p,ch);
            dishList.add(newDish);

        }

    }

}


void printAllDish() {
   
    for (int i = 0; i < dishList.getLength(); i++) {
        Dish dish = dishList.get(i);
        

        std::cout << "[" << i + 1 << "] " << dish.getFoodName() << "    " << dish.getPortion() << "    " << "$" << dish.getCharge() << std::endl;
        std::cout << "" << std::endl;

    }



}

void printAllChinese() {

    for (int i = 0; i < dishList.getLength(); i++) {
        Dish dish = dishList.get(i);
        if (dish.getCuisine() == "Chinese") {
            std::cout << "[" << i + 1 << "] " << dish.getFoodName() << "    " << dish.getPortion() << "    " << "$" << dish.getCharge() << std::endl;
            std::cout << "" << std::endl;
        }
    }
   

        cout << left << setw(3) << i + 1;
        cout << left << setw(25) << c.getName();
        cout << left << setw(15) << c.Member.getStatus();
        cout << right << setw(10) << c.Member.getPoint() << endl;
        cout << "+-------------------------------------------------------+" << endl;

    }
}

void printAllWestern() {


    for (int i = 0; i < dishList.getLength(); i++) {
        Dish dish = dishList.get(i);
        if (dish.getCuisine() == "Western") {
            std::cout << "[" << i + 1 << "] " << dish.getFoodName() << "    " << dish.getPortion() << "    " << "$" << dish.getCharge() << std::endl;
            std::cout << "" << std::endl;
        }
    }
    

}

void filterDish() {
    int option;

    std::cout << "[1] View all dishes" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "[2] View all Chinese dishes" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "[3] View all Western dishes" << std::endl;
    std::cout << "" << std::endl;
    std::cin >> option; 

    if (option == 1) {
        std::cout << "" << std::endl;
        printAllDish();
    }

    else if (option == 2) {
        std::cout << "" << std::endl;
        printAllChinese();

    }

    else if (option == 3) {
        std::cout << "" << std::endl;
        printAllWestern();

    }

}


void UserPage(Customer customer) {
    int option;

    std::cout << "+---------------Welcome To  Restaurant, " << customer.getName() << "---------------+" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "[1] View Menu" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "[2] Place an order" << std::endl;
    std::cout << "" << std::endl;
    std::cin >> option;


    if (option == 1) {
        filterDish();

    }

    else if (option == 2) {
        Dish dish = dishList.get(0);
        std::cout << dish.getCuisine();
    }

    else {
        std::cout << "Invalid input, try again" << std::endl;
        std::cout << "" << std::endl;
        UserPage(TemplateCust);

    }
}


void userLogin() {
    std::string userName;
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
            UserPage(TemplateCust);

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
    readDishFile();
    mainMenu();
}
            

