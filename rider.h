#ifndef RIDER_H
#define RIDER_H

#include <string>
#include <list>

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
        Rider(std::string firstName = "",
              std::string lastName = "",
              std::string gender = "",
              unsigned int age = 0,
              std::string phoneNum = "",
              double rating = 0.0,
              std::string pickupLocation = "",
              double pickupLatitude = 0.0,
              double pickupLongitude = 0.0,
              std::string dropoffLocation = "",
              double dropoffLatitude = 0.0,
              double dropoffLongitude = 0.0,
              std::string vehiclePref = "",
              std::string state = "",
              std::string driverFirstName = "",
              std::string driverLastName = "",
              std::string driverPhoneNum = "");

        //getters
        std::string getFirstName()const;
        std::string getLastName()const;
        std::string getGender()const;
        unsigned int getAge()const;
        std::string getPhoneNum()const;
        double getRating()const;
        std::string getPickupLocation()const;
        double getPickupLatitude()const;
        double getPickupLongitude()const;
        std::string getDropoffLocation()const;
        double getDropoffLatitude()const;
        double getDropoffLongitude()const;
        std::string getVehiclePref()const;
        std::string getState()const;
        std::string getDriverFirstName()const;
        std::string getDriverLastName()const;
        std::string getDriverPhoneNum()const;

        //setters
        void setState(std::string state);
        void setDriverFirstName(std::string driverFirstName);
        void setDriverLastNam(std::string driverLastName);
        void setDriverPhoneNum(std::string driverPhoneNum);

        //functions
        
};
bool isRiderNum(std::list<Rider> &riderList, std::string num);
std::ostream &operator<<(std::ostream &out_str, const Rider &rider);

#endif