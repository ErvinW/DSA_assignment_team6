#pragma once
#include <string>

using namespace std;

class Admin {
private:
    std::string username;
    std::string password;
    int branchID;

public:
    Admin();
    Admin(string username, string password, int branchID);
    ~Admin();

    // getters
    std::string getUsername();
    std::string getPassword();
    int getBranchID();

    // setters
    void setUsername(std::string username);
    void setPassword(std::string password);
    void setBranchID(int branchID);
};
