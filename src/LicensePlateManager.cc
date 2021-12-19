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

// void LicensePlateManager::UpdateLicensePlate(std::string first_name, std::string last_name, PlateNumber plate_number) {
//     bool found_driver = false;
//     if (first_name.length() == 0 || last_name.length() == 0) {
//         throw std::runtime_error("Invalid name");
//     }
//     if (!IsUniqueNumber(plate_number)) {
//         throw std::runtime_error("Plate number already exists, cannot be updated/repeated");
//     }
// /*     for (auto it = plates_.begin(); it != plates_.end(); ++it) {
//         if (it->second->first_name == first_name && it->second->last_name == last_name) {
//             found_driver = true;
//             it->second->plate_number = plate_number;
//             std::swap(plates_[plate_number], it->second);
//             plates_.erase(it);
//             return;
//         }
//     }
//     if (found_driver == false) {
//         throw std::runtime_error("The driver does not exist in the system");
//     } */
// }

// void LicensePlateManager::UpdateAddress(PlateNumber plate_number, std::string update_address) {
//     if (update_address.length() == 0) {
//         throw std::runtime_error("Invalid Address");
//     }
//    if (IsUniqueNumber(plate_number)) {
//         throw std::runtime_error("Passed in plate number does not exist in the system");
//     }
//     for (auto it = plates_.begin(); it != plates_.end(); ++it) {
//         if (it->first == plate_number) {
//             it->second->address = update_address;
//         }
//     }
// }

// void LicensePlateManager::UpdateAge(PlateNumber plate_number, int update_age) {
//     if (update_age < 18) {
//         throw std::runtime_error("Invalid age");
//     }
//     if (IsUniqueNumber(plate_number)) {
//         throw std::runtime_error("Passed in plate number does not exist in the system");
//     }
//     for (auto it = plates_.begin(); it != plates_.end(); ++it) {
//         if (it->first == plate_number) {
//             if (it->second->age > update_age) {
//                 throw std::runtime_error("Boo, How do you grow backwards?");
//             } else {
//                 it->second->age = update_age;
//             }
//         }
//     }
// }

// void LicensePlateManager::UpdateHeight(PlateNumber plate_number, double update_height) {
//     if (update_height < 0) {
//         throw std::runtime_error("Invalid height");
//     }
//     if (IsUniqueNumber(plate_number)) {
//         throw std::runtime_error("Passed in plate number does not exist in the system");
//     }
//     for (auto it = plates_.begin(); it != plates_.end(); ++it) {
//         if (it->first == plate_number) {
//             if (it->second->height > update_height) {
//                 throw std::runtime_error("Boo, How do you grow backwards?");
//             } else {
//                 it->second->height = update_height;
//             }
//         }
//     }
// }

// void LicensePlateManager::UpdateWeight(PlateNumber plate_number, double update_weight) {
//     if (update_weight < 0) {
//         throw std::runtime_error("Invalid weight");
//     }
//     if (IsUniqueNumber(plate_number)) {
//         throw std::runtime_error("Passed in plate number does not exist in the system");
//     }
//     for (auto it = plates_.begin(); it != plates_.end(); ++it) {
//         if (it->first == plate_number) {
//             it->second->weight = update_weight;
//         }
//     }
// }

// LicensePlateInfo *LicensePlateManager::FindLicensePlate(std::string plate_number) {
//     if (plate_number.length() == 0)
//             return nullptr;
//     if(plates_.count(plate_number) == 0)
//         return nullptr;
//     else
//         return plates_.at(plate_number);
// }

// LicensePlateInfo *LicensePlateManager::FindLicensePlate(std::string first_name, std::string last_name) {
//     if (first_name.length() == 0 || last_name.length() == 0) {
//         return nullptr;
//     }
//     for (auto it = plates_.begin(); it != plates_.end(); ++it) {
//         if (it->second->first_name == first_name && it->second->last_name == last_name) {
//             return plates_.at(it->first);
//         }
//     }
//     return nullptr;
// }

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

bool LicensePlateManager::IsUniqueNumber(std::string number) {
    if (number.empty())
        return false;
    char *err_msg = 0;
    char **paz_result = 0;    /* Results of the query */
    int row = 0, col = 0;

    std::string str_query = "SELECT * FROM LicensePlate WHERE plate = '" + number + "'";
    int rc = sqlite3_get_table(db_, str_query.data(), &paz_result, &row, &col, &err_msg);
    if( rc != SQLITE_OK ) {
        std::cerr << "IsUniqueNumber SQL error:" << err_msg;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Operation done successfully\n";
    }
    sqlite3_free_table(paz_result);
    if(row == 0)
        return true;
    return false;
}

void LicensePlateManager::AddPlate(const LicensePlateInfo& plate) {
    char *sql;
    char *err_msg = 0;
    asprintf(&sql, "INSERT INTO LicensePlate VALUES ('%s', '%s', '%s', '%s', '%s', %d, %f, %f)",
            plate.plate_number.data(), plate.first_name.data(), plate.last_name.data(), 
            plate.date_of_birth.data(), plate.address.data(), plate.age, plate.height, plate.weight );
    std::cout << sql << std::endl;
    int rc = sqlite3_exec(db_, sql, NULL, NULL, &err_msg);
    if( rc != SQLITE_OK ) {
        std::cerr << "AddPLate SQL error:" << err_msg;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Operation done successfully\n";
    }
    free(sql);
}

LicensePlateInfo LicensePlateManager::GeneratePlate(std::string first_name, std::string last_name, int age, std::string date_of_birth,
                            std::string address, double height, double weight) {
    PlateNumber plate_number = GeneratePlateNumber();
    LicensePlateInfo new_plate(plate_number, first_name, last_name, date_of_birth, address, age, height, weight);
    if (!IsValid(new_plate))
        throw std::runtime_error("invalid plate found in GeneratePlate()");
    AddPlate(new_plate);
    return new_plate;
}

PlateNumber LicensePlateManager::GeneratePlateNumber() {
    PlateNumber plate_number = "";
    if(last_serial_.empty()) {                  //no plates were automatically generated yet, assign to initial serial number
        plate_number = initial_serial_;
    } else {
        plate_number = last_serial_;
    }
    
    bool generated = false;                       //has a unique plate number has been generated?

    while(!generated) {                           //increment plate number until a unique one is reached
        plate_number = IncrementPlateNumber(plate_number);
        if(IsUniqueNumber(plate_number)) {
            generated = true;
        }
    }
    
    last_serial_ = plate_number;                 //plate_number is now the last serial number to be added

    return plate_number;
}

std::string LicensePlateManager::IncrementPlateNumber(std::string number) {
    size_t i = 6;                                 //start at end of string
    
    while(i >= 2) {                                  //currently on number indices 2-6
        char c = number.at(i);
        c++;
        if(c > '9') {                               //if the digit exceeds the last valid character, set the current character to zero and increment the next digit
            number[i] = '0';
            i--;
        } else {                                    //incremented and set character normally, no additional changes needed
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
        } else {                                    //incremented and set character normally, no additional changes needed
            number[i] = c;
            return number;
        }
    }

    throw std::runtime_error("Exceeded last valid serial number.");

    return number;
}

// LicensePlateInfo *LicensePlateManager::CreatePlate(PlateNumber plate_number, std::string first_name, std::string last_name, int age, std::string date_of_birth,
//                             std::string address, double height, double weight) {
    
//     LicensePlateInfo * new_plate = new LicensePlateInfo(plate_number, first_name, last_name, date_of_birth, address, age, height, weight);
//     if (!IsValid(new_plate) || !IsUnique(new_plate)) {
//         delete new_plate;
//         throw std::runtime_error("invalid plate found in CreatePlate()");
//     }
//     plates_[plate_number] = new_plate;
//     return new_plate;
// }

// bool LicensePlateManager::RemovePlate(std::string plate_number) {
//     if(plates_.count(plate_number) > 0) {
//         delete plates_.at(plate_number);
//         plates_.erase(plate_number);
//         return true;
//     }
//     return false;
// }

std::ostream& operator<< (std::ostream& os, const LicensePlateInfo * lpi) {
    if(lpi == NULL) {
        os << "Can't found the information of the license plate." << std::endl;
        return os;
    }
    os << "Plate number: " << lpi->plate_number << std::endl;
    os << "First name: " << lpi->first_name << std::endl;
    os << "Last name: " << lpi->last_name << std::endl;
    os << "DoB: " << lpi->date_of_birth << std::endl;
    os << "Address: " << lpi->address << std::endl;
    os << "Age: " << lpi->age << std::endl;
    os << "Height: " << lpi->height << std::endl;
    os << "Weight: " << lpi->weight << std::endl;
    return os;
}

std::ostream& operator<< (std::ostream& os, const std::vector<std::pair<PlateNumber, LicensePlateInfo*>>& plates_vec) {
    if(plates_vec.empty()) {
        os << "No license plates to print." << std::endl;
        return os;
    }

    for(auto &it : plates_vec) {
        os << it.first + "," + it.second->first_name + "," + it.second->last_name + "," + it.second->date_of_birth + ","
        + it.second->address + "," << it.second->age << "," << it.second->height << "," << it.second->weight << std::endl;
    }
    return os;
}

std::string LicensePlateManager::ScanPlate(const std::string& filename) {
    //http://techawarey.com/programming/install-opencv-c-c-in-ubuntu-18-04-lts-step-by-step-guide/
    std::ifstream img {filename};
    if (!img.is_open()) {
        throw std::runtime_error("file not successfully opened");
    }
    std::string out = LicensePlateScanner::GetPlateNumber(filename);
    out.erase(out.begin()+2, out.begin()+3);
    return out;
}
