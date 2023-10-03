#include "driver.h"
#include "rider.h"
#include <list>
#include <fstream>
#include <cmath>
#include <iomanip>

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
            Rider rider;
            bool validAccount = isRiderNum(riderList, phoneNum, rider);
            if(validAccount)
            {
                //Driver_on_the_way
                if(rider.getState() == "Driver_on_the_way")
                {
                    userOut << "You have already requested a ride and your driver is on the way to the pickup location.";
                    return 0;
                }
                //During_the_trip         
                if(rider.getState() == "During_the_trip")
                {
                    userOut << "You can not request a ride at this moment as you are already on a trip.";
                    return 0;
                }
                //Ready_to_request
                Driver closestDriver;
                double distance = 0.0;
                bool driverFound = rider.closestDriver(driverList, closestDriver, distance);

                //driver found
                if(driverFound)
                {      
                    std::string message = "Ride requested for user " + rider.getFirstName() + 
                                          ", looking for an " + rider.getVehiclePref() + " vehicle.\n" +
                                          "Pick Up Location: " + rider.getPickupLocation() + 
                                          ", Drop Off Location: " + rider.getDropoffLocation() + ".\n" +
                                          "We have found the closest driver " + closestDriver.getFirstName() + 
                                          "(" + doubleToString(closestDriver.getRating(), 3) + ") for you.\n" +
                                          closestDriver.getFirstName() + " is now " + doubleToString(distance, 3) + 
                                          " miles away from you.";

                    /* update by index direclty or update by replacing old with updated */
                    userOut << message;

                }
                //driver not found
                else 
                {
                    std::string message = "Ride requested for user " +  rider.getDriverFirstName() +
                                          ", looking for a Luxury vehicle.\n" + "Pick Up Location: " + 
                                          rider.getPickupLocation() + ", Drop Off Location: " + 
                                          rider.getDropoffLocation() + " .\n" + "Sorry we can not " +
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

        }
        else
        {
            std::cerr << "Invalid Mode" << std::endl;
            exit(1);
        }
    }
    else
    {
        userOut << "Phone number is invalid."; 
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
