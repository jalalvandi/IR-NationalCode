package main

import (
	"fmt"
	"regexp"
	"strings"
)

/**
 * Validates an Iranian National Code based on the official algorithm.
 * 
 * @param nationalCode The national code as a string
 * @return bool Returns true if valid, false otherwise
 */
func validateIranianNationalCode(nationalCode string) bool {
    // Remove non-numeric characters
    re := regexp.MustCompile("[^0-9]")
    cleanedCode := re.ReplaceAllString(nationalCode, "")
    
    // Check length (must be 8 to 10 digits)
    codeLength := len(cleanedCode)
    if codeLength < 8 || codeLength > 10 {
        return false
    }

    // Standardize to 10 digits by padding with leading zeros
    standardizedCode := strings.Repeat("0", 10-codeLength) + cleanedCode
    
    // Check if all digits are the same
    allSame := true
    for _, char := range standardizedCode[1:] {
        if char != standardizedCode[0] {
            allSame = false
            break
        }
    }
    if allSame {
        return false
    }

    // Extract check digit (last digit)
    checkDigit := int(standardizedCode[len(standardizedCode)-1] - '0')
    digits := standardizedCode[:len(standardizedCode)-1]

    // Calculate weighted sum (weights: 10 down to 2)
    sum := 0
    for i := 0; i < 9; i++ {
        sum += int(digits[i]-'0') * (10 - i)
    }

    // Compute remainder and check digit
    remainder := sum % 11
    calculatedCheckDigit := remainder
    if remainder >= 2 {
        calculatedCheckDigit = 11 - remainder
    }

    // Return true if check digits match
    return calculatedCheckDigit == checkDigit
}

// Test
func main() {
    fmt.Println(validateIranianNationalCode("6587452158")) // false
}