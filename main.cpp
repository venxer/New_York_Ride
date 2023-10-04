#include "driver.h"
#include "rider.h"
#include <list>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <algorithm>

std::list<Driver> readDriverInput(std::string inputFile);
std::list<Rider> readRiderInput(std::string inputFile);
bool validPhoneNumFormat(std::string phoneNum);
std::string doubleToString(double num, int targetLength);

int main(int argc, char const *argv[])
{
    std::string driverInput = argv[1];
    std::string riderInput = argv[2];
    std::string userOutput = argv[3];
    std::string driverOutput = argv[4];
    std::string riderOutput = argv[5];
    std::string phoneNum = argv[6];
    std::string status = argv[7];

    std::ofstream userOut(userOutput);
    std::ofstream driverOut(driverOutput);
    std::ofstream riderOut(riderOutput);

    std::list<Driver> driverList = readDriverInput(driverInput);
    std::list<Rider> riderList = readRiderInput(riderInput);

    // std::list<Driver> driverList = readDriverInput("drivers.txt");
    // for(Driver driver : driverList)
    // {
    //     std::cout << driver.getLongitude() << std::endl;
    // }

    //check if phone number is invalid
    if(validPhoneNumFormat(phoneNum))
    {
        if(status == "request")
        {
            //checks if phoneNum is a rider's phone number
            std::list<Rider>::iterator riderIterator;
            bool validAccount = isRiderNum(riderList, phoneNum, riderIterator);
            if(validAccount)
            {
                //Driver_on_the_way
                if(riderIterator->getState() == "Driver_on_the_way")
                {
                    userOut << "You have already requested a ride and your driver is on the way to the pickup location.";
                    return 0;
                }
                //During_the_trip         
                if(riderIterator->getState() == "During_the_trip")
                {
                    userOut << "You can not request a ride at this moment as you are already on a trip.";
                    return 0;
                }
                //Ready_to_request
                double distance = 0.0;
                std::list<Driver>::iterator closestDriverIterator;
                bool driverFound = riderIterator->closestDriver(driverList, distance, closestDriverIterator);
                //driver found
                if(driverFound)
                {   
                    //output message
                    std::string message = "Ride requested for user " + riderIterator->getFirstName() + 
                                          ", looking for an " + riderIterator->getVehiclePref() + " vehicle.\n" +
                                          "Pick Up Location: " + riderIterator->getPickupLocation() + 
                                          ", Drop Off Location: " + riderIterator->getDropoffLocation() + ".\n" +
                                          "We have found the closest driver " + closestDriverIterator->getFirstName() + 
                                          "(" + doubleToString(closestDriverIterator->getRating(), 3) + ") for you.\n" +
                                          closestDriverIterator->getFirstName() + " is now " + doubleToString(distance, 3) + 
                                          " miles away from you.";
                    //add driver to rider info
                    riderIterator->setDriverFirstName(closestDriverIterator->getFirstName());
                    riderIterator->setDriverLastName(closestDriverIterator->getLastName());
                    riderIterator->setDriverPhoneNum(closestDriverIterator->getPhoneNum());
                    //set state of rider
                    riderIterator->setState("Driver_on_the_way");
                    //add rider to driver info
                    closestDriverIterator->setRiderFirstName(riderIterator->getFirstName());
                    closestDriverIterator->setRiderLastName(riderIterator->getLastName());
                    closestDriverIterator->setRiderPhoneNum(riderIterator->getPhoneNum());
                    //set state of driver
                    closestDriverIterator->setState("On_the_way_to_pickup");
                    //output Data
                    userOut << message;
                    //update Data
                    for(Driver driver : driverList)
                    {
                        driverOut << driver;
                    }
                    for(Rider rider : riderList)
                    {
                        riderOut << rider;
                    }
                }
                //driver not found
                else 
                {
                    std::string message = "Ride requested for user " +  riderIterator->getDriverFirstName() +
                                          ", looking for a Luxury vehicle.\n" + "Pick Up Location: " + 
                                          riderIterator->getPickupLocation() + ", Drop Off Location: " + 
                                          riderIterator->getDropoffLocation() + ".\n" + "Sorry we can not " +
                                          "find a driver for you at this moment.";
                    userOut << message;
                }
            }
            else
            {
                userOut << "Account does not exist.";
                return 0;
            }
        }
        else if(status == "cancel")
        {
            //find the account the number belongs to
            std::list<Driver>::iterator driverIterator;
            bool validDriverAccount = isDriverNum(driverList, phoneNum, driverIterator);
            std::list<Rider>::iterator riderIterator;
            bool validRiderAccount = isRiderNum(riderList, phoneNum, riderIterator);
            //if account belongs to driver
            if(validDriverAccount)
            {
                if(driverIterator->getState() != "On_the_way_to_pickup")
                {
                    userOut << "You can only cancel a ride request if you are currently on the way to the pickup location.";
                    return 0;
                }
                if(driverIterator->getState() == "On_the_way_to_pickup")
                {
                    //gets the pointer of rider driver is carrying
                    std::list<Rider>::iterator riderWithDriver;
                    isRiderNum(riderList, driverIterator->getRiderPhoneNum(), riderWithDriver);
                    //finding new driver
                    double distance = 0.0;
                    std::list<Driver>::iterator newClosestDriver;
                    bool driverFound = riderWithDriver->closestDriver(driverList, distance, newClosestDriver);
                    //new driver found
                    if(driverFound)
                    {
                        //output message
                        std::string message = "Your driver " + driverIterator->getFirstName() + 
                                              " has cancelled the ride request. We will now find a new driver for you.\n" + 
                                              "Ride requested for user " + riderWithDriver->getFirstName() + 
                                              ", looking for an " + riderWithDriver->getVehiclePref() + " vehicle.\n" +
                                              "Pick Up Location: " + riderWithDriver->getPickupLocation() + 
                                              ", Drop Off Location: " + riderWithDriver->getDropoffLocation() + ".\n" +
                                              "We have found the closest driver " + newClosestDriver->getFirstName() + 
                                              "(" + doubleToString(newClosestDriver->getRating(), 3) + ") for you.\n" +
                                              newClosestDriver->getFirstName() + " is now " + doubleToString(distance, 3) + 
                                              " miles away from you.";
                        //add newDriver to rider info
                        riderWithDriver->setDriverFirstName(newClosestDriver->getFirstName());
                        riderWithDriver->setDriverLastName(newClosestDriver->getLastName());
                        riderWithDriver->setDriverPhoneNum(newClosestDriver->getPhoneNum());
                        //set state of rider
                        riderWithDriver->setState("Driver_on_the_way");
                        //add rider to newDriver info
                        newClosestDriver->setRiderFirstName(riderWithDriver->getFirstName());
                        newClosestDriver->setRiderLastName(riderWithDriver->getLastName());
                        newClosestDriver->setRiderPhoneNum(riderWithDriver->getPhoneNum());
                        //set state of driver
                        newClosestDriver->setState("On_the_way_to_pickup");
                        //update old driver info
                        driverIterator->setRiderFirstName("null");
                        driverIterator->setRiderLastName("null");
                        driverIterator->setRiderPhoneNum("null");
                        driverIterator->setState("Available");
                        //output data
                        userOut << message;
                        //update Data
                        for(Driver driver : driverList)
                        {
                            driverOut << driver;
                        }
                        for(Rider rider : riderList)
                        {
                            riderOut << rider;
                        }
                    }
                    //new driver not found
                    else
                    {
                        std::string message = "Ride requested for user " +  riderWithDriver->getDriverFirstName() +
                                              ", looking for a Luxury vehicle.\n" + "Pick Up Location: " + 
                                              riderWithDriver->getPickupLocation() + ", Drop Off Location: " + 
                                              riderWithDriver->getDropoffLocation() + ".\n" + "Sorry we can not " +
                                              "find a driver for you at this moment.";
                        userOut << message;
                    }
                }
            }
            //if account belongs to rider
            else if(validRiderAccount)
            {
                //driver is not OTW to pickup
                if(riderIterator->getState() != "Driver_on_the_way")
                {
                    userOut << "You can only cancel a ride request if your driver is currently on the way to the pickup location.";
                    return 0;
                }
                //driver is OTW
                if(riderIterator->getState() == "Driver_on_the_way")
                {
                    std::list<Driver>::iterator driverWithRiderIterator;
                    findDriver(driverList, riderIterator->getPhoneNum(), driverWithRiderIterator);
                    //remove rider from driver
                    driverWithRiderIterator->setRiderFirstName("null");
                    driverWithRiderIterator->setRiderLastName("null");
                    driverWithRiderIterator->setRiderPhoneNum("null");
                    //set driver state
                    driverWithRiderIterator->setState("Available");
                    //output message
                    std::string message = "Ride request for user " + riderIterator->getFirstName() +  "is now canceled by the user.";
                    //remove rider
                    riderList.erase(riderIterator);
                    //output Data
                    userOut << message;
                    //update Data
                    for(Driver driver : driverList)
                    {
                        driverOut << driver;
                    }
                    for(Rider rider : riderList)
                    {
                        riderOut << rider;
                    }
                    return 0;
                }
            }
            else
            {
                userOut << "Account does not exist.";
                return 0;
            }
        }
        else
        {
            std::cerr << "Invalid Mode" << std::endl;
            exit(1);
        }
    }
    else
    {
        if(status == "request") userOut << "Phone number is invalid."; 
        return 0;
    }

    return 0;
}

std::list<Driver> readDriverInput(std::string inputFile)
{
    std::list<Driver> driverInfo;
    //opens inputFIle
    std::ifstream in_str(inputFile);
    //checks if inputFIle is successfully opened
    if(!in_str.good())
    {
        std::cerr << "Invalid Driver Input" << std::endl; 
        exit(1);
    }

    std::string firstName, lastName, gender, phoneNum, vehicleType, state,
                riderFirstName, riderLastName, riderPhoneNum;
    unsigned int age;
    double rating, latitude, longitude;
    //reads each line of inputFIle to create a driver object per line
    while(in_str >> firstName >> lastName >> gender >> age >> phoneNum
                 >> rating >> latitude >> longitude >> vehicleType >> state 
                 >> riderFirstName >> riderLastName >> riderPhoneNum)
    {
        Driver driver (firstName,lastName, gender, age, phoneNum, 
                       rating, latitude, longitude, vehicleType, state, 
                       riderFirstName, riderLastName, riderPhoneNum);
        driverInfo.push_back(driver);       
    }
    //close inputFIle
    in_str.close();
    return driverInfo;
}
std::list<Rider> readRiderInput(std::string inputFile)
{
    std::list<Rider> riderInfo;
    //opens inputFIle
    std::ifstream in_str(inputFile);
    //checks if inputFIle is successfully opened
    if(!in_str.good())
    {
        std::cerr << "Invalid Rider Input" << std::endl; 
        exit(1);
    }
    std::string firstName, lastName, gender, phoneNum, pickupLocation, dropoffLocation,
                vehiclePref, state, driverFirstName, driverLastName, driverPhoneNum;
    unsigned int age;
    double rating, pickupLatitude, pickupLongitude, dropoffLatitude, dropoffLongitude;

    //reads each line of inputFIle to create a rider object per line
    while(in_str >> firstName >> lastName >> gender >> age >> phoneNum >> rating >> 
                    pickupLocation >> pickupLatitude >> pickupLongitude >> 
                    dropoffLocation >> dropoffLatitude >> dropoffLongitude >> 
                    vehiclePref >> state >> 
                    driverFirstName >> driverLastName >> driverPhoneNum)
    {
        Rider rider(firstName,lastName, gender, age, phoneNum, rating, 
                    pickupLocation, pickupLatitude, pickupLongitude, 
                    dropoffLocation, dropoffLatitude, dropoffLongitude, 
                    vehiclePref, state, 
                    driverFirstName, driverLastName, driverPhoneNum);
        riderInfo.push_back(rider);       
    }
    //close inputFIle
    in_str.close();
    return riderInfo;
}
//checks length and format of phoneNum and returns true if valid
bool validPhoneNumFormat(std::string phoneNum)
{
    if(phoneNum.length() != 12) return false;
    if(phoneNum[3] == '-' && phoneNum[7] == '-')
    {
        return true;
    }
    return false;
}
//double to string as desired length
std::string doubleToString(double num, int targetLength)
{
    //check length of targetLength
    if(targetLength > std::to_string(num).length())
    {
        return std::to_string(num);
    }
    return std::to_string(num).substr(0, targetLength);
}
