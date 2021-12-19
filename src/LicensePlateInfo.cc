#include "LicensePlateManager.hpp"
#include "LicensePlateInfo.hpp"

LicensePlateInfo& operator<< (LicensePlateInfo& plate_info, const std::string& line) {
    size_t idx = 0;
    plate_info.plate_number = SubstrFromPosToDel(line, &idx);
    plate_info.first_name = SubstrFromPosToDel(line, &idx);
    plate_info.last_name = SubstrFromPosToDel(line, &idx);
    plate_info.date_of_birth = SubstrFromPosToDel(line, &idx);
    plate_info.address = SubstrFromPosToDel(line, &idx);
    plate_info.age = std::stoi(SubstrFromPosToDel(line, &idx));
    plate_info.height = std::stod(SubstrFromPosToDel(line, &idx));
    plate_info.weight = std::stod(SubstrFromPosToDel(line, &idx));
    return plate_info;
};

std::string SubstrFromPosToDel(const std::string& str, size_t* idx_ptr) {
    size_t& idx = *idx_ptr;
    if(idx >= str.size()) {     //idx begins out of range, should only happen due to invalid input
        throw std::invalid_argument("incomplete entry or invalid formatting");
    }
    std::string substr;
    bool in_quote = false;
    for(; idx < str.size(); ++idx) {
        if(str.at(idx) == '"') {
            in_quote = !in_quote;
            continue;
        }
        if((str.at(idx) == ',' && !in_quote) || str.at(idx) == '\n') break;
        substr.push_back(str.at(idx));
    }
    if(in_quote) {          //incorrect formatting due to trailing quotation mark
        throw std::invalid_argument("incomplete entry or invalid formatting");
    }
    idx += 1;
    return substr;
};     
        