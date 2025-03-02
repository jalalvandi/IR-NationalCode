#include <string>
#include <regex>
#include <algorithm>

/**
 * Validates an Iranian National Code based on the official algorithm.
 *
 * This function checks the validity of an Iranian National Code by:
 * 1. Ensuring the input is 8 to 10 digits long and numeric
 * 2. Standardizing it to 10 digits by padding with leading zeros
 * 3. Checking for repeating digits (e.g., 1111111111 is invalid)
 * 4. Calculating the check digit using the official algorithm:
 *    - Multiply each of the first 9 digits by weights 10 down to 2
 *    - Sum the results and compute remainder when divided by 11
 *    - If remainder < 2, it’s the check digit; otherwise, 11 - remainder
 * 5. Comparing the calculated check digit with the provided one
 *
 * @param nationalCode The national code as a string (can include non-numeric characters)
 * @return bool Returns true if the code is valid, false otherwise
 */
bool validateIranianNationalCode(std::string nationalCode) {
    // Remove non-numeric characters
    std::string cleanedCode = std::regex_replace(nationalCode, std::regex("[^0-9]"), "");
    
    // Check length (must be 8 to 10 digits)
    int codeLength = cleanedCode.length();
    if (codeLength < 8 || codeLength > 10) {
        return false;
    }

    // Standardize to 10 digits by padding with leading zeros
    std::string standardizedCode = std::string(10 - codeLength, '0') + cleanedCode;
    
    // Check if all digits are the same
    if (std::all_of(standardizedCode.begin(), standardizedCode.end(), 
                    [&](char c) { return c == standardizedCode[0]; })) {
        return false;
    }

    // Extract check digit (last digit)
    int checkDigit = standardizedCode.back() - '0';
    standardizedCode.pop_back();

    // Calculate weighted sum (weights: 10 down to 2)
    int sum = 0;
    for (int i = 0; i < 9; i++) {
        sum += (standardizedCode[i] - '0') * (10 - i);
    }

    // Compute remainder and check digit
    int remainder = sum % 11;
    int calculatedCheckDigit = (remainder < 2) ? remainder : 11 - remainder;

    // Return true if check digits match
    return calculatedCheckDigit == checkDigit;
}

// Test
#include <iostream>
int main() {
    std::cout << std::boolalpha;
    std::cout << validateIranianNationalCode("6587452158") << std::endl; // false
    return 0;
}