#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <iostream>
#include <list>

class Driver
{
    private:
        std::string firstName;
        std::string lastName;
        std::string gender;
        unsigned int age;
        std::string phoneNum;
        double rating;
        double latitude;
        double longitude;
        std::string vehicleType;
        std::string state;
        std::string riderFirstName;
        std::string riderLastName;
        std::string riderPhoneNum;
        
    public:
        Driver(std::string firstName = "",
               std::string lastName = "",
               std::string gender = "",
               unsigned int age = 0,
               std::string phoneNum = "",
               double rating = 0.0,
               double latitude = 0.0,
               double longitude = 0.0,
               std::string vehicleType = "",
               std::string state = "",
               std::string riderFirstName = "null",
               std::string riderLastName = "null",
               std::string riderPhoneNum = "null");

        //getters
        std::string getFirstName()const;
        std::string getLastName()const;
        std::string getGender()const;
        unsigned int getAge()const;
        std::string getPhoneNum()const;
        double getRating()const;
        double getLatitude()const;
        double getLongitude()const;
        std::string getVehicleType()const;
        std::string getState()const;
        std::string getRiderFirstName()const;
        std::string getRiderLastName()const;
        std::string getRiderPhoneNum()const;
    
        //setters
        void setState(std::string state);
        void setRiderFirstName(std::string riderFirstName);
        void setRiderLastName(std::string riderLastName);
        void setRiderPhoneNum(std::string riderPhoneNum);

        //functions
        
};
bool findDriver(std::list<Driver> &driverList, std::string riderNum, 
                std::list<Driver>::iterator &driverWithRiderIterator);
bool isDriverNum(std::list<Driver> &driverList, const std::string num, 
                 std::list<Driver>::iterator &driverIterator);
std::ostream &operator<<(std::ostream &out_str, const Driver &driver);

#endif