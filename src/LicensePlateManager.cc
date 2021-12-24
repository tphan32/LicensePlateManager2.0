#include "LicensePlateManager.hpp"


static std::string valid_numbers = "0123456789";
static std::string valid_chars   = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

LicensePlateManager::LicensePlateManager(char* filename) {
    if (filename == NULL) {
        db_ = NULL;
    } else {
        int rc = sqlite3_open(filename, &db_);
        if(rc < 0)
            throw std::runtime_error("could not open file");
        else
            std::cout << "Successfully connected to the databse." << std::endl;

    }
}

LicensePlateManager::~LicensePlateManager() {
    if(!db_)
        return;
    sqlite3_close(db_);
}

bool LicensePlateManager::IsCorrectFormat(const PlateNumber& plate_number) {
    if (plate_number.size() == 7) {
        for (size_t i = 0; i < plate_number.size(); ++i) {
            if (i < 2 && valid_chars.find(plate_number[i]) == std::string::npos)
                return false;
            if (i >= 2 && valid_numbers.find(plate_number[i]) == std::string::npos)
                return false;
        }
    }
    else 
        return false;
    return true;
}

void LicensePlateManager::UpdateLicensePlate(const PlateNumber& old_plate_number, const PlateNumber& new_plate_number) {
    if(!IsCorrectFormat(old_plate_number) || !IsCorrectFormat(new_plate_number))
        throw std::runtime_error("Plate number(s) is(are) not in correct serial format!");

    if (!IsUniqueNumber(new_plate_number))
        throw std::runtime_error("New plate number already exists, cannot be updated/repeated");

    try {
        FindLicensePlate(old_plate_number);
    }
    catch (...) {
        throw;
    }

    char **result = 0;    /* Results of the query */
    int row = 0, col = 0;
    std::string query = "UPDATE LicensePlate SET plate = '" + new_plate_number + "' WHERE plate = '" + old_plate_number + "';"  +
                        "SELECT * FROM LicensePlate WHERE plate = '" + new_plate_number + "'";
    GetDataQuery(query, &result, row, col, "UpdateLicensePlate()");
    if (row <= 0) {
        sqlite3_free_table(result);
        throw std::runtime_error("Failed to update");
    }
    sqlite3_free_table(result);
}

void LicensePlateManager::UpdateAddress(const PlateNumber& plate_number, const std::string& new_address) {
    if (new_address.empty()) 
        throw std::runtime_error("Invalid Address");

    if (!IsCorrectFormat(plate_number))
        throw std::runtime_error("Invalid plate number");

    if (IsUniqueNumber(plate_number))
        throw std::runtime_error("Passed in plate number does not exist in the system");

    char **result = 0;    /* Results of the query */
    int row = 0, col = 0;
    std::string query = "UPDATE LicensePlate SET address = '" + new_address + "' WHERE plate = '" + plate_number + "';"  +
                        "SELECT address FROM LicensePlate WHERE plate = '" + plate_number + "'";
    GetDataQuery(query, &result, row, col, "UpdateAddress()");
    if (row <= 0 || result[1] != new_address) {
        sqlite3_free_table(result);
        throw std::runtime_error("Failed to update");
    }
    sqlite3_free_table(result);
}

void LicensePlateManager::UpdateAge(const PlateNumber& plate_number, int update_age) {
    if (update_age < 18)
        throw std::runtime_error("Invalid age");

    if (!IsCorrectFormat(plate_number))
        throw std::runtime_error("Invalid plate number");

    if (IsUniqueNumber(plate_number))
        throw std::runtime_error("Passed in plate number does not exist in the system");

    char **result = 0;    /* Results of the query */
    int row = 0, col = 0;
    
    std::string query = "UPDATE LicensePlate SET age = '" + std::to_string(update_age) + "' WHERE plate = '" + plate_number + "';"  +
                        "SELECT age FROM LicensePlate WHERE plate = '" + plate_number + "'";
    GetDataQuery(query, &result, row, col, "UpdateAge()");
    if (row <= 0 || atoi(result[1]) != update_age) {
        sqlite3_free_table(result);
        throw std::runtime_error("Failed to update");
    }
    sqlite3_free_table(result);
}

void LicensePlateManager::UpdateHeight(const PlateNumber& plate_number, double update_height) {
    if (update_height < 0)
        throw std::runtime_error("Invalid height");

    if (!IsCorrectFormat(plate_number))
        throw std::runtime_error("Invalid plate number");

    if (IsUniqueNumber(plate_number))
        throw std::runtime_error("Passed in plate number does not exist in the system");

    char **result = 0;    /* Results of the query */
    int row = 0, col = 0;
    
    std::string query = "UPDATE LicensePlate SET height = '" + std::to_string(update_height) + "' WHERE plate = '" + plate_number + "';"  +
                        "SELECT height FROM LicensePlate WHERE plate = '" + plate_number + "'";
    GetDataQuery(query, &result, row, col, "UpdateHeight()");
    if (row <= 0 || abs(atof(result[1]) - update_height) > ZERO) {
        sqlite3_free_table(result);
        throw std::runtime_error("Failed to update");
    }
    sqlite3_free_table(result);
}

void LicensePlateManager::UpdateWeight(const PlateNumber& plate_number, double update_weight) {
    if (update_weight < 0)
        throw std::runtime_error("Invalid weight");

    if (!IsCorrectFormat(plate_number))
        throw std::runtime_error("Invalid plate number");

    if (IsUniqueNumber(plate_number))
        throw std::runtime_error("Passed in plate number does not exist in the system");

    char **result = 0;    /* Results of the query */
    int row = 0, col = 0;
    std::string query = "UPDATE LicensePlate SET weight = '" + std::to_string(update_weight) + "' WHERE plate = '" + plate_number + "';"  +
                        "SELECT weight FROM LicensePlate WHERE plate = '" + plate_number + "'";
    GetDataQuery(query, &result, row, col, "UpdateHeight()");
    if (row <= 0 || abs(atof(result[1]) - update_weight) > ZERO ) {
        sqlite3_free_table(result);
        throw std::runtime_error("Failed to update");
    }
    sqlite3_free_table(result);
}

void LicensePlateManager::GetDataQuery(const std::string& query, char ***result, int& row, int& col, const std::string& op) {
    char *err_msg = 0;

    int rc = sqlite3_get_table(db_, query.data(), result, &row, &col, &err_msg);
    if(rc != SQLITE_OK) {
        std::cerr << "SQL error in GetDataQuery:" << err_msg; sqlite3_free(err_msg);
    } 
    else
        std::cout << op << " operation executed successfully\n";

}

LicensePlateInfo LicensePlateManager::FindLicensePlate(const std::string& plate_number) {
    if (plate_number.size() != 7)
        throw std::runtime_error("Passed in an invalid license plate");
    char **result = 0;    /* Results of the query */
    int row = 0, col = 0;

    std::string query = "SELECT * FROM LicensePlate WHERE plate = '" + plate_number + "'";
    GetDataQuery(query, &result, row, col, "Find Plate");
    if (row < 1) {
        sqlite3_free_table(result);
        throw std::runtime_error("Passed in plate number does not exist in the system");
    }
    LicensePlateInfo ret(result[8], result[9], result[10], result[11], result[12], atoi(result[13]), atof(result[14]), atof(result[15]));
    sqlite3_free_table(result);
    return ret;
}

std::vector<LicensePlateInfo> LicensePlateManager::FindLicensePlate(const std::string& first_name, const std::string& last_name) {
    if (first_name.empty() || last_name.empty())
        throw std::runtime_error("Passed in an empty first name and empty last name");
    char **result = 0;    /* Results of the query */
    int row = 0, col = 0;

    std::string query = "SELECT * FROM LicensePlate \
                         WHERE first_name = '" + first_name + "' AND last_name = '" + last_name + "' \
                         ORDER BY plate ASC";
    GetDataQuery(query, &result, row, col, "Find");
    if (row < 1) {
        sqlite3_free_table(result);
        throw std::runtime_error("License plate does not exist in the system");
    }
    std::vector<LicensePlateInfo> ret;
    for(int i = 1; i <= row; i++) {
        int idx = i*col;
        LicensePlateInfo lpi(result[idx], result[idx+1], result[idx+2], result[idx+3], result[idx+4], atoi(result[idx+5]), atof(result[idx+6]), atof(result[idx+7]));
        ret.push_back(lpi);
    }
    sqlite3_free_table(result);
    return ret;    
}

bool LicensePlateManager::IsValid(const LicensePlateInfo& plate) {    
    if (plate.height >= 0 && plate.weight >= 0 && plate.age >= 18 
        && plate.plate_number.size() == 7 && !plate.first_name.empty()
        && !plate.last_name.empty() && !plate.date_of_birth.empty() 
        && !plate.address.empty()) {
        for (size_t i = 0; i < plate.plate_number.size(); ++i) {
            if (i < 2 && valid_chars.find(plate.plate_number[i]) == std::string::npos)
                return false;
            if (i >= 2 && valid_numbers.find(plate.plate_number[i]) == std::string::npos)
                return false;
        }
    }
    else 
        return false;
    return true;
}

bool LicensePlateManager::IsUniqueNumber(const std::string& number) {
    if (number.empty())
        return false;
    char **result = 0;    /* Results of the query */
    int row = 0, col = 0;

    std::string query = "SELECT * FROM LicensePlate WHERE plate = '" + number + "'";
    GetDataQuery(query, &result, row, col, "Check Uniqueness");
    sqlite3_free_table(result);
    if(row == 0)
        return true;
    return false;
}

bool LicensePlateManager::AddPlate(const LicensePlateInfo& plate) {
    char *sql;
    char *err_msg = 0;
    asprintf(&sql, "INSERT INTO LicensePlate VALUES ('%s', '%s', '%s', '%s', '%s', %d, %f, %f); SELECT * FROM LicensePlate WHERE plate = '%s'",
            plate.plate_number.data(), plate.first_name.data(), plate.last_name.data(), 
            plate.date_of_birth.data(), plate.address.data(), plate.age, plate.height, plate.weight, plate.plate_number.data());
    std::string query = sql;
    char **result = 0;
    int row = 0, col = 0;
    free(sql);
    GetDataQuery(query, &result, row, col, "AddPlate");
    if(row == 1) {
        std::cout << "The new license plate was successfully inserted \n";
        return true;
    }
    else
        return false;
}

LicensePlateInfo LicensePlateManager::CreatePlate(const PlateNumber& plate_number, const std::string& first_name, const std::string& last_name, 
                                                int age, const std::string& date_of_birth, const std::string& address, double height, double weight) {
    
    LicensePlateInfo new_plate (plate_number, first_name, last_name, date_of_birth, address, age, height, weight);
    if (!IsValid(new_plate) || !IsUniqueNumber(plate_number)) 
        throw std::runtime_error("invalid plate found in CreatePlate()");

    if(!AddPlate(new_plate))
        throw std::runtime_error("Failed to insert the new license plate");
    return new_plate;
}

LicensePlateInfo LicensePlateManager::GeneratePlate(const std::string& first_name, const std::string& last_name, int age, 
                                                    const std::string& date_of_birth, const std::string& address, double height, double weight) {
    PlateNumber plate_number = GeneratePlateNumber();
    LicensePlateInfo new_plate(plate_number, first_name, last_name, date_of_birth, address, age, height, weight);
    if (!IsValid(new_plate))
        throw std::runtime_error("invalid plate found in GeneratePlate()");

    if(!AddPlate(new_plate))
        throw std::runtime_error("Failed to insert the new license plate");
    return new_plate;
}

PlateNumber LicensePlateManager::GeneratePlateNumber() {
    PlateNumber plate_number = "";
    if(last_serial_.empty())                  //no plates were automatically generated yet, assign to initial serial number
        plate_number = initial_serial_;
    else 
        plate_number = last_serial_;
    
    bool generated = false;                       //has a unique plate number has been generated?

    while(!generated) {                           //increment plate number until a unique one is reached
        plate_number = IncrementPlateNumber(plate_number);
        if(IsUniqueNumber(plate_number))
            generated = true;
    }
    
    last_serial_ = plate_number;                 //plate_number is now the last serial number to be added

    return plate_number;
}

std::string LicensePlateManager::IncrementPlateNumber(PlateNumber number) {
    size_t i = 6;                                 //start at end of string
    
    while(i >= 2) {                                  //currently on number indices 2-6
        char c = number.at(i);
        c++;
        if(c > '9') {                               //if the digit exceeds the last valid character, set the current character to zero and increment the next digit
            number[i] = '0';
            i--;
        } 
        else {                                    //incremented and set character normally, no additional changes needed
            number[i] = c;
            return number;
        }
    }

    while(i >= 0) {                             //currently on letter indices 0-1, starting at index 1
        char c = number.at(i);
        c++;
        if(c > 'Z') {                               //if the digit exceeds the last valid character, set the current character to A and increment the next digit
            number[i] = 'A';
            i--;
        } 
        else {                                    //incremented and set character normally, no additional changes needed
            number[i] = c;
            return number;
        }
    }
    throw std::runtime_error("Exceeded last valid serial number.");

    return number;
}



bool LicensePlateManager::RemovePlate(const std::string& plate_number) {
    try {
        FindLicensePlate(plate_number);
    }
    catch(const std::runtime_error& error) {
        throw;
    }
    char **result = 0;    /* Results of the query */
    int row = 0, col = 0;
    std::string query = "DELETE FROM LicensePlate WHERE plate = '" + plate_number + "';" +
                        "SELECT * FROM LicensePlate WHERE plate = '" + plate_number + "'";
    GetDataQuery(query, &result, row, col, "Remove");
    sqlite3_free_table(result);
    if(row == 0)
        return true;
    return false;
}

std::ostream& operator<< (std::ostream& os, const LicensePlateInfo& lpi) {
    os << "Plate number: " << lpi.plate_number << std::endl;
    os << "First name: " << lpi.first_name << std::endl;
    os << "Last name: " << lpi.last_name << std::endl;
    os << "DoB: " << lpi.date_of_birth << std::endl;
    os << "Address: " << lpi.address << std::endl;
    os << "Age: " << lpi.age << std::endl;
    os << "Height: " << lpi.height << std::endl;
    os << "Weight: " << lpi.weight << std::endl;
    return os;
}

std::ostream& operator<< (std::ostream& os, const std::vector<LicensePlateInfo>& plates_vec) {
    if(plates_vec.empty()) {
        os << "No license plates to print." << std::endl;
        return os;
    }

    for(auto &it : plates_vec) {
        os << it.plate_number + "," + it.first_name + "," + it.last_name + "," + it.date_of_birth + ","
        + it.address + "," << it.age << "," << it.height << "," << it.weight << std::endl;
    }
    return os;
}

std::string LicensePlateManager::ScanPlate(const std::string& filename) {
    //http://techawarey.com/programming/install-opencv-c-c-in-ubuntu-18-04-lts-step-by-step-guide/
    std::ifstream img {filename};
    if (!img.is_open() || filename.empty()) {
        img.close();
        throw std::runtime_error("file not successfully opened");
    }
    std::string out = LicensePlateScanner::GetPlateNumber(filename);
    out.erase(out.begin()+2, out.begin()+3);
    img.close();
    return out;
}
