#include "driver.h"
#include "rider.h"
#include <list>
#include <fstream>
#include <cmath>

std::list<Driver> readDriverInput(std::string inputFile);
std::list<Rider> readRiderInput(std::string inputFile);
bool validPhoneNumFormat(std::string phoneNum);

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
            if(isRiderNum(riderList, phoneNum))
            {
                Driver closestDriver = 
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