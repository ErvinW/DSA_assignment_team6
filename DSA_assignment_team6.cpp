
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

#include"Admin.h"

using namespace std;

List<Customer> customerList;
List<Dish> dishList;

Queue <Order> orderQueue;
Queue <Order> orderQueue2;
Queue <Order> orderQueue3;

List<Order>tempList;
List<Admin> adminList;
List<string> branchList;
Customer TemplateCust;
Admin Adm;
string branch;


void initAdmins() {

    adminList.add(Admin("Adm1", "PassAdm1", 1));
    adminList.add(Admin("Adm2", "PassAdm2", 2));
    adminList.add(Admin("Adm3", "PassAdm3", 3));

}
void displayAllCustomer()
{
    // Print the header

    cout << left << setw(25) << "Name";
    cout << left << setw(10) << "Member Status";
    cout << right << setw(15) << "Member Points" << endl;
    cout << "" << endl;
    cout << "+-------------------------------------------------------+" << endl;

    // Print the food items
    for (int i = 0; i < customerList.getLength(); i++)
    {
        auto c = customerList.get(i);


        // Use std::left for Food Name and Portion, and std::right for Charge

        cout << left << setw(0) << "[" << i + 1 << "]  ";
        cout << left << setw(25) << c.getName();
        cout << left << setw(15) << c.Member.getStatus();
        cout << right << setw(10) << c.Member.getPoint() << endl;
        cout << "+-------------------------------------------------------+" << endl;
    }
}

void initBranch() {
    branchList.add("Punggol");
    branchList.add("Clementi");
    branchList.add("Tiong Bahru");

}



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
        if (getline(iss, name, ',') && getline(iss, password, ',') && getline(iss, status, ',') &&  (iss >> points)) {
            Membership member = Membership(status, points);
            Order order = Order(name, dL, false, 0.0, "");
            List<Order> OrderL;
            Customer newCustomer = Customer(name, password, OrderL, member);
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
            Dish newDish = Dish(c, n, p, ch);
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
    while (true)
    {
        std::cout << "----------------------------------" << std::endl;
        std::cout << "[1] View all dishes" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "[2] View all Chinese dishes" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "[3] View all Western dishes" << std::endl;
        std::cout << endl;
        std::cout << "[4] Return to user menu" << std::endl;
        std::cout << "----------------------------------" << std::endl;
        std::cout << "" << std::endl;
        std::cin >> option;
    

        if (option == 1) {
            std::cout << "" << std::endl;
            printAllDish();
            //break;
        }

        else if (option == 2) {
            std::cout << "" << std::endl;
            printAllChinese();
            //break;

        }

        else if (option == 3) {
            std::cout << "" << std::endl;
            printAllWestern();
            //break;

        }

        else if (option == 4) {
            break;
        }
        else
        {
            cout << "Invalid Option. Please try again" << endl;
        }
    }

}

void createOrder()
{
    double charge = 0;

    while (true)
    {
        List<Dish> tempDL;

        cout << "+---------------Order Page---------------+" << std::endl;
        printAllDish();
        //cout << "" << endl;
        cout << "[1] Add Dish" << std::endl;
        cout << "" << std::endl;
        cout << "[2] Finish Add Dish" << std::endl;
        cout << "" << endl;
        cout << "[3] Cancel" << std::endl;
        cout << "" << endl;

        int option;
        cout << "Please enter an option: ";
        cin >> option;
        if (option == 2)
        {
            cout << TemplateCust.getName() << endl;

            for (int i = 0; i < tempDL.getLength(); i++) {
                auto dish = tempDL.get(i);
                cout << dish.getCuisine() << " " << dish.getFoodName() << " " << dish.getPortion() << " " << "$" << dish.getCharge() << endl;
            }
            /*for (int i = 0; i < TemplateCust.orderItem.orderList.getLength(); i++)
            {
                auto dish = TemplateCust.orderItem.orderList.get(i);
                cout << dish.getCuisine() << " " << dish.getFoodName() << dish.getPortion() << " $" << dish.getCharge() << endl;
            }*/
            cout << "Total cost - $" << charge << endl;
            Order order = Order(TemplateCust.getName(), tempDL, false, charge, branch);
            //orderQueue.enqueue(Order(TemplateCust.getName(), TemplateCust.orderItem.orderList, false, charge, branch));
            TemplateCust.oL.add(order);
            if (branch == "1") {
                orderQueue.enqueue(order);
                tempDL.clear();
            }

            else if (branch == "2") {
                orderQueue2.enqueue(order);
                tempDL.clear();

            }
            
            else {
                orderQueue3.enqueue(order);
                tempDL.clear();

            }
            break;
        }

        else if(option == 1)
        {
            int choice;
            cout << "Please enter the index of a dish: ";
            cin >> choice;
            for (int i = 0; i < dishList.getLength(); i++)
            {
                if (choice - 1 == i)
                {
                    //TemplateCust.orderItem.orderList.add(dishList.get(i));
                    tempDL.add(dishList.get(i));
                    charge += dishList.get(i).CalculateCharges();
                }
            }
        }
        else if (option == 3)
        {
            break;
        }
        else
        {
            cout << "Invalid input please try again" << endl;
        }
    }
}

void cancelOrder()
{
    if (orderQueue.isEmpty())
    {
        cout << "You have no made an order" << endl;
        return;
    }
    // Move from Queue to List
    for (int i = 0; i < orderQueue.getLength(); i++)
    {
        tempList.add(orderQueue.getFront());
        orderQueue.dequeue();
    }

    for (int i = 0; i < tempList.getLength(); i++)
    {
        auto order = tempList.get(i);
        if (order.getCustName() == TemplateCust.getName())
        {
              
            if (tempList.getLength() == 0)
            {
                cout << "You have not made an order" << endl;
                break;
            }
            cout << "[" << i+1 << "] " << order.getCustName() << " $" << order.getCharge() << endl;
        }
    }
    int choice;
    cout << "Please select an order to cancel:  ";
    cin >> choice;
    tempList.remove(choice - 1);
    cout << "Order has canceled" << endl;
    if (tempList.getLength() > 0)
    {
        for (int i = 0; i < tempList.getLength();i++)
        {
            orderQueue.enqueue(tempList.get(i));
            tempList.remove(i);
        }
    }  
}

std::string AdminPage(Admin admin) {
    std::string option;

    std::cout << "+---------------Welcome " << admin.getUsername() << "---------------+" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "[1] View orders" << std::endl;

    std::cin >> option;
    return option;


}


std::string UserPage(Customer customer) {
    std::string option;

    std::cout << "+---------------Welcome To  Restaurant, " << customer.getName() << "---------------+" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "[1] View Menu" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "[2] Place an order" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "[3] Cancel an order" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "[4] View invoice" << std::endl;
    std::cout << endl;
    std::cout << "[5] Exit" << std::endl;
    std::cout << endl;

    std::cin >> option;
    return option;
    /*
    if (option == "1") {
        //filterDish();
        return option;

    }

    else if (option == "2") {
        //createOrder();
        return option;

    }

    else if (option == "3") {
        //cancelOrder();
        return option;

    }

    else if (option == "4") {
        std::cout << endl;
        std::cout << "Exiting application...." << std::endl;
        
    }

    else {
        std::cout << "Invalid input, try again" << std::endl;
        std::cout << "" << std::endl;
        UserPage(TemplateCust);

    }
    */
}


//OK
bool userLogin() {
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
            return true;

            

        }

        else {

        }
    }
    return false; //
}


bool adminLogin() {
    std::string userName;
    std::string password;

    std::cout << "Enter username: ";
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    std::getline(cin, userName);


    std::cout << "Enter password: ";
    std::cin >> password;
    std::cout << "" << std::endl;

    for (int i = 0; i < adminList.getLength(); i++) {
        Admin temp = adminList.get(i);
        if (temp.getUsername() == userName && temp.getPassword() == password) {
            Adm = temp;
            return true;
        }

        else {

        }
    }
    return false;
}

bool userRegister() {
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
            cout << "Username already taken, try another name. You can try " << c.getName() << "123123 instead" << endl;
            cout << "" << endl;
            isNewUser = false;
            return isNewUser; //

            //break;
        }
    }

    if (isNewUser == true)
    {
        int memberPoint = 0;
        std::string memberStatus = "Ordinary";
        List <Dish> dL;
        Membership member = Membership(memberStatus, memberPoint);
        List<Order> oL;

        //Order order = Order(customerName, dL, false, 0.0, "");
        Customer newCustomer = Customer(customerName, custPassword, oL, member);
        TemplateCust = newCustomer;
        customerList.add(TemplateCust);

        std::ofstream file("Customer.csv", ios::app); // Open file in append mode

        if (!file.is_open()) {
            cerr << "Error opening file: Customer.csv" << std::endl;
        }

        // Write customer data to the file in CSV format
        file << customerName << "," << custPassword << ","
            << memberStatus << "," << memberPoint << endl;

        file.close();
        return true; //
    }
    //UserPage(TemplateCust);
}


void viewIncomingOrders() {
    if (orderQueue.isEmpty()) {
        std::cout << "There are no incoming orders." << std::endl;
        return;
    }

    std::cout << "+-------------------------------------+" << std::endl;
    std::cout << "|            Incoming Orders          |" << std::endl;
    std::cout << "+-------------------------------------+" << std::endl;

    int i = 0;
    while (!orderQueue.isEmpty()) {
        Order order = orderQueue.getFront();
        orderQueue.dequeue();
        orderQueue.enqueue(order);  // Re-enqueue the order to maintain the original queue state

        std::cout << "Order [" << i + 1 << "]" << std::endl;
        std::cout << "Customer Name: " << order.getCustName() << std::endl;
        std::cout << "Total Cost: $" << order.getCharge() << std::endl;
        std::cout << "Branch: " << order.getBranch() << std::endl;
        std::cout << "Dishes: " << std::endl;
        for (int j = 0; j < order.getOrderList().getLength(); j++) {
            Dish dish = order.getOrderList().get(j);
            std::cout << " - " << dish.getFoodName() << ", " << dish.getPortion() << ", $" << dish.getCharge() << std::endl;
        }
        std::cout << std::endl;
        i++;
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
    std::cout << "5. View Incoming Orders" << std::endl; 
    std::cout << "" << std::endl;
    std::cout << "4. Exit app" << std::endl;
    std::cout << endl;
    std::cout << "Please choose your role: ";
    int option;
    std::cin >> option;
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;

    if (option == 1) {
            bool login = userLogin();
            if (login == true) {
                while (true) {
                    std::string choice = UserPage(TemplateCust);

                    if (choice == "1") {
                        filterDish();
                    }

                    else if (choice == "2") {
                        createOrder();

                    }
                    else if (choice == "3")
                    {
                        cancelOrder();
                    }

                    else if (choice == "4") {
                        List<Order> temp = TemplateCust.getOrderList();
                        if (temp.getLength() > 0) {
                            std::cout << temp.getLength();

                        }

                        else {
                            std::cout << "No orders" << std::endl;

                        }
                        
                        

                    }

                    else if (choice == "5") {
                        std::cout << endl;
                        std::cout << endl;
                        std::cout << "Logging out" << std::endl;
                        mainMenu();
                    }
                    else {
                        std::cout << "Invalid input try again" << std::endl;

                    }
                }
            }

            else {
                std::cout << "Invalid account try again" << std::endl;
                mainMenu();
            }
       
        
    }



    else if (option == 2) {
        bool AdmLogin = adminLogin();
        if (AdmLogin == true) {

            while (true) {
                std::string choice = AdminPage(Adm);
                if (choice == "1") {
                    viewIncomingOrders();

                }
                else {
                    std::cout << "Invalid option, try again. " << std::endl;
                    AdminPage(Adm);

                }
            }

        }

        else {
            std::cout << "Invalid credentials, try again. " << std::endl;
            mainMenu();
            
        }
    }



    else if (option == 3) {
        bool reg = userRegister();
        if (reg == true) {
            std::cout << "Account Created!" << std::endl;
            mainMenu();
        }

        else {
            mainMenu();
        }
    }

    else if (option == 4) {
        std::cout << "Exiting app... goodbye..." << std::endl;
        cout << branch;
    }
    else if (option == 5) {
        viewIncomingOrders();
    }

    else {
        std::cout << "Invalid input. Try again." << std::endl;
        mainMenu();
    }

} 


void selectBranch() {
    string opt;
    cout << "---------- Select a Branch ----------" << endl;
    for (int i = 0; i < branchList.getLength(); i++) {
        cout << "[" << i + 1 << "]" << branchList.get(i) << endl;
    }
    cout << "Select an option: ";
    cin >> opt;
    cout << endl;
    cout << endl;

    if (opt == "1") {
        branch = branchList.get(1 - 1);
        mainMenu();
    }

    else if (opt == "2") {
        branch = branchList.get(2 - 1);
        mainMenu();
    }

    else if (opt == "3") {
        branch = branchList.get(3 - 1);
        mainMenu();
    }

    else {
        cout << "Invalid option" << endl;
        selectBranch();
    }

}

int main()
{
    initAdmins();
    initBranch();
    readCustFile();
    readDishFile();
    selectBranch();
    //mainMenu();
}
            

