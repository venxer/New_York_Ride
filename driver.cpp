#include "driver.h"
#include <iostream>
#include <list>

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
std::string Driver::getState()const{return state;}
std::string Driver::getRiderFirstName()const{return riderFirstName;}
std::string Driver::getRiderLastName()const{return riderLastName;}
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
void Driver::setRiderLastName(std::string riderLastName)
{
    this->riderLastName = riderLastName;
}
void Driver::setRiderPhoneNum(std::string riderPhoneNum)
{
    this->riderPhoneNum = riderPhoneNum;
}

//functions
//find the driver who the riderNum belongs to
bool findDriver(std::list<Driver> &driverList, std::string riderNum, 
                std::list<Driver>::iterator &driverWithRiderIterator)
{
    for(auto it = driverList.begin(); it != driverList.end(); ++it)
    {
        if(it->getRiderPhoneNum() == riderNum)
        {
            driverWithRiderIterator = it;
            return true;
        }
    }
    return false;
}

bool isDriverNum(std::list<Driver> &driverList, const std::string num, 
                 std::list<Driver>::iterator &driverIterator)
{
    for(auto it = driverList.begin(); it != driverList.end(); ++it)
    {
        if(it->getPhoneNum() == num)
        {
            driverIterator = it;
            return true;
        }
    }
    return false;
}

std::ostream &operator<<(std::ostream &out_str, const Driver &driver)
{
    out_str << driver.getFirstName() << " " << driver.getLastName() << " " 
            << driver.getGender() << " " << driver.getAge() << " " 
            << driver.getPhoneNum() << " " << driver.getRating() << " " 
            << driver.getLatitude() << " " << driver.getLongitude() << " " 
            << driver.getVehicleType() << " " << driver.getState() << " " 
            << driver.getRiderFirstName() << " " << driver.getRiderLastName() << " "
            << driver.getRiderPhoneNum() << "\n";
    return out_str;
}