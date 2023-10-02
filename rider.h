#ifndef RIDER_H
#define RIDER_H

#include <string>

class Rider
{
    private:
        std::string firstName;
        std::string lastName;
        std::string gender;
        unsigned int age;
        std::string phoneNum;
        double rating;
        std::string pickupLocation;
        double pickupLatitude;
        double pickupLongitude;
        std::string dropoffLocation;
        double dropoffLatitude;
        double dropoffLongitude;
        std::string vehiclePref;
        std::string state;
        std::string driverFirstName;
        std::string driverLastName;
        std::string driverPhoneNum;
        
    public:
        Rider(std::string firstName,
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
              std::string driverPhoneNum);

        std::string getFirstName(){return firstName;}
        std::string getLastName(){return lastName;}
        std::string getGender(){return gender;}
        unsigned int getAge(){return age;}
        std::string getPhoneNum(){return phoneNum;}
        double getRating(){return rating;}
        std::string getPickupLocation(){return pickupLocation;}
        double getPickupLatitude(){return pickupLatitude;}
        double getPickupLongitude(){return pickupLongitude;}
        std::string getDropoffLocation(){return dropoffLocation;}
        double getDropoffLatitude(){return dropoffLatitude;}
        double getDropoffLongitude(){return dropoffLongitude;}
        std::string getVehiclePref(){return vehiclePref;}
        std::string getState(){return state;}
        std::string getDriverFirstName(){return driverFirstName;}
        std::string getDriverLastName(){return driverLastName;}
        std::string getDriverPhoneNum(){return driverPhoneNum;}
};

std::ostream &operator<<(std::ostream &out_str, const Rider &rider);

#endif