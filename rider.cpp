#include "rider.h"
#include <iostream>
#include <list>

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
std::string Rider::getFirstName()const{return firstName;}
std::string Rider::getLastName()const{return lastName;}
std::string Rider::getGender()const{return gender;}
unsigned int Rider::getAge()const{return age;}
std::string Rider::getPhoneNum()const{return phoneNum;}
double Rider::getRating()const{return rating;}
std::string Rider::getPickupLocation()const{return pickupLocation;}
double Rider::getPickupLatitude()const{return pickupLatitude;}
double Rider::getPickupLongitude()const{return pickupLongitude;}
std::string Rider::getDropoffLocation()const{return dropoffLocation;}
double Rider::getDropoffLatitude()const{return dropoffLatitude;}
double Rider::getDropoffLongitude()const{return dropoffLongitude;}
std::string Rider::getVehiclePref()const{return vehiclePref;}
std::string Rider::getState()const{return state;}
std::string Rider::getDriverFirstName()const{return driverFirstName;}
std::string Rider::getDriverLastName()const{return driverLastName;}
std::string Rider::getDriverPhoneNum()const{return driverPhoneNum;}

//setters
void Rider::setState(std::string state)
{
    /* 
     *valid states:
     *Ready_to_request
     *Driver_on_the_way
     *During_the_trip
     */
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

//checks if a any rider has the phone number
bool isRiderNum(std::list<Rider> &riderList, std::string num)
{
    for(Rider rider : riderList)
    {
        if(rider.getPhoneNum() == num)
        {
            return true;
        }
    }
    return false;
}
std::ostream &operator<<(std::ostream &out_str, const Rider &rider)
{
    out_str << rider.getFirstName() << " " << rider.getLastName() << " " 
            << rider.getGender() << " " << rider.getAge() << " " 
            << rider.getPhoneNum() << " " << rider.getRating() << " " 
            << rider.getPickupLocation() << " " << rider.getPickupLatitude() << " " 
            << rider.getPickupLongitude() << " " << rider.getDropoffLocation() << " " 
            << rider.getDropoffLatitude() << " " << rider.getDropoffLongitude() << " " 
            << rider.getVehiclePref() << " " << rider.getState() << " " 
            << rider.getDriverFirstName() << " " << rider.getDriverLastName() 
            << " " << rider.getDriverPhoneNum() << "\n";
    return out_str;
}