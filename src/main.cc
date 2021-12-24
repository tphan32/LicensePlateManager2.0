#include "LicensePlateManager.hpp"
#include "Menu.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    if(argc > 2 || argc < 2) {
        std::cout << "Usage: " << argv[0] << " INPUT_FILE\n" << "Input should be a database:\n";
        return 1;
    }

    std::cout << "Loading license plates from: " << argv[1] << std::endl;
    try {
        LicensePlateManager * manager = new LicensePlateManager(argv[1]);
        // LicensePlateInfo ret = manager->GeneratePlate("Jimin", "Kim", 22, "11/12/1995", "Illinois, Korea", 199, 6.7);
        // std::cout << ret.plate_number << std::endl;
        // LicensePlateInfo a = manager->FindLicensePlate("AQ11010");
        // std::cout << a;
        // std::cout << manager->RemovePlate("AQ11002");
        manager->UpdateWeight("AQ12345", 333);
        std::vector<LicensePlateInfo> a = manager->FindLicensePlate("Jimin", "Kim"); 
        std::cout << a;
    }
    catch(const std::runtime_error& error) {
        std::cout << error.what() << std::endl;
    }

/*     Menu menu(manager);
    menu.MainMenu();

    delete manager; */

    return 0;
}