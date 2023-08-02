#pragma once
#include <string>

class Admin {
private:
    std::string username;
    std::string password;
    int branchID;

public:
    Admin();
    Admin(const std::string& username, const std::string& password, int branchID);
    ~Admin();

    // getters
    std::string getUsername() const;
    std::string getPassword() const;
    int getBranchID() const;

    // setters
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setBranchID(int branchID);
};
