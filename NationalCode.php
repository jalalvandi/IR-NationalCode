<?php

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
 * @param string $nationalCode The national code to validate (can include non-numeric characters)
 * @return bool Returns true if the code is valid, false otherwise
 */
function validateIranianNationalCode(string $nationalCode = ''): bool
{
    // Remove non-numeric characters from the input
    $cleanedCode = preg_replace('/[^0-9]/', '', (string) $nationalCode);
    $codeLength = strlen($cleanedCode);

    // Check if length is between 8 and 10 digits
    if ($codeLength < 8 || $codeLength > 10) {
        return false;
    }

    // Standardize to 10 digits by padding with leading zeros
    $standardizedCode = str_pad($cleanedCode, 10, '0', STR_PAD_LEFT);
    $digits = str_split($standardizedCode);

    // Check if all digits are the same (invalid case)
    if (count(array_unique($digits)) === 1) {
        return false;
    }

    // Extract the check digit (last digit)
    $checkDigit = (int) array_pop($digits);

    // Calculate weighted sum (weights: 10 down to 2)
    $sum = 0;
    for ($i = 0; $i < 9; $i++) {
        $sum += (int) $digits[$i] * (10 - $i);
    }

    // Compute remainder and check digit
    $remainder = $sum % 11;
    $calculatedCheckDigit = $remainder < 2 ? $remainder : 11 - $remainder;

    // Return true if calculated check digit matches the provided one
    return $calculatedCheckDigit === $checkDigit;
}

// Test cases
var_dump(validateIranianNationalCode('1111111111')); // false (repeating digits)
var_dump(validateIranianNationalCode('12345'));      // false (too short)