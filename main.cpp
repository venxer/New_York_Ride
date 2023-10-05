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
    //check for too few or too many arguments
    if(argc != 8)
    {
        std::cerr << "Invalid Inputs" << std::endl;
        exit(1);
    }
    //stores each input
    std::string driverInput = argv[1];
    std::string riderInput = argv[2];
    std::string userOutput = argv[3];
    std::string driverOutput = argv[4];
    std::string riderOutput = argv[5];
    std::string phoneNum = argv[6];
    std::string status = argv[7];

    //open output files
    std::ofstream userOut(userOutput);
    std::ofstream driverOut(driverOutput);
    std::ofstream riderOut(riderOutput);

    //for grammar
    std::string an_OR_a = "";

    //list of driver and rider objects from driverInput and riderOutput respectively
    std::list<Driver> driverList = readDriverInput(driverInput);
    std::list<Rider> riderList = readRiderInput(riderInput);

    //check if phone number is invalid
    if(validPhoneNumFormat(phoneNum))
    {
        /* request mode */
        if(status == "request")
        {
            //check if phone number belongs to a Rider from riderList
            std::list<Rider>::iterator riderIterator;
            bool validAccount = findRider(riderList, phoneNum, riderIterator);
            if(validAccount)
            {
                /* Rider State: Driver_on_the_way */
                if(riderIterator->getState() == "Driver_on_the_way")
                {
                    userOut << "You have already requested a ride and your driver is on the way to the pickup location.";
                }

                /* Rider State: During_the_trip */   
                if(riderIterator->getState() == "During_the_trip")
                {
                    userOut << "You can not request a ride at this moment as you are already on a trip.";
                }

                /* Rider State: Ready_to_request */
                //finds the closest Driver to Rider
                double distance = 0.0;
                std::list<Driver>::iterator closestDriverIterator;
                bool driverFound = riderIterator->closestDriver(driverList, distance, closestDriverIterator);
                /* Driver found for Rider */
                if(driverFound)
                {   
                    //output message
                    if(riderIterator->getVehiclePref() == "Economy") an_OR_a += "n";
                    std::string message = "Ride requested for user " + riderIterator->getFirstName() + 
                                          ", looking for a" + an_OR_a + " " + riderIterator->getVehiclePref() + " vehicle.\n" +
                                          "Pick Up Location: " + riderIterator->getPickupLocation() + 
                                          ", Drop Off Location: " + riderIterator->getDropoffLocation() + ".\n" +
                                          "We have found the closest driver " + closestDriverIterator->getFirstName() + 
                                          "(" + doubleToString(closestDriverIterator->getRating(), 3) + ") for you.\n" +
                                          closestDriverIterator->getFirstName() + " is now " + doubleToString(distance, 3) + 
                                          " miles away from you.";
                    //update Rider with Driver info
                    riderIterator->setDriverFirstName(closestDriverIterator->getFirstName());
                    riderIterator->setDriverLastName(closestDriverIterator->getLastName());
                    riderIterator->setDriverPhoneNum(closestDriverIterator->getPhoneNum());
                    //update state of Rider
                    riderIterator->setState("Driver_on_the_way");
                    //update Driver with Rider info
                    closestDriverIterator->setRiderFirstName(riderIterator->getFirstName());
                    closestDriverIterator->setRiderLastName(riderIterator->getLastName());
                    closestDriverIterator->setRiderPhoneNum(riderIterator->getPhoneNum());
                    //update state of Driver
                    closestDriverIterator->setState("On_the_way_to_pickup");
                    //output message
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
                /* Driver not found */
                else 
                {
                    if(riderIterator->getVehiclePref() == "Economy") an_OR_a += "n";
                    std::string message = "Ride requested for user " +  riderIterator->getDriverFirstName() +
                                          ", looking for a" + an_OR_a + " " + riderIterator->getVehiclePref() + " vehicle.\n" + 
                                          "Pick Up Location: " + riderIterator->getPickupLocation() + ", Drop Off Location: " + 
                                          riderIterator->getDropoffLocation() + ".\n" + "Sorry we can not " +
                                          "find a driver for you at this moment.";
                    userOut << message;
                }
            }
            //phone number does not belong to any Rider
            else
            {
                userOut << "Account does not exist.";
            }
        }
        /* cancel mode */
        else if(status == "cancel")
        {
            //find the Rider or Driver the number belongs to
            std::list<Driver>::iterator driverIterator;
            bool validDriverAccount = findDriver(driverList, phoneNum, driverIterator);
            std::list<Rider>::iterator riderIterator;
            bool validRiderAccount = findRider(riderList, phoneNum, riderIterator);
            /* Driver's Account */
            if(validDriverAccount)
            {
                /* Driver State: Available OR During_the_trip*/
                if(driverIterator->getState() != "On_the_way_to_pickup")
                {
                    userOut << "You can only cancel a ride request if you are currently on the way to the pickup location.";
                }
                /* Driver State: On_the_way_to_pickup */
                else
                {
                    //uses phone number of Rider from Driver's data to find pointer to Rider
                    std::list<Rider>::iterator riderWithDriver;
                    findRider(riderList, driverIterator->getRiderPhoneNum(), riderWithDriver);
                    //finding new Driver for Rider
                    double distance = 0.0;
                    std::list<Driver>::iterator newClosestDriver;
                    bool driverFound = riderWithDriver->closestDriver(driverList, distance, newClosestDriver);
                    /* new Driver found */
                    if(driverFound)
                    {
                        //output message
                        if(riderWithDriver->getVehiclePref() == "Economy") an_OR_a += "n";
                        std::string message = "Your driver " + driverIterator->getFirstName() + 
                                              " has cancelled the ride request. We will now find a new driver for you.\n" + 
                                              "Ride requested for user " + riderWithDriver->getFirstName() + 
                                              ", looking for a" + an_OR_a + " " + riderWithDriver->getVehiclePref() + " vehicle.\n" +
                                              "Pick Up Location: " + riderWithDriver->getPickupLocation() + 
                                              ", Drop Off Location: " + riderWithDriver->getDropoffLocation() + ".\n" +
                                              "We have found the closest driver " + newClosestDriver->getFirstName() + 
                                              "(" + doubleToString(newClosestDriver->getRating(), 3) + ") for you.\n" +
                                              newClosestDriver->getFirstName() + " is now " + doubleToString(distance, 3) + 
                                              " miles away from you.";
                        //update Rider with newDriver info
                        riderWithDriver->setDriverFirstName(newClosestDriver->getFirstName());
                        riderWithDriver->setDriverLastName(newClosestDriver->getLastName());
                        riderWithDriver->setDriverPhoneNum(newClosestDriver->getPhoneNum());
                        //update state of rider
                        riderWithDriver->setState("Driver_on_the_way");
                        //update newDriver with Rider info
                        newClosestDriver->setRiderFirstName(riderWithDriver->getFirstName());
                        newClosestDriver->setRiderLastName(riderWithDriver->getLastName());
                        newClosestDriver->setRiderPhoneNum(riderWithDriver->getPhoneNum());
                        //update state of newDriver
                        newClosestDriver->setState("On_the_way_to_pickup");
                        //update oldDriver to no Rider
                        driverIterator->setRiderFirstName("null");
                        driverIterator->setRiderLastName("null");
                        driverIterator->setRiderPhoneNum("null");
                        //update state of oldDriver
                        driverIterator->setState("Available");
                        //output message
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
                    /* newDriver not found*/
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
            /* Rider's Account */
            else if(validRiderAccount)
            {
                /* Rider State: Ready_to_request OR During_the_trip */
                if(riderIterator->getState() != "Driver_on_the_way")
                {
                    userOut << "You can only cancel a ride request if your driver is currently on the way to the pickup location.";
                }
                /* Rider State: Driver_on_the_way */
                else
                {
                    std::list<Driver>::iterator driverWithRiderIterator;
                    findDriver(driverList, riderIterator->getDriverPhoneNum(), driverWithRiderIterator);
                    //update Driver to no Rider
                    driverWithRiderIterator->setRiderFirstName("null");
                    driverWithRiderIterator->setRiderLastName("null");
                    driverWithRiderIterator->setRiderPhoneNum("null");
                    //update state of Driver
                    driverWithRiderIterator->setState("Available");
                    //output message
                    std::string message = "Ride request for user " + riderIterator->getFirstName() +  " is now canceled by the user.";
                    //remove Rider from riderList
                    riderList.erase(riderIterator);
                    //output message
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
            }
            /* Phone number does not belong to a Rider or Driver*/
            else
            {
                userOut << "Account does not exist.";
            }
        }
        /* Mode is not request or cancel*/
        else
        {
            std::cerr << "Invalid Mode" << std::endl;
            exit(1);
        }
    }
    /* Invalid Phone number */
    else
    {
        userOut << "Phone number is invalid."; 
    }

    //close all files
    userOut.close();
    driverOut.close();
    riderOut.close();
    
    return 0;
}
/**
 * reads file with driver data and create and pushs a Driver object with
 * data from each line into a list
 * 
 * @param inputFile file with driver data with each driver seperated by line
 * 
 * @return a list of Driver objects, each with data from the like
 */
std::list<Driver> readDriverInput(std::string inputFile)
{
    std::list<Driver> driverInfo;
    //opens inputFile
    std::ifstream in_str(inputFile);
    //checks if inputFile is successfully opened
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

    //close inputFile
    in_str.close();
    return driverInfo;
}
/**
 * reads file with rider data and create and pushs a Rider object with
 * data from each line into a list
 * 
 * @param inputFile file with rider data with each rider seperated by line
 * 
 * @return a list of Rider objects, each with data from the like
 */
std::list<Rider> readRiderInput(std::string inputFile)
{
    std::list<Rider> riderInfo;
    //opens inputFile
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
    //reads each line of inputFile to create a rider object per line
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
        //add rider to list of riderInfo
        riderInfo.push_back(rider);       
    }

    //close inputFIle
    in_str.close();
    return riderInfo;
}
/**
 * checks if phone number is in the format of XXX-XXX-XXXX
 * where X represents any digits from 0-9
 * 
 * @param phoneNum input phone number to be validated
 * 
 * @return true if valid format, false otherwise
 */
bool validPhoneNumFormat(std::string phoneNum)
{
    if(phoneNum.length() != 12) return false;
    if(phoneNum[3] == '-' && phoneNum[7] == '-')
    {
        return true;
    }
    return false;
}
/**
 * turns a double to a string
 * 
 * @param num double as an input
 * @param targetLength desired length of output string
 * 
 * @return double as string with specific length
 */
std::string doubleToString(double num, int targetLength)
{
    //check length of targetLength
    if(targetLength > std::to_string(num).length())
    {
        return std::to_string(num);
    }
    return std::to_string(num).substr(0, targetLength);
}