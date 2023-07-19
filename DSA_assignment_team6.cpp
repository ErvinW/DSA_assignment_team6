#include <iostream>
#include <string>
#include <iomanip>
#include <fstream> 
#include <vector>
#include <sstream>
#include "List.h"
#include "Customer.h"
#include "Membership.h"
#include "Dish.h"
#include "Chinese.h"
#include "Western.h"
#include "Queue.h"
#include "Admin.h"



using namespace std;

List <Customer> customerList;
List <Admin> adminList;
List <Dish> foodItemList;
List <Chinese> chineseList;
List <Western> westernList;
Queue <Order> orderList;


void intialiseAdmin()
{
    adminList.add(Admin("Jack"));
    adminList.add(Admin("Marry"));
    adminList.add(Admin("David"));
}






void initialiseMenu()
{
    foodItemList.add(Chinese("Chinese", "Mapo Tofu", "Small", 20));
    foodItemList.add(Chinese("Chinese", "Mapo Tofu", "Medium", 25));
    foodItemList.add(Chinese("Chinese", "Mapo Tofu", "Large", 30));
    foodItemList.add(Chinese("Chinese", "Spring Rolls", "Small", 5));
    foodItemList.add(Chinese("Chinese", "Spring Rolls", "Medium", 8));
    foodItemList.add(Chinese("Chinese", "Spring Rolls", "Large", 10));
    foodItemList.add(Chinese("Chinese", "Wonton Soup", "Small", 5));
    foodItemList.add(Chinese("Chinese", "Wonton Soup", "Medium", 6));
    foodItemList.add(Chinese("Chinese", "Wonton Soup", "Large", 8));
    foodItemList.add(Chinese("Chinese", "Char Siu", "Small", 20));
    foodItemList.add(Chinese("Chinese", "Char Siu", "Medium", 30));
    foodItemList.add(Chinese("Chinese", "Char Siu", "Large", 40));
    foodItemList.add(Chinese("Chinese", "Kungpao Chicken", "Small", 25));
    foodItemList.add(Chinese("Chinese", "Kungpao Chicken", "Medium", 30));
    foodItemList.add(Chinese("Chinese", "Kungpao Chicken", "Large", 35));
    foodItemList.add(Western("Western", "Pasta", "Small", 22));
    foodItemList.add(Western("Western", "Pasta", "Medium", 25));
    foodItemList.add(Western("Western", "Pasta", "Large", 28));
    foodItemList.add(Western("Western", "Chicken Chop", "Small", 30));
    foodItemList.add(Western("Western", "Chicken Chop", "Medium", 35));
    foodItemList.add(Western("Western", "Chicken Chop", "Large", 40));
    foodItemList.add(Western("Western", "Fish and Chips", "Small", 20));
    foodItemList.add(Western("Western", "Fish and Chips", "Medium", 25));
    foodItemList.add(Western("Western", "Fish and Chips", "Large", 30));
    foodItemList.add(Western("Western", "Pizza", "Small", 30));
    foodItemList.add(Western("Western", "Pizza", "Medium", 40));
    foodItemList.add(Western("Western", "Pizza", "Large", 50));
    foodItemList.add(Western("Western", "Fried Chicken Wings", "Small", 5));
    foodItemList.add(Western("Western", "Fried Chicken Wings", "Medium", 15));
    foodItemList.add(Western("Western", "Fried Chicken Wings", "Large", 25));
}

void assignDish()
{
    for (int i = 0; i < foodItemList.getLength(); i++)
    {
        auto d = foodItemList.get(i);
        if (d.getCuisine() == "Chinese")
        {
            chineseList.add(Chinese(d.getCuisine(), d.getFoodName(), d.getPortion(), d.getCharge()));

        }
        else
        {
            westernList.add(Western(d.getCuisine(), d.getFoodName(), d.getPortion(), d.getCharge()));
        }
    }
}

void displayAllFood()
{
    // Print the header

    cout << left << setw(25) << "Food Name";
    cout << left << setw(15) << "Portion";
    cout << right << setw(15) << "Charge" << endl;
    cout << "+-------------------------------------------------------+" << endl;

    // Print the food items
    for (int i = 0; i < foodItemList.getLength(); i++)
    {
        auto d = foodItemList.get(i);

        // Use std::left for Food Name and Portion, and std::right for Charge

        cout << left << setw(3) << i + 1;
        cout << left << setw(25) << d.getFoodName();
        cout << left << setw(15) << d.getPortion();
        cout << right << setw(10) << "$" << d.getCharge() << endl;
        cout << "+-------------------------------------------------------+" << endl;

    }
}

void displayAllCustomer()
{
    // Print the header
    cout << "" << endl;
    cout << left << setw(23) << "   Name";
    cout << left << setw(20) << "Member Status";
    cout << right << setw(15) << "Member Points" << endl;
    
    cout << "+-------------------------------------------------------+" << endl;

    // Print the food items
    for (int i = 0; i < customerList.getLength(); i++)
    {
        auto c = customerList.get(i);


        // Use std::left for Food Name and Portion, and std::right for Charge

        cout << left << setw(3) << i + 1 ;
        cout << left << setw(20) << c.getName();
        cout << left << setw(12) << c.Member.getStatus();
        cout << right << setw(11) << c.Member.getPoint() << endl;
        cout << "+-------------------------------------------------------+" << endl;
        cout << "" << endl;
    }
}

#include <fstream>

void readCustomersFromFile() {
    ifstream inFile("Customer.csv");
    if (!inFile) {
        cerr << "Error opening Customer.csv for reading." << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string name, memberStatus;
        int memberPoint;

        if (getline(iss, name, ',') && getline(iss, memberStatus, ',') && (iss >> memberPoint)) {
            Membership member = Membership(memberStatus, memberPoint);
            Order order = Order(false);
            Customer newCustomer = Customer(name, order, member);
            customerList.add(newCustomer);
        }
    }
    inFile.close();
}


// Adding all the food items to the List using add function

void registerAccount()
{
    readCustomersFromFile(); // Read the existing customers from the file
    displayAllCustomer();
    string customerName;
    cout << "Please enter your name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, customerName);

    bool isNewUser = true;
    for (int i = 0; i < customerList.getLength(); i++) 
    {
        auto c = customerList.get(i);
        if (c.getName() == customerName) {
            cout << "You have already registered for an account." << endl;
            isNewUser = false;
            break;
        }
    }

    if (isNewUser == true) 
    {
        int memberPoint = 0;
        string memberStatus = "Ordinary";
        Membership member = Membership(memberStatus, memberPoint);
        Order order = Order(false);
        Customer newCustomer = Customer(customerName, order, member);
        customerList.add(newCustomer);

        ofstream outFile("Customer.csv", ios::app); // Open the file in append mode
        if (!outFile) {
            std::cerr << "Error opening Customer.csv for writing." << endl;
            return;
        }

        outFile << customerName << "," << memberPoint << "," << memberStatus << "\n";
        outFile.close();
        
    }
}
 

bool customerLogIn()
{
    string customerName;
    cout << "Please enter your name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, customerName);

    bool isOldUser = false;

    for (int i = 0; i < customerList.getLength(); i++)
    {
        auto c = customerList.get(i);
        if (customerName == c.getName())
        {
            cout << "Welcome back " << c.getName() << endl;
            isOldUser = true;
            break;
        }
    }
    if (isOldUser != true)
    {
        cout << "You need to register for an account first" << endl;
        return false;
    }
}



bool adminLogIn()
{
    string adminName;
    cout << "Please log in with your name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, adminName);

    bool isOldUser = false;

    for (int i = 0; i < adminList.getLength(); i++)
    {
        auto c = adminList.get(i);
        if (adminName == c.getName())
        {
            cout << "Welcome back " << c.getName() << endl;
            isOldUser = true;
            break;
        }
    }
    if (isOldUser != true)
    {
        cout << "You are not register as an admin yet" << endl;
        return false;
        
    }
}



void OrderFood()
{
    displayAllCustomer();
    string name;
    cout << "Please enter the customer name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    for (int i = 0; i < customerList.getLength(); i++)
    {
        auto c = customerList.get(i);
        if (name == c.getName())
        {
            while (true)
            {
                displayAllFood();
                cout << "" << endl;
                int option;
                cout << "1. Please select a dish";
                cout << "2. Finish ordering";
                cin >> option;
                for (int i = 0; i < foodItemList.getLength();i++)
                {
                    if (option - 1 == i)
                    {
                        c.orderItem.addDish(foodItemList.get(i));

                    }
                    else
                    {
                        orderList.enqueue(c.orderItem);
                    }
                }
            }

        }
    }

    cout << "" << endl;


}



int main()
{
    intialiseAdmin();
    initialiseMenu();
    assignDish();
    bool check = true;


    while (true)
    {
        while (true)
        {
            int option;
            cout << "+---------------Welcome To  Restaurant---------------+" << endl;
            cout << "1. User" << endl;
            cout << "" << endl;
            cout << "2. Admin" << endl;
            cout << "" << endl;
            cout << "Please choose your role: ";
            cin >> option;
            if (option == 1)
            {
                while (check == true)
                {
                    int option;
                    cout << "+---------------Welcome To  Restaurant---------------+" << endl;
                    cout << "1. Register Customer" << endl;
                    cout << "" << endl;
                    cout << "2. Login Customer" << endl;
                    cout << "" << endl;
                    cout << "Please choose an option: ";
                    cin >> option;
                    if (option == 1)
                    {
                        registerAccount();

                        while (true)
                        {
                            int choice;
                            cout << "+----------------------------------------------------+" << endl;
                            cout << "1. Browse All Food Selection" << endl;
                            cout << "2. Create an order" << endl;
                            cout << "3. Delete an order" << endl;
                            cout << "4. Exit" << endl;
                            cout << "Please choose an option: ";
                            cin >> choice;
                            cout << "" << endl;

                            if (choice == 1)
                            {
                                displayAllFood();
                                cout << "" << endl;
                            }
                            else if (choice == 2)
                            {

                            }
                            else if (choice == 3)
                            {

                            }
                            else if (choice == 4)
                            {
                                // Exit the loop and end the program
                                break;
                            }
                            else
                            {
                                cout << "Invalid choice. Please try again." << endl;
                            }
                        }
                    }

                    else if (option == 2)
                    {
                        if (customerLogIn() == false)
                        {
                            break;
                        }

                        while (true)
                        {
                            int choice;
                            cout << "+----------------------------------------------------+" << endl;
                            cout << "1. Browse All Food Selection" << endl;
                            cout << "2. Create an order" << endl;
                            cout << "3. Delete an order" << endl;
                            cout << "4. Exit" << endl;
                            cout << "Please choose an option: ";
                            cin >> choice;
                            cout << "" << endl;

                            if (choice == 1)
                            {
                                displayAllFood();
                                cout << "" << endl;
                            }
                            else if (choice == 2)
                            {

                            }
                            else if (choice == 3)
                            {

                            }
                            else if (choice == 4)
                            {
                                // Exit the loop and end the program
                                break;
                            }
                            else
                            {
                                cout << "Invalid choice. Please try again." << endl;
                            }
                        }
                    }

                }
            }
            else if (option == 2)
            {
                if (adminLogIn() == false)
                {
                    break;
                }

                while (true)
                {
                    int choice;
                    cout << "+----------------------------------------------------+" << endl;
                    cout << "1. View the incoming orders" << endl;
                    cout << "2. Update status of the orders" << endl;
                    cout << "3. View the customer information for that order" << endl;
                    cout << "4. Exit" << endl;
                    cout << "Please choose an option: ";
                    cin >> choice;
                    cout << "" << endl;

                    if (choice == 1)
                    {

                    }
                    else if (choice == 2)
                    {

                    }
                    else if (choice == 3)
                    {

                    }
                }

            }
            else
            {
                cout << "Invalid choice. Please try again." << endl;
            }

        }
    }
}

