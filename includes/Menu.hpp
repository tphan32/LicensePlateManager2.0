#pragma once

#include <iostream>
#include <cstdio>

#include "LicensePlateManager.hpp"

class Menu {
    public:
        Menu(LicensePlateManager * manager);

        /* The main menu, starting point for the command line.
        */
        void MainMenu();

    private:
        LicensePlateManager * manager = nullptr;

        /* Submenu containing add/remove functions.
        */
        void AddRemove();

        /* Adds a license plate, with either a generated or manually entered plate number.
        */
        void Add();

        /* Removes a license plate with a matching license plate number.
        */
        void Remove();

        /* Updates the license plate number of the given owner's license plate.
        */
       void Update();

       void UpdateInfo();

       void UpdateNumber();

        /* Submenu containing save/load functions.
        */
        void SaveLoad();

        /* Calls manager's Sort() function
        */
        void PrintList();

        /*  Takes user input for a file name, calls manager's SavePlates() function.
        */
        void Save();

        /* Take user input for a file name, call manager's LoadPlates() function.
        */
        void Load();

        /* Lookup a license plate with a file or manual entry.
        */
        void Lookup();
};