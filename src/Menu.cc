#include "Menu.hpp"

Menu::Menu(LicensePlateManager * manager) : manager(manager) {

}

void Menu::MainMenu() {
    std::cout << std::endl;
    std::cout << "Illinois License Plate Manager\n"
                << "------------------------------\n";

    
    bool exit = false;
    while(!exit) {      //exit menu on user input, "return" to this menu whenever a submenu finishes executing
        std::cout << "1) Add/Remove\n"
                << "2) Save/Load\n"
                << "3) Print License Plates\n"
                << "4) Look-up A License Plate\n"
                << "5) Exit\n";

        int input = -1;
        std::cin >> input;

        switch(input) {
            case(1) :
                AddRemove();
                break;
            case(2) :
                SaveLoad();
                break;
            case (3) :
                PrintList();
                break;
            case (4) :
                Lookup();
                break;
            case (5) :
                exit = true;
                break;

            default:
                std::cout << "Please enter a valid command." << std::endl;
        }
    }
}

void Menu::AddRemove() {
    std::cout << std::endl;
    std::cout << "Add/Remove License Plates\n"
                << "-------------------------\n";

    bool exit = false;
    while(!exit) {      //exit menu on user input, "return" to this menu whenever a submenu finishes executing
        std::cout << "1) Add License Plate\n"
                << "2) Remove License Plate\n"
                << "3) Update License Plate\n"
                << "4) Return to Main Menu\n";
        int input = -1;
        std::cin >> input;

        switch(input) {
            case(1) :
                Add();
                break;
            case(2) :
                Remove();
                break;
            case(3) :
                Update();
                break;
            case (4) :
                exit = true;
                break;

            default:
                std::cout << "Please enter a valid command." << std::endl;
        }
    }
    std::cout << std::endl;
}

void Menu::Add() {
    std::cout << std::endl;
    std::cout << "Automatically Generate Plate Number?\n"
                << "------------------------------------\n";

    bool exit = false;
    bool manual = false;                //manual entry? call CreatePlate() if true, GeneratePlate() if false
    while(!exit) {      //exit loop on user input, continuing the to the rest of the function
        std::cout << "1) Generate Plate Number\n"
                << "2) Manual Entry\n"
                << "3) Return\n";
        int input = -1;
        std::cin >> input;

        switch(input) {
            case(1) :
                manual = false;
                exit = true;
                break;
            case(2) :
                manual = true;
                exit = true;
                break;
            case (3) :
                return;
                break;

            default:
                std::cout << "Please enter a valid command." << std::endl;
        }
    }

    std::string plate_number = "";

    if(manual) {
        bool valid_input = false;
        
        while(!valid_input) {               //will have to add a way to check for valid custom plate numbers
            std::cout << "Input plate number: ";
            std::cin >> plate_number;
            if(manager->IsUniqueNumber(plate_number)) {
                valid_input = true;
            } else {
                std::cout << "Plate number \"" << plate_number << "\" already exists." << std::endl;
            }
        }
    }


    //user input for CreatePlate() or GeneratePlate()
    std::string first_name = "";
    std::string last_name = "";
    std::string date_of_birth = "\"";
    std::string address = "";
    char address_c[256];
    int age = -1;
    double height = -1.0;
    double weight = -1.0;
    std::string age_s = "";
    std::string height_s = "";
    std::string weight_s = "";

    std::cout << "Input first name: ";
    std::cin >> first_name;
    std::cout << "Input last name: ";
    std::cin >> last_name;
    std::cout << "Input date of birth (MM/DD/YYYY): ";
    std::cin >> date_of_birth;
    std::cout << "Input address: ";
    std::cin.getline(address_c, 256);
    std::cin.getline(address_c, 256);
    address += address_c;
    std::cout << "Input age: ";
    std::cin >> age_s;
    try {
        age = std::stoi(age_s);
    } catch (const std::invalid_argument& e) {
        std::cout << "Invalid integer value entered for age. Returning to Add/Remove menu." << std::endl;
        return;
    }
    std::cout << "Input height: ";
    std::cin >> height_s;
    try {
        height = std::stoi(height_s);
    } catch (const std::invalid_argument& e) {
        std::cout << "Invalid numerical value entered for height. Returning to Add/Remove menu." << std::endl;
        return;
    }
    std::cout << "Input weight: ";
    std::cin >> weight_s;
    try {
        weight = std::stoi(weight_s);
    } catch (const std::invalid_argument& e) {
        std::cout << "Invalid numerical value entered for weight. Returning to Add/Remove menu." << std::endl;
        return;
    }

    LicensePlateInfo * plate = nullptr;
    if(manual) {
        plate = manager->CreatePlate(plate_number, first_name, last_name, age, date_of_birth, address, height, weight);
    } else {
        plate = manager->GeneratePlate(first_name, last_name, age, date_of_birth, address, height, weight);
    }
    std::cout << "Successfully added license plate." << std::endl;
}

void Menu::Remove() {
    std::cout << std::endl;
    std::string plate_number = "";
    std::cout << "Input plate number: ";
    std::cin >> plate_number;

    if(manager->RemovePlate(plate_number)) {
        std::cout << "Successfully removed license plate " << plate_number << std::endl;
    } else {
        std::cout << "Could not find license plate " << plate_number << std::endl;
    }
}

void Menu::Update() {
    std::cout << std::endl;
    std::cout << "Update License Plate\n"
                << "-------------------------\n";

    bool exit = false;
    while(!exit) {      //exit menu on user input, "return" to this menu whenever a submenu finishes executing
        std::cout << "1) Update Information\n"
                << "2) Update License Plate Number\n"
                << "3) Return to Main Menu\n";
        int input = -1;
        std::cin >> input;

        switch(input) {
            case(1) :
                UpdateInfo();
                break;
            case(2) :
                UpdateNumber();
                break;
            case (3) :
                exit = true;
                break;

            default:
                std::cout << "Please enter a valid command." << std::endl;
        }
    }
    std::cout << std::endl;
}

void Menu::UpdateInfo() {
    std::cout << std::endl;
    std::string platenumber = "";
    std::cout << "Input plate number: ";
    std::cin >> platenumber;
    if(manager->FindLicensePlate(platenumber) == nullptr) {         //plate was not found
        std::cout << "Could not find license plate number " << platenumber << std::endl;
        std::cout << std::endl;
        return;
    }
    std::string address = "";
    char address_c[256];
    std::string age_s = "";
    std::string height_s = "";
    std::string weight_s = "";
    int age = -1;
    double height = -1.0;
    double weight = -1.0;

    std::cout << std::endl;
    std::cout << "Update License Plate: " << platenumber << "\n"
                << "-------------------------\n";

    bool exit = false;
    while(!exit) {      //exit menu on user input, "return" to this menu whenever a submenu finishes executing
        std::cout << "1) Update Address\n"
                << "2) Update Age\n"
                << "3) Update Height\n"
                << "4) Update Weight\n"
                << "5) Exit\n";
        int input = -1;
        std::cin >> input;

        switch(input) {
            case(1) :
                std::cout << "Input new address: ";
                std::cin.getline(address_c, 256);
                std::cin.getline(address_c, 256);
                address += address_c;
                manager->UpdateAddress(platenumber, address);
                break;
            case(2) :
                std::cout << "Input new age: ";
                std::cin >> age_s;
                try{
                    age = std::stoi(age_s);
                } catch(const std::invalid_argument& e) {
                    std::cout << "Error: Entered an invalid value." << std::endl;
                    break;
                }
                manager->UpdateAge(platenumber, age);
                break;
            case(3) :
                std::cout << "Input new height: ";
                std::cin >> height_s;
                try{
                    height = std::stod(height_s);
                } catch(const std::invalid_argument& e) {
                    std::cout << "Error: Entered an invalid value." << std::endl;
                    break;
                }
                manager->UpdateHeight(platenumber, height);
                break;
            case(4) :
                std::cout << "Input new weight: ";
                std::cin >> weight_s;
                try{
                    weight = std::stod(weight_s);
                } catch(const std::invalid_argument& e) {
                    std::cout << "Error: Entered an invalid value." << std::endl;
                    break;
                }
                manager->UpdateWeight(platenumber, weight);
                break;
            case(5) :
                exit = true;
                break;

            default:
                std::cout << "Please enter a valid command." << std::endl;
        }
    }
    
    std::cout << std::endl;
}

void Menu::UpdateNumber() {
    std::cout << std::endl;
    std::string firstname = "";
    std::string lastname = "";
    std::string platenumber = "";
    std::cout << "Input first name: ";
    std::cin >> firstname;
    std::cout << "Input last name: ";
    std::cin >> lastname;
    std::cout << "Input new plate number: ";
    std::cin >> platenumber;

    try {
        manager->UpdateLicensePlate(firstname, lastname, platenumber);
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}

void Menu::PrintList() {
    std::cout << std::endl;
    std::cout << manager->Sort();
    std::cout << std::endl;
}

void Menu::SaveLoad() {
    std::cout << std::endl;
    std::cout << "Save/Load\n"
                << "------------------------------\n";

    
    bool exit = false;
    while(!exit) {          //exit menu on any valid input
        std::cout << "1) Save Current List\n"
                << "2) Load List from File\n"
                << "3) Exit\n";

        int input = -1;
        std::cin >> input;

        switch(input) {
            case(1) :
                Save();
                return;
                break;
            case(2) :
                Load();
                return;
                break;
            case (3) :
                return;
                break;

            default:
                std::cout << "Please enter a valid command." << std::endl;
        }
    }
}

void Menu::Save() {
    std::cout << std::endl;
    std::cout << std::endl;
    std::string filename = "";
    std::cout << "Input name of file to save to: ";
    std::cin >> filename;

    try {
        manager->SavePlates(filename);
    }
    catch(const std::runtime_error& error) {
        std::cout << error.what() << std::endl;
        return;
    }
    std::cout << "Successfully saved to file." << std::endl;
}

void Menu::Load() {
    std::cout << std::endl;
    std::string filename = "";
    std::cout << "Input name of file to load: ";
    std::cin >> filename;

    try {
        manager->LoadPlates(filename);
    }
    catch(const std::runtime_error& error) {
        std::cout << error.what() << std::endl;
        return;
    }
    std::cout << "Successfully loaded from file." << std::endl;
}

void Menu::Lookup() {
    std::cout << std::endl;
    std::string filename, plate_number;

    std::cout << "Look-up License Plate\n"
              << "-------------------------\n";

    bool exit = false;
    while(!exit) {      //exit menu on user input, "return" to this menu whenever a submenu finishes executing
        std::cout << "1) Image Input\n"
                  << "2) Manual Input\n"
                  << "3) Return to Main Menu\n";
        int input = -1;
        std::cin >> input;

        switch(input) {
            case(1): {
                std::cout << "Input name of file to scan: ";
                std::cin >> filename;
                try {
                    plate_number = manager->ScanPlate(filename);
                }
                catch(const std::runtime_error& error) {
                    std::cout << error.what() << std::endl;
                    return;
                }
                std::cout << "Successfully scanned the plate number from the file." << std::endl;
                std::cout << "+---------+\n";
                std::cout << "| " + plate_number + " |\n";
                std::cout << "+---------+\n";
                if(!plate_number.empty())
                    std::cout << manager->FindLicensePlate(plate_number);
                break;
            }
            case(2): {
                int input2 = -1;
                std::cout << "1) Input full name\n";
                std::cout << "2) Input license plate number\n";
                std::cin  >> input2;
                if(input2 == 1) {
                    std::string first_name, last_name;
                    std::cout << "Input first name: ";
                    std::cin >> first_name;
                    std::cout << "Input last name: ";
                    std::cin >> last_name;
                    if(!first_name.empty() && !last_name.empty())
                        std::cout << manager->FindLicensePlate(first_name, last_name);
                }
                else if(input2 == 2) {
                    std::cout << "Input license plate number: ";
                    std::cin >> plate_number;
                    if(!plate_number.empty())
                        std::cout << manager->FindLicensePlate(plate_number);
                }
                else
                    std::cout << "Please enter a valid command." << std::endl;
                break;
            }
            case (3): {
                exit = true;
                break;
            }
            default: {
                std::cout << "Please enter a valid command." << std::endl;
            }
        }
    }
    std::cout << std::endl;
}