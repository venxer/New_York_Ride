#include "driver.h"
#include "rider.h"
#include "list"
#include "fstream"

std::list<Driver> readDriverInput(std::string inputFile);
std::list<Rider> readRiderInput(std::string inputFile);
bool validPhoneNumFormat(std::string phoneNum);

int main(int argc, char const *argv[])
{
    std::string driverInput = argv[1];
    std::string riderInput = argv[2];
    std::string updateDriverOutput = argv[3];
    std::string updateRriverOutput = argv[4];
    std::string phoneNum = argv[5];
    std::string status = argv[6];

    std::list<Driver> driverList = readDriverInput(driverInput);
    std::list<Rider> riderList = readRiderInput(riderInput);

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
    if(phoneNum.length() < 8) return false;
    if(phoneNum[3] == '-' && phoneNum[7] == '-')
    {
        return true;
    }
    return false;
}




