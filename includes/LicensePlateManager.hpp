#pragma once

#include "LicensePlateInfo.hpp"
#include "LicensePlateScanner.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <cstdlib>
#include <string>
#include <ctype.h>
#include <vector>
#include <map>
#include <cmath>
#include <bits/stdc++.h>

#include <sqlite3.h> 

#define ZERO 0.0001

class LicensePlateManager {
    public:
        /*
        * Default constructor
        */
        LicensePlateManager() = default;

        /*
        * Initializes a list of license plates based on information contained in 
            * @param filename A string containing the directory of the file to be read from
        */
        LicensePlateManager(char* filename);

        /*
        * Destructor, deletes all license plates contained in the manager.
        */
        ~LicensePlateManager();

        bool IsCorrectFormat(const PlateNumber& plate_number);

        /*
        * Adds a license plate to plates_
            * @param plate The LicensePlateInfo to add to plates_
        */
        bool AddPlate(const LicensePlateInfo& plate);

        /*
        * Updates the license plate number with the LicensePlateInfo matches the driver's name
            * @param driver's first name
            * @param driver's last name
            * @param the updated plate number
        */
        void UpdateLicensePlate(const PlateNumber& old_plate_number, const PlateNumber& new_plate_number);

        /*
        * Updates the LicensePlateInfo based on the plate number given
            * @param plate number 
            * @param the updated address
        */
        void UpdateAddress(const PlateNumber& plate_number, const std::string& new_address);

        /*
        * Updates the LicensePlateInfo based on the plate number given
            * @param plate number 
            * @param the updated age
        */
        void UpdateAge(const PlateNumber& plate_number, int update_age);

        /*
        * Updates the LicensePlateInfo based on the plate number given
            * @param plate number 
            * @param the updated height
        */
        void UpdateHeight(const PlateNumber& plate_number, double update_height);

        /*
        * Updates the LicensePlateInfo based on the plate number given
            * @param plate number 
            * @param the updated weight
        */
        void UpdateWeight(const PlateNumber& plate_number, double update_weight);

        /*
        * Finds a license plate.
            * @param plate_number The license plate number to search for
            * @return A LicensePlate with a matching plate_number or nullptr if there is no match.
        */
        LicensePlateInfo FindLicensePlate(const std::string& plate_number);

        /*
        * Finds a license plate based on the name of the driver
            * @param driver's full name 
            * @return A LicensePlate if found a match else returns a nullptr
        */
        std::vector<LicensePlateInfo> FindLicensePlate(const std::string&, const std::string&);

        /*
        * Checks a given license plate is a valid Illinois license plate.
            * @param plate The license plate being checked.
            * @return true if the license plate is a valid Illinois license plate, false otherwise.
        */
        bool IsValid(const LicensePlateInfo& plate);

        /*
        * Helper function for IsUnique(), determines whether a plate number is already added to plates_
            * @param number The plate number to search for
            * @return true if the plate number does not exist in plates_, false otherwise
        */
        bool IsUniqueNumber(const std::string& number);

        /* Creates a LicensePlate with an automatically generated plate number.
            * @param first_name
            * @param last_name
            * @param age
            * @param date_of_birth
            * @param address
            * @param height
            * @param weight
            * @return A LicensePlate with a valid plate number containing the given information.
        */
        LicensePlateInfo GeneratePlate(const std::string& first_name, const std::string& last_name, int age, 
                                        const std::string& date_of_birth, const std::string& address, double height, double weight);


        /* Creates a LicensePlate with an automatically generated plate number.
            @return A PlateNumber that contains a valid plat number and is not duplicated.
        */
        PlateNumber GeneratePlateNumber();


        /* Creates a LicensePlate with a given plate number if it is valid.
            * @param plate_number
            * @param first_name
            * @param last_name
            * @param age
            * @param date_of_birth
            * @param address
            * @param height
            * @param weight
            * @return A LicensePlate containing the given information, nullptr if plate_number is invalid.
        */
        LicensePlateInfo CreatePlate(const PlateNumber& plate_number, const std::string& first_name, const std::string& last_name, 
                                    int age, const std::string& date_of_birth, const std::string& address, double height, double weight);


        /* Removes a LicensePlate with a given plate number.
            * @param plate_number The plate number to be removed.
            * @return True if the removal is successful, false otherwise.
        */
        bool RemovePlate(const std::string& plate_number);

        /*  Scans an image of the format png and returns a license plate number
        *   @param ...
        *   @return The scanned license plate number
        */
        std::string ScanPlate(const std::string& filename);


    private:
        PlateNumber initial_serial_ = "AQ11001";                 //The initial serial number to generate plate numbers from
        PlateNumber last_serial_ = "";                        //The last serial number that was automatically generated

        sqlite3 *db_;
        
        /*
        * Helper function for GeneratePlate(), increments a generated license plate serial number
        * @param number The plate number to be incremented
        */
        std::string IncrementPlateNumber(PlateNumber number);

        void GetDataQuery(const std::string& query, char ***result, int& row, int& col, const std::string& op);
};

/*
* Helper function for printing out the information of a license plate
* @param os indicates which output stream will be used 
* @param lpi is a pointer pointing to a license plate to be printed
*/
std::ostream& operator<< (std::ostream& os, const LicensePlateInfo& lpi);

/*
* Helper function for printing out the information of a license plate
* @param os indicates which output stream will be used 
* @param plates_vec is a vector of license plates to be printed
*/
std::ostream& operator<< (std::ostream& os, const std::vector<LicensePlateInfo>& plates_vec);