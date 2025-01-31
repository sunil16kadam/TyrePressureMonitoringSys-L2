/////////////////////////////////////////////////////////////////////////////////////
// Project name: 
// Author: Sunil Kadam
// Last modification date: 25 Jan 2025
/////////////////////////////////////////////////////////////////////////////////////

// main.cpp
#include "../Headers/TPMS.h"
#include <iostream>

int main() {
    TPMS tpms;

    // tpms.handleEvent("start");
    // while (true);

    std::string command;
    while (true) {
        std::cout << "Enter command (start/stop/log/recover/exit): ";
        std::cin >> command;
        //command = "start";

        if (command == "exit") {
            std::cout << "Exiting system..." << std::endl;
            break;
        }

        tpms.handleEvent(command);
    }

    return 0;
}
