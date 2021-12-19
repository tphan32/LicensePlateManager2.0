#pragma once

#include <string>
#include <iostream>
typedef std::string PlateNumber;

struct LicensePlateInfo {
    double height = -1.0;
    double weight = -1.0;
    int age  = -1;
    PlateNumber plate_number = "";
    std::string first_name = "";
    std::string last_name = "";
    std::string date_of_birth = "";
    std::string address = "";

    LicensePlateInfo() {};

    LicensePlateInfo(std::string first_name, std::string last_name, std::string date_of_birth, std::string address,         \
                    int age, double height, double weight) : height(height), weight(weight), age(age), plate_number(""),    \
                    first_name(first_name), last_name(last_name), date_of_birth(date_of_birth), address(address) {};
                    
    LicensePlateInfo(PlateNumber plate_number, std::string first_name, std::string last_name, std::string date_of_birth,    \
                    std::string address, int age, double height, double weight) : height(height), weight(weight), age(age), \
                    plate_number(plate_number), first_name(first_name), last_name(last_name), date_of_birth(date_of_birth), \
                    address(address) {};
    
};
/*
* Overloaded operator<< used to insert data stored in line into a LicensePlateInfo object
* @params plate_info A LicensePlateInfo object used to store information read from line
* @params line       A string object, extracted from a csv file, which contain LicensePlateInfo's data
*/
LicensePlateInfo& operator<<(LicensePlateInfo& plate_info, const std::string& line);

/*
* A helper function for opertator<<. This helps to extract pieces of information stored in str
* @param str     A string object containing information about a license plate
* @param idx_ptr Offset to where we begin to read data in str
*/
std::string SubstrFromPosToDel(const std::string& str, size_t* idx_ptr);