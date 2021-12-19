// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#include "catch.hpp"
#include "LicensePlateManager.hpp"
#include <string>
#include <sstream>
/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

// TEST_CASE("Parameterized constructor", "[Constructor]") { 
//     SECTION("Empty file") {
//         LicensePlateManager manager("");
//         REQUIRE(manager.GetPlates().size() == 0);
//     }
//     SECTION("Small file") {
//         LicensePlateManager manager("data/data_info.csv");
//         REQUIRE_FALSE(manager.GetPlates().empty());
//     }
// }

// TEST_CASE("Plates Successfully Loaded to Manager", "[LoadPlates()]") {
//     std::ostringstream ss;

//     LicensePlateManager manager;
//     manager.LoadPlates("data/data_info.csv");
//     REQUIRE(!manager.GetPlates().empty());
//     std::map<PlateNumber, LicensePlateInfo*> sample = {};
//     std::map<PlateNumber, LicensePlateInfo*> stored = manager.GetPlates();
//     LicensePlateInfo* info = new LicensePlateInfo("CD80519", "Michael", "Nowak", "03/21/1987", "Round Rock, Texas, United States", 34, 6.1, 180);
//     sample.insert(std::pair<PlateNumber, LicensePlateInfo*> ("CD80519", info));
//     LicensePlateInfo* info1 = new LicensePlateInfo("AQ11010", "Michaeler", "Bowaker", "03/22/1987", "Square Rock, Texas, United States", 34, 6.1, 180);
//     sample.insert(std::pair<PlateNumber, LicensePlateInfo*> ("AQ11010", info1));
//     LicensePlateInfo* info2 = new LicensePlateInfo("AQ11012", "Nathan", "Park", "11/22/2021", "106 E University Ave, Urbana, IL 61801", 21, 6.6, 100);
//     sample.insert(std::pair<PlateNumber, LicensePlateInfo*> ("AQ11012", info2));
//     bool result = true;
//     for (auto it = stored.begin(); it != stored.end(); ++it) {
//         auto iter = sample[it->first];
//         if (it->second->plate_number != iter->plate_number) {
//             result = false;
//         }
//     }
//     REQUIRE(result == true);

//     SECTION("Load single entry") {
//         LicensePlateManager manager;
//         manager.LoadPlates("data/one_entry.csv");
//         std::map<PlateNumber, LicensePlateInfo*> stored = manager.GetPlates();
//         ss << stored.begin()->second;
//         std::string ans = "Plate number: CD80519\nFirst name: Michael\nLast name: Nowak\nDoB: 03/21/1987\nAddress: Round Rock, Texas, United States\nAge: 34\nHeight: 6.1\nWeight: 180\n";
//         REQUIRE(ss.str() == ans);
//     }

//     SECTION("Open nonexistent file") {
//         LicensePlateManager manager;
//         CHECK_THROWS(manager.LoadPlates("data/aaa.csv"));
//     }

//     SECTION("File contains no valid entries") {
//         LicensePlateManager manager;
//         CHECK_THROWS(manager.LoadPlates("data/invalid_entry.csv"));
//     }

//     SECTION("File contains one invalid entry") {
//         LicensePlateManager manager;
//         CHECK_THROWS(manager.LoadPlates("data/valid_invalid_entries.csv"));
//         std::map<PlateNumber, LicensePlateInfo*> stored = manager.GetPlates();
//         ss << stored.begin()->second;
//         std::string ans = "Plate number: CD80519\nFirst name: Pikachu\nLast name: Chuchu\nDoB: 03/21/1966\nAddress: Kanto\nAge: 50\nHeight: 1.1\nWeight: 200\n";
//         REQUIRE(ss.str() == ans);
//         REQUIRE(stored.size() == 1);
//     }

//     SECTION("LoadPlates doesn't overwrite current data") {
//         LicensePlateManager manager;
//         manager.CreatePlate("AQ11011", "Nathan", "Park", 18, "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 7, 300);
//         manager.LoadPlates("data/data_info.csv");
//         auto data = manager.GetPlates();
//         REQUIRE(data.size() == 4);
//         std::string ans = "Plate number: AQ11011\nFirst name: Nathan\nLast name: Park\nDoB: 12/21/1221\nAddress: 201 N Goodwin Ave, Urbana, IL 61801\nAge: 18\nHeight: 7\nWeight: 300\n";
//         ss << data["AQ11011"];
//         REQUIRE(ss.str() == ans);
//     }

//     SECTION("Invalid data doesn't overwrite current data") {
//         REQUIRE_THROWS(manager.LoadPlates("data/invalid_entry.csv"));
//         REQUIRE(manager.GetPlates().size() == 3);
//     }

//     SECTION("LoadPlates() ignores entries with invalid formatting") {
//         LicensePlateManager manager;
//         manager.LoadPlates("data/test_ignore.csv");
//         REQUIRE(manager.GetPlates().size() == 3);
//     }
// }

// TEST_CASE("Insertion of a duplicate license plate number is rejected", "[CreatePlate()]") { 
//     std::ostringstream ss;
//     LicensePlateManager manager;
//     manager.CreatePlate("AQ11001", "Michealer", "Nowaker", 101, "11/11/1920", "Chicago, Illinois", 200, 125);
//     CHECK_THROWS(manager.CreatePlate("AQ11001", "Michealest", "Nowakest", 102, "11/11/1919", "Chicago, Illinois", 200, 125));
//     std::map<PlateNumber, LicensePlateInfo*> stored = manager.GetPlates();
//     REQUIRE(stored.size() == 1);
//     ss << stored.begin()->second;
//     std::string ans = "Plate number: AQ11001\nFirst name: Michealer\nLast name: Nowaker\nDoB: 11/11/1920\nAddress: Chicago, Illinois\nAge: 101\nHeight: 200\nWeight: 125\n";
//     REQUIRE(ss.str() == ans);

//     SECTION("Create invalid license plate") {
//         LicensePlateManager manager;
//         CHECK_THROWS(manager.CreatePlate("AQ1@001", "Michealest", "Nowakest", 102, "11/11/1919", "Chicago, Illinois", 200, 125));
//         std::map<PlateNumber, LicensePlateInfo*> stored = manager.GetPlates();
//         REQUIRE(stored.empty());
//     }

//     SECTION("Create a valid license plate") {
//         LicensePlateManager manager;
//         LicensePlateInfo* ret = manager.CreatePlate("AQ11001", "Michealer", "Nowaker", 101, "11/11/1920", "Chicago, Illinois", 200, 125);
//         std::map<PlateNumber, LicensePlateInfo*> stored = manager.GetPlates();
//         REQUIRE(stored.size() == 1);
//         std::ostringstream ss;
//         ss << ret;
//         std::string ans = "Plate number: AQ11001\nFirst name: Michealer\nLast name: Nowaker\nDoB: 11/11/1920\nAddress: Chicago, Illinois\nAge: 101\nHeight: 200\nWeight: 125\n";
//         REQUIRE(ss.str() == ans);
//     }

//     SECTION("Create mulitple license plates") {
//         std::ostringstream ss;
//         LicensePlateManager manager;
//         std::string ans1 = "Plate number: AQ11001\nFirst name: Michealer\nLast name: Nowaker\nDoB: 11/11/1920\nAddress: Chicago, Illinois\nAge: 101\nHeight: 200\nWeight: 125\n";
//         std::string ans2 = "Plate number: AM51021\nFirst name: Ed\nLast name: Sheeran\nDoB: 01/12/1987\nAddress: Mars\nAge: 34\nHeight: 6\nWeight: 200\n";
//         std::string ans3 = "Plate number: AO20198\nFirst name: The\nLast name: Weaken\nDoB: 01/12/1965\nAddress: Las Vegas, Neveda\nAge: 34\nHeight: 6\nWeight: 150\n";
//         std::string ans4 = "Plate number: BM23586\nFirst name: Post\nLast name: Malone\nDoB: 07/04/1995\nAddress: Syracuse, New York\nAge: 26\nHeight: 6.1\nWeight: 250\n";
//         std::string ans  = ans1 + ans2 + ans3 + ans4;

//         LicensePlateInfo* ret = manager.CreatePlate("AQ11001", "Michealer", "Nowaker", 101, "11/11/1920", "Chicago, Illinois", 200, 125);
//         ss << ret;
//         ret = manager.CreatePlate("AM51021", "Ed", "Sheeran", 34, "01/12/1987", "Mars", 6, 200);
//         ss << ret;
//         ret = manager.CreatePlate("AO20198", "The", "Weaken", 34, "01/12/1965", "Las Vegas, Neveda", 6, 150);
//         ss << ret;
//         ret = manager.CreatePlate("BM23586", "Post", "Malone", 26, "07/04/1995", "Syracuse, New York", 6.1, 250);
//         ss << ret;

//         REQUIRE(ss.str() == ans);
//         std::map<PlateNumber, LicensePlateInfo*> stored = manager.GetPlates();
//         REQUIRE(stored.size() == 4);
//     }
// }

// TEST_CASE("Renmove license plates", "[Insertion/Deletion]") {
//     SECTION("Remove empty list") {
//         LicensePlateManager manager;
//         REQUIRE_FALSE(manager.RemovePlate("BM23586"));
//     }

//     SECTION("Remove an entry") {
//         LicensePlateManager manager;
//         LicensePlateInfo *d = new LicensePlateInfo("BM23586", "Post", "Malone",  "07/04/1995", "Syracuse, New York",26, 6.1, 250) ;
//         manager.AddPlate(d);
//         REQUIRE(manager.GetPlates().size() == 1);
//         REQUIRE(manager.RemovePlate("BM23586"));
//         REQUIRE(manager.GetPlates().size() == 0);
//     }

//     SECTION("Remove multiple entries") {
//         LicensePlateManager manager;
//         LicensePlateInfo *a = new LicensePlateInfo("AQ11001", "Michealer", "Nowaker", "11/11/1920", "Chicago, Illinois", 101, 200, 125) ;
//         LicensePlateInfo *b = new LicensePlateInfo("AM51021", "Ed", "Sheeran", "01/12/1987", "Mars", 34, 6, 200) ;
//         LicensePlateInfo *c = new LicensePlateInfo("AO20198", "The", "Weaken", "01/12/1965", "Las Vegas, Neveda",34, 6, 150) ;
//         LicensePlateInfo *d = new LicensePlateInfo("BM23586", "Post", "Malone",  "07/04/1995", "Syracuse, New York",26, 6.1, 250) ;
//         manager.AddPlate(a); manager.AddPlate(b); manager.AddPlate(c); manager.AddPlate(d);
//         REQUIRE(manager.GetPlates().size() == 4);
//         REQUIRE(manager.RemovePlate("AM51021"));
//         REQUIRE(manager.RemovePlate("AO20198"));
//         REQUIRE(manager.GetPlates().size() == 2);
//         REQUIRE(manager.RemovePlate("BM23586"));
//         REQUIRE(manager.GetPlates().size() == 1);
//     }

//     SECTION("Remove the same license plate twice") {
//         LicensePlateManager manager;
//         LicensePlateInfo *a = new LicensePlateInfo("AQ11001", "Michealer", "Nowaker", "11/11/1920", "Chicago, Illinois", 101, 200, 125) ;
//         LicensePlateInfo *b = new LicensePlateInfo("AM51021", "Ed", "Sheeran", "01/12/1987", "Mars", 34, 6, 200) ;
//         LicensePlateInfo *c = new LicensePlateInfo("AO20198", "The", "Weaken", "01/12/1965", "Las Vegas, Neveda",34, 6, 150) ;
//         LicensePlateInfo *d = new LicensePlateInfo("BM23586", "Post", "Malone",  "07/04/1995", "Syracuse, New York",26, 6.1, 250) ;
//         manager.AddPlate(a); manager.AddPlate(b); manager.AddPlate(c); manager.AddPlate(d);
//         REQUIRE(manager.GetPlates().size() == 4);
//         REQUIRE(manager.RemovePlate("AM51021"));
//         REQUIRE_FALSE(manager.RemovePlate("AM51021"));
//         REQUIRE(manager.GetPlates().size() == 3);
//     }

//     SECTION("Remove the license plate with the same name") {
//         LicensePlateManager manager;
//         LicensePlateInfo *a = new LicensePlateInfo("AQ11001", "Michealer", "Nowaker", "11/11/1920", "Chicago, Illinois", 101, 200, 125) ;
//         LicensePlateInfo *b = new LicensePlateInfo("AM51021", "Michealer", "Nowaker", "01/12/1987", "Mars", 34, 6, 200) ;
//         std::string ans = "Plate number: AQ11001\nFirst name: Michealer\nLast name: Nowaker\nDoB: 11/11/1920\nAddress: Chicago, Illinois\nAge: 101\nHeight: 200\nWeight: 125\n";
//         manager.AddPlate(a); manager.AddPlate(b);
//         REQUIRE(manager.GetPlates().size() == 2);
//         REQUIRE(manager.RemovePlate("AM51021"));
//         REQUIRE(manager.GetPlates().size() == 1);
//         auto data = manager.GetPlates();
//         std::ostringstream ss;
//         ss << data.begin()->second;
//         REQUIRE(ss.str() == ans);
//     }
// }



// TEST_CASE("Automatically generated license plates increment correctly from initial_plate_", "[Insertion/Deletion]") {
//     LicensePlateManager manager;
//     for(int i = 0; i < 100; i++) {
//         manager.GeneratePlate(std::to_string(i), "Nowakest", 999, "DOB", "LOCATION", 200, 125);
//     }

//     bool correct = true;
//     for(int i = 0; i < 100; i++) {
//         int num = 11002;
//         std::string number = "AQ";
//         number += std::to_string(num + i);
//         LicensePlateInfo * info = manager.FindLicensePlate(number);
//         if(info->first_name.compare(std::to_string(i)) != 0) {
//             correct = false;
//             break;
//         }
//     }
//     REQUIRE(correct);
// }

// TEST_CASE("Automatically generated license plates do not overwrite existing ones", "[Insertion/Deletion]") {
//     LicensePlateManager manager;
//     manager.CreatePlate("AQ11009", "Michealer", "Nowaker", 101, "11/11/1920", "Chicago, Illinois", 200, 125);
//     manager.CreatePlate("AQ11010", "Michealer", "Nowaker", 101, "11/11/1920", "Chicago, Illinois", 200, 125);
//     manager.CreatePlate("AQ11011", "Michealer", "Nowaker", 101, "11/11/1920", "Chicago, Illinois", 200, 125);

//     for(int i = 0; i < 10; i++) {
//         manager.GeneratePlate("Michealest", "Nowakest", 999, "DOB", "LOCATION", 200, 125);
//     }

//     LicensePlateInfo * info = manager.FindLicensePlate("AQ11009");
//     REQUIRE(info->first_name.compare("Michealer") == 0);
//     info = manager.FindLicensePlate("AQ11010");
//     REQUIRE(info->first_name.compare("Michealer") == 0);
//     info = manager.FindLicensePlate("AQ11011");
//     REQUIRE(info->first_name.compare("Michealer") == 0);
// }

// TEST_CASE("Passed in plate number is a valid plate || Passed in plate number is not a valid plate", "[IsValid()]") {
//     LicensePlateManager manager;

//     //tests for valid plate number
//     LicensePlateInfo* good_info = new LicensePlateInfo("AQ11011", "Nathan", "Park", "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 18, 7.0, 300);
//     REQUIRE(manager.IsValid(good_info) == true);

//     //tests for invalid plate number
//     LicensePlateInfo* bad_info = new LicensePlateInfo("A!20111", "Nemo", "Fish", "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 18, 1, 4);
//     REQUIRE(manager.IsValid(bad_info) == false);

//     SECTION("Bad format - > 3 letters") {
//         LicensePlateInfo bad_info = LicensePlateInfo("AAA011Z", "Nemo", "Fish", "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 18, 1, 4);
//         REQUIRE_FALSE(manager.IsValid(&bad_info));
//     }

//     SECTION("Bad format - invalid letters") {
//         LicensePlateInfo bad_info = LicensePlateInfo("AAAZ$H^", "Nemo", "Fish", "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 18, 1, 4);
//         REQUIRE_FALSE(manager.IsValid(&bad_info));
//     }

//     SECTION("Bad format - 4 numbers") {
//         LicensePlateInfo bad_info = LicensePlateInfo("AA2221@", "Nemo", "Fish", "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 18, 1, 4);
//         REQUIRE_FALSE(manager.IsValid(&bad_info));
//     }
    
//     SECTION("Bad format - missing a number") {
//         LicensePlateInfo bad_info = LicensePlateInfo("AS2221", "Nemo", "Fish", "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 18, 1, 4);
//         REQUIRE_FALSE(manager.IsValid(&bad_info));
//     }

//     SECTION("Bad format - missing a letter") {
//         LicensePlateInfo bad_info = LicensePlateInfo("A72221", "Nemo", "Fish", "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 18, 1, 4);
//         REQUIRE_FALSE(manager.IsValid(&bad_info));
//     }

//     SECTION("Bad format - > 7 characters") {
//         LicensePlateInfo bad_info = LicensePlateInfo("AA222111", "Nemo", "Fish", "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 18, 1, 4);
//         REQUIRE_FALSE(manager.IsValid(&bad_info));
//     }

//     SECTION("Invalid age, weight, height - no last name, first name, address, dob") {
//         LicensePlateInfo a = LicensePlateInfo("AA72221", "Nemo", "Fish", "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 17, 1, 4);
//         REQUIRE_FALSE(manager.IsValid(&a));
//         LicensePlateInfo b = LicensePlateInfo("AA72221", "", "Fish", "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 19, 1, 4);
//         REQUIRE_FALSE(manager.IsValid(&b));
//         LicensePlateInfo c = LicensePlateInfo("AA72221", "Nemo", "", "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 22, 1, 4);
//         REQUIRE_FALSE(manager.IsValid(&c));
//         LicensePlateInfo d = LicensePlateInfo("AA72221", "Nemo", "Fish", "", "201 N Goodwin Ave, Urbana, IL 61801", 123, 1, 4);
//         REQUIRE_FALSE(manager.IsValid(&d));
//         LicensePlateInfo e = LicensePlateInfo("AA72221", "Nemo", "Fish", "12/21/1221", "", 173, 1, 4);
//         REQUIRE_FALSE(manager.IsValid(&e));
//         LicensePlateInfo f = LicensePlateInfo("AA72221", "Nemo", "Fish", "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 13, -1, 4);
//         REQUIRE_FALSE(manager.IsValid(&f));
//         LicensePlateInfo g = LicensePlateInfo("AA72221", "", "Fish", "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 17, 1, -2);
//         REQUIRE_FALSE(manager.IsValid(&g));
//     }

// }

// TEST_CASE("Passed in plate number is a unique plate || Passed in plate number is not a unique plate", "[IsUnique()]") {
//     LicensePlateManager manager;

//     manager.CreatePlate("CD80519", "Michael", "Nowak", 34, "03/21/1987", "Round Rock, Texas, United States", 6.1, 180);
//     manager.CreatePlate("AQ20111", "Nemo", "Fish", 18, "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 1, 4);
//     manager.CreatePlate("AQ11010", "Michaeler", "Bowaker", 34, "03/22/1987", "Square Rock, Texas, United States", 6.1, 180);
//     //tests for unique plate number
//     LicensePlateInfo* unique = new LicensePlateInfo("AQ11011", "Nathan", "Park", "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 18, 7.0, 300);
//     REQUIRE(manager.IsUnique(unique) == true);

//     //tests for not unique plate number
//     LicensePlateInfo* not_unique = new LicensePlateInfo("AQ20111", "Nemo", "Fish", "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 18, 1, 4);
//     REQUIRE(manager.IsUnique(not_unique) == false);
// }

// TEST_CASE("Manager Successfully Found the Info By Plate Number", "[FindLicensePlate()]") {
//     LicensePlateManager manager;
//     manager.CreatePlate("AQ11001", "Michealer", "Nowaker", 101, "11/11/1920", "Chicago, Illinois", 200, 125);
//     manager.CreatePlate("AQ11011", "Nathan", "Park", 18, "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 7.0, 300);

//     LicensePlateInfo* info = manager.GetPlates()["AQ11001"];
//     REQUIRE(manager.FindLicensePlate("AQ11001") == info);

//     SECTION("Find nonexistent license plate") {
//         REQUIRE(manager.FindLicensePlate("AQ11002") == nullptr);
//     }

//     SECTION("Find invalid license plate") {
//         REQUIRE(manager.FindLicensePlate("") == nullptr);
//         REQUIRE(manager.FindLicensePlate("AQ1100") == nullptr);
//     }
// }

// TEST_CASE("Manager Successfully Found the Info By Driver's Name", "[FindLicensePlate()]") {
//     LicensePlateManager manager;
//     std::ostringstream ss;
//     manager.CreatePlate("AQ11001", "Michealer", "Nowaker", 101, "11/11/1920", "Chicago, Illinois", 200, 125);
//     manager.CreatePlate("AQ11011", "Nathan", "Park", 18, "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 7, 300);

//     LicensePlateInfo* info = manager.GetPlates()["AQ11011"];
//     REQUIRE(manager.FindLicensePlate("Nathan", "Park") == info);

//     SECTION("Find nonexistent license plate") {
//         REQUIRE(manager.FindLicensePlate("Post", "Malone") == nullptr);
//     }

//     SECTION("Find invalid license plate") {
//         REQUIRE(manager.FindLicensePlate("Post", "") == nullptr);
//         REQUIRE(manager.FindLicensePlate("", "Malone") == nullptr);
//         REQUIRE(manager.FindLicensePlate("", "") == nullptr);
//     }

//     SECTION("Return the first Nathan Park record") {
//         manager.CreatePlate("AQ11012", "Nathan", "Park", 22, "12/21/1222", "203 N Goodwin Ave, Urbana, IL 61801", 7.1, 310);
//         ss << manager.GetPlates()["AQ11011"];
//         std::string ans = "Plate number: AQ11011\nFirst name: Nathan\nLast name: Park\nDoB: 12/21/1221\nAddress: 201 N Goodwin Ave, Urbana, IL 61801\nAge: 18\nHeight: 7\nWeight: 300\n";
//         REQUIRE(ss.str() == ans);
//     }
// }

// TEST_CASE("Sort data", "[Sort()]") {
//     LicensePlateManager manager;
//     std::ostringstream ss;
//     SECTION("Sort empty list") {
//         REQUIRE(manager.Sort().size() == 0);
//     }

//     SECTION("Sort a single record") {
//         manager.CreatePlate("AQ11011", "Nathan", "Park", 18, "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 7, 300);
//         std::string ans = "AQ11011,Nathan,Park,12/21/1221,201 N Goodwin Ave, Urbana, IL 61801,18,7,300\n";
//         std::vector<std::pair<PlateNumber, LicensePlateInfo*>> sorted = manager.Sort();
//         REQUIRE(sorted.size() == 1);
//         ss << sorted;
//         REQUIRE(ss.str() == ans);
//     }

//     SECTION("Sort multiple records") {
//         manager.CreatePlate("AQ11011", "Nathan", "Stark", 18, "12/21/1221", "201 N Goodwin Ave, Urbana, IL 61801", 7, 300);
//         manager.LoadPlates("data/data_info.csv");
//         std::string ans1 = "AQ11010,Michaeler,Bowaker,03/22/1987,Square Rock, Texas, United States,34,6.1,180\n";
//         std::string ans2 = "CD80519,Michael,Nowak,03/21/1987,Round Rock, Texas, United States,34,6.1,180\n";
//         std::string ans3 = "AQ11012,Nathan,Park,11/22/2021,106 E University Ave, Urbana, IL 61801,21,6.6,100\n";
//         std::string ans4 = "AQ11011,Nathan,Stark,12/21/1221,201 N Goodwin Ave, Urbana, IL 61801,18,7,300\n";
//         std::string ans = ans1 + ans2 + ans3 + ans4;
//         std::vector<std::pair<PlateNumber, LicensePlateInfo*>> sorted = manager.Sort();
//         REQUIRE(sorted.size() == 4);
//         ss << sorted;
//         REQUIRE(ss.str() == ans);
//     }
// }

// TEST_CASE("Overloaded << operator for LicensePlateInfo throws the correct error for invalid inputs", "[FindLicensePlate()]") {
//     LicensePlateInfo info;
//     SECTION("Invalid numerical values for age, height, or weight") {
//         REQUIRE_THROWS_WITH(info << "AQ11010,Michaeler,Bowaker,03/22/1987,\"Square Rock, Texas, United States\",NOTAVALIDAGE,6.1,180", "stoi");
//         REQUIRE_THROWS_WITH(info << "AQ11010,Michaeler,Bowaker,03/22/1987,\"Square Rock, Texas, United States\",123,ASDF,180", "stod");
//         REQUIRE_THROWS_WITH(info << "AQ11010,Michaeler,Bowaker,03/22/1987,\"Square Rock, Texas, United States\",123,6.1,HEIGHT", "stod");
//     }

//     SECTION("Incorrect formatting or incomplete entries") {
//         REQUIRE_THROWS_WITH(info << "", "incomplete entry or invalid formatting");
//         REQUIRE_THROWS_WITH(info << "AQ11010,Michaeler,Bowaker,03/22/1987,\"", "incomplete entry or invalid formatting");
//         REQUIRE_THROWS_WITH(info << "AQ11010,Michaeler,Bowaker,03/22/1987,\"Square", "incomplete entry or invalid formatting");
//         REQUIRE_THROWS_WITH(info << "AQ11010,Michaeler,Bowaker,03/22/1987,\"Square Rock, Texas, United States\",123,6.1,", "incomplete entry or invalid formatting");
//         REQUIRE_THROWS_WITH(info << "AQ11010,Michaeler,Bowaker,03/22/1987", "incomplete entry or invalid formatting");
//         REQUIRE_THROWS_WITH(info << "AQ11010 Michaeler Bowaker,03/22/1987 \"Square Rock, Texas, United States\" 123 6.1 180", "incomplete entry or invalid formatting");
//     }

// }

// TEST_CASE("Scan license plate number from an image", "[ScanPlate()]") {
//     LicensePlateManager manager;
//     CHECK(manager.ScanPlate("data/plate.png").compare("CD80519") == 0);
//     CHECK(manager.ScanPlate("data/plate2.png").compare("AH69887") == 0);
//     CHECK(manager.ScanPlate("data/plate3.png").compare("AK36398") == 0);
//     CHECK(manager.ScanPlate("data/plate4.png").compare("AG75117") == 0);
// }

// TEST_CASE("Updates driver's plate number", "[UpdateLicensePlate()]") {
//     LicensePlateManager manager;
//     LicensePlateInfo *a = new LicensePlateInfo("AQ11001", "Peppa", "Pig", "05/31/2004", "Chicago, Illinois", 19, 3.2, 50) ;
//     manager.AddPlate(a);
//     std::map<PlateNumber, LicensePlateInfo*> sample = {};

//     SECTION("Correctly updates License Plate number by driver's name") {
//         manager.UpdateLicensePlate("Peppa", "Pig", "AQ11111");
//         std::map<PlateNumber, LicensePlateInfo*> stored = manager.GetPlates();
//         LicensePlateInfo* info = new LicensePlateInfo("AQ11111", "Peppa", "Pig", "05/31/2004", "Chicago, Illinois", 19, 3.2, 50);
//         sample.insert(std::pair<PlateNumber, LicensePlateInfo*> ("AQ11111", info));
//         REQUIRE(sample["AQ11111"]->plate_number == stored["AQ11111"]->plate_number);
//     }

//     SECTION("Cannot update License Plate due to duplicated/repeated plate number") {
//         CHECK_THROWS(manager.UpdateLicensePlate("Peppa", "Pig", "AQ11001"));
//     }

//     SECTION("Driver does not exist") {
//         CHECK_THROWS(manager.UpdateLicensePlate("George", "Pig", "AQ11111"));
//     }

//     SECTION("Invalid name") {
//         CHECK_THROWS(manager.UpdateLicensePlate("", "Pig", "AQ11111"));
//     }
// }

// TEST_CASE("Updates driver's address", "[UpdateAddress()]") {
//     LicensePlateManager manager;
//     LicensePlateInfo *a = new LicensePlateInfo("AQ11001", "Sponge", "Bob", "05/01/1999", "Chicago, Illinois", 19, 3.2, 0.1) ;
//     manager.AddPlate(a);
//     std::map<PlateNumber, LicensePlateInfo*> sample = {};

//     SECTION("Updates the address") {
//         manager.UpdateAddress("AQ11001", "Pineapple House, Bikini Bottom, Pacific Ocean");
//         std::map<PlateNumber, LicensePlateInfo*> stored = manager.GetPlates();
//         LicensePlateInfo* info = new LicensePlateInfo("AQ11001", "Sponge", "Bob", "05/01/1999", "Pineapple House, Bikini Bottom, Pacific Ocean", 19, 3.2, 0.1);
//         sample.insert(std::pair<PlateNumber, LicensePlateInfo*> ("AQ11001", info));
//         REQUIRE(sample["AQ11001"]->address == stored["AQ11001"]->address);
//     }

//     SECTION("Pass in invalid address") {
//         CHECK_THROWS(manager.UpdateAddress("AQ11001", ""));
//     }
// }

// TEST_CASE("Updates driver's age", "[UpdateAge()]") {
//     LicensePlateManager manager;
//     LicensePlateInfo *a = new LicensePlateInfo("AQ11001", "Mickey", "Mouse", "01/01/1928", "Clubhouse, Mouseton", 93, 5.2, 56) ;
//     manager.AddPlate(a);
//     std::map<PlateNumber, LicensePlateInfo*> sample = {};

//     SECTION("Updates driver's age") {
//         manager.UpdateAge("AQ11001", 100);
//         std::map<PlateNumber, LicensePlateInfo*> stored = manager.GetPlates();
//         LicensePlateInfo* info = new LicensePlateInfo("AQ11001", "Mickey", "Mouse", "01/01/1928", "Clubhouse, Mouseton", 100, 5.2, 56);
//         sample.insert(std::pair<PlateNumber, LicensePlateInfo*> ("AQ11001", info));
//         REQUIRE(sample["AQ11001"]->age == stored["AQ11001"]->age);
//     }

//     SECTION("Driver's age to a lower number") {
//         CHECK_THROWS(manager.UpdateAge("AQ11001", 56));
//     }
// }

// TEST_CASE("Updates driver's height", "[UpdateHeight()]") {
//     LicensePlateManager manager;
//     LicensePlateInfo *a = new LicensePlateInfo("AQ11001", "Tom", "Cat", "01/01/1940", "House, New York", 19, 6, 40) ;
//     manager.AddPlate(a);
//     std::map<PlateNumber, LicensePlateInfo*> sample = {};

//     SECTION("Updates driver's height") {
//         manager.UpdateHeight("AQ11001", 7);
//         std::map<PlateNumber, LicensePlateInfo*> stored = manager.GetPlates();
//         LicensePlateInfo* info = new LicensePlateInfo("AQ11001", "Tom", "Cat", "01/01/1940", "House, New York", 19, 7, 40);
//         sample.insert(std::pair<PlateNumber, LicensePlateInfo*> ("AQ11001", info));
//         REQUIRE(sample["AQ11001"]->height == stored["AQ11001"]->height);
//     }

//     SECTION("Driver's height to a lower number") {
//         CHECK_THROWS(manager.UpdateHeight("AQ11001", 3));
//     }
// }

// TEST_CASE("Updates driver's weight", "[UpdateWeight()]") {
//     LicensePlateManager manager;
//     LicensePlateInfo *a = new LicensePlateInfo("AQ11001", "Winnie", "Pooh", "08/21/1921", "Hundred Acre Wood, East Sussex, England", 91, 5.6, 78) ;
//     manager.AddPlate(a);
//     std::map<PlateNumber, LicensePlateInfo*> sample = {};

//     SECTION("Updates driver's weight") {
//         manager.UpdateWeight("AQ11001", 80);
//         std::map<PlateNumber, LicensePlateInfo*> stored = manager.GetPlates();
//         LicensePlateInfo* info = new LicensePlateInfo("AQ11001", "Winnie", "Pooh", "08/21/1921", "Hundred Acre Wood, East Sussex, England", 91, 5.6, 80);
//         sample.insert(std::pair<PlateNumber, LicensePlateInfo*> ("AQ11001", info));
//         REQUIRE(sample["AQ11001"]->weight == stored["AQ11001"]->weight);
//     }

//     SECTION("Invalid weight") {
//         CHECK_THROWS(manager.UpdateWeight("AQ11001", -1));
//     }
// }

// /////////////////////////////////////////////////////////////////////////////////////////////