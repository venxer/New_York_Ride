#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <iostream>

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
        Driver(std::string firstName,
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
               std::string riderPhoneNum);

        std::string getFirstName();
        std::string getLastName();
        std::string getGender();
        unsigned int getAge();
        std::string getPhoneNum();
        double getRating();
        double getLatitude();
        double getLongitude();
        std::string getVehicleType();
        std::string getstate();
        std::string getRiderFirstName();
        std::string getRiderLastNam();
        std::string getRiderPhoneNum();
    
};

std::ostream &operator<<(std::ostream &out_str, const Driver &driver);

#endif