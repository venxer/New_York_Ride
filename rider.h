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
};

std::ostream &operator<<(std::ostream &out_str, const Rider &rider);

#endif