#include "rider.h"
#include <iostream>

//constuctor
Rider::Rider(std::string firstName,
             std::string lastName,
             std::string gender,
             unsigned int age,
             std::string phoneNum,
             double rating,
             std::string pickupLocation,
             double pickupLatitude,
             double pickupLongitude,
             std::string dropoffLocation,
             double dropoffLatitude,
             double dropoffLongitude,
             std::string vehiclePref,
             std::string state,
             std::string driverFirstName,
             std::string driverLastName,
             std::string driverPhoneNum)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->gender = gender;
    this->age = age;
    this->phoneNum = phoneNum;
    this->rating = rating;
    this->pickupLocation = pickupLocation;
    this->pickupLatitude = pickupLatitude;
    this->pickupLongitude = pickupLongitude;
    this->dropoffLocation = dropoffLocation;
    this->dropoffLatitude = dropoffLatitude;
    this->dropoffLongitude = dropoffLongitude;
    this->vehiclePref = vehiclePref;
    this->state = state;
    this->driverFirstName = driverFirstName;
    this->driverLastName = driverLastName;
    this->driverPhoneNum = driverPhoneNum;
}

//getters
std::string Rider::getFirstName(){return firstName;}
std::string Rider::getLastName(){return lastName;}
std::string Rider::getGender(){return gender;}
unsigned int Rider::getAge(){return age;}
std::string Rider::getPhoneNum(){return phoneNum;}
double Rider::getRating(){return rating;}
std::string Rider::getPickupLocation(){return pickupLocation;}
double Rider::getPickupLatitude(){return pickupLatitude;}
double Rider::getPickupLongitude(){return pickupLongitude;}
std::string Rider::getDropoffLocation(){return dropoffLocation;}
double Rider::getDropoffLatitude(){return dropoffLatitude;}
double Rider::getDropoffLongitude(){return dropoffLongitude;}
std::string Rider::getVehiclePref(){return vehiclePref;}
std::string Rider::getState(){return state;}
std::string Rider::getDriverFirstName(){return driverFirstName;}
std::string Rider::getDriverLastName(){return driverLastName;}
std::string Rider::getDriverPhoneNum(){return driverPhoneNum;}

//setters
void Rider::setState(std::string state)
{
    this->state = state;
}
void Rider::setDriverFirstName(std::string driverFirstName)
{
    this->driverFirstName = driverFirstName;
}
void Rider::setDriverLastNam(std::string driverLastName)
{
    this->driverLastName = driverLastName;
}
void Rider::setDriverPhoneNum(std::string driverPhoneNum)
{
    this->driverPhoneNum = driverPhoneNum;
}

std::ostream &operator<<(std::ostream &out_str, const Rider &rider)
{
    out_str << "rider" << std::endl;

    return out_str;
}