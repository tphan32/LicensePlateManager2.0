# License Plate Manager

A C++ based license plate manager that contains Illinois state license plates and basic identifying information for their respective owners. The manager will be able to store new license plates received through either manual entry or random generation as well as update information belonging to existing license plates. Users will be able to look up a license plate number through manual input of the number or an image input. 

## Features

- Ability to generate valid, non-duplicate license plate numbers in ascending order from a given starting point.
- Ability to save and load a csv data file containing license plates information.
- Ability to look up and update license plates by providing either driver’s full name, or their license plate number.
- Print the list of license plates in ascending order alphabetically by the driver’s last name.
- Ability to scan an image of a license plate.

## Prerequisites

This program requires Tesseract, an open-source OCR library, and OpenCV, an open source computer vision library.

Tesseract installation instructions: https://tesseract-ocr.github.io/tessdoc/Compiling-%E2%80%93-GitInstallation.html

OpenCV installation instructions: https://docs.opencv.org/4.5.1/d7/d9f/tutorial_linux_install.html

## Build

After successfully installed required libraries, users can build the app with:
```
make
```

Build test cases:
```
make tests
```

## Usage

### Starts the manager
```
./bin/exec
```

### Starts the manager, initialized with license plates from the given csv data file
```
./bin/exec [<load file>]
```

### Interacts with the manager

Available options are:
```
1) Add/Remove
2) Save/Load
3) Print License Plates
4) Lookup A License Plate
5) Exit
```
- Add/Remove: add or remove a license plate. 
- Save/Load: save the current list of license plate to a csv file or load a list of license plates from a csv file.
- Print License Plates: print out the list of current license plates handled by the manager.
- Lookup A License Plate: lookup a license plate by scanning a plate number from a picture or entering manual entry and print it out.
- Exit: to exit the app.
- Users can select options by entering the corresponding number for that option. e.g. enter 1 to add or remove a new license plate

## Tests

### Runs test cases

Multiple test cases are written for the app. To run the test cases:
```
make tests
./bin/tests
```
