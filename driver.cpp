#include "driver.h"
#include <iostream>

//constuctor
Driver::Driver(std::string firstName,
               std::string lastName,
               std::string gender,
               unsigned int age,
               std::string phoneNum,
               double rating,
               double latitude,
               double longitude,
               std::string vehicleType,
               std::string state,
               std::string riderFirstName,
               std::string riderLastName,
               std::string riderPhoneNum)
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

std::string Driver::getFirstName(){return firstName;}
std::string Driver::getLastName(){return lastName;}
std::string Driver::getGender(){return gender;}
unsigned int Driver::getAge(){return age;}
std::string Driver::getPhoneNum(){return phoneNum;}
double Driver::getRating(){return rating;}
double Driver::getLatitude(){return latitude;}
double Driver::getLongitude(){return longitude;}
std::string Driver::getVehicleType(){return vehicleType;}
std::string Driver::getstate(){return state;}
std::string Driver::getRiderFirstName(){return riderFirstName;}
std::string Driver::getRiderLastNam(){return riderLastName;}
std::string Driver::getRiderPhoneNum(){return riderPhoneNum;}

std::ostream &operator<<(std::ostream &out_str, const Driver &driver);
{

}