#include "Admin.h"

Admin::Admin() {}

Admin::Admin(std::string un, std::string pwd, int bID)
{
    username = un;
    password = pwd;
    branchID = bID;
}

Admin::~Admin() {}

std::string Admin::getUsername(){
    return username;
}

std::string Admin::getPassword(){
    return password;
}

int Admin::getBranchID()  
{
    return branchID;
}

void Admin::setUsername(std::string un) {
    username = un;
    
}

void Admin::setPassword(std::string pwd) {
    password = pwd;
    
}

void Admin::setBranchID(int bID) {
    branchID = bID;
}
