#include "Admin.h"

Admin::Admin() {}

Admin::Admin(const std::string& username, const std::string& password, int branchID)
    : username(username), password(password), branchID(branchID) {}

Admin::~Admin() {}

std::string Admin::getUsername() const {
    return this->username;
}

std::string Admin::getPassword() const {
    return this->password;
}

int Admin::getBranchID() const {
    return this->branchID;
}

void Admin::setUsername(const std::string& username) {
    this->username = username;
}

void Admin::setPassword(const std::string& password) {
    this->password = password;
}

void Admin::setBranchID(int branchID) {
    this->branchID = branchID;
}
