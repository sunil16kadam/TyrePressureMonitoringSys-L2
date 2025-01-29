#ifndef SUPPORTING_FUNCTIONS_H
#define SUPPORTING_FUNCTIONS_H

#include <iostream>
#include <limits>

////////////////////////////////////////////////////////////////////////////////////////////////
// Code to robustly get an integer input from the user,
// ensuring it ignores any leftover buffer data,
// handles invalid inputs, and
// keeps prompting until a valid integer is entered:
// Example Usage:
//      #include <iostream>
//      int main() {
//          int quantity;
//          getIntegerInput(quantity);
//          return 0;
//      }


void getIntegerInput(int& myInt) {
    while (true) {
        std::cin >> myInt;

        // Check if the input was successful
        if (std::cin.good()) {
            break;  // Valid integer input
        }

        // If input failed, clear the error state and ignore invalid input
        std::cin.clear();  // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
        std::cerr << "Invalid input. Please enter a valid integer.\n";
    }

    // Clear the remaining newline from the buffer if necessary
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Function to get a string input from the user,
// ensuring it ignores any previous input or buffer data and
// keeps prompting until a valid non-empty string is entered.
// The string must be terminated by a newline character.
// String may contains multiple words separated by whitespace characters.
// Example usage:
            // #include <iostream>
            // #include <string>
            // int main() {
            //     std::string title;
            //     getStringInput(title);
            //     return 0;
            // }

#include <iostream>
#include <string>
#include <limits>

void getStringInput(std::string& input) {
    while (true) {
        std::getline(std::cin, input);

        // Check if input is not empty and contains valid characters
        if (!input.empty()) {
            break;  // Valid input
        }

        // If empty input, print error and re-prompt
        std::cerr << "Invalid input. Please enter a non-empty string.\n";

        // Clear any remaining input and reset state
        std::cin.clear();  // Clear error flags if any
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard leftover input
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////


#endif // SUPPORTING_FUNCTIONS_H
