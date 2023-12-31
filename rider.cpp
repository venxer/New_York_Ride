#include "rider.h"
#include <iostream>
#include <list>
#include <cmath>

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
void Rider::setDriverLastName(std::string driverLastName)
{
    this->driverLastName = driverLastName;
}
void Rider::setDriverPhoneNum(std::string driverPhoneNum)
{
    this->driverPhoneNum = driverPhoneNum;
}

//functions
/**
 * calculate the distance between two coordinates using Haversine formula
 * 
 * @param lat1 Latitude of the first coordinate
 * @param lon1 Longitude of the first coordinate
 * @param lat2 Latitude of the second coordinate
 * @param lon2 Longitude of the second coordinate
 * 
 * @return Distance between the two coordinates in miles.
 */
double calculateDistance(double lat1, double lon1, double lat2, double lon2) 
{
    const double radiusOfEarth = 6371.0; // Earth's radius in kilometers

    // convert latitude and longitude from degrees to radians
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    // Haversine formula
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1) * cos(lat2) * sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    // distance in kilometers
    double distanceKM = radiusOfEarth * c;
    // convert it to distance in miles
    double distanceMiles = distanceKM * 0.621371;

    return distanceMiles;
}
/**
 * finds the Rider from the given list associated number provided
 * 
 * @param riderList list of Riders to search through
 * @param num phone number of the targeted Rider
 * @param riderIterator points to the targeted Rider
 * 
 * @return true if Rider with specific number is found, false otherwise
 */
bool findRider(std::list<Rider> &riderList, const std::string num, 
                std::list<Rider>::iterator &riderIterator)
{
    for(std::list<Rider>::iterator it = riderList.begin(); it != riderList.end(); ++it)
    {
        if(it->getPhoneNum() == num)
        {
            riderIterator = it;
            return true;
        }
    }
    return false;
}
/**
 * Finds the closest available driver with the preferred vehicle 
 * type based on the rider's location.
 * 
 * @param driverList list of Drivers to search through
 * @param distanceOut reference to a double variable that will store the
 *                    shortest distance to the closest driver
 * @param closestDriverIterator reference to an iterator that will point to
 *                              the closest driver if one exists.
 * 
 * @return true if available driver with the preferred vehicle type is found, false otherwise.
 */
bool Rider::closestDriver(std::list<Driver> &driverList, double &distanceOut, 
                          std::list<Driver>::iterator &closestDriverIterator)
{
    bool driverIsFound = false;
    double shortestDistance = -1.0;
    
    for(std::list<Driver>::iterator it = driverList.begin(); it != driverList.end(); ++it)
    {
        //filters for available and preffered viechle
        if(it->getState() == "Available" && 
           it->getVehicleType() == vehiclePref)
        {
            driverIsFound = true;
            //gets distance between rider and driver
            double distance = calculateDistance(pickupLatitude, pickupLongitude,
                                                it->getLatitude(), it->getLongitude());
            //finds driver with shortest distance from rider
            if(shortestDistance == -1.0 || distance < shortestDistance)
            {
                shortestDistance = distance;
                closestDriverIterator = it;
                distanceOut = shortestDistance;
            }
        }
    }
    return driverIsFound;
}
/**
 * output stream in format firstName, lastName, gender, age, phoneNum, rating, pickupLocation, 
 * pickupLatitude, pickupLongitude, dropoffLocation, dropoffLatitude, dropoffLongitude, vehiclePref, 
 * state, driverFirstName, driverLastName, driverPhoneNum
 *
 * @param out_str output stream
 * @param rider rider object whose data would be printed
 * 
 * @return output stream with rider data seperated by space
 */
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