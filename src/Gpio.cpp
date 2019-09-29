/*
    Created by Yanir Harel, 28.9.2019
    ---------------------------------
    This is an embeded module to set a gpio pin to a specified communication manner,
    and set the pin o either 1 or 0 i.e. power or not.
*/

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include "../include/Torq/Gpio.hpp"

using namespace std;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;

GPIOClass::GPIOClass() {
    this->gpionum = "4"; //GPIO4 is default
}

GPIOClass::GPIOClass(string gnum) {
    this->gpionum = gnum;  //Instatiate GPIOClass object for GPIO pin number "gnum"
}

int GPIOClass::export_gpio() {
    string export_str = "/sys/class/gpio/export";
    ofstream exportgpio;
    exportgpio.open(export_str.c_str()); // Open "export" file. Convert C++ string to C string. Required for all Linux pathnames
    if (exportgpio.fail()) {
        cout << " OPERATION FAILED: Unable to export GPIO"<< this->gpionum <<" ."<< endl;
        return -1;
    }

    exportgpio << this->gpionum ; //write GPIO number to export
    exportgpio.close(); //close export file#
    
    return 0;
}

int GPIOClass::unexport_gpio() {
    string unexport_str = "/sys/class/gpio/unexport";
    ofstream unexportgpio;
    unexportgpio.open(unexport_str.c_str()); //Open unexport file
    if (unexportgpio.fail()) {
        cout << " OPERATION FAILED: Unable to unexport GPIO"<< this->gpionum <<" ."<< endl;
        return -1;
    }

    unexportgpio << this->gpionum ; //write GPIO number to unexport
    unexportgpio.close(); //close unexport file
    return 0;
}

int GPIOClass::setdir_gpio(string dir) {

    string setdir_str ="/sys/class/gpio/gpio" + this->gpionum + "/direction";
    ofstream setdirgpio;
     // open direction file for gpio
    setdirgpio.open(setdir_str.c_str());
    if (setdirgpio.fail()) {
        cout << " OPERATION FAILED: Unable to set direction of GPIO"<< this->gpionum <<" ."<< endl;
        return -1;
    }

    setdirgpio << dir; //write direction to direction file
    setdirgpio.close(); // close direction file
    
    return 0;
}

int GPIOClass::setval_gpio(string val) {

    string setval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
    ofstream setvalgpio; // open value file for gpio
    setvalgpio.open(setval_str.c_str());
    if (setvalgpio.fail()) {
        cout << " OPERATION FAILED: Unable to set the value of GPIO"<< this->gpionum <<" ."<< endl;
        return -1;
    }

    setvalgpio << val ;//write value to value file
    setvalgpio.close();// close value file
    
    return 0;
}

int GPIOClass::getval_gpio(string& val) {

    string getval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
    ifstream getvalgpio(getval_str.c_str());// open value file for gpio
    if (getvalgpio.fail()) {
        cout << " OPERATION FAILED: Unable to get value of GPIO"<< this->gpionum <<" ."<< endl;
        return -1;
            }

    getvalgpio >> val ;  //read gpio value

    if(val != "0")
        val = "1";
    else
        val = "0";

    getvalgpio.close(); //close the value file
    
    return 0;
}

string GPIOClass::get_gpionum() {
    return this->gpionum;
}