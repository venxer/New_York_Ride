#include "driver.h"
#include <iostream>

//constuctor
Driver::Driver(std::string firstName = "",
               std::string lastName = "",
               std::string gender = "",
               unsigned int age = 0,
               std::string phoneNum = "",
               double rating = 0.0,
               double latitude = 0.0,
               double longitude = 0.0,
               std::string vehicleType = "",
               std::string state = "",
               std::string riderFirstName = "",
               std::string riderLastName = "",
               std::string riderPhoneNum = "")
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->gender = gender;
    this->age = age;
    this->phoneNum = phoneNum;
    this->rating = rating;
    this->latitude = latitude;
    this->longitude = longitude;
    this->vehicleType = vehicleType;
    this->state = state;
    this->riderFirstName = riderFirstName;
    this->riderLastName = riderLastName;
    this->riderPhoneNum = riderPhoneNum;
}

//getters
std::string Driver::getFirstName()const{return firstName;}
std::string Driver::getLastName()const{return lastName;}
std::string Driver::getGender()const{return gender;}
unsigned int Driver::getAge()const{return age;}
std::string Driver::getPhoneNum()const{return phoneNum;}
double Driver::getRating()const{return rating;}
double Driver::getLatitude()const{return latitude;}
double Driver::getLongitude()const{return longitude;}
std::string Driver::getVehicleType()const{return vehicleType;}
std::string Driver::getstate()const{return state;}
std::string Driver::getRiderFirstName()const{return riderFirstName;}
std::string Driver::getRiderLastNam()const{return riderLastName;}
std::string Driver::getRiderPhoneNum()const{return riderPhoneNum;}

//setters
void Driver::setState(std::string state)
{
    /*
     *valid states: 
     *Available
     *On_the_way_to_pickup
     *During_the_trip
     */ 
    this->state = state;
}
void Driver::setRiderFirstName(std::string riderFirstName)
{
    this->riderFirstName = riderFirstName;
}
void Driver::setRiderLastNam(std::string riderLastName)
{
    this->riderLastName = riderLastName;
}
void Driver::setRiderPhoneNum(std::string riderPhoneNum)
{
    this->riderPhoneNum = riderPhoneNum;
}

std::ostream &operator<<(std::ostream &out_str, const Driver &driver)
{
    out_str << "driver" << std::endl;
    return out_str;
}